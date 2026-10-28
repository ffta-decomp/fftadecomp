#!/usr/bin/env python3
"""Generate build-local addresses for resource consumers from the selected layout."""

import argparse
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
# Offsets within a selected asset module are part of its decoded source format.
ASSET_SITES = (
    ("ITEM_ICON_ARCHIVE_ADDRESS", "IndexedItemIconArchive", 0),
    ("ITEM_ICON_INDEX_FIELDS_ADDRESS", "ItemIconIndexFields_003c7fe4", 0),
    ("FOLLOWUP_A7_ARCHIVE_ADDRESS", "ItemGraphicsFollowup_003d3d14", 0x50),
    ("FOLLOWUP_GRAPHICS_INDEX_FIELDS_ADDRESS", "ItemGraphicsFollowup_003d3d14", 0),
    ("INTERLEAVED_GRAPHICS_INDEX_ADDRESS", "InterleavedGraphicsIndex_003b8f50", 0),
    ("INTERLEAVED_A7_ARCHIVE_ADDRESS", "InterleavedA7Graphics_003b9004", 0),
    ("INDEXED_CHARACTER_GRAPHICS_ARCHIVE_ADDRESS", "IndexedGraphicsArchive_003e105c", 0),
    ("GRAPHICS_LAYOUT_ARCHIVE_ADDRESS", "IndexedGraphicsLayout_00417f88", 0),
    ("SPRITE_RESOURCE_TABLE_ADDRESS", "SharedSpritePointerTable", 0x390E44 - 0x36DAA4),
    ("SPRITE_PIXEL_BANK_ADDRESS", "SharedSpritePixelBank", 0),
    ("SPRITE_DESCRIPTOR_BANK_ADDRESS", "SharedSpriteDescriptorBank", 0),
    ("TEXT_CALLBACK_TABLE_ADDRESS", "TextCallbackPointerTable", 0),
)


def generate(config):
    modules = {module["name"]: module for module in config["modules"]}
    if len(modules) != len(config["modules"]):
        raise ValueError("duplicate module name in build manifest")
    addresses = {}
    for name, module_name, relative_offset in ASSET_SITES:
        module = modules.get(module_name)
        if module is None or module["kind"] != "asset" or not module.get("enabled", True):
            raise ValueError(f"{name}: required asset module is not selected")
        if not 0 <= relative_offset < module["size"]:
            raise ValueError(f"{name}: address leaves its asset module")
        addresses[name] = config["rom_base"] + module["offset"] + relative_offset
    lines = ["/* Generated from the selected retail asset module layout. */",
             "#ifndef FFTA_GENERATED_ASSET_ADDRESSES_H",
             "#define FFTA_GENERATED_ASSET_ADDRESSES_H"]
    lines += [f"#define {name} 0x{value:08X}u"
              for name, value in addresses.items()]
    lines += ["#endif", ""]
    return "\n".join(lines), addresses


def write(config, output, build_root=None):
    selected_root = (ROOT / "build") if build_root is None else Path(build_root).resolve()
    if not output.resolve().is_relative_to(selected_root):
        raise ValueError("generated build header must remain under root build/")
    source, addresses = generate(config)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(source)
    return addresses


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", type=Path, default=ROOT / "config/retail-us.json")
    parser.add_argument("--output", type=Path, default=ROOT / "build/generated/asset_addresses.h")
    args = parser.parse_args()
    print(json.dumps(write(json.loads(args.config.read_text()), args.output), indent=2))


if __name__ == "__main__":
    main()
