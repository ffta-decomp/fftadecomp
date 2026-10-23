#!/usr/bin/env python3
"""Compare bounded retail and locally compiled ARM7TDMI function contracts.

Run with an explicitly supplied private case bank. This is CPU-level evidence,
not a replacement for a selected-ROM build, mGBA replay, or hardware validation.
"""
import argparse
import hashlib
import json
import sys
import time
from pathlib import Path

from unicorn import (Uc, UcError, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE,
                     UC_HOOK_MEM_WRITE)
from unicorn import __version__ as UNICORN_VERSION
from unicorn import arm_const

ROOT = Path(__file__).resolve().parents[1]
RETAIL_SHA = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROM_BASE, ROM_SIZE = 0x08000000, 0x1000000
RAM_RANGES = ((0x02000000, 0x02040000), (0x03000000, 0x03008000))
STACK_TOP, STACK_BOTTOM, SENTINEL = 0x03007000, 0x03006000, ROM_BASE
REGISTERS = {"r" + str(i): getattr(arm_const, "UC_ARM_REG_R" + str(i))
             for i in range(13)}
INPUT_REGISTERS = {"r0", "r1", "r2", "r3", "r12"}
PRESERVED = {"r" + str(i): 0x5A000000 + i for i in range(4, 12)}
# Acquisition selection passes fourteen stack words to its initialization helper.
# Keep capture explicitly bounded; this is not a claim about callee semantics.
MAX_HELPER_STACK_WORDS = 16


def digest(data):
    return hashlib.sha256(data).hexdigest()


def integer(value, label):
    if type(value) is not int or not 0 <= value <= 0xFFFFFFFF:
        raise ValueError(label + " must be a numeric u32")
    return value


def contained(address, size, ranges):
    return size >= 0 and any(start <= address and address + size <= end
                             for start, end in ranges)


def memory_value(item):
    address = integer(item["address"], "memory address")
    data = bytes.fromhex(item["hex"])
    if not data or not contained(address, len(data), RAM_RANGES):
        raise ValueError("fixture memory must be nonempty EWRAM/IWRAM")
    return address, data


def helper_pointer_value(item, arguments, stack):
    """Resolve an explicitly declared register or stack argument pointer."""
    keys = [key for key in ("argument", "stack_argument") if key in item]
    if len(keys) != 1:
        raise ValueError("helper pointer requires one argument selector")
    key = keys[0]
    values = arguments if key == "argument" else stack
    index = item[key]
    if type(index) is not int or not 0 <= index < len(values):
        raise ValueError("helper pointer argument index is outside its contract")
    return values[index]


def comparable_calls(calls):
    """Compare declared stack objects by their typed observations, not frame layout."""
    normalized = []
    for call in calls:
        row = dict(call)
        row["arguments"] = list(call["arguments"])
        row["stack_arguments"] = list(call["stack_arguments"])
        pointers = []
        for index, pointer in enumerate(call.get("pointer_arguments", [])):
            key = "argument" if "argument" in pointer else "stack_argument"
            target = "arguments" if key == "argument" else "stack_arguments"
            row[target][pointer[key]] = {"stack_object": index}
            pointers.append({k: v for k, v in pointer.items() if k != "address"})
        if pointers:
            row["pointer_arguments"] = pointers
        normalized.append(row)
    return normalized


def overlay_report(retail, report, report_directory, manifest):
    """Check the local build's provenance before applying any candidate bytes."""
    if report.get("schema") != "local-module-build-v1":
        raise ValueError("unsupported local build report schema")
    if digest(retail) != RETAIL_SHA or report.get("retail_sha256") != RETAIL_SHA:
        raise ValueError("retail revision mismatch")
    if report.get("manifest_sha256") != digest(manifest.read_bytes()):
        raise ValueError("local build manifest is stale or different")
    selected = {m["name"]: m for m in json.loads(manifest.read_text())["modules"]}
    candidate, spans = bytearray(retail), []
    if not report.get("segments"):
        raise ValueError("local build has no segments")
    for item in report["segments"]:
        offset = integer(item["rom_offset"], "segment ROM offset")
        size = integer(item["generated_size"], "generated size")
        reference_size = integer(item["reference_size"], "reference size")
        original = selected.get(item["module"])
        if (not original or original["offset"] != offset
                or original["size"] != reference_size
                or item.get("fits") is not True or size == 0
                or size > reference_size or offset + reference_size > len(retail)):
            raise ValueError("segment does not fit its selected source envelope")
        if any(offset < end and start < offset + reference_size for start, end in spans):
            raise ValueError("overlapping local candidate envelopes")
        spans.append((offset, offset + reference_size))
        binary = Path(item["binary"])
        if not binary.is_absolute():
            binary = report_directory / binary
        data = binary.read_bytes()
        if len(data) != size or digest(data) != item["binary_sha256"]:
            raise ValueError("candidate binary hash/size mismatch")
        candidate[offset:offset + size] = data
    return bytes(candidate)


def execute_case(rom, case):
    started = time.perf_counter()
    if len(rom) != ROM_SIZE:
        raise ValueError("expected a 16 MiB CPU ROM image")
    entry = integer(case["entry"], "Thumb entry")
    if entry & 1 == 0:
        raise ValueError("entry must include the Thumb mode bit")
    execution = [tuple(pair) for pair in case["execute_ranges"]]
    for start, end in execution:
        integer(start, "execution start"); integer(end, "execution end")
        if start & 1 or end <= start or not contained(start, end - start,
                ((ROM_BASE, ROM_BASE + ROM_SIZE),) + RAM_RANGES):
            raise ValueError("invalid declared execution range")
    if not contained(entry & ~1, 2, execution):
        raise ValueError("entry is outside declared execution ranges")
    budget = case.get("max_steps", 100000)
    if type(budget) is not int or not 1 <= budget <= 10000000:
        raise ValueError("max_steps must be between 1 and 10000000")
    observe = case.get("observe", {})
    observed_registers = observe.get("registers", ["r0"])
    if any(name not in REGISTERS for name in observed_registers):
        raise ValueError("invalid observed register")
    expected = case.get("expected", {})
    if any(name not in REGISTERS for name in expected.get("registers", {})):
        raise ValueError("invalid oracle register")
    memory = [memory_value(item) for item in case.get("memory", [])]
    watched = []
    for item in observe.get("memory", []):
        address, size = integer(item["address"], "observed address"), item["size"]
        if type(size) is not int or size <= 0 or not contained(address, size, RAM_RANGES):
            raise ValueError("observed memory must lie in EWRAM/IWRAM")
        watched.append((address, size))
    stack_arguments = [integer(x, "stack argument") for x in case.get("stack_arguments", [])]
    if len(stack_arguments) > 64:
        raise ValueError("at most 64 input stack words are supported")
    writable = [(STACK_BOTTOM, STACK_TOP + 4 * len(stack_arguments))]
    writable += [(a, a + len(data)) for a, data in memory]
    writable += [(a, a + size) for a, size in watched]
    helpers = {}
    for item in case.get("helpers", []):
        address = integer(item["address"], "helper entry")
        if address & 1 or address in helpers or address == SENTINEL:
            raise ValueError("helper entries must be distinct even addresses")
        if type(item.get("arg_count")) is not int or not 0 <= item["arg_count"] <= 4:
            raise ValueError("helper arg_count must be explicit and between 0 and 4")
        if (type(item.get("stack_count", 0)) is not int or
                not 0 <= item.get("stack_count", 0) <= MAX_HELPER_STACK_WORDS):
            raise ValueError("invalid helper stack_count")
        if not item.get("returns"):
            raise ValueError("helper requires an explicit return sequence")
        selectors = set()
        for pointer in item.get("pointer_arguments", []):
            # Only declared stack objects may ignore their concrete addresses.
            helper_pointer_value(pointer, [0] * item["arg_count"],
                                 [0] * item.get("stack_count", 0))
            key = "argument" if "argument" in pointer else "stack_argument"
            selector = (key, pointer[key])
            if selector in selectors:
                raise ValueError("duplicate helper pointer argument")
            selectors.add(selector)
            if (type(pointer.get("size")) is not int or
                    not 1 <= pointer["size"] <= STACK_TOP - STACK_BOTTOM or
                    pointer.get("direction") not in ("in", "out", "inout", "opaque")):
                raise ValueError("invalid helper pointer size or direction")
        for value in item["returns"]:
            integer(value, "helper return")
        for register, value in item.get("clobber", {}).items():
            if register not in {"r1", "r2", "r3", "r12"}:
                raise ValueError("helper may only clobber caller-saved scratch registers")
            integer(value, "helper clobber value")
        helpers[address] = item
    uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
    uc.mem_map(ROM_BASE, ROM_SIZE); uc.mem_write(ROM_BASE, rom)
    for start, end in RAM_RANGES:
        uc.mem_map(start, end - start)
    for address, data in memory:
        uc.mem_write(address, data)
    for index, value in enumerate(stack_arguments):
        uc.mem_write(STACK_TOP + 4 * index, value.to_bytes(4, "little"))
    uc.reg_write(arm_const.UC_ARM_REG_SP, STACK_TOP)
    uc.reg_write(arm_const.UC_ARM_REG_LR, SENTINEL | 1)
    for name, value in PRESERVED.items():
        uc.reg_write(REGISTERS[name], value)
    for name, value in case.get("registers", {}).items():
        if name not in INPUT_REGISTERS:
            raise ValueError("input register must be r0..r3 or r12")
        uc.reg_write(REGISTERS[name], integer(value, "input register"))
    state = {"steps": 0, "returned": False, "failures": [], "calls": []}
    counts = {}

    def fail(kind, **details):
        state["failures"].append({"kind": kind, **details})
        uc.emu_stop()

    def on_write(machine, access, address, size, value, _):
        if not contained(address, size, writable):
            fail("undeclared_write", address=address, size=size,
                 pc=machine.reg_read(arm_const.UC_ARM_REG_PC))

    def on_code(machine, address, size, _):
        if address == SENTINEL:
            state["returned"] = True
            machine.emu_stop()
            return
        state["steps"] += 1
        helper = helpers.get(address)
        if helper:
            index = counts.get(address, 0); counts[address] = index + 1
            result = helper["returns"][min(index, len(helper["returns"]) - 1)]
            current_sp = machine.reg_read(arm_const.UC_ARM_REG_SP)
            values = [machine.reg_read(REGISTERS["r" + str(i)])
                      for i in range(helper["arg_count"])]
            stack = [int.from_bytes(machine.mem_read(current_sp + 4*i, 4), "little")
                     for i in range(helper.get("stack_count", 0))]
            call = {"address": address, "arguments": values,
                    "stack_arguments": stack, "return": result}
            pointers = []
            for specification in helper.get("pointer_arguments", []):
                pointer = helper_pointer_value(specification, values, stack)
                size = specification["size"]
                if not contained(pointer, size, ((max(current_sp, STACK_BOTTOM), STACK_TOP),)):
                    fail("helper_stack_pointer", helper=address, address=pointer, size=size)
                    return
                observation = {**specification, "address": pointer}
                if specification["direction"] in ("in", "inout"):
                    observation["before"] = bytes(machine.mem_read(pointer, size)).hex()
                pointers.append(observation)
            if pointers:
                call["pointer_arguments"] = pointers
                # Preserve aliasing evidence without requiring identical stack layout.
                call["pointer_aliases"] = [
                    {"first": i, "second": j,
                     "overlap": a["address"] < b["address"] + b["size"] and
                                b["address"] < a["address"] + a["size"]}
                    for i, a in enumerate(pointers) for j, b in enumerate(pointers) if i < j]
            state["calls"].append(call)
            for item in helper.get("writes", []):
                if "argument" in item or "stack_argument" in item:
                    if "address" in item:
                        raise ValueError("helper write cannot have both address and argument")
                    offset = item.get("offset", 0)
                    if type(offset) is not int or offset < 0:
                        raise ValueError("helper write offset must be a nonnegative integer")
                    target = helper_pointer_value(item, values, stack) + offset
                    target, data = memory_value({"address": target, "hex": item["hex"]})
                    key = "argument" if "argument" in item else "stack_argument"
                    declared = next((p for p in pointers if p.get(key) == item[key]), None)
                    if declared and (declared["direction"] == "in" or
                                     offset + len(data) > declared["size"]):
                        fail("helper_pointer_write_bounds", helper=address,
                             address=target, size=len(data))
                        return
                else:
                    target, data = memory_value(item)
                if not contained(target, len(data), writable):
                    fail("undeclared_helper_write", address=target, size=len(data))
                    return
                machine.mem_write(target, data)
            for pointer in pointers:
                if pointer["direction"] in ("out", "inout"):
                    pointer["after"] = bytes(machine.mem_read(pointer["address"],
                                                              pointer["size"])).hex()
            for name, value in helper.get("clobber", {}).items():
                machine.reg_write(REGISTERS[name], value)
            machine.reg_write(REGISTERS["r0"], result)
            machine.reg_write(arm_const.UC_ARM_REG_PC,
                              machine.reg_read(arm_const.UC_ARM_REG_LR))
        elif not contained(address, size, execution):
            fail("unconfigured_execution", address=address)

    uc.hook_add(UC_HOOK_CODE, on_code)
    uc.hook_add(UC_HOOK_MEM_WRITE, on_write)
    try:
        uc.emu_start(entry, ROM_BASE + ROM_SIZE, count=budget)
    except UcError as error:
        state["failures"].append({"kind": "cpu_fault", "detail": str(error),
                                  "pc": uc.reg_read(arm_const.UC_ARM_REG_PC)})
    if not state["returned"] and not state["failures"]:
        state["failures"].append({"kind": "step_limit_or_no_return",
                                  "pc": uc.reg_read(arm_const.UC_ARM_REG_PC)})
    for name, value in PRESERVED.items():
        if state["returned"] and uc.reg_read(REGISTERS[name]) != value:
            state["failures"].append({"kind": "callee_saved", "register": name,
                                      "expected": value, "actual": uc.reg_read(REGISTERS[name])})
    if state["returned"] and uc.reg_read(arm_const.UC_ARM_REG_SP) != STACK_TOP:
        state["failures"].append({"kind": "stack_not_restored",
                                  "actual": uc.reg_read(arm_const.UC_ARM_REG_SP)})
    values = {name: uc.reg_read(REGISTERS[name]) for name in observed_registers}
    for name, value in (expected.get("registers", {}) if state["returned"] else {}).items():
        actual = uc.reg_read(REGISTERS[name])
        if actual != integer(value, "expected register"):
            state["failures"].append({"kind": "register_oracle", "register": name,
                                      "expected": value, "actual": actual})
    for item in expected.get("memory", []) if state["returned"] else []:
        address, data = memory_value(item)
        actual = bytes(uc.mem_read(address, len(data)))
        if data != actual:
            first = next(i for i, (a, b) in enumerate(zip(data, actual)) if a != b)
            state["failures"].append({"kind": "memory_oracle", "address": address + first,
                                      "expected": data[first], "actual": actual[first]})
    state.update(registers=values, memory=[{"address": address,
                 "hex": bytes(uc.mem_read(address, size)).hex()} for address, size in watched],
                 seconds=time.perf_counter() - started)
    return state


def compare_bank(retail, candidate, bank):
    if bank.get("schema") != "module-cases-v1" or not bank.get("cases"):
        raise ValueError("expected a nonempty module-cases-v1 bank")
    if len({case["name"] for case in bank["cases"]}) != len(bank["cases"]):
        raise ValueError("duplicate case name")
    results = []
    for case in bank["cases"]:
        left, right = execute_case(retail, case), execute_case(candidate, case)
        differences = []
        for name in left["registers"]:
            if left["registers"][name] != right["registers"][name]:
                differences.append({"kind": "register", "register": name,
                                    "retail": left["registers"][name],
                                    "candidate": right["registers"][name]})
        for a, b in zip(left["memory"], right["memory"]):
            if a["hex"] != b["hex"]:
                av, bv = bytes.fromhex(a["hex"]), bytes.fromhex(b["hex"])
                first = next(i for i, (x, y) in enumerate(zip(av, bv)) if x != y)
                differences.append({"kind": "memory", "address": a["address"] + first,
                                    "retail": av[first], "candidate": bv[first]})
        left_calls, right_calls = comparable_calls(left["calls"]), comparable_calls(right["calls"])
        if case.get("observe", {}).get("call_trace", True) and left_calls != right_calls:
            first = next((i for i, (a, b) in enumerate(zip(left_calls, right_calls))
                          if a != b), min(len(left_calls), len(right_calls)))
            differences.append({"kind": "helper_trace", "index": first,
                                "retail": left["calls"][first:first+1],
                                "candidate": right["calls"][first:first+1]})
        passed = not differences and not left["failures"] and not right["failures"]
        results.append({"name": case["name"], "passed": passed,
                        "differences": differences, "retail": left, "candidate": right})
    return {"schema": "module-cases-result-v1", "passed": all(x["passed"] for x in results),
            "case_count": len(results), "cases": results,
            "unicorn_version": UNICORN_VERSION, "natural_coverage": False,
            "limits": ["CPU-level function contracts; unpatched dependencies are retail.",
                       "Explicit helpers are controlled; helper internals and natural reachability are not covered.",
                       "No MMIO, interrupt, hardware timing or physical-device validation.",
                       "Only declared observations are compared; initialized bytes are not an uninitialized-read analysis."]}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--retail", type=Path, required=True)
    parser.add_argument("--build-report", type=Path, required=True)
    parser.add_argument("--cases", type=Path, required=True)
    parser.add_argument("--manifest", type=Path, default=ROOT / "config/retail-us.json")
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    output = args.output.resolve()
    if output.is_relative_to(ROOT) or output in {
            args.retail.resolve(), args.build_report.resolve(), args.cases.resolve()}:
        parser.error("report must be a distinct external output")
    started = time.perf_counter()
    try:
        retail = args.retail.read_bytes()
        if len(retail) != ROM_SIZE or digest(retail) != RETAIL_SHA:
            raise ValueError("retail revision mismatch")
        bank = json.loads(args.cases.read_text())
        if bank.get("retail_sha256") != RETAIL_SHA:
            raise ValueError("case-bank revision mismatch")
        build = json.loads(args.build_report.read_text())
        candidate = overlay_report(retail, build, args.build_report.resolve().parent, args.manifest)
        result = compare_bank(retail, candidate, bank)
        result.update(retail_sha256=digest(retail), candidate_sha256=digest(candidate),
                      build_report_sha256=digest(args.build_report.read_bytes()),
                      case_bank_sha256=digest(args.cases.read_bytes()),
                      elapsed_seconds=time.perf_counter() - started)
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(json.dumps(result, indent=2) + "\n")
        print(json.dumps({"passed": result["passed"], "case_count": result["case_count"],
                          "elapsed_seconds": result["elapsed_seconds"]}))
        return 0 if result["passed"] else 1
    except (ValueError, KeyError, TypeError, OSError) as error:
        parser.error(str(error))


if __name__ == "__main__":
    sys.exit(main())
