"""Serialize retail scene text from token and compression records."""
import hashlib
import struct


RETAIL_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
PARAMETER_BYTES = {
    **{x: 0 for x in (0x40, 0x41, 0x42, 0x4a, 0x4d, 0x4f, 0x52, 0x54, 0x56, 0x57, 0x58)},
    **{x: 1 for x in (0x00, 0x1b, 0x1d, 0x46, 0x4b, 0x51, 0x53, 0x32, 0x04)},
    0x45: 2,
}
ALT_CONTROL_CODES = (0x04, 0x46, 0x4b, 0x45, 0x45, None, 0x53, 0x51,
                     0x4d, 0x52, 0x42, 0x57, 0x54, 0x40, 0x4f, 0x41,
                     0x56, 0x4a, None, 0x1b, 0x1d, 0x58, 0x00)


def require(condition, description):
    if not condition:
        raise ValueError(description)


def encode_tokens(entry, verify_hash=True):
    alternate = entry["encoding"] == "alternate"
    out = bytearray()
    half_mode = False
    for token in entry["tokens"]:
        kind = token["type"]
        if kind == "full_glyph":
            code = token["code"]
            if alternate or half_mode or not 0 <= code < 0x8000:
                raise ValueError("Invalid full glyph")
            out.extend((0x80 | (code >> 8), code & 255))
        elif kind == "half_glyph":
            code = token["code"]
            if alternate:
                if not 0 <= code <= 0xff:
                    raise ValueError("Invalid alternate half glyph")
                out.extend((0, code))
            else:
                if not 1 <= code <= 0xfe:
                    raise ValueError("Invalid normal half glyph")
                if not half_mode:
                    out.append(1)
                    half_mode = True
                out.append(code + 1)
        elif kind == "control":
            code = token["code"]
            params = bytes.fromhex(token["parameters_hex"])
            if len(params) != PARAMETER_BYTES[code] and not (alternate and code == 0x45 and len(params) == 1):
                raise ValueError("Invalid control parameters")
            if alternate:
                if code == 0x45:
                    value = token["value"] & 0xffffff00
                    opcode = {0x454c00: 3, 0x455200: 4}[value]
                else:
                    opcode = ALT_CONTROL_CODES.index(code)
                out.append(0x80 + opcode)
            else:
                if half_mode:
                    raise ValueError("Control after half mode")
                out.extend((0x40, code + 0x21))
            out.extend(params)
        elif kind == "control_eos" and not alternate:
            out.append(0)
        else:
            raise ValueError(f"Unknown text token {kind}")
    out.append(0xff if alternate else 0)
    if verify_hash and hashlib.sha256(out).hexdigest() != entry["decoded_sha256"]:
        raise ValueError(f"Text tokens differ at 0x{entry['rom_offset']:x}")
    return bytes(out)


def parse_compression(data, expected):
    """Decode commands into typed operations, retaining the chosen copy forms."""
    pos = 0
    out = bytearray()
    operations = []
    while len(out) < expected:
        command = data[pos]
        pos += 1
        if command & 0x80:
            length = ((command >> 3) & 15) + 3
            distance = (((command & 7) << 8) | data[pos]) + 1
            pos += 1
            op = {"form": "short_copy", "length": length, "distance": distance}
        elif command & 0x40:
            length = (command & 63) + 1
            payload = data[pos:pos + length]
            pos += length
            out.extend(payload)
            op = {"form": "literal", "data_hex": payload.hex()}
        elif command & 0x20:
            length = (command & 31) + 2
            out.extend(bytes(length))
            op = {"form": "short_zero", "length": length}
        elif command & 0x10:
            second, third = data[pos:pos + 2]
            pos += 2
            length = (((second & 0xc0) >> 2) | (command & 15)) + 4
            distance = (((second & 63) << 8) | third) + 1
            op = {"form": "extended_copy", "length": length, "distance": distance}
        elif command in (1, 2):
            length = data[pos] + 3
            pos += 1
            out.extend(bytes((0xff if command == 1 else 0,)) * length)
            op = {"form": "repeat_ff" if command == 1 else "repeat_zero", "length": length}
        elif command == 0:
            length = data[pos] + 5
            distance = ((data[pos + 1] << 8) | data[pos + 2]) + 1
            pos += 3
            op = {"form": "long_copy", "length": length, "distance": distance}
        else:
            raise ValueError("Unknown compression command")
        if op["form"].endswith("copy"):
            for _ in range(length):
                if not 0 < distance <= len(out):
                    raise ValueError("Invalid compression distance")
                out.append(out[-distance])
        operations.append(op)
        if len(out) > expected:
            raise ValueError("Compression output overrun")
    return operations, bytes(out), pos


def encode_compression(operations):
    out = bytearray()
    for op in operations:
        form = op["form"]
        if form == "literal":
            data = bytes.fromhex(op["data_hex"])
            require(1 <= len(data) <= 64, "Invalid literal length")
            out.append(0x40 | (len(data) - 1))
            out.extend(data)
            continue
        length = op["length"]
        if form == "short_zero":
            require(2 <= length <= 33, "Invalid short zero length")
            out.append(0x20 | (length - 2))
        elif form in ("repeat_ff", "repeat_zero"):
            require(3 <= length <= 258, "Invalid repeat length")
            out.extend((1 if form == "repeat_ff" else 2, length - 3))
        else:
            distance = op["distance"] - 1
            if form == "short_copy":
                require(3 <= length <= 18 and 0 <= distance <= 2047, "Invalid short copy")
                out.extend((0x80 | ((length - 3) << 3) | (distance >> 8), distance & 255))
            elif form == "extended_copy":
                require(4 <= length <= 67 and 0 <= distance <= 16383, "Invalid extended copy")
                value = length - 4
                out.extend((0x10 | (value & 15), ((value & 48) << 2) | (distance >> 8), distance & 255))
            elif form == "long_copy":
                require(5 <= length <= 260 and 0 <= distance <= 65535, "Invalid long copy")
                out.extend((0, length - 5, distance >> 8, distance & 255))
            else:
                raise ValueError(f"Unknown compression form {form}")
    return bytes(out)


def encode_entry(entry):
    payload = encode_tokens(entry)
    out = bytearray(struct.pack("<H", entry["flags"]))
    if entry["compressed"]:
        expected = payload + bytes.fromhex(entry["decoded_tail_hex"])
        commands = encode_compression(entry["compression_ops"])
        operations, decoded, consumed = parse_compression(commands, len(expected))
        if decoded != expected or consumed != len(commands) or operations != entry["compression_ops"]:
            raise ValueError(f"Compressed text mismatch at 0x{entry['rom_offset']:x}")
        out.extend(len(expected).to_bytes(4, "big"))
        out.extend(commands)
    else:
        out.extend(payload)
    out.extend(bytes.fromhex(entry["line_padding_hex"]))
    return bytes(out)


def encode_scene_text(document):
    if document["reference_sha256"] != RETAIL_SHA256:
        raise ValueError("Wrong scene text revision")
    table = document["table_rom_offset"]
    end = document["end_exclusive"]
    pages = document["pages"]
    out = bytearray(b"\x00" * (end - table))
    unique = {}
    for page in pages:
        sections = page["subpages"] if page["status"] == "group" else [page]
        for section in sections:
            if section["status"] != "decoded":
                raise ValueError("Unresolved scene text page")
            offset = section["page_rom_offset"]
            if offset in unique:
                if section["entries"] != unique[offset]["entries"]:
                    raise ValueError("Aliased pages differ")
            else:
                unique[offset] = section
    for i, page in enumerate(pages):
        if page["status"] == "group":
            target = page["group_rom_offset"]
        else:
            target = page["page_rom_offset"]
        struct.pack_into("<I", out, i * 4, target - table)
    for page in pages:
        if page["status"] == "group":
            group = page["group_rom_offset"] - table
            for i, section in enumerate(page["subpages"]):
                struct.pack_into("<I", out, group + i * 4,
                                 section["page_rom_offset"] - table)
            out[group + len(page["subpages"]) * 4:group + len(page["subpages"]) * 4 + len(bytes.fromhex(page["group_padding_hex"]))] = bytes.fromhex(page["group_padding_hex"])
    for offset, page in unique.items():
        end = min((candidate for candidate in unique if candidate > offset),
                  default=document["end_exclusive"])
        if offset < document["pages"][61]["group_rom_offset"] < end:
            end = document["pages"][61]["group_rom_offset"]
        encoded = encode_text_page(page, end)
        out[offset - table:offset - table + len(encoded)] = encoded
    return bytes(out)


def encode_text_page(page, end):
    start = page["page_rom_offset"]
    require(start < end, "Invalid text page range")
    out = bytearray(end - start)
    entries = page["entries"]
    for i, entry in enumerate(entries):
        struct.pack_into("<H", out, i * 2, entry["rom_offset"] - start)
        encoded = encode_entry(entry)
        position = entry["rom_offset"] - start
        require(position >= 2 * (len(entries) + 1) and position + len(encoded) <= len(out),
                "Text entry outside page")
        out[position:position + len(encoded)] = encoded
    struct.pack_into("<H", out, len(entries) * 2, 0xffff)
    return bytes(out)


def encode_fixed_text_table(document):
    if document["reference_sha256"] != RETAIL_SHA256:
        raise ValueError("Wrong fixed text revision")
    return b"".join(struct.pack("<I", 0 if page["status"] == "null" else
                                0x08000000 + page["page_rom_offset"])
                    for page in document["pages"])


def encode_fixed_text_page(document, page_offset):
    if document["reference_sha256"] != RETAIL_SHA256:
        raise ValueError("Wrong fixed text revision")
    pages = [page for page in document["pages"] + document.get("consumer_pages", [])
             if page.get("page_rom_offset") == page_offset and page["status"] == "decoded"]
    if not pages:
        raise ValueError(f"Unknown fixed text page at 0x{page_offset:x}")
    if any(page["entries"] != pages[0]["entries"] for page in pages[1:]):
        raise ValueError("Aliased fixed text pages differ")
    return encode_text_page(pages[0], pages[0]["page_end_exclusive"])
