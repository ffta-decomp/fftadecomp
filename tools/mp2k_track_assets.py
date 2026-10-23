"""Lossless FFTA MP2K track events in a consumer-bounded ROM interval.

The retail dispatcher, not a generic M4A opcode table, defines the operand
widths here. The parser follows cursor, running status, three pattern return
slots, and the track's one-byte repeat counter. Timing and playback are not
simulated. Strict regions require every byte to have one event owner. Sparse
regions retain unowned bytes from the pinned reference and reparse all owned
runs together before a build can select them.
"""

import hashlib
import struct
from collections import deque


ROM_BASE = 0x08000000
ROM_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
TERMINATORS = {0xB1, 0xB6, 0xB7, 0xB8, 0xB9, 0xC6, 0xC7,
               0xC9, 0xCA, 0xCB, 0xCD}
SCALAR_COMMANDS = {0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0,
                   0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC8}


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def byte(value, name):
    if type(value) is not int or not 0 <= value < 256:
        raise ValueError(f"invalid {name}")
    return value


def offset(value, start, end, name):
    if type(value) is not int or not start <= value < end:
        raise ValueError(f"{name} leaves the track region")
    return value


def parse_event(rom, cursor, status, end):
    """Decode one retail event and return its typed fields and next status."""
    raw = rom[cursor]
    explicit = raw >= 0x80
    opcode = raw if explicit else status
    if not 0x80 <= opcode <= 0xFF:
        raise ValueError(f"track at {cursor:#x} has no running status")
    operand = cursor + int(explicit)
    if explicit and opcode >= 0xBD:
        status = opcode
    event = {"offset": cursor, "opcode": opcode, "explicit": explicit}

    if opcode <= 0xB0:
        event["kind"] = "wait"
    elif opcode in TERMINATORS:
        event["kind"] = "end"
    elif opcode in (0xB2, 0xB3):
        event["kind"] = "jump" if opcode == 0xB2 else "pattern_call"
        if operand + 4 > end:
            raise ValueError("truncated track target")
        event["target_offset"] = struct.unpack_from("<I", rom, operand)[0] - ROM_BASE
        operand += 4
    elif opcode == 0xB4:
        event["kind"] = "pattern_return"
    elif opcode == 0xB5:
        event["kind"] = "repeat"
        if operand + 5 > end:
            raise ValueError("truncated track repeat")
        event["repeat_count"] = rom[operand]
        event["target_offset"] = struct.unpack_from("<I", rom, operand + 1)[0] - ROM_BASE
        operand += 5
    elif opcode in SCALAR_COMMANDS:
        event["kind"] = "scalar"
        if operand >= end:
            raise ValueError("truncated track scalar")
        event["value"] = rom[operand]
        operand += 1
    elif opcode == 0xCC:
        # Retail 0x08144ad8 consumes a selector and a value.
        event["kind"] = "extended"
        if operand + 2 > end:
            raise ValueError("truncated extended track command")
        event["selector"] = rom[operand]
        event["value"] = rom[operand + 1]
        operand += 2
    elif opcode == 0xCE:
        event["kind"] = "end_note"
        if operand < end and rom[operand] < 0x80:
            event["key"] = rom[operand]
            operand += 1
    else:
        # Retail 0x08144e08 consumes up to three bytes below 0x80.
        event["kind"] = "note"
        values = []
        while len(values) < 3 and operand < end and rom[operand] < 0x80:
            values.append(rom[operand])
            operand += 1
        event["values"] = values
    event["size"] = operand - cursor
    if event["size"] <= 0 or operand > end:
        raise ValueError("track event does not advance within the region")
    return event, status


def address_runs(addresses):
    """Return sorted, exclusive-end runs from a set of owned byte addresses."""
    runs = []
    for address in sorted(addresses):
        if not runs or address != runs[-1][1]:
            runs.append([address, address + 1])
        else:
            runs[-1][1] = address + 1
    return runs


def decode_region(rom, start, end, seeds, *, allow_gaps=False):
    if not 0 <= start < end <= len(rom):
        raise ValueError("invalid track region")
    if not seeds or len(set(seeds)) != len(seeds):
        raise ValueError("track entries are missing or duplicated")
    for seed in seeds:
        offset(seed, start, end, "track entry")

    work = deque((seed, 0, (), 0) for seed in seeds)
    visited = set()
    events = {}
    owners = {}
    while work:
        cursor, status, returns, repeat_counter = work.popleft()
        state = (cursor, status, returns, repeat_counter)
        if state in visited:
            continue
        visited.add(state)
        if len(visited) > (end - start) * 16:
            raise ValueError("track state traversal exceeded the region cap")
        offset(cursor, start, end, "track cursor")
        event, next_status = parse_event(rom, cursor, status, end)
        if cursor in events and events[cursor] != event:
            raise ValueError(f"conflicting running status at {cursor:#x}")
        events[cursor] = event
        for address in range(cursor, cursor + event["size"]):
            if address in owners and owners[address] != cursor:
                raise ValueError(f"overlapping track events at {address:#x}")
            owners[address] = cursor
        after = cursor + event["size"]
        kind = event["kind"]
        if kind == "end":
            continue
        if kind == "jump":
            next_states = [(event["target_offset"], next_status, returns, repeat_counter)]
        elif kind == "pattern_call":
            if len(returns) >= 3:
                raise ValueError("retail pattern return stack is full")
            next_states = [(event["target_offset"], next_status,
                            returns + (after,), repeat_counter)]
        elif kind == "pattern_return" and returns:
            next_states = [(returns[-1], next_status, returns[:-1], repeat_counter)]
        elif kind == "repeat":
            count = event["repeat_count"]
            if count == 0:
                next_states = [(event["target_offset"], next_status,
                                returns, repeat_counter)]
            elif repeat_counter + 1 < count:
                next_states = [(event["target_offset"], next_status,
                                returns, (repeat_counter + 1) & 0xFF)]
            else:
                next_states = [(after, next_status, returns, 0)]
        else:
            next_states = [(after, next_status, returns, repeat_counter)]
        work.extend(next_states)

    if not allow_gaps and len(owners) != end - start:
        missing = next(address for address in range(start, end) if address not in owners)
        raise ValueError(f"track interval has an unclassified byte at {missing:#x}")
    if any(seed not in events for seed in seeds):
        raise ValueError("track entry is not an event boundary")
    result = {"schema_version": 1, "start": start, "end": end,
            "source_sha256": sha256(rom[start:end]),
            "track_entry_offsets": list(seeds),
            "visited_states": len(visited),
            "events": [events[address] for address in sorted(events)]}
    if allow_gaps:
        result["decoded_spans"] = address_runs(owners)
        result["unclassified_spans"] = address_runs(
            address for address in range(start, end) if address not in owners)
        result["decoded_bytes"] = len(owners)
        result["unclassified_bytes"] = end - start - len(owners)
    return result


def encode_event(event, start, end, event_starts):
    opcode = byte(event["opcode"], "track opcode")
    explicit = event["explicit"]
    if type(explicit) is not bool:
        raise ValueError("track opcode explicit flag is invalid")
    kind = event["kind"]
    output = bytearray((opcode,)) if explicit else bytearray()
    if kind == "wait" and 0x80 <= opcode <= 0xB0:
        pass
    elif kind == "end" and opcode in TERMINATORS:
        pass
    elif kind in ("jump", "pattern_call") and opcode == (0xB2 if kind == "jump" else 0xB3):
        target = offset(event["target_offset"], start, end, "track target")
        if target not in event_starts:
            raise ValueError("track target is not an event boundary")
        output.extend(struct.pack("<I", ROM_BASE + target))
    elif kind == "pattern_return" and opcode == 0xB4:
        pass
    elif kind == "repeat" and opcode == 0xB5:
        output.append(byte(event["repeat_count"], "repeat count"))
        target = offset(event["target_offset"], start, end, "repeat target")
        if target not in event_starts:
            raise ValueError("repeat target is not an event boundary")
        output.extend(struct.pack("<I", ROM_BASE + target))
    elif kind == "scalar" and opcode in SCALAR_COMMANDS:
        output.append(byte(event["value"], "scalar value"))
    elif kind == "extended" and opcode == 0xCC:
        output.extend((byte(event["selector"], "extended selector"),
                       byte(event["value"], "extended value")))
    elif kind == "end_note" and opcode == 0xCE:
        if "key" in event:
            value = byte(event["key"], "end-note key")
            if value >= 0x80:
                raise ValueError("end-note key must be below 0x80")
            output.append(value)
    elif kind == "note" and 0xCF <= opcode <= 0xFF:
        values = event["values"]
        if type(values) is not list or len(values) > 3:
            raise ValueError("note has too many operands")
        for value in values:
            value = byte(value, "note operand")
            if value >= 0x80:
                raise ValueError("note operands must be below 0x80")
            output.append(value)
    else:
        raise ValueError(f"opcode {opcode:#x} has an invalid event kind")
    if not explicit and (opcode < 0xBD or not output or output[0] >= 0x80):
        raise ValueError("running status event is not encoded by a data byte")
    if len(output) != event["size"]:
        raise ValueError("track event size changed")
    return bytes(output)


def encode_region(asset):
    start, end = asset["start"], asset["end"]
    if asset["schema_version"] != 1 or not 0 <= start < end:
        raise ValueError("invalid track asset schema or extent")
    events = asset["events"]
    starts = {event["offset"] for event in events}
    if len(starts) != len(events):
        raise ValueError("duplicate track event offsets")
    if any(seed not in starts for seed in asset["track_entry_offsets"]):
        raise ValueError("track entry is not an event boundary")
    output = bytearray()
    for event in events:
        if event["offset"] != start + len(output):
            raise ValueError("track event boundaries have a gap or overlap")
        output.extend(encode_event(event, start, end, starts))
    if len(output) != end - start:
        raise ValueError("track asset length changed")
    # Re-run the retail cursor grammar after edits. This catches stale running
    # status or a branch that makes formerly owned bytes unreachable.
    candidate = bytearray(end)
    candidate[start:end] = output
    parsed = decode_region(candidate, start, end, asset["track_entry_offsets"])
    if parsed["events"] != events:
        raise ValueError("edited track events no longer match the cursor grammar")
    return bytes(output)


def encode_detached_wait_end_tail(asset, reference):
    """Encode a detached wait/end tail without persisting a track entry.

    The start is used only as an ephemeral cursor for the existing MP2K event
    grammar and reparse. Predecessor provenance remains descriptive and does
    not establish runtime reachability.
    """
    if (asset.get("schema_version") != 1 or
            asset.get("descriptor_type") != "mp2k-detached-wait-end-tail" or
            "track_entry_offsets" in asset):
        raise ValueError("invalid detached MP2K tail descriptor")
    start = asset.get("start")
    typed_end = asset.get("typed_end_exclusive")
    physical_end = asset.get("physical_end_exclusive")
    wait_bytes = asset.get("wait_bytes")
    end_bytes = asset.get("end_bytes")
    if (type(start) is not int or type(typed_end) is not int or
            type(physical_end) is not int or type(wait_bytes) is not int or
            type(end_bytes) is not int or wait_bytes <= 0 or end_bytes != 1 or
            typed_end != start + wait_bytes + end_bytes or
            physical_end < typed_end or physical_end > len(reference)):
        raise ValueError("detached MP2K tail extent conflicts with its schema")
    if (asset.get("typed_source_sha256") !=
            sha256(reference[start:typed_end]) or
            asset.get("physical_source_sha256") !=
            sha256(reference[start:physical_end])):
        raise ValueError("detached MP2K tail source hash differs")

    suffix = asset.get("zero_alignment_candidate")
    suffix_bytes = physical_end - typed_end
    if suffix_bytes == 0:
        if suffix is not None:
            raise ValueError("empty detached tail suffix has metadata")
    else:
        if (not isinstance(suffix, dict) or
                suffix.get("start") != typed_end or
                suffix.get("end_exclusive") != physical_end or
                suffix.get("bytes") != suffix_bytes or
                suffix.get("sha256") != sha256(reference[typed_end:physical_end]) or
                reference[typed_end:physical_end] != bytes(suffix_bytes)):
            raise ValueError("detached tail zero suffix metadata differs")

    predecessor = asset.get("predecessor_jump")
    if not isinstance(predecessor, dict):
        raise ValueError("detached tail predecessor provenance is missing")
    predecessor_offset = predecessor.get("offset")
    if (type(predecessor_offset) is not int or predecessor_offset < 0 or
            predecessor_offset + 5 != start):
        raise ValueError("detached tail predecessor boundary conflicts")
    parsed_predecessor, _ = parse_event(reference, predecessor_offset, 0, start)
    if parsed_predecessor != predecessor or parsed_predecessor.get("kind") != "jump":
        raise ValueError("detached tail predecessor jump differs from retail")

    events = asset.get("events")
    if not isinstance(events, list) or len(events) != wait_bytes + end_bytes:
        raise ValueError("detached tail event count conflicts with byte extent")
    if (not events or events[-1].get("kind") != "end" or
            any(event.get("kind") != "wait" for event in events[:-1])):
        raise ValueError("detached tail must contain waits followed by one end")
    temporary_region = {
        "schema_version": 1,
        "start": start,
        "end": typed_end,
        "track_entry_offsets": [start],
        "events": events,
    }
    return encode_region(temporary_region)


def encode_sparse_span(asset, span_start, span_end):
    """Encode only a typed event run, leaving other source bytes unselected."""
    start, end = asset["start"], asset["end"]
    if (asset["schema_version"] != 1 or
            not start <= span_start < span_end <= end or
            [span_start, span_end] not in asset["decoded_spans"]):
        raise ValueError("sparse track span differs from its decoded boundary")
    events = asset["events"]
    event_starts = {event["offset"] for event in events}
    if len(event_starts) != len(events):
        raise ValueError("duplicate sparse track event offset")
    output = bytearray()
    for event in events:
        event_start = event["offset"]
        if span_start <= event_start < span_end:
            if event_start != span_start + len(output):
                raise ValueError("sparse track events leave a gap or overlap")
            output.extend(encode_event(event, start, end, event_starts))
    if len(output) != span_end - span_start:
        raise ValueError("sparse track span has unowned bytes")
    return bytes(output)


def encode_sparse_region(asset, reference):
    """Validate all owned runs together against the retail cursor grammar."""
    start, end = asset["start"], asset["end"]
    if (asset.get("schema_version") != 1 or not 0 <= start < end <= len(reference) or
            asset.get("source_sha256") != sha256(reference[start:end])):
        raise ValueError("sparse track source revision or extent differs")
    decoded = asset["decoded_spans"]
    unknown = asset["unclassified_spans"]
    if (not decoded or any(type(run) is not list or len(run) != 2
                           for run in decoded + unknown)):
        raise ValueError("invalid sparse track spans")
    runs = sorted((run[0], run[1], kind) for kind, spans in
                  (("decoded", decoded), ("unknown", unknown)) for run in spans)
    cursor = start
    for run_start, run_end, _ in runs:
        if (type(run_start) is not int or type(run_end) is not int or
                run_start != cursor or run_end <= run_start or run_end > end):
            raise ValueError("sparse track spans do not partition the region")
        cursor = run_end
    if (cursor != end or
            sum(run_end - run_start for run_start, run_end in decoded) != asset["decoded_bytes"] or
            sum(run_end - run_start for run_start, run_end in unknown) != asset["unclassified_bytes"]):
        raise ValueError("sparse track span accounting differs")
    candidate = bytearray(reference[:end])
    encoded = {}
    for span_start, span_end in decoded:
        data = encode_sparse_span(asset, span_start, span_end)
        candidate[span_start:span_end] = data
        encoded[(span_start, span_end)] = data
    parsed = decode_region(candidate, start, end, asset["track_entry_offsets"],
                           allow_gaps=True)
    for field in ("events", "track_entry_offsets", "visited_states",
                  "decoded_spans", "unclassified_spans", "decoded_bytes",
                  "unclassified_bytes"):
        if parsed[field] != asset[field]:
            raise ValueError(f"edited sparse track {field} differs after traversal")
    return encoded


def verify_retail(asset, rom):
    if sha256(rom) != ROM_SHA256 or asset["source_sha256"] != sha256(
            rom[asset["start"]:asset["end"]]):
        raise ValueError("track source revision differs")
    if encode_region(asset) != rom[asset["start"]:asset["end"]]:
        raise ValueError("track asset does not reproduce retail bytes")
    if decode_region(rom, asset["start"], asset["end"],
                     asset["track_entry_offsets"]) != asset:
        raise ValueError("track asset differs from retail parsing")
    return asset["end"] - asset["start"]
