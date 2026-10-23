"""Typed byte/halfword run streams with command-counted consumer ownership."""

import hashlib
import json
import shutil
import struct
from pathlib import Path


ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
ROUTE_CATALOG_SHA256 = "d712a2ba9385d0637b6dd1b619f21b18615fa80c2a611334acc4f4183423ff3d"
BANK_START = 0x8F4674
BANK_END = 0x8F6CFC
RUN_COUNT = 78
ROUTE_FILE = "counted-run-routes-v2.json"


def _sha256(data):
    return hashlib.sha256(data).hexdigest()


def _checked_integer(value, maximum, field):
    if type(value) is not int or not 0 <= value <= maximum:
        raise ValueError(f"{field} is outside its encoded range")
    return value


def _route_records(route_catalog):
    if (route_catalog.get("reference_sha256") != ROM_SHA256 or
            route_catalog.get("run_count") != RUN_COUNT or
            not isinstance(route_catalog.get("run_records"), list) or
            len(route_catalog["run_records"]) != RUN_COUNT):
        raise ValueError("counted run route catalog revision or count differs")

    records = []
    for route_record in route_catalog["run_records"]:
        start = route_record.get("run_start")
        end = route_record.get("run_end")
        routes = route_record.get("counted_routes")
        if (type(start) is not int or type(end) is not int or
                not BANK_START <= start < end <= BANK_END or
                not isinstance(routes, list) or not routes):
            raise ValueError("counted run route record is incomplete")
        if any(not isinstance(route, dict) for route in routes):
            raise ValueError("counted run route is not an object")
        opcodes = {route.get("opcode") for route in routes}
        if len(opcodes) != 1 or next(iter(opcodes)) not in (4, 5):
            raise ValueError("run routes do not select one supported command width")
        opcode = next(iter(opcodes))
        expected_width = 2 if opcode == 4 else 1
        if route_record.get("unit_width") != expected_width:
            raise ValueError("run unit width differs from the counted command opcode")
        for route in routes:
            if (type(route.get("command_start")) is not int or
                    type(route.get("descriptor")) is not int or
                    route.get("opcode") != opcode):
                raise ValueError("counted run route fields differ")
        records.append({
            "start": start,
            "end_exclusive": end,
            "unit_width": expected_width,
            "counted_routes": [
                {"command_start": route["command_start"],
                 "descriptor": route["descriptor"], "opcode": opcode}
                for route in routes],
        })

    records.sort(key=lambda row: row["start"])
    if (records[0]["start"] != BANK_START or
            records[-1]["end_exclusive"] != BANK_END or
            any(left["end_exclusive"] != right["start"]
                for left, right in zip(records, records[1:]))):
        raise ValueError("counted run records do not partition the proved bank")
    return records


def decode_stream(data, unit_width):
    if unit_width not in (1, 2) or len(data) < 6:
        raise ValueError("run stream is shorter than its typed header")
    width, height, position_x, position_y, kind, flags = data[:6]
    if not width or not height or flags & 0x02 == 0:
        raise ValueError("run stream dimensions or compression flag differ")

    runs = []
    cursor = 6
    covered_cells = 0
    cell_limit = width * height
    while covered_cells < cell_limit:
        if cursor + 2 > len(data):
            raise ValueError("run control word is truncated")
        control = struct.unpack_from("<H", data, cursor)[0]
        cursor += 2
        count = control & 0x3FFF
        mode_bits = control >> 14
        if not count or covered_cells + count > cell_limit:
            raise ValueError("run count leaves the declared dimensions")

        value_count = 1 if mode_bits else count
        payload_bytes = value_count * unit_width
        if cursor + payload_bytes > len(data):
            raise ValueError("run payload is truncated")
        values = [int.from_bytes(data[cursor + index * unit_width:
                                       cursor + (index + 1) * unit_width],
                                 "little")
                  for index in range(value_count)]
        cursor += payload_bytes
        unit_padding = (-payload_bytes) % 2
        if cursor + unit_padding > len(data) or data[cursor:cursor + unit_padding] != b"\0" * unit_padding:
            raise ValueError("run unit alignment is nonzero or truncated")
        cursor += unit_padding
        runs.append({"count": count, "mode_bits": mode_bits,
                     "values": values, "padding_bytes": unit_padding})
        covered_cells += count

    alignment_bytes = (-cursor) % 4
    if (cursor + alignment_bytes != len(data) or
            data[cursor:] != b"\0" * alignment_bytes):
        raise ValueError("run stream end or word alignment differs")
    return {"width_cells": width, "height_cells": height,
            "position_x": position_x, "position_y": position_y,
            "kind": kind, "flags": flags, "unit_width": unit_width,
            "runs": runs, "alignment_bytes": alignment_bytes}


def encode_stream(fields):
    width = _checked_integer(fields.get("width_cells"), 0xFF, "width")
    height = _checked_integer(fields.get("height_cells"), 0xFF, "height")
    unit_width = fields.get("unit_width")
    if not width or not height or unit_width not in (1, 2):
        raise ValueError("run stream dimensions or unit width differ")
    output = bytearray((width, height,
                        _checked_integer(fields.get("position_x"), 0xFF, "position_x"),
                        _checked_integer(fields.get("position_y"), 0xFF, "position_y"),
                        _checked_integer(fields.get("kind"), 0xFF, "kind"),
                        _checked_integer(fields.get("flags"), 0xFF, "flags")))
    if fields["flags"] & 0x02 == 0:
        raise ValueError("run stream compression flag is missing")

    covered_cells = 0
    cell_limit = width * height
    for run_index, run in enumerate(fields.get("runs", [])):
        count = _checked_integer(run.get("count"), 0x3FFF, "run count")
        mode_bits = _checked_integer(run.get("mode_bits"), 3, "run mode")
        values = run.get("values")
        if not count or not isinstance(values, list):
            raise ValueError("run record is empty or malformed")
        expected_values = 1 if mode_bits else count
        if len(values) != expected_values or covered_cells + count > cell_limit:
            raise ValueError("run payload count differs from dimensions")
        output.extend(struct.pack("<H", count | (mode_bits << 14)))
        maximum = (1 << (unit_width * 8)) - 1
        for value in values:
            output.extend(_checked_integer(value, maximum, "run value").to_bytes(
                unit_width, "little"))
        payload_bytes = expected_values * unit_width
        unit_padding = (-payload_bytes) % 2
        if run.get("padding_bytes") != unit_padding:
            raise ValueError(f"run {run_index} unit padding differs")
        output.extend(b"\0" * unit_padding)
        covered_cells += count

    if covered_cells != cell_limit:
        raise ValueError("run records do not fill the declared dimensions")
    alignment_bytes = (-len(output)) % 4
    if fields.get("alignment_bytes") != alignment_bytes:
        raise ValueError("run stream word alignment differs")
    output.extend(b"\0" * alignment_bytes)
    return bytes(output)


def expand_stream(fields):
    unit_width = fields["unit_width"]
    value_mask = (1 << (unit_width * 8)) - 1
    expanded = []
    for run in fields["runs"]:
        mode_bits = run["mode_bits"]
        values = run["values"]
        if mode_bits & 0x02:
            expanded.extend((values[0] + index) & value_mask
                            for index in range(run["count"]))
        elif mode_bits & 0x01:
            expanded.extend([values[0]] * run["count"])
        else:
            expanded.extend(values)
    return expanded


def _load_route_catalog(source_dir):
    route_path = source_dir / ROUTE_FILE
    route_bytes = route_path.read_bytes()
    if _sha256(route_bytes) != ROUTE_CATALOG_SHA256:
        raise ValueError("counted run route catalog hash differs")
    routes = json.loads(route_bytes)
    if routes.get("reference_sha256") != ROM_SHA256:
        raise ValueError("counted run route catalog targets another ROM")
    return route_bytes, routes, _route_records(routes)


def export_family(rom, route_catalog_path, output_dir):
    if _sha256(rom) != ROM_SHA256:
        raise ValueError("expected the pinned US retail ROM")
    route_path = Path(route_catalog_path)
    route_bytes = route_path.read_bytes()
    if _sha256(route_bytes) != ROUTE_CATALOG_SHA256:
        raise ValueError("counted-run-routes-v2 ownership input differs")
    route_catalog = json.loads(route_bytes)
    route_records = _route_records(route_catalog)

    output_dir = Path(output_dir)
    if output_dir.exists():
        raise ValueError("counted dimension run extraction requires a new directory")
    records_dir = output_dir / "records"
    records_dir.mkdir(parents=True)
    shutil.copyfile(route_path, output_dir / ROUTE_FILE)

    manifest_records = []
    padding_bytes = 0
    for route_record in route_records:
        start = route_record["start"]
        end = route_record["end_exclusive"]
        source_bytes = rom[start:end]
        fields = decode_stream(source_bytes, route_record["unit_width"])
        if encode_stream(fields) != source_bytes:
            raise ValueError(f"run at 0x{start:x} does not round-trip")
        expanded = expand_stream(fields)
        if len(expanded) != fields["width_cells"] * fields["height_cells"]:
            raise ValueError(f"run at 0x{start:x} expands to the wrong cell count")
        filename = f"run-{start:08x}.json"
        (records_dir / filename).write_text(json.dumps(fields, indent=2) + "\n")
        run_padding = fields["alignment_bytes"] + sum(
            run["padding_bytes"] for run in fields["runs"])
        padding_bytes += run_padding
        manifest_records.append({
            **route_record,
            "file": f"records/{filename}",
            "source_sha256": _sha256(source_bytes),
            "expanded_sha256": _sha256(b"".join(
                value.to_bytes(fields["unit_width"], "little")
                for value in expanded)),
            "padding_bytes": run_padding,
        })

    manifest = {
        "schema_version": 1,
        "reference_sha256": ROM_SHA256,
        "route_catalog_sha256": ROUTE_CATALOG_SHA256,
        "route_catalog_file": ROUTE_FILE,
        "start": BANK_START,
        "end_exclusive": BANK_END,
        "record_count": RUN_COUNT,
        "padding_bytes": padding_bytes,
        "records": manifest_records,
    }
    (output_dir / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    return manifest


def encode_bank(manifest, source_dir, reference_rom=None):
    source_dir = Path(source_dir)
    if (manifest.get("schema_version") != 1 or
            manifest.get("reference_sha256") != ROM_SHA256 or
            manifest.get("route_catalog_sha256") != ROUTE_CATALOG_SHA256 or
            manifest.get("route_catalog_file") != ROUTE_FILE or
            (manifest.get("start"), manifest.get("end_exclusive"),
             manifest.get("record_count")) != (BANK_START, BANK_END, RUN_COUNT)):
        raise ValueError("counted dimension run bank descriptor differs")
    _, _, expected_records = _load_route_catalog(source_dir)
    records = manifest.get("records")
    if not isinstance(records, list) or len(records) != RUN_COUNT:
        raise ValueError("counted dimension run manifest record count differs")
    if reference_rom is not None and _sha256(reference_rom) != ROM_SHA256:
        raise ValueError("reference ROM hash differs")

    output = bytearray()
    total_padding = 0
    for index, (record, expected) in enumerate(zip(records, expected_records)):
        for key in ("start", "end_exclusive", "unit_width", "counted_routes"):
            if record.get(key) != expected[key]:
                raise ValueError(f"run record {index} ownership metadata differs")
        filename = record.get("file")
        if filename != f"records/run-{expected['start']:08x}.json":
            raise ValueError(f"run record {index} source name differs")
        run_path = (source_dir / filename).resolve()
        if not run_path.is_relative_to(source_dir.resolve()) or not run_path.is_file():
            raise ValueError(f"run record {index} source is missing or escaped")
        fields = json.loads(run_path.read_text())
        if fields.get("unit_width") != expected["unit_width"]:
            raise ValueError(f"run record {index} data width differs from owner")
        encoded = encode_stream(fields)
        span_size = expected["end_exclusive"] - expected["start"]
        if len(encoded) != span_size:
            raise ValueError(f"run record {index} encoded length differs")
        if reference_rom is not None:
            if _sha256(reference_rom[expected["start"]:expected["end_exclusive"]]) != record.get("source_sha256"):
                raise ValueError(f"run record {index} source hash differs from retail")
        decoded = decode_stream(encoded, expected["unit_width"])
        if decoded != fields:
            raise ValueError(f"run record {index} does not parse back to its typed fields")
        total_padding += (fields["alignment_bytes"] + sum(
            run["padding_bytes"] for run in fields["runs"]))
        output.extend(encoded)

    if len(output) != BANK_END - BANK_START:
        raise ValueError("counted dimension run bank length differs")
    if manifest.get("padding_bytes") != total_padding:
        raise ValueError("counted dimension run padding total differs")
    if reference_rom is not None and output != reference_rom[BANK_START:BANK_END]:
        raise ValueError("counted dimension run bank differs from retail")
    return bytes(output)
