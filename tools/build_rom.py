#!/usr/bin/env python3
"""Build verified recovered modules and compose a private transitional GBA ROM."""
import argparse
import hashlib
import inspect
import json
import os
import re
import platform
import shutil
import struct
import subprocess
import sys
import tempfile
import time
from collections import OrderedDict
from pathlib import Path
from ability_definition_codec import encode_ability_definitions
from audio_song_codec import encode_song_header, encode_song_table
from audio_tone_pcm_codec import (encode_pcm_bank, encode_tone_root,
                                  pcm_payload_files)
from mp2k_track_assets import (ROM_SHA256 as MP2K_ROM_SHA256,
                               encode_region as encode_mp2k_track_region,
                               encode_sparse_region as encode_mp2k_sparse_region,
                               encode_detached_wait_end_tail as
                               encode_mp2k_detached_wait_end_tail)
from extract_coordinate_paths import encode as encode_coordinate_paths
from extract_scene_index import encode as encode_scene_index
from extract_transfer_tile_attributes import encode as encode_transfer_tile_attributes
from extract_nested_battle_scripts import encode_sections as encode_nested_battle_script_sections
from extract_object_animation_resources import (encode_resource as encode_object_animation_resource,
                                                load_catalog as load_object_animation_catalog)
from unclassified_object_animation_codec import encode_resource as encode_unclassified_object_animation
from extract_indexed_transfer_tiles import (encode_tile_bank as encode_indexed_transfer_tiles,
                                            load_graphics_codec as load_transfer_graphics_codec)
from font_codec import encode_atlas
from indexed_graphics_codec import encode_indexed_archive, indexed_entry_source_files
from extract_bg_overlay_banks import (encode as encode_bg_overlay_banks,
                                      source_files as bg_overlay_source_files)
from extract_map_graphics import (map_animation_entry, map_graphics_entry,
                                  map_graphics_wrapper_entry,
                                  reconstruct_map_animation_metadata,
                                  reconstruct_map_animation_tiles,
                                  reconstruct_map_graphics_stream,
                                  reconstruct_map_graphics_wrapper)
from extract_intro_assets import (intro_stream_entry, reconstruct_intro_palette,
                                  reconstruct_intro_stream)
from job_definition_codec import encode_job_definitions
from item_definition_codec import encode_item_definitions
from mission_definition_codec import encode_mission_definitions
from consumer_indexed_table_codec import (encode_equipment_masks,
                                          encode_mission_property_rows)
from map_layout_source_codec import (encode_map_layout_overlay,
                                     encode_map_layout_redirect,
                                     encode_map_layout_source)
from extract_map_table import encode_map_table
from extract_map_secondary_animations import (bank_entry as secondary_animation_entry,
                                              reconstruct_bank as reconstruct_secondary_animation_bank)
from extract_vram_lz77_graphics import (reconstruct_stream as reconstruct_vram_graphics_stream,
                                        stream_entry as vram_graphics_entry)
from extract_world_map_palettes import encode_palette_bank, encode_palette_table
from extract_world_map_overlays import encode_overlay_bank, encode_overlay_table
from extract_world_map_display import (encode_display_source, encode_palette_bank as encode_display_palette_bank,
                                       encode_palette_table as encode_display_palette_table)
from extract_direct_tilemap_runs import encode_copy as encode_direct_tilemap_run
from extract_graphics_layout_banks import encode_bank as encode_graphics_layout_bank
from extract_opening_layout_banks import encode_layout_run as encode_opening_layout_run
from extract_graphics_palettes import encode_bank as encode_graphics_palette_bank
from extract_pointer_lz77_records import (decoded_source_files as pointer_record_sources,
                                          reconstruct_run as reconstruct_pointer_record_run,
                                          run_entry as pointer_record_run_entry)
from extract_pointer_raw_records import (gap_entry as pointer_raw_gap_entry,
                                         payload_source_files as pointer_raw_source_files,
                                         reconstruct_gap as reconstruct_pointer_raw_gap)
from extract_graphics_action_scripts import (fragment_entry as graphics_action_fragment_entry,
                                             fragment_source_file as graphics_action_source_file,
                                             reconstruct_fragment as reconstruct_graphics_action_fragment)
from graphics_action_bank_codec import encode_bank as encode_graphics_action_bank
from nested_counted_palette_codec import encode_bank as encode_nested_counted_palette_bank
from extract_graphics_nested_actions import encode_prefix as encode_graphics_nested_action_prefix
from extract_graphics_nested_frames import encode_root as encode_graphics_nested_frame_root
from extract_graphics_sample_tails import encode_tail as encode_graphics_sample_tail
from extract_pointer_custom_lzss import encode_stream as encode_pointer_custom_lzss_stream
from extract_indexed_custom_lzss import encode_bank as encode_indexed_custom_lzss_bank
from extract_indexed_graphics_archive import encode_archive as encode_indexed_graphics_archive
from extract_indexed_graphics_layout import encode_bank as encode_indexed_graphics_layout_bank
from extract_indexed_color_rows import encode_bank as encode_indexed_color_rows_bank
from extract_graphics_cell_run import encode_run as encode_graphics_cell_run
from extract_direct_graphics_tiles import encode_bank as encode_direct_graphics_tiles
from extract_intro_object_tiles import encode_tiles as encode_intro_object_tiles
from extract_opening_dma_tiles import encode_tiles as encode_opening_dma_tiles
from extract_opening_bg_graphics import encode_segment as encode_opening_bg_segment
from extract_opening_palettes import encode_bank as encode_opening_palette_bank
from extract_opening_tail_graphics import encode_segment as encode_opening_tail_segment
from extract_opening_tilemaps import encode_run as encode_opening_tilemap_run
from extract_opening_indexed_maps import (encode_maps as encode_opening_indexed_maps,
                                          encode_table as encode_opening_indexed_map_table)
from extract_opening_frame_tiles import encode_tiles as encode_opening_frame_tiles
from extract_opening_tile_attributes import encode_segment as encode_opening_tile_attributes
from extract_world_map_packed_attributes import encode_block as encode_world_map_packed_attributes
from extract_indexed_halfword_maps import (encode_data as encode_indexed_halfword_map_data,
                                           encode_table as encode_indexed_halfword_map_table)
from extract_graphics_coordinate_paths import (encode_points as encode_graphics_coordinate_points,
                                               encode_directory as encode_graphics_coordinate_directory)
from extract_graphics_object_dispatch import encode as encode_graphics_object_dispatch
from extract_object_animation_placements import encode_run as encode_object_animation_placement_run
from extract_content_pair_records import (encode_entries as encode_content_entry_bank,
                                          encode_pairs as encode_content_pair_bank,
                                          encode_records as encode_content_record_bank)
from extract_opening_residual_maps import (encode_small_maps as encode_opening_residual_maps,
                                           encode_prefix as encode_opening_halfword_prefix)
from extract_direct_graphics_palettes import encode_bank as encode_direct_graphics_palettes
from extract_graphics_palette_run import encode_run as encode_graphics_palette_run
from extract_graphics_word_run import encode_run as encode_graphics_word_run
from extract_indexed_tile_frames import encode_frames as encode_indexed_tile_frames
from extract_a7_graphics_batch import encode_batch as encode_a7_graphics_batch
from extract_font_widths import encode_widths as encode_font_widths
from extract_item_icon_index_fields import encode_index_fields as encode_item_icon_index_fields
from extract_item_graphics_followup import encode_followup as encode_item_graphics_followup
from extract_interleaved_a7_graphics import (bank_entry as interleaved_a7_bank_entry,
                                             encode_bank as encode_interleaved_a7_bank)
from extract_interleaved_graphics_index import encode_index as encode_interleaved_graphics_index
from extract_indexed_palette_blocks import encode_palette_blocks as encode_indexed_palette_blocks
from extract_pointer_a7_graphics import (bank_entry as pointer_a7_bank_entry,
                                         encode_bank as encode_pointer_a7_bank)
from extract_graphics_frame_resources import (record_entry as graphics_frame_record_entry,
                                              record_source_file as graphics_frame_source_file,
                                              reconstruct_record as reconstruct_graphics_frame_record)
from extract_pointer_palette_records import (group_entry as pointer_palette_group_entry,
                                             group_source_files as pointer_palette_source_files,
                                             reconstruct_group as reconstruct_pointer_palette_group)
from extract_graphics_containers import (root_entry as graphics_container_root_entry,
                                         root_source_file as graphics_container_source_file,
                                         reconstruct_root as reconstruct_graphics_container_root)
from extract_graphics_run_records import encode_record as encode_graphics_run_record
from counted_dimension_runs import (encode_bank as encode_counted_dimension_run_bank)
from item_ability_set_codec import encode_item_ability_sets
from scene_script_codec import encode_scene_scripts
from extract_scene_banners import encode_frame_table, encode_sprite_table
from scene_text_codec import (encode_scene_text, encode_fixed_text_page,
                              encode_fixed_text_table)
from extract_sprite_graphics import (frame_source_files, frame_index_source_files,
                                     frame_preview_files,
                                     frame_palette_source_files,
                                     frame_layer_source_files,
                                     reconstruct_descriptor_bank,
                                     reconstruct_pixel_bank, reconstruct_oam_lists,
                                     reconstruct_pointer_table)
from generate_asset_addresses import write as write_asset_addresses
from unit_record_codec import encode_unit_records
from text_callback_table_codec import encode as encode_text_callback_table
from content_word_bank_codec import (encode as encode_content_word_bank,
                                     encode_catalog_bank)
from ability_list_bank_codec import encode_ability_list_bank
from consumer_bounded_tables_codec import encode_table as encode_consumer_bounded_table

ROOT = Path(__file__).resolve().parents[1]
BUILD_ROOT = ROOT / "build"
MIXED_COMPONENTS = {"battle", "missions", "jobs", "abilities", "items",
                    "equipment", "menus", "audio", "graphics", "input",
                    "saves", "system"}
MIXED_EXCEPTION_COMPONENTS = {
    "system_kernel": "system",
    "low_level_engine": "system",
    "graphics": "graphics",
    "audio": "audio",
    # Preserve the existing measured-performance exception across components.
    "performance_critical": None,
}


def validate_source_mix(module):
    inline_bytes = module.get("inline_assembly_bytes", 0)
    if module["kind"] != "mixed":
        if inline_bytes:
            raise ValueError(f"{module['name']}: inline assembly bytes require mixed kind")
        return
    instruction_bytes = module.get("instructions_bytes", 0)
    if (type(inline_bytes) is not int or type(instruction_bytes) is not int
            or inline_bytes <= 0 or inline_bytes > instruction_bytes):
        raise ValueError(f"{module['name']}: invalid inline assembly byte count")
    if module.get("component") not in MIXED_COMPONENTS:
        raise ValueError(f"{module['name']}: mixed component must identify a supported system")
    exception = module.get("assembly_ratio_exception")
    if exception is not None:
        if (not isinstance(exception, dict) or
                not isinstance(exception.get("class"), str) or
                exception.get("class") not in MIXED_EXCEPTION_COMPONENTS or
                not isinstance(exception.get("reason"), str) or
                not exception["reason"].strip()):
            raise ValueError(f"{module['name']}: invalid documented assembly ratio exception")
        required_component = MIXED_EXCEPTION_COMPONENTS[exception["class"]]
        if required_component is not None and module["component"] != required_component:
            raise ValueError(f"{module['name']}: assembly ratio exception class/component mismatch")
    # Build validity retains the historical <=10% boundary. Completion credit
    # separately requires <10% or an eligible documented low-level exception.
    if inline_bytes * 10 > instruction_bytes and exception is None:
        raise ValueError(f"{module['name']}: inline assembly exceeds 10% without a documented exception")


class BuildInputSession:
    """Build-local hash memo, with content revalidation before publication.

    Stat identities are only a fast in-process drift check, never persisted
    content proof. Every retained digest is reread at the publication gate.
    """
    def __init__(self, max_files=65536):
        self.max_files = max_files
        self.files = {}
        self.pending_receipts = {}
        self.pending_directories = []
        self.staging_roots = {}
        self.verified = False
        self.stats = {"hash_reads": 0, "hash_hits": 0, "hash_bytes": 0,
                      "revalidated_files": 0, "external_object_hits": 0,
                      "external_object_misses": 0}

    @staticmethod
    def signature(path):
        st = path.stat()
        return (st.st_dev, st.st_ino, st.st_size, st.st_mtime_ns, st.st_ctime_ns)

    def digest(self, path):
        self.verified = False
        # The fingerprint boundary already resolves/checks source ownership.
        # Keep lexical '..': symlink/../file need not mean dirname/file.
        path = Path(path).absolute()
        signature = self.signature(path)
        previous = self.files.get(path)
        if previous is not None:
            if previous[0] != signature:
                raise SystemExit(f"Build input changed during build: {path}")
            self.stats["hash_hits"] += 1
            return previous[1]
        if len(self.files) >= self.max_files:
            raise SystemExit("Build input identity budget exceeded")
        digest = sha_file(path)
        if self.signature(path) != signature:
            raise SystemExit(f"Build input changed while hashing: {path}")
        self.files[path] = (signature, digest)
        self.stats["hash_reads"] += 1
        self.stats["hash_bytes"] += signature[2]
        return digest

    def verify(self):
        self.verified = False
        for path, (signature, digest) in self.files.items():
            if (self.signature(path) != signature or sha_file(path) != digest or
                    self.signature(path) != signature):
                raise SystemExit(f"Build input changed before publication: {path}")
            self.stats["revalidated_files"] += 1
        self.verified = True

    def stage_cache(self, cache_dir, key, artifacts, metadata):
        cache_dir.mkdir(parents=True, exist_ok=True)
        self.verified = False
        cache_dir = cache_dir.resolve()
        if cache_dir not in self.staging_roots:
            temporary = tempfile.TemporaryDirectory(prefix=".build-pending-", dir=cache_dir)
            self.pending_directories.append(temporary)
            self.staging_roots[cache_dir] = Path(temporary.name)
        directory = self.staging_roots[cache_dir]
        suffixes = {"data": ".bin", "object": ".o", "linked": ".elf",
                    "compiler_data": ".compiler-data.json"}
        files = []
        for artifact, data in artifacts.items():
            source = directory / (key + suffixes[artifact])
            source.write_bytes(data)
            files.append((source, cache_dir / source.name))
        receipt = directory / (key + ".json")
        receipt.write_text(json.dumps(metadata, sort_keys=True) + "\n")
        self.pending_receipts[(cache_dir / receipt.name).resolve()] = (receipt, files)

    def publish(self):
        # The caller must pass every byte/entry validator and verify() first.
        # Receipts are published last; failed builds never expose new receipts.
        if not self.verified:
            raise SystemExit("Build inputs must be verified before cache publication")
        for destination, (receipt, files) in self.pending_receipts.items():
            for source, target in files:
                os.replace(source, target)
            os.replace(receipt, destination)
        self.close()

    def close(self):
        """Discard only this session's unpublished files, including on failure."""
        self.verified = False
        self.pending_receipts.clear()
        try:
            for temporary in self.pending_directories:
                temporary.cleanup()
        finally:
            self.pending_directories.clear()
            self.staging_roots.clear()


class AssetJsonCache:
    """Content-keyed LRU with a conservative parsed-object byte budget."""
    def __init__(self, max_bytes=256 * 1024 * 1024, max_entries=1024,
                 footprint_dir=None):
        self.footprint_dir = Path(footprint_dir) if footprint_dir is not None else None
        self.footprint_runtime = {
            "python": sys.version, "platform": platform.platform(),
            "maxsize": sys.maxsize,
            "algorithm_sha256": hashlib.sha256(inspect.getsource(
                AssetJsonCache.memory_size).encode()).hexdigest(),
        } if self.footprint_dir is not None else None
        self.max_bytes = max_bytes
        self.max_entries = max_entries
        self.entries = OrderedDict()
        self.bytes = 0
        self.stats = {"hits": 0, "parses": 0, "evictions": 0,
                      "oversized": 0, "peak_retained_bytes": 0,
                      "footprint_hits": 0, "footprint_recounts": 0,
                      "footprint_invalid": 0, "footprint_write_failures": 0}

    @staticmethod
    def memory_size(value):
        # Count the retained object graph, including interned JSON keys/scalars
        # only once per entry. Separate cache entries remain independently
        # charged, even if Python happens to share objects across them.
        size = 0
        seen = set()
        pending = [value]
        while pending:
            current = pending.pop()
            identity = id(current)
            if identity in seen:
                continue
            seen.add(identity)
            size += sys.getsizeof(current)
            if isinstance(current, dict):
                pending.extend(current.keys())
                pending.extend(current.values())
            elif isinstance(current, list):
                pending.extend(current)
        return size

    def graph_charge(self, value, source_digest):
        if self.footprint_dir is None:
            self.stats["footprint_recounts"] += 1
            return self.memory_size(value)
        identity = {**self.footprint_runtime, "source_sha256": source_digest,
                    "schema": "asset-json-footprint-v1"}
        canonical = lambda record: json.dumps(
            record, sort_keys=True, separators=(",", ":")).encode()
        path = self.footprint_dir / (sha(canonical(identity)) + ".json")
        try:
            # Only a tiny metadata receipt is allowed, never decoded payloads.
            with path.open("rb") as stream:
                raw = stream.read(4097)
            if len(raw) > 4096:
                raise ValueError("footprint receipt exceeds metadata limit")
            record = json.loads(raw)
            if not isinstance(record, dict) or set(record) != {
                    "identity", "graph_bytes", "record_sha256"}:
                raise ValueError("invalid footprint receipt schema")
            charge = record["graph_bytes"]
            body = {"identity": record["identity"], "graph_bytes": charge}
            if (record["identity"] != identity or type(charge) is not int or
                    not sys.getsizeof(value) <= charge <= sys.maxsize or
                    record["record_sha256"] != sha(canonical(body))):
                raise ValueError("invalid footprint identity, charge or checksum")
            self.stats["footprint_hits"] += 1
            return charge
        except FileNotFoundError:
            pass
        except (OSError, ValueError, TypeError):
            self.stats["footprint_invalid"] += 1
        self.stats["footprint_recounts"] += 1
        charge = self.memory_size(value)
        body = {"identity": identity, "graph_bytes": charge}
        record = {**body, "record_sha256": sha(canonical(body))}
        try:
            atomic_write(path, canonical(record) + b"\n")
        except OSError:
            # Optional accounting acceleration; the measured charge still
            # enforces this process's cache budget when storage is unavailable.
            self.stats["footprint_write_failures"] += 1
        return charge

    def clear(self):
        self.entries.clear()
        self.bytes = 0
        for key in self.stats:
            self.stats[key] = 0

    def load(self, path):
        path = Path(path).absolute()
        digest = input_sha_file(path)
        key = (str(path), digest)
        if key in self.entries:
            self.stats["hits"] += 1
            self.entries.move_to_end(key)
            return self.entries[key][0]
        raw = path.read_bytes()
        if sha(raw) != digest:
            raise SystemExit(f"Asset JSON changed while reading: {path}")
        value = json.loads(raw)
        self.stats["parses"] += 1
        size = self.graph_charge(value, digest) + sys.getsizeof(key) + sys.getsizeof(key[0]) + sys.getsizeof(digest) + 128
        if size <= self.max_bytes and self.max_entries > 0:
            while self.entries and (self.bytes + size > self.max_bytes or
                                    len(self.entries) >= self.max_entries):
                _, (_, old_size) = self.entries.popitem(last=False)
                self.bytes -= old_size
                self.stats["evictions"] += 1
            self.entries[key] = (value, size)
            self.bytes += size
            self.stats["peak_retained_bytes"] = max(
                self.stats["peak_retained_bytes"], self.bytes)
        else:
            self.stats["oversized"] += 1
        return value


INPUT_SESSION = None
ASSET_JSON_CACHE = AssetJsonCache(footprint_dir=BUILD_ROOT / "json-footprints")


def input_sha_file(path):
    return INPUT_SESSION.digest(path) if INPUT_SESSION is not None else sha_file(path)


def load_asset_json(path):
    return ASSET_JSON_CACHE.load(path)


# Preserve the established explicit reset interface for callers/tests.
load_asset_json.cache_clear = ASSET_JSON_CACHE.clear


def add_stage_time(timings, name, started):
    if timings is not None:
        timings[name] = timings.get(name, 0.0) + time.perf_counter() - started


def run(args):
    subprocess.run(args, check=True)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def sha_file(path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def build_cache_context():
    """Hash shared build inputs once rather than once for every module."""
    inputs = {}

    def add_file(path):
        resolved = path.resolve()
        if not resolved.is_file():
            raise SystemExit(f"Build input is missing: {resolved}")
        inputs[str(resolved)] = input_sha_file(resolved)

    add_file(Path(__file__))
    add_file(ROOT / "tools/generate_asset_addresses.py")
    for path in sorted((ROOT / "tools").glob("*_codec.py")):
        # This leaf codec is fingerprinted only for the bounded-table family.
        if path.name != "consumer_bounded_tables_codec.py":
            add_file(path)
    # Asset serialization and padding do not invoke the C compiler or linker.
    # Preserve their serializer inputs without unrelated code-only dependencies.
    resource_inputs = dict(inputs)
    add_file(BUILD_ROOT / "generated/asset_addresses.h")
    for path in sorted((ROOT / "include").rglob("*")):
        if path.is_file():
            add_file(path)
    for path in (ROOT / "asm/external_thumb_symbols.s",
                 ROOT / "config/symbols.ld"):
        add_file(path)

    tool_paths = {
        "clang": shutil.which("clang"),
        "agbcc": str(BUILD_ROOT / "toolchain/agbcc"),
        "assembler": shutil.which("arm-none-eabi-as"),
        "linker": shutil.which("arm-none-eabi-ld"),
        "objcopy": shutil.which("arm-none-eabi-objcopy"),
        "nm": shutil.which("arm-none-eabi-nm"),
    }
    for name, path in tool_paths.items():
        if path:
            add_file(Path(path))

    # Source-local ABI headers are not found under the public include directory.
    # Keep their conservative dependency set out of assembly and asset keys.
    source_headers = {str(path.resolve()): input_sha_file(path)
                      for path in sorted((ROOT / "src").rglob("*.h")) if path.is_file()}
    return {"inputs": inputs, "resource_inputs": resource_inputs,
            "source_headers": source_headers,
            "python": sys.version, "platform": platform.platform()}


def build_cache_fingerprint(module, base, config, assets_dir, context):
    """Hash module-specific inputs with the shared compiler/linker context."""
    context_key = "resource_inputs" if module["kind"] in ("asset", "padding") else "inputs"
    inputs = dict(context[context_key])
    if module["kind"] in ("c", "mixed"):
        inputs.update(context["source_headers"])
    if module["kind"] != "padding":
        if module["kind"] == "asset" and assets_dir is None:
            raise SystemExit(f"{module['name']}: pass --assets-dir to rebuild extracted assets")
        source_root = assets_dir.resolve() if module["kind"] == "asset" else ROOT
        source = (source_root / module["source"]).resolve()
        if not source.is_relative_to(source_root) or not source.is_file():
            raise SystemExit(f"{module['name']}: source is missing or outside its source root")
        inputs[str(source)] = input_sha_file(source)
        # Self-contained ASM does not assemble the optional external symbol object.
        # Includes may consume it indirectly, so retain conservative inputs there.
        if (module["kind"] == "assembly" and
                not module.get("external_symbols", False) and
                not re.search(r"(?mi)^\s*\.(?:include|incbin)\b", source.read_text())):
            inputs.pop(str((ROOT / "asm/external_thumb_symbols.s").resolve()), None)
        if module["kind"] == "asset" and module.get("format") in (
                "intro-object-tiles-8bpp", "opening-bg-graphics",
                "opening-dma-tiles-8bpp", "opening-frame-tiles",
                "opening-indexed-map-table", "opening-indexed-maps",
                "opening-layout-banks", "opening-palette-bank",
                "opening-halfword-prefix", "opening-residual-maps",
                "opening-tail-graphics", "opening-tile-attributes",
                "opening-tilemaps"):
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
        if module["kind"] == "asset" and module.get("format") in (
                "bios-lz77-vram-graphics", "world-map-palette-table",
                "world-map-palette-bank", "world-map-overlay-table",
                "world-map-overlay-bank", "world-map-display-source",
                "world-map-display-fragment", "world-map-display-palette-table",
                "world-map-display-palette-bank", "world-map-packed-attributes"):
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
        if module["kind"] == "asset" and module.get("format") in (
                "map-table-json", "map-layout-source", "map-layout-redirect",
                "map-layout-overlay",
                "map-lzss-stream", "map-graphics-wrapper",
                "map-animation-metadata", "map-animation-tiles",
                "map-secondary-animation-bank"):
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
        if module["kind"] == "asset" and module.get("format") in (
                "sprite-frame-bank", "sprite-pointer-table", "sprite-oam-lists",
                "sprite-descriptor-bank"):
            inputs[str((ROOT / "tools/extract_sprite_graphics.py").resolve())] = input_sha_file(
                ROOT / "tools/extract_sprite_graphics.py")
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
        if module["kind"] == "asset" and module.get("format") == "sprite-frame-bank":
            manifest = load_asset_json(source)
            for codec in ("indexed_graphics_codec.py", "rgba_palette_codec.py"):
                codec_source = ROOT / "tools" / codec
                inputs[str(codec_source.resolve())] = input_sha_file(codec_source)
            for frame_source in (*frame_source_files(manifest, source.parent),
                                 *frame_index_source_files(manifest, source.parent),
                                 *frame_preview_files(manifest, source.parent)):
                resolved = frame_source.resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: frame source is missing or outside --assets-dir")
                inputs[str(resolved)] = input_sha_file(resolved)
            for palette_source in frame_palette_source_files(manifest, source.parent):
                resolved = palette_source.resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: sprite palette is missing or outside --assets-dir")
                inputs[str(resolved)] = input_sha_file(resolved)
            for layer_source in frame_layer_source_files(manifest, source.parent):
                resolved = layer_source.resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: sprite object layer is missing or outside --assets-dir")
                inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "audio-pcm-bank":
            manifest = load_asset_json(source)
            for payload in pcm_payload_files(manifest, source.parent):
                resolved = payload.resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: PCM payload is missing or outside --assets-dir")
                inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") in (
                "mp2k-track-region", "mp2k-track-span",
                "mp2k-detached-wait-end-tail"):
            for dependency in (ROOT / "tools/mp2k_track_assets.py",
                               ROOT / "config/asset-tables.json"):
                inputs[str(dependency.resolve())] = input_sha_file(dependency)
        if module["kind"] == "asset" and module.get("format") in (
                "equipment-class-masks-json", "mission-property60-rows-json"):
            for dependency in (ROOT / "tools/consumer_indexed_table_codec.py",
                               ROOT / "config/asset-tables.json"):
                inputs[str(dependency.resolve())] = input_sha_file(dependency)
        if module["kind"] == "asset" and module.get("format") in (
                "a7-item-icons", "a7-roster-thumbnails", "a7-scene-banners"):
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
            extractor = {
                "a7-item-icons": "extract_item_icons.py",
                "a7-roster-thumbnails": "extract_character_thumbnails.py",
                "a7-scene-banners": "extract_scene_banners.py",
            }[module["format"]]
            inputs[str((ROOT / "tools" / extractor).resolve())] = input_sha_file(
                ROOT / "tools" / extractor)
            manifest = load_asset_json(source)
            archive_sources = [source.parent / "dictionary.bin"] + list(
                indexed_entry_source_files(manifest, source.parent))
            for archive_source in archive_sources:
                resolved = archive_source.resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: A7 source is missing or outside --assets-dir")
                inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") in (
                "banner-sprite-table", "banner-frame-table"):
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
            inputs[str((ROOT / "tools/extract_scene_banners.py").resolve())] = input_sha_file(
                ROOT / "tools/extract_scene_banners.py")
        if module["kind"] == "asset" and module.get("format") in (
                "map-lzss-stream", "map-graphics-wrapper", "map-animation-metadata",
                "map-animation-tiles"):
            inputs[str((ROOT / "tools/extract_map_graphics.py").resolve())] = input_sha_file(
                ROOT / "tools/extract_map_graphics.py")
        if module["kind"] == "asset" and module.get("format") in (
                "map-layout-source", "map-layout-redirect", "map-layout-overlay"):
            for script in ("extract_map_layout.py", "serialize_map_layout.py",
                           "map_layout_source_codec.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") in (
                "intro-lzss-stream", "intro-palette"):
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
            inputs[str((ROOT / "tools/extract_intro_assets.py").resolve())] = input_sha_file(
                ROOT / "tools/extract_intro_assets.py")
            inputs[str((ROOT / "tools/extract_map_graphics.py").resolve())] = input_sha_file(
                ROOT / "tools/extract_map_graphics.py")
        if module["kind"] == "asset" and module.get("format") == "intro-lzss-stream":
            item = intro_stream_entry(load_asset_json(source), module["offset"])
            decoded = (source.parent / "decoded" / item["file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: intro decoded source is missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "pointer-custom-lzss-stream":
            for script in ("extract_pointer_custom_lzss.py", "extract_map_graphics.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            entry = next((entry for entry in asset["entries"]
                          if entry["start"] == module["offset"]), None)
            if entry is None:
                raise SystemExit(f"{module['name']}: pointer custom-LZSS source is missing")
            decoded = (source.parent / entry["file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: pointer custom-LZSS file is missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "indexed-custom-lzss-bank":
            for script in ("extract_indexed_custom_lzss.py", "extract_map_graphics.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            bank = next((bank for bank in asset["banks"]
                         if bank["start"] == module["offset"]), None)
            if bank is None:
                raise SystemExit(f"{module['name']}: indexed custom-LZSS bank is missing")
            for record in bank["records"]:
                decoded = (source.parent / record["file"]).resolve()
                if not decoded.is_relative_to(source_root) or not decoded.is_file():
                    raise SystemExit(f"{module['name']}: indexed custom-LZSS tile is missing")
                inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "indexed-graphics-archive":
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
            for script in ("extract_indexed_graphics_archive.py", "extract_map_graphics.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            for record in asset["records"]:
                decoded = (source.parent / record["file"]).resolve()
                if not decoded.is_relative_to(source_root) or not decoded.is_file():
                    raise SystemExit(f"{module['name']}: indexed graphics source is missing")
                inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "indexed-graphics-layout-bank":
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
            path = ROOT / "tools/extract_indexed_graphics_layout.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "indexed-color-rows-bank":
            path = ROOT / "tools/extract_indexed_color_rows.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "indexed-graphics-pair-bank":
            for script in ("extract_indexed_graphics_pairs.py", "extract_graphics_layout_banks.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "graphics-cell-run":
            for script in ("extract_graphics_cell_run.py", "extract_graphics_layout_banks.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "direct-graphics-tiles":
            path = ROOT / "tools/extract_direct_graphics_tiles.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "intro-object-tiles-8bpp":
            path = ROOT / "tools/extract_intro_object_tiles.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            decoded = (source.parent / load_asset_json(source)["pixel_file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: opening OBJ tile pixels are missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "opening-dma-tiles-8bpp":
            path = ROOT / "tools/extract_opening_dma_tiles.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            decoded = (source.parent / load_asset_json(source)["pixel_file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: opening DMA tile pixels are missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "opening-frame-tiles":
            path = ROOT / "tools/extract_opening_frame_tiles.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            decoded = (source.parent / load_asset_json(source)["pixel_file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: opening frame pixels are missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "opening-tile-attributes":
            path = ROOT / "tools/extract_opening_tile_attributes.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            entry = next((entry for entry in load_asset_json(source)["segments"]
                          if entry["start"] == module["offset"]), None)
            if entry is None:
                raise SystemExit(f"{module['name']}: opening attribute segment is missing")
            decoded = (source.parent / entry["file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: opening attributes are missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "world-map-packed-attributes":
            path = ROOT / "tools/extract_world_map_packed_attributes.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            decoded = (source.parent / load_asset_json(source)["file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: packed attributes are missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") in (
                "indexed-halfword-map-table", "indexed-halfword-map-data"):
            path = ROOT / "tools/extract_indexed_halfword_maps.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            if module["format"] == "indexed-halfword-map-data":
                for entry in load_asset_json(source)["records"]:
                    decoded = (source.parent / entry["file"]).resolve()
                    if not decoded.is_relative_to(source_root) or not decoded.is_file():
                        raise SystemExit(f"{module['name']}: indexed halfword block is missing")
                    inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") in (
                "graphics-coordinate-points", "graphics-coordinate-directory"):
            path = ROOT / "tools/extract_graphics_coordinate_paths.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "graphics-object-dispatch":
            path = ROOT / "tools/extract_graphics_object_dispatch.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "object-animation-placement-run":
            for path in (ROOT / "tools/extract_object_animation_placements.py",
                         ROOT / "config/unclassified-object-assets.json"):
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") in (
                "content-word-bank-json", "catalog-word-bank-json"):
            for path in (ROOT / "tools/content_word_bank_codec.py",
                         ROOT / "tools/scene_text_codec.py",
                         ROOT / "tools/extract_resources.py"):
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == \
                "consumer-bounded-table-json":
            for path in (ROOT / "tools/consumer_bounded_tables_codec.py",
                         ROOT / "tools/consumer_bounded_table_registry_codec.py",
                         ROOT / "tools/counted_data_v2_layouts.py",
                         ROOT / "tools/remaining_data41_layouts.py"):
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == \
                "consumer-counted-dimension-run-bank-json":
            path = ROOT / "tools/counted_dimension_runs.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            run_manifest = load_asset_json(source)
            for filename in [run_manifest.get("route_catalog_file")] + [
                    record.get("file") for record in run_manifest.get("records", [])]:
                decoded = (source.parent / filename).resolve()
                if not decoded.is_relative_to(source_root) or not decoded.is_file():
                    raise SystemExit(f"{module['name']}: counted run source is missing")
                inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") in (
                "content-entry-bank", "content-pair-bank", "content-record-bank"):
            path = ROOT / "tools/extract_content_pair_records.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            for file_key in ("records_file", "pair_lists_file", "entries_file"):
                decoded = (source.parent / asset[file_key]).resolve()
                if not decoded.is_relative_to(source_root) or not decoded.is_file():
                    raise SystemExit(f"{module['name']}: content record input is missing")
                inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") in (
                "opening-residual-maps", "opening-halfword-prefix"):
            for script in ("extract_opening_residual_maps.py", "extract_opening_tilemaps.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            names = ([entry["file"] for entry in asset["small_maps"]]
                     if module["format"] == "opening-residual-maps"
                     else [asset["prefix_file"]])
            for file_name in names:
                decoded = (source.parent / file_name).resolve()
                if not decoded.is_relative_to(source_root) or not decoded.is_file():
                    raise SystemExit(f"{module['name']}: opening residual fields are missing")
                inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "opening-bg-graphics":
            path = ROOT / "tools/extract_opening_bg_graphics.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            entry = next((entry for entry in load_asset_json(source)["segments"]
                          if entry["start"] == module["offset"]), None)
            if entry is None:
                raise SystemExit(f"{module['name']}: opening BG segment is missing")
            decoded = (source.parent / entry["file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: opening BG fields are missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "bg-overlay-banks":
            for dependency in (ROOT / "tools/extract_bg_overlay_banks.py",
                               ROOT / "tools/indexed_graphics_codec.py",
                               ROOT / "config/asset-tables.json"):
                inputs[str(dependency.resolve())] = input_sha_file(dependency)
            for file_name in bg_overlay_source_files(load_asset_json(source)):
                decoded = (source.parent / file_name).resolve()
                if not decoded.is_relative_to(source_root) or not decoded.is_file():
                    raise SystemExit(f"{module['name']}: BG overlay source is missing")
                inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "opening-palette-bank":
            path = ROOT / "tools/extract_opening_palettes.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            decoded = (source.parent / load_asset_json(source)["palette_file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: opening palette colors are missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "opening-tail-graphics":
            path = ROOT / "tools/extract_opening_tail_graphics.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            entry = next((entry for entry in load_asset_json(source)["segments"]
                          if entry["start"] == module["offset"]), None)
            if entry is None:
                raise SystemExit(f"{module['name']}: opening tail segment is missing")
            decoded = (source.parent / entry["file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: opening tail pixels are missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "opening-tilemaps":
            path = ROOT / "tools/extract_opening_tilemaps.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            for entry in load_asset_json(source)["maps"]:
                decoded = (source.parent / entry["file"]).resolve()
                if not decoded.is_relative_to(source_root) or not decoded.is_file():
                    raise SystemExit(f"{module['name']}: opening tilemap fields are missing")
                inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") in (
                "opening-indexed-map-table", "opening-indexed-maps"):
            for script in ("extract_opening_indexed_maps.py", "extract_opening_tilemaps.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            if module["format"] == "opening-indexed-maps":
                for entry in load_asset_json(source)["entries"]:
                    decoded = (source.parent / entry["file"]).resolve()
                    if not decoded.is_relative_to(source_root) or not decoded.is_file():
                        raise SystemExit(f"{module['name']}: opening indexed-map fields are missing")
                    inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "direct-graphics-palettes":
            path = ROOT / "tools/extract_direct_graphics_palettes.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "graphics-palette-run":
            for script in ("extract_graphics_palette_run.py", "extract_graphics_layout_banks.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "graphics-word-run":
            for script in ("extract_graphics_word_run.py", "extract_graphics_layout_banks.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "indexed-tile-frames":
            for script in ("extract_indexed_tile_frames.py", "extract_direct_graphics_tiles.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "a7-graphics-batch":
            for script in ("extract_a7_graphics_batch.py", "indexed_graphics_codec.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            for item in asset["archives"]:
                archive_dir = (source.parent / item["directory"]).resolve()
                if not archive_dir.is_relative_to(source_root) or not archive_dir.is_dir():
                    raise SystemExit(f"{module['name']}: A7 graphics archive is missing")
                archive_manifest = archive_dir / "manifest.json"
                inputs[str(archive_manifest)] = input_sha_file(archive_manifest)
                nested = load_asset_json(archive_manifest)
                dictionary = archive_dir / "dictionary.bin"
                inputs[str(dictionary)] = input_sha_file(dictionary)
                for entry in indexed_entry_source_files(nested, archive_dir):
                    inputs[str(entry.resolve())] = input_sha_file(entry)
        if module["kind"] == "asset" and module.get("format") == "font-widths":
            path = ROOT / "tools/extract_font_widths.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "item-icon-index-fields":
            path = ROOT / "tools/extract_item_icon_index_fields.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "item-graphics-followup":
            for script in ("extract_item_graphics_followup.py", "indexed_graphics_codec.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(assets_dir / module["source"])
            for item in asset["archives"]:
                archive_dir = (assets_dir / module["source"]).parent / item["directory"]
                archive_manifest = archive_dir / "manifest.json"
                inputs[str(archive_manifest.resolve())] = input_sha_file(archive_manifest)
                nested = load_asset_json(archive_manifest)
                dictionary = archive_dir / "dictionary.bin"
                inputs[str(dictionary.resolve())] = input_sha_file(dictionary)
                for entry in indexed_entry_source_files(nested, archive_dir):
                    inputs[str(entry.resolve())] = input_sha_file(entry)
        if module["kind"] == "asset" and module.get("format") == "interleaved-a7-graphics":
            for script in ("extract_interleaved_a7_graphics.py", "indexed_graphics_codec.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            source = assets_dir / module["source"]
            asset = load_asset_json(source)
            item = interleaved_a7_bank_entry(asset, module["offset"])
            archive_dir = source.parent / item["directory"]
            archive_manifest = archive_dir / "manifest.json"
            inputs[str(archive_manifest.resolve())] = input_sha_file(archive_manifest)
            nested = load_asset_json(archive_manifest)
            dictionary = archive_dir / "dictionary.bin"
            inputs[str(dictionary.resolve())] = input_sha_file(dictionary)
            for entry in indexed_entry_source_files(nested, archive_dir):
                inputs[str(entry.resolve())] = input_sha_file(entry)
        if module["kind"] == "asset" and module.get("format") == "interleaved-graphics-index":
            path = ROOT / "tools/extract_interleaved_graphics_index.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "indexed-palette-blocks":
            path = ROOT / "tools/extract_indexed_palette_blocks.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "pointer-a7-graphics":
            for script in ("extract_pointer_a7_graphics.py", "indexed_graphics_codec.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            source = assets_dir / module["source"]
            asset = load_asset_json(source)
            item = pointer_a7_bank_entry(asset, module["offset"])
            archive_dir = source.parent / item["directory"]
            archive_manifest = archive_dir / "manifest.json"
            inputs[str(archive_manifest.resolve())] = input_sha_file(archive_manifest)
            nested = load_asset_json(archive_manifest)
            dictionary = archive_dir / "dictionary.bin"
            inputs[str(dictionary.resolve())] = input_sha_file(dictionary)
            for entry in indexed_entry_source_files(nested, archive_dir):
                inputs[str(entry.resolve())] = input_sha_file(entry)
        if module["kind"] == "asset" and module.get("format") == "map-table-json":
            path = ROOT / "tools/extract_map_table.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "coordinate-paths-json":
            path = ROOT / "tools/extract_coordinate_paths.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") in (
                "scene-index-json", "transfer-tile-attributes-json"):
            filename = ("extract_scene_index.py" if module["format"] == "scene-index-json"
                        else "extract_transfer_tile_attributes.py")
            path = ROOT / "tools" / filename
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "nested-battle-script-section":
            path = ROOT / "tools/extract_nested_battle_scripts.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "object-animation-json":
            for path in (ROOT / "tools/extract_object_animation_resources.py",
                         ROOT / "config/object-animation-roots.json"):
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "unclassified-object-animation-json":
            for path in (ROOT / "tools/unclassified_object_animation_codec.py",
                         ROOT / "tools/catalog_unclassified_object_assets.py",
                         ROOT / "config/unclassified-object-assets.json"):
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "indexed-transfer-tile-bank":
            for filename in ("extract_indexed_transfer_tiles.py", "indexed_graphics_codec.py"):
                path = ROOT / "tools" / filename
                inputs[str(path.resolve())] = input_sha_file(path)
            manifest = load_asset_json(source)
            for record in manifest["records"]:
                for page in record["tile_pages"]:
                    image = (source.parent / page["file"]).resolve()
                    if not image.is_relative_to(source_root) or not image.is_file():
                        raise SystemExit(f"{module['name']}: indexed tile image is missing")
                    inputs[str(image)] = input_sha_file(image)
        if module["kind"] == "asset" and module.get("format") == "map-secondary-animation-bank":
            path = ROOT / "tools/extract_map_secondary_animations.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            bank = secondary_animation_entry(load_asset_json(source), module["offset"])
            for frame in bank["unique_frames"]:
                frame_source = (source.parent / "frames" / frame["file"]).resolve()
                if not frame_source.is_relative_to(source_root) or not frame_source.is_file():
                    raise SystemExit(f"{module['name']}: secondary animation frame is missing")
                inputs[str(frame_source)] = input_sha_file(frame_source)
        if module["kind"] == "asset" and module.get("format") == "bios-lz77-vram-graphics":
            for script in ("extract_vram_lz77_graphics.py", "extract_map_layout.py",
                           "map_layout_source_codec.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            entry = vram_graphics_entry(load_asset_json(source), module["offset"])
            decoded = (source.parent / "decoded" / entry["file"]).resolve()
            if not decoded.is_relative_to(source_root) or not decoded.is_file():
                raise SystemExit(f"{module['name']}: VRAM graphics source is missing")
            inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") in (
                "world-map-palette-table", "world-map-palette-bank"):
            path = ROOT / "tools/extract_world_map_palettes.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") in (
                "world-map-overlay-table", "world-map-overlay-bank"):
            path = ROOT / "tools/extract_world_map_overlays.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") in (
                "world-map-display-source", "world-map-display-fragment",
                "world-map-display-palette-bank", "world-map-display-palette-table"):
            path = ROOT / "tools/extract_world_map_display.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            if module["format"] in ("world-map-display-source", "world-map-display-fragment"):
                entry = next((entry for entry in load_asset_json(source)["sources"]
                              if entry["start"] == module["offset"]), None)
                if entry is None and module["format"] == "world-map-display-fragment":
                    entry = next((entry for entry in load_asset_json(source)["sources"]
                                  if entry["start"] < module["offset"] < entry["start"] + entry["size"]), None)
                if entry is None:
                    raise SystemExit(f"{module['name']}: world-map display source is missing")
                decoded = (source.parent / entry["file"]).resolve()
                if not decoded.is_relative_to(source_root) or not decoded.is_file():
                    raise SystemExit(f"{module['name']}: world-map display decoded source is missing")
                inputs[str(decoded)] = input_sha_file(decoded)
            elif module["format"] == "world-map-display-palette-bank":
                for entry in load_asset_json(source)["palettes"]:
                    decoded = (source.parent / entry["file"]).resolve()
                    if not decoded.is_relative_to(source_root) or not decoded.is_file():
                        raise SystemExit(f"{module['name']}: world-map display palette is missing")
                    inputs[str(decoded)] = input_sha_file(decoded)
        if module["kind"] == "asset" and module.get("format") == "direct-tilemap-run":
            path = ROOT / "tools/extract_direct_tilemap_runs.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "graphics-layout-bank":
            path = ROOT / "tools/extract_graphics_layout_banks.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "opening-layout-banks":
            for script in ("extract_opening_layout_banks.py", "extract_graphics_layout_banks.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "graphics-embedded-layout-bank":
            for script in ("extract_graphics_embedded_layout.py", "extract_graphics_layout_banks.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "graphics-palette-bank":
            path = ROOT / "tools/extract_graphics_palettes.py"
            inputs[str(path.resolve())] = input_sha_file(path)
        if module["kind"] == "asset" and module.get("format") == "pointer-lz77-record-run":
            descriptor_source = ROOT / "config/asset-tables.json"
            inputs[str(descriptor_source.resolve())] = input_sha_file(descriptor_source)
            for script in ("extract_pointer_lz77_records.py",
                           "map_layout_source_codec.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            for decoded in pointer_record_sources(load_asset_json(source), module["offset"], source.parent):
                resolved = decoded.resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: decoded record source is missing")
                inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "pointer-raw-record-gap":
            for script in ("extract_pointer_raw_records.py", "extract_pointer_lz77_records.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            for payload in pointer_raw_source_files(load_asset_json(source), module["offset"], source.parent):
                resolved = payload.resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: raw record source is missing")
                inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "graphics-action-fragment":
            for script in ("extract_graphics_action_scripts.py", "extract_pointer_lz77_records.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            resolved = graphics_action_source_file(load_asset_json(source), module["offset"], source.parent).resolve()
            if not resolved.is_relative_to(source_root) or not resolved.is_file():
                raise SystemExit(f"{module['name']}: graphics action source is missing")
            inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "graphics-action-script-bank-json":
            path = ROOT / "tools/graphics_action_bank_codec.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            for entry in asset["records"]:
                resolved = (source.parent / entry["file"]).resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: action script source is missing")
                inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "graphics-nested-action-prefix":
            for script in ("extract_graphics_nested_actions.py", "extract_graphics_action_scripts.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            entry = next((entry for entry in asset["entries"]
                          if entry["start"] == module["offset"]), None)
            if entry is None:
                raise SystemExit(f"{module['name']}: nested graphics action is missing")
            resolved = (source.parent / entry["file"]).resolve()
            if not resolved.is_relative_to(source_root) or not resolved.is_file():
                raise SystemExit(f"{module['name']}: nested graphics action source is missing")
            inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "graphics-frame-record":
            for script in ("extract_graphics_frame_resources.py", "extract_pointer_lz77_records.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            resolved = graphics_frame_source_file(load_asset_json(source), module["offset"], source.parent).resolve()
            if not resolved.is_relative_to(source_root) or not resolved.is_file():
                raise SystemExit(f"{module['name']}: graphics frame source is missing")
            inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "graphics-nested-frame-root":
            for script in ("extract_graphics_nested_frames.py", "extract_graphics_frame_resources.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            entry = next((entry for entry in asset["entries"]
                          if entry["start"] == module["offset"]), None)
            if entry is None:
                raise SystemExit(f"{module['name']}: nested graphics frame is missing")
            resolved = (source.parent / entry["file"]).resolve()
            if not resolved.is_relative_to(source_root) or not resolved.is_file():
                raise SystemExit(f"{module['name']}: nested graphics frame source is missing")
            inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "graphics-sample-tail":
            for script in ("extract_graphics_sample_tails.py", "extract_graphics_nested_frames.py",
                           "extract_graphics_frame_resources.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            entry = next((entry for entry in asset["entries"]
                          if entry["start"] == module["offset"]), None)
            if entry is None:
                raise SystemExit(f"{module['name']}: graphics sample tail is missing")
            resolved = (source.parent / entry["file"]).resolve()
            if not resolved.is_relative_to(source_root) or not resolved.is_file():
                raise SystemExit(f"{module['name']}: graphics sample tail source is missing")
            inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "pointer-palette-group":
            for script in ("extract_pointer_palette_records.py", "extract_pointer_lz77_records.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            for palette in pointer_palette_source_files(load_asset_json(source), module["offset"], source.parent):
                resolved = palette.resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: counted palette source is missing")
                inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "nested-counted-palette-bank-json":
            path = ROOT / "tools/nested_counted_palette_codec.py"
            inputs[str(path.resolve())] = input_sha_file(path)
            asset = load_asset_json(source)
            for entry in asset["records"]:
                resolved = (source.parent / entry["file"]).resolve()
                if not resolved.is_relative_to(source_root) or not resolved.is_file():
                    raise SystemExit(f"{module['name']}: nested palette source is missing")
                inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "graphics-container-root":
            for script in ("extract_graphics_containers.py", "extract_pointer_lz77_records.py"):
                path = ROOT / "tools" / script
                inputs[str(path.resolve())] = input_sha_file(path)
            resolved = graphics_container_source_file(load_asset_json(source), module["offset"], source.parent).resolve()
            if not resolved.is_relative_to(source_root) or not resolved.is_file():
                raise SystemExit(f"{module['name']}: graphics container source is missing")
            inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "graphics-run-record":
            script = ROOT / "tools/extract_graphics_run_records.py"
            inputs[str(script.resolve())] = input_sha_file(script)
            asset = load_asset_json(source)
            entry = next((record for record in asset["records"]
                          if record["start"] == module["offset"]), None)
            if entry is None:
                raise SystemExit(f"{module['name']}: graphics run record is missing")
            resolved = (source.parent / "records" / entry["file"]).resolve()
            if not resolved.is_relative_to(source_root) or not resolved.is_file():
                raise SystemExit(f"{module['name']}: graphics run source is missing")
            inputs[str(resolved)] = input_sha_file(resolved)
        if module["kind"] == "asset" and module.get("format") == "map-animation-tiles":
            item = next((item for item in load_asset_json(source)["animations"]
                         if item and item["tiles_offset"] == module["offset"]), None)
            if item is None:
                raise SystemExit(f"{module['name']}: map animation tiles are absent")
            for frame in item["frames"]:
                frame_source = (source.parent / "animations" / frame["file"]).resolve()
                if not frame_source.is_relative_to(source_root) or not frame_source.is_file():
                    raise SystemExit(f"{module['name']}: map animation frame is missing")
                inputs[str(frame_source)] = input_sha_file(frame_source)
        if module["kind"] == "asset" and module.get("format") == "map-lzss-stream":
            item = map_graphics_entry(load_asset_json(source), module["offset"])
            graphics_source = (source.parent / "graphics" / item["file"]).resolve()
            if (not graphics_source.is_relative_to(source_root) or
                    not graphics_source.is_file()):
                raise SystemExit(f"{module['name']}: map graphics are missing or outside --assets-dir")
            inputs[str(graphics_source)] = input_sha_file(graphics_source)

    payload = {
        "module": module,
        "rom_base": base,
        "input_revision": {"id": config["id"], "sha256": config["sha256"]},
        "python": context["python"],
        "platform": context["platform"],
        "inputs": inputs,
    }
    return sha(json.dumps(payload, sort_keys=True, separators=(",", ":")).encode())


def atomic_write(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    descriptor, temporary = tempfile.mkstemp(prefix=".module-cache-", dir=path.parent)
    try:
        with os.fdopen(descriptor, "wb") as stream:
            stream.write(data)
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


def module_linked_entry_count(module):
    functions = module.get("functions", [{"name": module["name"]}])
    return sum(not function["name"].startswith("Compiler")
               for function in functions)


def compile_module_cached(module, work, base, assets_dir, config, cache_dir,
                          cache_context, reference, tool_cache_dir=None, stage_timings=None,
                          materialize_link_artifacts=True):
    started = time.perf_counter()
    key = build_cache_fingerprint(module, base, config, assets_dir, cache_context)
    add_stage_time(stage_timings, "fingerprinting", started)
    started = time.perf_counter()
    metadata_path = cache_dir / (key + ".json")
    artifact_paths = {"data": cache_dir / (key + ".bin")}
    if module["kind"] in ("c", "mixed", "assembly"):
        artifact_paths.update({
            "object": cache_dir / (key + ".o"),
            "linked": cache_dir / (key + ".elf"),
        })

    if module.get("compiler_data_policy"):
        artifact_paths["compiler_data"] = cache_dir / (key + ".compiler-data.json")

    try:
        metadata = json.loads(metadata_path.read_text())
        valid = isinstance(metadata, dict) and metadata.get("key") == key
        stored_hashes = metadata.get("files", {}) if isinstance(metadata, dict) else {}
        valid = valid and isinstance(stored_hashes, dict)
        for artifact, path in artifact_paths.items():
            valid = (valid and path.is_file() and
                     sha_file(path) == stored_hashes.get(artifact))
        if module["kind"] in ("c", "mixed"):
            valid = (valid and
                     metadata.get("linked_function_entries_checked") ==
                     module_linked_entry_count(module))
        if valid:
            for artifact, suffix in (("object", ".o"), ("linked", ".elf"), ("compiler_data", ".compiler-data.json")):
                if (artifact in artifact_paths and
                        (materialize_link_artifacts or artifact == "compiler_data" or
                         module.get("linker_veneer_policy"))):
                    shutil.copyfile(artifact_paths[artifact], work / (module["name"] + suffix))
            data = artifact_paths["data"].read_bytes()
            add_stage_time(stage_timings, "module_cache_lookup", started)
            return data, True, key
    except (AttributeError, OSError, TypeError, json.JSONDecodeError):
        pass

    add_stage_time(stage_timings, "module_cache_lookup", started)
    started = time.perf_counter()
    options = {}
    if tool_cache_dir is not None:
        options["tool_cache_dir"] = tool_cache_dir
    if stage_timings is not None:
        options["stage_timings"] = stage_timings
    data = compile_module(module, work, base, assets_dir, reference, **options)
    add_stage_time(stage_timings, "module_compile", started)
    started = time.perf_counter()
    artifacts = {"data": data}
    if module["kind"] in ("c", "mixed", "assembly"):
        for artifact, suffix in (("object", ".o"), ("linked", ".elf"), ("compiler_data", ".compiler-data.json")):
            source = work / (module["name"] + suffix)
            if source.is_file():
                artifacts[artifact] = source.read_bytes()

    cache_dir.mkdir(parents=True, exist_ok=True)
    suffixes = {"data": ".bin", "object": ".o", "linked": ".elf", "compiler_data": ".compiler-data.json"}
    metadata = {"key": key, "files": {name: sha(contents) for name, contents in artifacts.items()}}
    if INPUT_SESSION is not None:
        INPUT_SESSION.stage_cache(cache_dir, key, artifacts, metadata)
    else:
        for artifact, contents in artifacts.items():
            atomic_write(cache_dir / (key + suffixes[artifact]), contents)
        atomic_write(metadata_path, (json.dumps(metadata, sort_keys=True) + "\n").encode())
    add_stage_time(stage_timings, "module_cache_publish", started)
    return data, False, key


def cache_linked_entry_validation(cache_dir, key, checked_entries):
    metadata_path = cache_dir / (key + ".json")
    if INPUT_SESSION is not None:
        pending = INPUT_SESSION.pending_receipts.get(metadata_path.resolve())
        if pending is not None:
            metadata_path = pending[0]
    metadata = json.loads(metadata_path.read_text())
    metadata["linked_function_entries_checked"] = checked_entries
    atomic_write(metadata_path, (json.dumps(metadata, sort_keys=True) + "\n").encode())


def version_line(command):
    result = subprocess.run(command, text=True, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, check=False)
    return result.stdout.splitlines()[0].strip() if result.stdout else "unknown"


SPARSE_REGION_CACHE = {}


ELF_SECTION_HEADER = re.compile(
    r"^\s*(\d+)\s+(\S+)\s+([0-9a-fA-F]+)\s+"
    r"([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(\S+)"
)

def parse_elf_sections(section_listing: str) -> list[dict]:
    """Parse the section table emitted by arm-none-eabi-objdump -h."""
    sections = []
    current = None
    for line in section_listing.splitlines():
        match = ELF_SECTION_HEADER.match(line)
        if match:
            if current is not None:
                sections.append(current)
            current = {
                "index": int(match.group(1)),
                "name": match.group(2),
                "size": int(match.group(3), 16),
                "flags": set(),
            }
            continue
        if current is not None:
            current["flags"].update(re.findall(
                r"\b(CONTENTS|ALLOC|LOAD|READONLY|CODE|DATA|NEVER_LOAD)\b", line))
    if current is not None:
        sections.append(current)
    if not sections:
        raise ValueError("could not read ELF section table from objdump output")
    return sections


def validate_elf_load_sections(elf: Path) -> list[dict]:
    """Reject data omitted by the local path, which extracts only the .text section."""
    objdump = shutil.which("arm-none-eabi-objdump")
    if objdump is None:
        raise ValueError("required tool is missing: objdump")
    listing = subprocess.check_output([objdump, "-h", str(elf)], text=True)
    sections = parse_elf_sections(listing)
    unsupported = [section for section in sections
                   if section["name"] != ".text" and section["size"] > 0
                   and section["flags"].intersection({"ALLOC", "LOAD"})]
    if unsupported:
        details = ", ".join(
            f"{section['name']} ({section['size']} bytes; "
            f"{','.join(sorted(section['flags']))})" for section in unsupported)
        raise ValueError(
            "unsupported nonempty allocated/load sections outside .text: " + details)
    return [{**section, "flags": sorted(section["flags"])} for section in sections]


DEAD_SWITCH_LITERAL_POLICY = "agbcc-unreferenced-switch-pointer-v1"
DEAD_SYMBOL_LITERAL_POLICY = "agbcc-unreferenced-symbol-pointer-v1"


DEAD_POINTER_OBJECTS_POLICY = "agbcc-unreferenced-pointer-objects-v1"


def normalize_compiler_pointer_objects(assembly, policy):
    """Remove a reviewed, hash-pinned sequence of unused four-byte objects.

    This is an explicit legacy compatibility exception, not section GC. The
    complete original compiler output and ordered object inventory are pinned.
    All references outside each object's own declarations are forbidden.
    """
    if set(policy) != {"name", "input_assembly_sha256", "objects"}:
        raise ValueError("pointer object policy requires exact audit fields")
    if (policy["name"] != DEAD_POINTER_OBJECTS_POLICY
            or policy["input_assembly_sha256"] != sha(assembly.encode())
            or not assembly.startswith("@ Generated by gcc 2.9-arm-")):
        raise ValueError("pointer object compiler output differs from reviewed input")
    objects = policy["objects"]
    if not isinstance(objects, list) or not objects or len(objects) > 32:
        raise ValueError("expected bounded pointer object inventory")
    blocks, labels = [], []
    for item in objects:
        if not isinstance(item, dict) or set(item) != {"label", "target"}:
            raise ValueError("invalid pointer object descriptor")
        label, target = item["label"], item["target"]
        if (not isinstance(label, str) or not isinstance(target, str)
                or not re.fullmatch(r"(?:\.LC[0-9]+|[A-Za-z_][A-Za-z0-9_]*)", label)
                or not re.fullmatch(r"(?:[0-9]+|[A-Za-z_][A-Za-z0-9_]*(?:\+[0-9]+)?)", target)
                or label in labels):
            raise ValueError("unsupported or duplicate pointer object")
        block = "\t.align\t2, 0\n"
        if not label.startswith(".LC"):
            block += f"\t.type\t {label},object\n\t.size\t {label},4\n"
        block += f"{label}:\n\t.word\t{target}\n"
        blocks.append(block)
        labels.append(label)
    section_pattern = re.compile(r"(?ms)^\t\.section \.rodata\n(.*?)(?=^\.text\n)")
    sections = list(section_pattern.finditer(assembly))
    if (not sections or assembly.count(".rodata") != len(sections)
            or "".join(section.group(1) for section in sections) != "".join(blocks)):
        raise ValueError("pointer object section differs from reviewed inventory")
    normalized = section_pattern.sub("", assembly)
    # Check outside each declaration, including other objects, to reject
    # aliases, exported symbols, inter-object pointers and code/data users.
    for label, block in zip(labels, blocks):
        outside = assembly.replace(block, "", 1)
        token = r"(?<![\w.$])" + re.escape(label) + r"(?![\w.$])"
        if re.search(token, outside):
            raise ValueError("pointer object is referenced or exported: " + label)
    return normalized, {
        "policy": policy["name"], "removed_bytes": 4 * len(objects),
        "objects": objects, "incoming_symbol_references": 0,
        "input_assembly_sha256": sha(assembly.encode()),
        "output_assembly_sha256": sha(normalized.encode()),
    }


def normalize_compiler_switch_literal(assembly, policy):
    """Remove one explicitly permitted unreferenced agbcc pointer object.

    The table and its live text literal remain untouched. This is intentionally
    not a general dead-data eliminator: any unexpected shape fails closed.
    """
    if isinstance(policy, dict):
        return normalize_compiler_pointer_objects(assembly, policy)
    if policy not in (DEAD_SWITCH_LITERAL_POLICY, DEAD_SYMBOL_LITERAL_POLICY):
        raise ValueError("unsupported compiler data policy")
    if not assembly.startswith("@ Generated by gcc 2.9-arm-"):
        raise ValueError("switch pointer policy requires agbcc output")
    pattern = re.compile(
        r"(?m)^\t\.section \.rodata\n\t\.align\t2, 0\n"
        r"(?P<label>\.LC[0-9]+):\n\t\.word\t(?P<table>[A-Za-z_.$][A-Za-z0-9_.$]*)\n(?=\.text\n)"
    )
    if assembly.count(".rodata") != 1:
        raise ValueError("additional read-only data or section references")
    matches = list(pattern.finditer(assembly))
    if len(matches) != 1:
        raise ValueError("expected exactly one compiler switch pointer")
    match = matches[0]
    label, table = match.group("label", "table")
    token = r"(?<![\w.$])" + re.escape(label) + r"(?![\w.$])"
    if len(re.findall(token, assembly)) != 1:
        raise ValueError("compiler switch pointer is referenced or exported")
    # Require an actual multi-entry local jump table, not an arbitrary pointer.
    table_pattern = r"(?m)^" + re.escape(table) + r":\n(?:\t\.word\t\.L[0-9]+\n){2,}"
    if policy == DEAD_SWITCH_LITERAL_POLICY:
        if not re.fullmatch(r"\.L[0-9]+", table) or len(re.findall(table_pattern, assembly)) != 1:
            raise ValueError("compiler pointer target is not a local jump table")
    else:
        # External-symbol variant: keep the duplicate text literal and its
        # relocation. Never admit expressions, local tables or owned objects.
        remaining = assembly[match.end():]
        if (not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", table)
                or re.search(r"(?m)^" + re.escape(table) + r":", assembly)
                or len(re.findall(r"(?m)^\t\.word\t" + re.escape(table)
                                  + r"$", remaining)) != 1):
            raise ValueError("expected external symbol and one preserved text pointer")
    normalized = assembly[:match.start()] + assembly[match.end():]
    return normalized, {
        "policy": policy, "removed_bytes": 4, "local_label": label,
        "table_label": table, "target_symbol": table, "incoming_symbol_references": 0,
        "input_assembly_sha256": sha(assembly.encode()),
        "output_assembly_sha256": sha(normalized.encode()),
    }


def c_preprocessor_command(module, source):
    """Return production preprocessing argv without an output destination."""
    flags = module.get("compiler_flags", ["-O0", "-mthumb-interwork"])
    preprocessor_flags = [flag for flag in flags
                          if flag.startswith("-D") or flag.startswith("-U")]
    return ["clang", "-E", "-P", "-x", "c", "-nostdinc",
            "-I", str(ROOT / "include"),
            "-I", str(BUILD_ROOT / "generated"),
            *preprocessor_flags, str(source)]


def validate_function_ranges(module, generated_size):
    """Return C/mixed records partitioning the complete selected output span.

    Linked veneers belong to that selected span, even when the ELF function
    symbol itself is shorter. Assembly entry inventories need not partition
    their literals or alignment and deliberately bypass this C-only contract.
    """
    if module.get("kind") not in ("c", "mixed"):
        return []
    name = module.get("name", "<unnamed>")
    offset = module.get("offset")
    if (type(offset) is not int or offset < 0 or
            type(generated_size) is not int or generated_size <= 0):
        raise SystemExit(f"{name}: invalid selected function span")
    functions = module.get("functions", [{"name": name, "offset": offset,
                                          "size": generated_size}])
    if not isinstance(functions, list) or not functions:
        raise SystemExit(f"{name}: functions must be a nonempty list")
    cursor = offset
    for function in functions:
        if not isinstance(function, dict):
            raise SystemExit(f"{name}: invalid function record")
        start, size = function.get("offset"), function.get("size")
        if (not isinstance(function.get("name"), str) or not function["name"] or
                type(start) is not int or type(size) is not int or size <= 0 or
                start != cursor or start + size > offset + generated_size):
            raise SystemExit(f"{name}: invalid function boundaries")
        cursor = start + size
    if cursor != offset + generated_size:
        raise SystemExit(f"{name}: function ranges do not cover module")
    return functions


def assemble_external_symbols(assembler, source, output, flags, cache_dir=None):
    """Assemble aliases, optionally reusing an immutable verified object."""
    source_bytes = source.read_bytes()
    # These directives introduce file dependencies not represented by this key.
    if cache_dir is None or re.search(rb"(?i)\.(?:include|incbin)\b", source_bytes):
        run([assembler, *flags, str(source), "-o", str(output)])
        return
    identity = {"schema": "external-symbol-object-v1",
                "source_sha256": sha(source_bytes),
                "assembler_sha256": input_sha_file(Path(assembler).resolve()),
                "flags": flags}
    key = sha(json.dumps(identity, sort_keys=True).encode())
    cache_dir = Path(cache_dir) / "external-symbols"
    cache_dir.mkdir(parents=True, exist_ok=True)
    entry = cache_dir / key

    def read_cached():
        try:
            record = json.loads((entry / "object.json").read_text())
            data = (entry / "object.o").read_bytes()
            if (record["identity"] != identity or not data or
                    record["object_sha256"] != sha(data)):
                raise ValueError("object identity or content hash differs")
            return data
        except (OSError, ValueError, KeyError, TypeError) as error:
            raise SystemExit(f"Invalid external-symbol object cache {key}: {error}")

    if INPUT_SESSION is not None:
        counter = "external_object_hits" if entry.exists() else "external_object_misses"
        INPUT_SESSION.stats[counter] += 1
    if not entry.exists():
        # Publish object and hash together; readers never see a half-written pair.
        with tempfile.TemporaryDirectory(prefix=key + "-", dir=cache_dir) as temp:
            directory = Path(temp)
            snapshot = directory / "external_symbols.s"
            snapshot.write_bytes(source_bytes)
            obj = directory / "object.o"
            run([assembler, *flags, str(snapshot), "-o", str(obj)])
            data = obj.read_bytes()
            if not data:
                raise SystemExit("External-symbol assembler produced an empty object")
            if sha(Path(assembler).resolve().read_bytes()) != identity["assembler_sha256"]:
                raise SystemExit("External-symbol assembler changed during compilation")
            (directory / "object.json").write_text(json.dumps(
                {"identity": identity, "object_sha256": sha(data)}, sort_keys=True))
            try:
                os.rename(directory, entry)
            except OSError:
                # Another parallel job may have atomically published this key.
                if not entry.is_dir():
                    raise
    output.write_bytes(read_cached())


def compile_module(module, work, base, assets_dir, reference=None,
                   tool_cache_dir=None, stage_timings=None):
    validate_function_ranges(module, module.get("size"))

    def timed(stage, operation):
        started = time.perf_counter()
        try:
            return operation()
        finally:
            if stage_timings is not None:
                stage_timings[stage] = (stage_timings.get(stage, 0.0) +
                                        time.perf_counter() - started)

    if module.get("compiler_data_policy") and module["kind"] != "c":
        raise ValueError("compiler data policy requires a pure C module")
    name = module["name"]
    if module["kind"] == "padding":
        value = module.get("fill_byte")
        if type(value) is not int or not 0 <= value <= 0xff or module["size"] < 1:
            raise SystemExit(f"{name}: invalid padding fill or size")
        return bytes([value]) * module["size"]
    if module["kind"] == "asset":
        if assets_dir is None:
            raise SystemExit(f"{name}: pass --assets-dir to rebuild extracted assets")
        source = (assets_dir / module["source"]).resolve()
        if not source.is_relative_to(assets_dir.resolve()) or not source.is_file():
            raise SystemExit(f"{name}: asset source is missing or outside --assets-dir")
        if module["format"] == "font-pgm-4bpp":
            return encode_atlas(source.read_bytes(), module["glyph_count"], module["atlas_columns"])
        if module["format"] == "scene-scripts-json":
            return encode_scene_scripts(load_asset_json(source))
        if module["format"] == "scene-text-json":
            return encode_scene_text(load_asset_json(source))
        if module["format"] == "fixed-text-table-json":
            return encode_fixed_text_table(load_asset_json(source))
        if module["format"] == "fixed-text-page-json":
            return encode_fixed_text_page(load_asset_json(source), module["page_rom_offset"])
        if module["format"] == "ability-list-bank-json":
            return encode_ability_list_bank(load_asset_json(source))
        if module["format"] == "catalog-word-bank-json":
            return encode_catalog_bank(load_asset_json(source), module["bank_id"])
        if module["format"] == "consumer-bounded-table-json":
            return encode_consumer_bounded_table(load_asset_json(source),
                                                 module["table_id"])
        if module["format"] == "consumer-counted-dimension-run-bank-json":
            asset = load_asset_json(source)
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    (asset.get("start"), asset.get("end_exclusive")) !=
                    (module["offset"], module["offset"] + module["size"]) or
                    asset.get("route_catalog_sha256") != module.get("route_catalog_sha256") or
                    asset.get("padding_bytes") != module.get("asset_padding_bytes")):
                raise SystemExit(f"{name}: counted dimension run bank boundary differs")
            return encode_counted_dimension_run_bank(asset, source.parent, reference)
        if module["format"] == "graphics-action-script-bank-json":
            asset = load_asset_json(source)
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    (asset.get("start"), asset.get("end_exclusive")) !=
                    (module["offset"], module["offset"] + module["size"]) or
                    module.get("asset_padding_bytes") != asset.get("padding_bytes")):
                raise SystemExit(f"{name}: graphics action bank boundary differs")
            return encode_graphics_action_bank(asset, source.parent)
        if module["format"] == "nested-counted-palette-bank-json":
            asset = load_asset_json(source)
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    (asset.get("start"), asset.get("end_exclusive")) !=
                    (module["offset"], module["offset"] + module["size"]) or
                    module.get("asset_padding_bytes") != asset.get("padding_bytes")):
                raise SystemExit(f"{name}: nested palette bank boundary differs")
            return encode_nested_counted_palette_bank(asset, source.parent)
        if module["format"] == "coordinate-paths-json":
            asset = load_asset_json(source)
            if (asset.get("start") != module["offset"] or
                    asset.get("end") != module["offset"] + module["size"] or
                    module["asset_padding_bytes"] != 84):
                raise SystemExit(f"{name}: coordinate-path boundary differs")
            return encode_coordinate_paths(asset)
        if module["format"] in ("scene-index-json", "transfer-tile-attributes-json"):
            asset = load_asset_json(source)
            if (asset.get("start") != module["offset"] or
                    asset.get("end") != module["offset"] + module["size"] or
                    asset.get("reference_sha256") != module["reference_sha256"]):
                raise SystemExit(f"{name}: adjacent resource boundary differs")
            if module["format"] == "scene-index-json":
                return encode_scene_index(asset)
            return encode_transfer_tile_attributes(asset)
        if module["format"] == "nested-battle-script-section":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: nested battle-script revision differs")
            sections = encode_nested_battle_script_sections(asset)
            bounds = (module["offset"], module["offset"] + module["size"])
            if bounds not in sections:
                raise SystemExit(f"{name}: nested battle-script section differs")
            return sections[bounds]
        if module["format"] == "object-animation-json":
            asset = load_asset_json(source)
            catalog = load_object_animation_catalog(ROOT / "config/object-animation-roots.json")
            entry = next((root for root in catalog["roots"]
                          if root["start"] == module["offset"]), None)
            if (entry is None or entry["end"] != module["offset"] + module["size"] or
                    module.get("asset_padding_bytes") !=
                    entry["secondary_table_start"] - entry["first_table_end"] or
                    asset.get("reference_sha256") != module["reference_sha256"]):
                raise SystemExit(f"{name}: object animation boundary differs")
            return encode_object_animation_resource(asset, entry)
        if module["format"] == "unclassified-object-animation-json":
            asset = load_asset_json(source)
            catalog = load_asset_json(ROOT / "config/unclassified-object-assets.json")
            entry = next((row for row in catalog["resources"]
                          if row["rom_start"] == module["offset"]), None)
            if (entry is None or entry["build_status"] != "selected" or
                    entry["rom_end_exclusive"] + entry["following_alignment_bytes"] !=
                    module["offset"] + module["size"] or
                    module.get("asset_padding_bytes") !=
                    entry["inter_table_alignment_bytes"] + entry["following_alignment_bytes"] or
                    asset.get("reference_sha256") != module["reference_sha256"]):
                raise SystemExit(f"{name}: unclassified object boundary differs")
            return encode_unclassified_object_animation(asset, entry)
        if module["format"] == "indexed-transfer-tile-bank":
            asset = load_asset_json(source)
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    asset.get("data_start") != module["offset"] or
                    asset.get("data_end") != module["offset"] + module["size"]):
                raise SystemExit(f"{name}: indexed transfer tile boundary differs")
            codec = load_transfer_graphics_codec(ROOT / "tools/indexed_graphics_codec.py")
            return encode_indexed_transfer_tiles(asset, source.parent / "tiles", codec)
        if module["format"] == "u16le-json":
            table = load_asset_json(source)
            values = table["values"]
            if table["rom_offset"] != module["offset"] or len(values) != module["value_count"]:
                raise SystemExit(f"{name}: table offset or value count mismatch")
            if any(type(value) is not int or not 0 <= value <= 0xffff for value in values):
                raise SystemExit(f"{name}: invalid halfword value")
            return struct.pack("<" + "H" * len(values), *values)
        if module["format"] == "text-callback-table-json":
            asset = load_asset_json(source)
            if asset.get("start") != module["offset"] or \
                    asset.get("end") != module["offset"] + module["size"] or \
                    asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: text callback table boundary differs")
            return encode_text_callback_table(asset)
        if module["format"] == "content-word-bank-json":
            asset = load_asset_json(source)
            if (module["offset"] != asset.get("payload_start") or
                    module["offset"] + module["size"] != asset.get("table_end") or
                    module["reference_sha256"] != asset.get("reference_sha256")):
                raise SystemExit(f"{name}: content word bank boundary differs")
            return encode_content_word_bank(asset)
        if module["format"] == "unit-record14-json":
            asset = load_asset_json(source)
            if asset.get("rom_offset") != module["offset"] or \
                    asset.get("entry_count") != module["entry_count"] or \
                    asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: indexed unit-record metadata mismatch")
            return encode_unit_records(asset)
        if module["format"] == "job-definitions-json":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: job-definition revision mismatch")
            return encode_job_definitions(asset)
        if module["format"] == "ability-definitions-json":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: ability-definition revision mismatch")
            return encode_ability_definitions(asset)
        if module["format"] == "item-definitions-json":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: item-definition revision mismatch")
            return encode_item_definitions(asset)
        if module["format"] == "mission-definitions-json":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: mission-definition revision mismatch")
            return encode_mission_definitions(asset)
        if module["format"] in ("equipment-class-masks-json",
                                "mission-property60-rows-json"):
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"] or \
                    asset.get("rom_offset") != module["offset"] or \
                    asset.get("entry_count") != module["entry_count"]:
                raise SystemExit(f"{name}: indexed table metadata differs")
            if module["format"] == "equipment-class-masks-json":
                return encode_equipment_masks(asset)
            return encode_mission_property_rows(asset)
        if module["format"] in ("audio-song-table", "audio-song-header"):
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: audio song revision mismatch")
            if module["format"] == "audio-song-table":
                if (asset["song_table"]["start"] != module["offset"] or
                        asset["song_table"]["end"] !=
                        module["offset"] + module["size"]):
                    raise SystemExit(f"{name}: audio song table boundary differs")
                return encode_song_table(asset)
            header = next((row for row in asset["headers"]
                           if row["start"] == module["offset"]), None)
            if header is None or header["end"] != module["offset"] + module["size"]:
                raise SystemExit(f"{name}: audio song header boundary differs")
            return encode_song_header(asset, module["offset"])
        if module["format"] in ("audio-tone-root", "audio-pcm-bank"):
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: audio tone revision mismatch")
            if module["format"] == "audio-tone-root":
                root = next((row for row in asset["tone_roots"]
                             if row["start"] == module["offset"]), None)
                if root is None or root["end"] != module["offset"] + module["size"]:
                    raise SystemExit(f"{name}: audio tone root boundary differs")
                return encode_tone_root(asset, module["offset"])
            bank = asset["sample_bank"]
            if ((bank["start"], bank["end"]) !=
                    (module["offset"], module["offset"] + module["size"]) or
                    bank["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: audio PCM bank boundary differs")
            return encode_pcm_bank(asset, source.parent)
        if module["format"] == "mp2k-track-region":
            asset = load_asset_json(source)
            if "region" in asset:
                regions = [asset["region"]]
            else:
                regions = asset["regions"]
            matching = [row for row in regions if row["start"] == module["offset"]]
            if len(matching) != 1:
                raise SystemExit(f"{name}: audio track region is absent or ambiguous")
            region = matching[0]
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    (region["start"], region["end"]) !=
                    (module["offset"], module["offset"] + module["size"])):
                raise SystemExit(f"{name}: audio track revision or boundary differs")
            return encode_mp2k_track_region(region)
        if module["format"] == "mp2k-track-span":
            start = module["offset"]
            end = start + module["size"]
            if module["reference_sha256"] != MP2K_ROM_SHA256 or reference is None:
                raise SystemExit(f"{name}: audio sparse track revision differs")
            key = (str(source), input_sha_file(source))
            if key not in SPARSE_REGION_CACHE:
                SPARSE_REGION_CACHE[key] = encode_mp2k_sparse_region(
                    load_asset_json(source), reference)
            try:
                return SPARSE_REGION_CACHE[key][(start, end)]
            except KeyError as error:
                raise SystemExit(f"{name}: audio sparse track span is absent") from error
        if module["format"] == "mp2k-detached-wait-end-tail":
            asset = load_asset_json(source)
            if (reference is None or
                    module["reference_sha256"] != MP2K_ROM_SHA256 or
                    asset.get("reference_sha256") != MP2K_ROM_SHA256 or
                    (asset.get("start"), asset.get("typed_end_exclusive")) !=
                    (module["offset"], module["offset"] + module["size"])):
                raise SystemExit(f"{name}: detached audio tail revision or boundary differs")
            return encode_mp2k_detached_wait_end_tail(asset, reference)
        if module["format"] == "item-ability-sets-json":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: item-ability-set revision mismatch")
            return encode_item_ability_sets(asset)
        if module["format"] == "sprite-frame-bank":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"] or \
                    asset.get("pixel_bank", {}).get("start") != module["offset"] or \
                    asset.get("pixel_bank", {}).get("bytes") != module["size"]:
                raise SystemExit(f"{name}: sprite bank revision or boundaries differ")
            return reconstruct_pixel_bank(asset, source.parent)
        if module["format"] == "sprite-pointer-table":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"] or \
                    asset.get("pointer_block_region", {}).get("start") != module["offset"] or \
                    asset.get("resource_table", {}).get("end") != module["offset"] + module["size"]:
                raise SystemExit(f"{name}: sprite pointer revision or boundaries differ")
            return reconstruct_pointer_table(asset)
        if module["format"] == "sprite-oam-lists":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"] or \
                    asset.get("oam_bank", {}).get("start") != module["offset"] or \
                    asset.get("oam_bank", {}).get("end") != module["offset"] + module["size"] + 4:
                raise SystemExit(f"{name}: sprite OAM revision or boundaries differ")
            return reconstruct_oam_lists(asset)
        if module["format"] == "sprite-descriptor-bank":
            asset = load_asset_json(source)
            descriptor_bank = asset.get("descriptor_bank", {})
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    descriptor_bank.get("start") != module["offset"] or
                    descriptor_bank.get("end") != module["offset"] + module["size"] or
                    descriptor_bank.get("alignment_bytes") != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: sprite descriptor revision or boundaries differ")
            return reconstruct_descriptor_bank(asset)
        if module["format"] in ("a7-item-icons", "a7-roster-thumbnails",
                                "a7-scene-banners"):
            asset = load_asset_json(source)
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    asset.get("archive_file_offset") != module["offset"] or
                    asset.get("archive", {}).get("source_span_bytes") != module["size"]):
                raise SystemExit(f"{name}: A7 archive revision or boundaries differ")
            return encode_indexed_archive(asset, source.parent)
        if module["format"] in ("banner-sprite-table", "banner-frame-table"):
            asset = load_asset_json(source)
            table_name = ("sprite_table" if module["format"] == "banner-sprite-table"
                          else "frame_table")
            table = asset.get(table_name, {})
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    table.get("start") != module["offset"] or
                    table.get("end") != module["offset"] + module["size"]):
                raise SystemExit(f"{name}: banner table revision or boundaries differ")
            return (encode_sprite_table(asset) if table_name == "sprite_table"
                    else encode_frame_table(asset))
        if module["format"] == "map-lzss-stream":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: map graphics revision differs")
            item = map_graphics_entry(asset, module["offset"])
            if item["compressed_bytes"] != module["size"]:
                raise SystemExit(f"{name}: map graphics stream size differs")
            return reconstruct_map_graphics_stream(asset, source.parent, module["offset"])
        if module["format"] == "map-graphics-wrapper":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: map graphics revision differs")
            item = map_graphics_wrapper_entry(asset, module["offset"])
            if item["stream_offset"] - item["wrapper_offset"] != module["size"]:
                raise SystemExit(f"{name}: map wrapper size differs")
            return reconstruct_map_graphics_wrapper(asset, module["offset"])
        if module["format"] == "map-animation-metadata":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: map animation revision differs")
            item = map_animation_entry(asset, module["offset"])
            if item["tiles_offset"] - item["metadata_offset"] != module["size"]:
                raise SystemExit(f"{name}: map animation metadata size differs")
            return reconstruct_map_animation_metadata(asset, module["offset"])
        if module["format"] == "map-animation-tiles":
            asset = load_asset_json(source)
            if asset.get("reference_sha256") != module["reference_sha256"]:
                raise SystemExit(f"{name}: map animation revision differs")
            item = next((item for item in asset["animations"]
                         if item and item["tiles_offset"] == module["offset"]), None)
            if item is None or item["tile_bank_bytes"] != module["size"]:
                raise SystemExit(f"{name}: map animation tile bank size differs")
            return reconstruct_map_animation_tiles(asset, source.parent, module["offset"])
        if module["format"] == "map-layout-source":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["wrapper_offset"] != module["offset"] or
                    asset["source_end"] - asset["wrapper_offset"] != module["size"]):
                raise SystemExit(f"{name}: map layout source revision or boundaries differ")
            return encode_map_layout_source(asset)
        if module["format"] == "map-layout-redirect":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: map layout redirect revision differs")
            records = [record for record in asset["redirect_wrappers"]
                       if record["offset"] == module["offset"]]
            if len(records) != 1 or module["size"] != 4:
                raise SystemExit(f"{name}: map layout redirect boundary differs")
            return encode_map_layout_redirect(records[0])
        if module["format"] == "map-layout-overlay":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["wrapper_offset"] != module["offset"] or
                    asset["source_end"] - asset["wrapper_offset"] != module["size"]):
                raise SystemExit(f"{name}: map redirect overlay revision or boundaries differ")
            return encode_map_layout_overlay(asset)
        if module["format"] == "intro-lzss-stream":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: intro graphics revision differs")
            item = intro_stream_entry(asset, module["offset"])
            if item["consumed_bytes"] != module["size"]:
                raise SystemExit(f"{name}: intro graphics source boundary differs")
            return reconstruct_intro_stream(asset, source.parent, module["offset"])
        if module["format"] == "pointer-custom-lzss-stream":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: pointer custom-LZSS revision differs")
            entry = next((entry for entry in asset["entries"]
                          if entry["start"] == module["offset"]), None)
            if entry is None or entry["encoded_bytes"] != module["size"]:
                raise SystemExit(f"{name}: pointer custom-LZSS boundary differs")
            return encode_pointer_custom_lzss_stream(entry, source.parent)
        if module["format"] == "indexed-custom-lzss-bank":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: indexed custom-LZSS revision differs")
            bank = next((bank for bank in asset["banks"]
                         if bank["start"] == module["offset"]), None)
            if bank is None or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: indexed custom-LZSS bank boundary differs")
            padding = sum(record["padding_bytes"] for record in bank["records"])
            if padding != module["asset_padding_bytes"]:
                raise SystemExit(f"{name}: indexed custom-LZSS padding differs")
            return encode_indexed_custom_lzss_bank(bank, source.parent)
        if module["format"] == "indexed-graphics-archive":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: indexed graphics archive revision or boundary differs")
            return encode_indexed_graphics_archive(asset, source.parent)
        if module["format"] == "indexed-graphics-layout-bank":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: indexed graphics layout revision or boundary differs")
            return encode_indexed_graphics_layout_bank(asset)
        if module["format"] == "indexed-color-rows-bank":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: indexed color rows revision or boundary differs")
            return encode_indexed_color_rows_bank(asset)
        if module["format"] == "indexed-graphics-pair-bank":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: indexed graphics pair revision differs")
            bank = next((bank for pair in asset["pairs"]
                         for bank in (pair["cell_bank"], pair["word_bank"])
                         if bank["start"] == module["offset"]), None)
            if bank is None or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: indexed graphics pair boundary differs")
            padding = sum(2 for record in bank["records"] if "alignment_halfword" in record)
            if padding != module["asset_padding_bytes"]:
                raise SystemExit(f"{name}: indexed graphics pair padding differs")
            return encode_graphics_layout_bank(asset, module["offset"])
        if module["format"] == "graphics-cell-run":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: graphics cell run revision or boundary differs")
            return encode_graphics_cell_run(asset)
        if module["format"] == "direct-graphics-tiles":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: direct graphics tile revision differs")
            bank = next((bank for bank in asset["banks"]
                         if bank["start"] == module["offset"]), None)
            if bank is None or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: direct graphics tile boundary differs")
            return encode_direct_graphics_tiles(asset, module["offset"])
        if module["format"] == "intro-object-tiles-8bpp":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: opening OBJ tile revision or boundary differs")
            return encode_intro_object_tiles(asset, source.parent)
        if module["format"] == "opening-dma-tiles-8bpp":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: opening DMA tile revision or boundary differs")
            return encode_opening_dma_tiles(asset, source.parent)
        if module["format"] == "opening-frame-tiles":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: opening frame tile revision or boundary differs")
            return encode_opening_frame_tiles(asset, source.parent)
        if module["format"] == "opening-tile-attributes":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: opening attribute revision differs")
            entry = next((entry for entry in asset["segments"]
                          if entry["start"] == module["offset"]), None)
            if (entry is None or entry["end"] - entry["start"] != module["size"] or
                    entry["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: opening attribute boundary or padding differs")
            return encode_opening_tile_attributes(asset, source.parent, module["offset"])
        if module["format"] == "world-map-packed-attributes":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: world-map packed attribute boundary differs")
            return encode_world_map_packed_attributes(asset, source.parent)
        if module["format"] in ("indexed-halfword-map-table", "indexed-halfword-map-data"):
            asset = load_asset_json(source)
            start_key, end_key = (("table_start", "table_end") if
                                  module["format"] == "indexed-halfword-map-table" else
                                  ("data_start", "data_end"))
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset[start_key] != module["offset"] or
                    asset[end_key] - asset[start_key] != module["size"]):
                raise SystemExit(f"{name}: indexed halfword map boundary differs")
            if module["format"] == "indexed-halfword-map-table":
                return encode_indexed_halfword_map_table(asset)
            return encode_indexed_halfword_map_data(asset, source.parent)
        if module["format"] in ("graphics-coordinate-points", "graphics-coordinate-directory"):
            asset = load_asset_json(source)
            start_key, end_key = (("points_start", "points_end") if
                                  module["format"] == "graphics-coordinate-points" else
                                  ("directory_start", "directory_end"))
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset[start_key] != module["offset"] or
                    asset[end_key] - asset[start_key] != module["size"]):
                raise SystemExit(f"{name}: graphics coordinate boundary differs")
            if module["format"] == "graphics-coordinate-points":
                return encode_graphics_coordinate_points(asset)
            return encode_graphics_coordinate_directory(asset)
        if module["format"] == "graphics-object-dispatch":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: graphics dispatch boundary differs")
            return encode_graphics_object_dispatch(asset)
        if module["format"] == "object-animation-placement-run":
            asset = load_asset_json(source)
            placement_run = next((entry for entry in asset["runs"]
                                  if entry["start"] == module["offset"]), None)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    placement_run is None or
                    placement_run["end"] - placement_run["start"] != module["size"]):
                raise SystemExit(f"{name}: animation placement boundary differs")
            return encode_object_animation_placement_run(asset, placement_run)
        if module["format"] in ("content-entry-bank", "content-pair-bank",
                                "content-record-bank"):
            asset = load_asset_json(source)
            boundary_keys = {"content-entry-bank": ("entry_start", "entry_end"),
                             "content-pair-bank": ("pair_start", "pair_end"),
                             "content-record-bank": ("record_start", "record_end")}
            start_key, end_key = boundary_keys[module["format"]]
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset[start_key] != module["offset"] or
                    asset[end_key] - asset[start_key] != module["size"]):
                raise SystemExit(f"{name}: content pair/record boundary differs")
            if module["format"] == "content-entry-bank":
                return encode_content_entry_bank(asset, source.parent)
            if module["format"] == "content-pair-bank":
                return encode_content_pair_bank(asset, source.parent)[0]
            return encode_content_record_bank(asset, source.parent)
        if module["format"] in ("opening-residual-maps", "opening-halfword-prefix"):
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: opening residual revision differs")
            if module["format"] == "opening-residual-maps":
                if (asset["small_start"] != module["offset"] or
                        asset["small_end"] - asset["small_start"] != module["size"] or
                        asset["small_padding_bytes"] != module["asset_padding_bytes"]):
                    raise SystemExit(f"{name}: opening residual map boundary differs")
                return encode_opening_residual_maps(asset, source.parent)
            if (asset["prefix_start"] != module["offset"] or
                    asset["prefix_end"] - asset["prefix_start"] != module["size"] or
                    asset["prefix_copy_halfwords"] != 600):
                raise SystemExit(f"{name}: opening halfword prefix boundary differs")
            return encode_opening_halfword_prefix(asset, source.parent)
        if module["format"] == "opening-bg-graphics":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: opening BG revision differs")
            entry = next((entry for entry in asset["segments"]
                          if entry["start"] == module["offset"]), None)
            if entry is None or entry["end"] - entry["start"] != module["size"]:
                raise SystemExit(f"{name}: opening BG segment boundary differs")
            return encode_opening_bg_segment(asset, source.parent, module["offset"])
        if module["format"] == "bg-overlay-banks":
            asset = load_asset_json(source)
            if (asset.get("reference_sha256") != module["reference_sha256"] or
                    asset.get("start") != module["offset"] or
                    asset.get("end") != module["offset"] + module["size"]):
                raise SystemExit(f"{name}: BG overlay revision or boundary differs")
            return encode_bg_overlay_banks(asset, source.parent)
        if module["format"] == "opening-palette-bank":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: opening palette revision or boundary differs")
            return encode_opening_palette_bank(asset, source.parent)
        if module["format"] == "opening-tail-graphics":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: opening tail revision differs")
            entry = next((entry for entry in asset["segments"]
                          if entry["start"] == module["offset"]), None)
            if entry is None or entry["end"] - entry["start"] != module["size"]:
                raise SystemExit(f"{name}: opening tail segment boundary differs")
            return encode_opening_tail_segment(asset, source.parent, module["offset"])
        if module["format"] == "opening-tilemaps":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: opening tilemap revision or boundary differs")
            return encode_opening_tilemap_run(asset, source.parent)
        if module["format"] in ("opening-indexed-map-table", "opening-indexed-maps"):
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: opening indexed-map revision differs")
            if module["format"] == "opening-indexed-map-table":
                if (asset["table_start"] != module["offset"] or
                        asset["table_end"] - asset["table_start"] != module["size"]):
                    raise SystemExit(f"{name}: opening indexed-map table boundary differs")
                return encode_opening_indexed_map_table(asset)
            if (asset["map_start"] != module["offset"] or
                    asset["map_end"] - asset["map_start"] != module["size"]):
                raise SystemExit(f"{name}: opening indexed-map run boundary differs")
            return encode_opening_indexed_maps(asset, source.parent)
        if module["format"] == "direct-graphics-palettes":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: direct graphics palette revision differs")
            bank = next((bank for bank in asset["banks"]
                         if bank["start"] == module["offset"]), None)
            if bank is None or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: direct graphics palette boundary differs")
            return encode_direct_graphics_palettes(asset, module["offset"])
        if module["format"] == "graphics-palette-run":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: graphics palette run revision or boundary differs")
            return encode_graphics_palette_run(asset)
        if module["format"] == "graphics-word-run":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: graphics word run revision or boundary differs")
            return encode_graphics_word_run(asset)
        if module["format"] == "indexed-tile-frames":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"]):
                raise SystemExit(f"{name}: indexed tile frames revision or boundary differs")
            return encode_indexed_tile_frames(asset)
        if module["format"] == "a7-graphics-batch":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: A7 graphics batch revision or boundary differs")
            return encode_a7_graphics_batch(asset, source.parent)
        if module["format"] == "font-widths":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    module["asset_padding_bytes"] != 1):
                raise SystemExit(f"{name}: font width revision or boundary differs")
            return encode_font_widths(asset)
        if module["format"] == "item-icon-index-fields":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["record_count"] != 522):
                raise SystemExit(f"{name}: item icon field revision or boundary differs")
            return encode_item_icon_index_fields(asset)
        if module["format"] == "item-graphics-followup":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["padding_bytes"] != module["asset_padding_bytes"] or
                    asset["entry_count"] != 563):
                raise SystemExit(f"{name}: item graphics follow-up revision or boundary differs")
            return encode_item_graphics_followup(asset, source.parent)
        if module["format"] == "interleaved-a7-graphics":
            asset = load_asset_json(source)
            item = interleaved_a7_bank_entry(asset, module["offset"])
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    item["end"] - item["start"] != module["size"] or
                    item["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: interleaved A7 revision or boundary differs")
            return encode_interleaved_a7_bank(asset, source.parent, module["offset"])
        if module["format"] == "interleaved-graphics-index":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["record_count"] != 45):
                raise SystemExit(f"{name}: interleaved graphics index revision or boundary differs")
            return encode_interleaved_graphics_index(asset)
        if module["format"] == "indexed-palette-blocks":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["block_count"] != 6):
                raise SystemExit(f"{name}: indexed palette revision or boundary differs")
            return encode_indexed_palette_blocks(asset)
        if module["format"] == "pointer-a7-graphics":
            asset = load_asset_json(source)
            item = pointer_a7_bank_entry(asset, module["offset"])
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    item["end"] - item["start"] != module["size"] or
                    item["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: pointer-backed A7 revision or boundary differs")
            return encode_pointer_a7_bank(asset, source.parent, module["offset"])
        if module["format"] == "intro-palette":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: intro palette revision differs")
            events = [event for event in asset.get("palette_events", [])
                      if event["source_rom_offset"] == module["offset"]]
            if len(events) != 1 or events[0]["byte_count"] != module["size"]:
                raise SystemExit(f"{name}: intro palette source boundary differs")
            return reconstruct_intro_palette(asset, module["offset"])
        if module["format"] == "map-table-json":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["rom_offset"] != module["offset"] or
                    asset["record_count"] * asset["record_bytes"] != module["size"]):
                raise SystemExit(f"{name}: map table revision or boundary differs")
            return encode_map_table(asset)
        if module["format"] == "map-secondary-animation-bank":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: secondary animation revision differs")
            bank = secondary_animation_entry(asset, module["offset"])
            if bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: secondary animation bank boundary differs")
            return reconstruct_secondary_animation_bank(asset, source.parent, module["offset"])
        if module["format"] == "bios-lz77-vram-graphics":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: VRAM graphics revision differs")
            entry = vram_graphics_entry(asset, module["offset"])
            if entry["encoded_bytes"] != module["size"]:
                raise SystemExit(f"{name}: VRAM graphics source boundary differs")
            return reconstruct_vram_graphics_stream(asset, source.parent, module["offset"])
        if module["format"] in ("world-map-palette-table", "world-map-palette-bank"):
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: world-map palette revision differs")
            bank = asset["pointer_table"] if module["format"] == "world-map-palette-table" else asset["palette_bank"]
            if bank["start"] != module["offset"] or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: world-map palette source boundary differs")
            return (encode_palette_table(asset) if module["format"] == "world-map-palette-table"
                    else encode_palette_bank(asset))
        if module["format"] in ("world-map-overlay-table", "world-map-overlay-bank"):
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: world-map overlay revision differs")
            bank = asset["pointer_table"] if module["format"] == "world-map-overlay-table" else asset["overlay_bank"]
            if bank["start"] != module["offset"] or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: world-map overlay source boundary differs")
            return (encode_overlay_table(asset) if module["format"] == "world-map-overlay-table"
                    else encode_overlay_bank(asset))
        if module["format"] in ("world-map-display-source", "world-map-display-fragment",
                                 "world-map-display-palette-bank", "world-map-display-palette-table"):
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: world-map display revision differs")
            if module["format"] in ("world-map-display-source", "world-map-display-fragment"):
                entry = next((entry for entry in asset["sources"]
                              if entry["start"] == module["offset"]), None)
                if entry is None and module["format"] == "world-map-display-fragment":
                    entry = next((entry for entry in asset["sources"]
                                  if entry["start"] < module["offset"] < entry["start"] + entry["size"]), None)
                if entry is None or (module["format"] == "world-map-display-source" and
                                     (entry["start"] != module["offset"] or entry["size"] != module["size"])) or (
                        module["format"] == "world-map-display-fragment" and
                        not ((entry["start"], module["offset"], module["size"], entry["size"]) in
                             ((0x9569ac, 0x9569ac, 8, 32),
                              (0x960ec0, 0x960ec0, 0x3978, 0x39a8),
                              (0x9675ac, 0x9675b0, 0x2bfc, 0x2cb4)))):
                    raise SystemExit(f"{name}: world-map display source boundary differs")
                data = encode_display_source(asset, source.parent, entry["start"])
                start = module["offset"] - entry["start"]
                return data[start:start + module["size"]]
            bank = asset["palette_table"] if module["format"] == "world-map-display-palette-table" else asset["palette_bank"]
            if bank["start"] != module["offset"] or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: world-map display palette boundary differs")
            return (encode_display_palette_table(asset) if module["format"] == "world-map-display-palette-table"
                    else encode_display_palette_bank(asset, source.parent))
        if module["format"] == "direct-tilemap-run":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: direct tilemap revision differs")
            entry = next((entry for entry in asset["copies"] if entry["start"] == module["offset"]), None)
            if entry is None or entry["end"] - entry["start"] != module["size"]:
                raise SystemExit(f"{name}: direct tilemap source boundary differs")
            return encode_direct_tilemap_run(asset, module["offset"])
        if module["format"] == "graphics-layout-bank":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: graphics layout revision differs")
            entry = next((bank for pair in asset["pairs"] for bank in
                          (pair["cell_bank"], pair["word_bank"]) if bank["start"] == module["offset"]), None)
            if entry is None or entry["end"] - entry["start"] != module["size"]:
                raise SystemExit(f"{name}: graphics layout bank boundary differs")
            return encode_graphics_layout_bank(asset, module["offset"])
        if module["format"] == "opening-layout-banks":
            asset = load_asset_json(source)
            if (asset["reference_sha256"] != module["reference_sha256"] or
                    asset["start"] != module["offset"] or
                    asset["end"] - asset["start"] != module["size"] or
                    asset["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: opening layout revision or boundary differs")
            return encode_opening_layout_run(asset)
        if module["format"] == "graphics-embedded-layout-bank":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: embedded graphics layout revision differs")
            bank = next((bank for pair in asset["pairs"]
                         for bank in (pair["cell_bank"], pair["word_bank"])
                         if bank["start"] == module["offset"]), None)
            if bank is None or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: embedded graphics layout boundary differs")
            padding = sum("alignment_halfword" in record for record in bank["records"]) * 2
            if padding != module["asset_padding_bytes"]:
                raise SystemExit(f"{name}: embedded graphics layout padding differs")
            return encode_graphics_layout_bank(asset, module["offset"])
        if module["format"] == "graphics-palette-bank":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: graphics palette revision differs")
            bank = asset["bank"]
            if bank["start"] != module["offset"] or bank["end"] - bank["start"] != module["size"]:
                raise SystemExit(f"{name}: graphics palette bank boundary differs")
            return encode_graphics_palette_bank(asset)
        if module["format"] == "pointer-lz77-record-run":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: pointer-backed archive revision differs")
            record_run = pointer_record_run_entry(asset, module["offset"])
            if (record_run["end"] - record_run["start"] != module["size"] or
                    record_run["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: pointer-backed archive boundary differs")
            return reconstruct_pointer_record_run(asset, source.parent, module["offset"])
        if module["format"] == "pointer-raw-record-gap":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: raw record revision differs")
            record_gap = pointer_raw_gap_entry(asset, module["offset"])
            if (record_gap["end"] - record_gap["start"] != module["size"] or
                    record_gap["leading_padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: raw record gap boundary differs")
            return reconstruct_pointer_raw_gap(asset, source.parent, module["offset"])
        if module["format"] == "graphics-action-fragment":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: graphics action revision differs")
            fragment = graphics_action_fragment_entry(asset, module["offset"])
            if fragment["size"] != module["size"]:
                raise SystemExit(f"{name}: graphics action fragment boundary differs")
            return reconstruct_graphics_action_fragment(asset, source.parent, module["offset"])
        if module["format"] == "graphics-nested-action-prefix":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: nested graphics action revision differs")
            entry = next((entry for entry in asset["entries"]
                          if entry["start"] == module["offset"]), None)
            if entry is None or entry["end"] - entry["start"] != module["size"]:
                raise SystemExit(f"{name}: nested graphics action boundary differs")
            return encode_graphics_nested_action_prefix(entry, source.parent)
        if module["format"] == "graphics-frame-record":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: graphics frame revision differs")
            record = graphics_frame_record_entry(asset, module["offset"])
            if (record["selected_bytes"] != module["size"] or
                    record["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: graphics frame record boundary differs")
            return reconstruct_graphics_frame_record(asset, source.parent, module["offset"])
        if module["format"] == "graphics-nested-frame-root":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: nested graphics frame revision differs")
            entry = next((entry for entry in asset["entries"]
                          if entry["start"] == module["offset"]), None)
            if entry is None or entry["end"] - entry["start"] != module["size"]:
                raise SystemExit(f"{name}: nested graphics frame boundary differs")
            return encode_graphics_nested_frame_root(entry, source.parent)
        if module["format"] == "graphics-sample-tail":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: graphics sample tail revision differs")
            entry = next((entry for entry in asset["entries"]
                          if entry["start"] == module["offset"]), None)
            if (entry is None or entry["end"] - entry["start"] != module["size"] or
                    entry["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: graphics sample tail boundary differs")
            return encode_graphics_sample_tail(entry, source.parent)
        if module["format"] == "pointer-palette-group":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: counted palette revision differs")
            group = pointer_palette_group_entry(asset, module["offset"])
            if (group["end"] - group["start"] != module["size"] or
                    group["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: counted palette group boundary differs")
            return reconstruct_pointer_palette_group(asset, source.parent, module["offset"])
        if module["format"] == "graphics-container-root":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: graphics container revision differs")
            root = graphics_container_root_entry(asset, module["offset"])
            if (root["end"] - root["start"] != module["size"] or
                    root["padding_bytes"] != module["asset_padding_bytes"]):
                raise SystemExit(f"{name}: graphics container boundary differs")
            return reconstruct_graphics_container_root(asset, source.parent, module["offset"])
        if module["format"] == "graphics-run-record":
            asset = load_asset_json(source)
            if asset["reference_sha256"] != module["reference_sha256"]:
                raise SystemExit(f"{name}: graphics run revision differs")
            record = next((record for record in asset["records"]
                           if record["start"] == module["offset"]), None)
            if record is None or record["end"] - record["start"] != module["size"]:
                raise SystemExit(f"{name}: graphics run boundary differs")
            return encode_graphics_run_record(record, source.parent)
        raise SystemExit(f"{name}: unknown asset format")
    if module["kind"] not in ("c", "mixed", "assembly"):
        raise SystemExit(f"{name}: unknown module kind")
    source = ROOT / module["source"]
    assembler = shutil.which("arm-none-eabi-as")
    linker = shutil.which("arm-none-eabi-ld")
    objcopy = shutil.which("arm-none-eabi-objcopy")
    if not all((assembler, linker, objcopy)):
        raise SystemExit("Install arm-none-eabi-binutils before building")
    asm = work / (name + ".s")
    if module["kind"] in ("c", "mixed"):
        compiler = BUILD_ROOT / "toolchain/agbcc"
        if not compiler.exists():
            raise SystemExit("Run python3 tools/bootstrap.py first")
        preprocessed = work / (name + ".i")
        flags = module.get("compiler_flags", ["-O0", "-mthumb-interwork"])
        preprocessor_flags = [flag for flag in flags if flag.startswith("-D") or flag.startswith("-U")]
        timed("preprocessing", lambda: run(
            [*c_preprocessor_command(module, source), "-o", str(preprocessed)]))
        compiler_flags = [flag for flag in flags if flag not in preprocessor_flags]
        timed("agbcc", lambda: run(
            [str(compiler), *compiler_flags, str(preprocessed), "-o", str(asm)]))
        if module.get("compiler_data_policy") is not None:
            normalized, evidence = normalize_compiler_switch_literal(
                asm.read_text(), module["compiler_data_policy"])
            shutil.copyfile(asm, work / (name + ".compiler-original.s"))
            asm.write_text(normalized)
            (work / (name + ".compiler-data.json")).write_text(
                json.dumps(evidence, indent=2) + "\n")
    else:
        asm = source
    obj = work / (name + ".o")
    elf = work / (name + ".elf")
    binary = work / (name + ".bin")
    timed("assembly", lambda: run(
        [assembler, "-mcpu=arm7tdmi", "-mthumb-interwork", str(asm), "-o", str(obj)]))
    link_objects = [str(obj)]
    if module.get("external_symbols", module["kind"] in ("c", "mixed")):
        external_obj = work / (name + "_external.o")
        excluded = module.get("external_exclude_symbols", [])
        external_flags = []
        for symbol in excluded:
            if not symbol.isidentifier():
                raise SystemExit(f"{name}: invalid external symbol exclusion")
            external_flags.extend(["--defsym", "OMIT_" + symbol + "=1"])
        timed("external_object", lambda: assemble_external_symbols(
            assembler, ROOT / "asm/external_thumb_symbols.s", external_obj,
            ["-mcpu=arm7tdmi", "-mthumb-interwork", *external_flags], tool_cache_dir))
        link_objects.append(str(external_obj))
    timed("linking", lambda: run(
        [linker, "-T", str(ROOT / "config/symbols.ld"), "-Ttext", hex(base + module["offset"]),
         *link_objects, "-o", str(elf)]))
    timed("elf_validation", lambda: validate_elf_load_sections(elf))
    timed("extraction", lambda: run(
        [objcopy, "-O", "binary", "-j", ".text", str(elf), str(binary)]))
    generated = binary.read_bytes()
    trailing_alignment_bytes = module.get("trailing_alignment_bytes", 0)
    if trailing_alignment_bytes:
        if not isinstance(trailing_alignment_bytes, int) or trailing_alignment_bytes < 1:
            raise SystemExit(f"{name}: invalid trailing alignment byte count")
        if len(generated) <= trailing_alignment_bytes:
            raise SystemExit(f"{name}: trailing alignment consumes module")
        generated = generated[:-trailing_alignment_bytes]
    return generated


def verified_linker_veneers(module, work, rom_base):
    """Accept only pinned ARMv4T Thumb absolute-call thunks generated by ld."""
    policy = module.get("linker_veneer_policy")
    if policy is None:
        return []
    if policy != "armv4t-thumb-absolute-v1" or module["kind"] not in ("c", "mixed"):
        raise SystemExit(f"{module['name']}: unsupported linker veneer policy")
    name = module["name"]
    def nm(path):
        result = {}
        for line in subprocess.check_output(["arm-none-eabi-nm", "-n", str(path)], text=True).splitlines():
            fields = line.split()
            if len(fields) == 3:
                result[fields[2]] = (int(fields[0], 16), fields[1])
        return result
    linked = nm(work / (name + ".elf"))
    obj = nm(work / (name + ".o"))
    header = subprocess.check_output(["arm-none-eabi-objdump", "-h", str(work / (name + ".o"))], text=True)
    text_size = next((int(row.split()[2], 16) for row in header.splitlines()
                      if len(row.split()) >= 3 and row.split()[1] == ".text"), None)
    if text_size is None:
        raise SystemExit(f"{name}: object text section is missing")
    with tempfile.TemporaryDirectory(prefix="veneer-check-", dir=work) as temp:
        binary = Path(temp) / "text.bin"
        run(["arm-none-eabi-objcopy", "-O", "binary", "-j", ".text", str(work / (name + ".elf")), str(binary)])
        data = binary.read_bytes()
    start = rom_base + module["offset"]
    prefix = bytes.fromhex("7847fde700c09fe51cff2fe1")
    result, spans = [], []
    for symbol, (address, kind) in linked.items():
        if kind not in ("T", "t") or not symbol.startswith("__") or not symbol.endswith("_veneer"):
            continue
        target_name = symbol[2:-7]
        target = linked.get(target_name)
        offset = address - start
        if (symbol in obj or target_name in {key for key, value in obj.items() if value[1] in ("T", "t")} or
                target is None or target[1] not in ("A", "T", "t") or
                not rom_base <= target[0] < rom_base + 0x1000000 or
                address & 3 or offset < text_size or offset + 16 > len(data) or
                offset + 16 > module["size"] or data[offset:offset + 12] != prefix or
                int.from_bytes(data[offset + 12:offset + 16], "little") != (target[0] | 1) or
                any(address < end and begin < address + 16 for begin, end in spans)):
            raise SystemExit(f"{name}: unsupported or malformed linker veneer {symbol}")
        spans.append((address, address + 16))
        result.append({"symbol": symbol, "gba_address": address, "size": 16,
                       "target_symbol": target_name, "target_thumb_entry": target[0] | 1,
                       "instruction_bytes": 12, "literal_bytes": 4})
    return sorted(result, key=lambda row: row["gba_address"])


def check_linked_function_entries(module, work, rom_base):
    """Reject shifted entries or undeclared code inside a compiled C module."""
    functions = module.get("functions", [{"name": module["name"],
                                          "offset": module["offset"],
                                          "size": module["size"]}])
    expected = {function.get("link_symbol", module.get("link_symbol", function["name"])):
                rom_base + function["offset"]
                for function in functions
                if not function["name"].startswith("Compiler")}
    output = subprocess.check_output(
        ["arm-none-eabi-nm", "-n", str(work / (module["name"] + ".elf"))],
        text=True)
    symbols = {}
    text_symbols = []
    for line in output.splitlines():
        fields = line.split()
        if len(fields) != 3:
            continue
        address, kind, name = fields
        value = int(address, 16)
        symbols[name] = (value, kind)
        if kind in ("T", "t"):
            if name != ".gcc2_compiled.":
                text_symbols.append((name, value))
    object_output = subprocess.check_output(
        ["arm-none-eabi-nm", "-n", str(work / (module["name"] + ".o"))],
        text=True)
    object_text_symbols = {}
    for line in object_output.splitlines():
        fields = line.split()
        if len(fields) == 3 and fields[1] in ("T", "t"):
            object_text_symbols[fields[2]] = int(fields[0], 16)
    for name, address in expected.items():
        linked = symbols.get(name)
        relative = address - rom_base - module["offset"]
        # A linker-script absolute alias can override an object text symbol.
        # Require the compiled object's text entry at the same relative offset.
        valid = (linked is not None and linked[0] == address and
                 ((linked[1] in ("T", "t")) or
                  (linked[1] == "A" and object_text_symbols.get(name) == relative)))
        if not valid:
            actual = linked[0] if linked is not None else None
            raise SystemExit(f"{module['name']}: {name} linked at "
                             f"{hex(actual) if actual is not None else 'missing'}, "
                             f"expected {hex(address)}")
    valid_addresses = set(expected.values())
    valid_addresses.update(row["gba_address"] for row in
                           verified_linker_veneers(module, work, rom_base))
    for name, address in text_symbols:
        if address not in valid_addresses:
            raise SystemExit(f"{module['name']}: undeclared code symbol "
                             f"{name} at {hex(address)}")
    return len(expected)


def dependency_revision(directory):
    """Source exports can retain their immutable upstream revision without .git."""
    marker = directory / "SOURCE_REVISION"
    if marker.is_file():
        revision = marker.read_text().strip()
        if not re.fullmatch(r"[0-9a-f]{40}", revision):
            raise ValueError("Invalid dependency source revision marker")
        return revision
    return subprocess.check_output(
        ["git", "-C", str(directory), "rev-parse", "HEAD"], text=True).strip()


def main():
    global INPUT_SESSION, ROOT, BUILD_ROOT
    previous_root, previous_build_root = ROOT, BUILD_ROOT
    previous_footprint_dir = ASSET_JSON_CACHE.footprint_dir
    previous_session = INPUT_SESSION
    session = BuildInputSession()
    INPUT_SESSION = session
    try:
        return _main_with_input_session()
    finally:
        INPUT_SESSION = previous_session
        ROOT, BUILD_ROOT = previous_root, previous_build_root
        ASSET_JSON_CACHE.footprint_dir = previous_footprint_dir
        session.close()


def _main_with_input_session():
    global ROOT, BUILD_ROOT
    build_started = time.perf_counter()
    stage_timings = {}
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--input", required=True, type=Path, help="User-supplied reference ROM")
    p.add_argument("--config", required=True, type=Path, help="Revision-specific manifest")
    p.add_argument("--output", required=True, type=Path, help="External output ROM path")
    p.add_argument("--report", required=True, type=Path, help="External JSON report path")
    p.add_argument("--assets-dir", type=Path, help="External decoded asset source directory")
    p.add_argument("--no-cache", action="store_true", help="Recompile all modules instead of using build/module-cache")
    p.add_argument("--extension-config", type=Path,
                   help="Explicit optional source/resource extension manifest (no recovery credit)")
    p.add_argument("--project-root", type=Path, help="Explicit read-only source project using this toolkit")
    p.add_argument("--build-dir", type=Path, help="External compiler/cache/generated-header directory")
    args = p.parse_args()
    if args.project_root is not None:
        ROOT = args.project_root.resolve()
        if not (ROOT / "config/symbols.ld").is_file():
            raise SystemExit("Project root has no config/symbols.ld")
    BUILD_ROOT = args.build_dir.resolve() if args.build_dir is not None else ROOT / "build"
    ASSET_JSON_CACHE.footprint_dir = BUILD_ROOT / "json-footprints"
    if not args.input.is_file() or len({args.input.resolve(), args.output.resolve(), args.report.resolve()}) != 3:
        raise SystemExit("Input must exist; input, output, and report must be distinct paths")
    if args.output.resolve().is_relative_to(ROOT) or args.report.resolve().is_relative_to(ROOT):
        raise SystemExit("ROM and report paths must be outside the source tree")
    if args.assets_dir and args.assets_dir.resolve().is_relative_to(ROOT):
        raise SystemExit("Asset sources must be outside the source tree")
    ASSET_JSON_CACHE.clear()
    SPARSE_REGION_CACHE.clear()
    config_digest = input_sha_file(args.config)
    config_bytes = args.config.read_bytes()
    if sha(config_bytes) != config_digest:
        raise SystemExit("Manifest changed while reading")
    config = json.loads(config_bytes)
    reference = args.input.read_bytes()
    if len(reference) != config["size"] or sha(reference) != config["sha256"]:
        raise SystemExit("Input revision mismatch: refusing to compile against a different ROM")
    configured_modules = sorted(config["modules"], key=lambda m: m["offset"])
    last = 0
    for m in configured_modules:
        if m["offset"] < last or m["offset"] + m["size"] > len(reference):
            raise SystemExit("Invalid or overlapping module range")
        last = m["offset"] + m["size"]
    modules = [m for m in configured_modules if m.get("enabled", True)]
    # Reject malformed selected metadata before preprocessing, cache creation,
    # asset generation or compilation of any otherwise-valid earlier module.
    for module in modules:
        validate_function_ranges(module, module["size"])
    write_asset_addresses(config, BUILD_ROOT / "generated/asset_addresses.h", build_root=BUILD_ROOT)
    work = BUILD_ROOT / "match"
    work.mkdir(parents=True, exist_ok=True)
    cache_dir = BUILD_ROOT / "module-cache"
    tool_cache_dir = BUILD_ROOT / "local-tool-cache"
    cache_context = None if args.no_cache else build_cache_context()
    built = bytearray(reference)
    found = []
    linked_function_entries = 0
    module_cache_hits = 0
    module_cache_misses = 0
    linked_entry_cache_hits = 0
    for m in modules:
        try:
            validate_source_mix(m)
        except ValueError as error:
            raise SystemExit(str(error)) from error
        asset_padding = m.get("asset_padding_bytes", 0)
        if (not isinstance(asset_padding, int) or asset_padding < 0 or
                asset_padding > m["size"] or
                (asset_padding and m["kind"] != "asset")):
            raise SystemExit(f"{m['name']}: invalid asset padding byte count")
        if args.no_cache:
            data = compile_module(m, work, config["rom_base"], args.assets_dir,
                                  reference, stage_timings=stage_timings)
            cache_hit = False
            cache_key = None
        else:
            data, cache_hit, cache_key = compile_module_cached(
                m, work, config["rom_base"], args.assets_dir, config, cache_dir,
                cache_context, reference, tool_cache_dir=tool_cache_dir,
                stage_timings=stage_timings, materialize_link_artifacts=False)
            module_cache_hits += cache_hit
            module_cache_misses += not cache_hit
        if m["kind"] in ("c", "mixed"):
            if cache_hit:
                checked_entries = module_linked_entry_count(m)
                linked_entry_cache_hits += checked_entries
            else:
                checked_entries = check_linked_function_entries(
                    m, work, config["rom_base"])
                if not args.no_cache:
                    cache_linked_entry_validation(cache_dir, cache_key, checked_entries)
            linked_function_entries += checked_entries
        offset = m["offset"]
        target = reference[offset:offset + m["size"]]
        policy = m.get("match_policy", "exact")
        if policy not in ("exact", "allow-differences") or (policy == "allow-differences" and m["kind"] not in ("c", "mixed")):
            raise SystemExit(f"{m['name']}: invalid match policy")
        if len(data) != len(target):
            raise SystemExit(f"{m['name']}: size {len(data)} != expected {len(target)}")
        differences = [{"rom_offset": offset + i, "reference_byte": a, "generated_byte": b}
                       for i, (a, b) in enumerate(zip(target, data)) if a != b]
        if differences and policy == "exact":
            raise SystemExit(f"{m['name']}: first mismatch at ROM offset 0x{differences[0]['rom_offset']:08x}")
        if policy == "allow-differences" and not differences:
            raise SystemExit(f"{m['name']}: matching C span must use exact match policy")
        if policy == "allow-differences" and differences != m.get("expected_differences"):
            raise SystemExit(f"{m['name']}: generated differences do not match the pinned manifest")
        function_records = []
        if m["kind"] in ("c", "mixed"):
            for function in validate_function_ranges(m, len(data)):
                start = function["offset"]
                end = start + function["size"]
                generated = data[start - offset:end - offset]
                original = reference[start:end]
                function_records.append({"name": function["name"], "rom_offset": start,
                                         "size": len(generated), "sha256": sha(generated),
                                         "exact_binary_match": generated == original,
                                         "matching_bytes": sum(a == b for a, b in zip(generated, original))})
        built[offset:offset + len(data)] = data
        found.append({"name": m["name"], "kind": m["kind"], "rom_offset": offset,
                      "gba_address": hex(config["rom_base"] + offset), "size": len(data),
                      "sha256": sha(data), "exact_binary_match": not differences,
                      "assembly_and_literals_match": not differences if m["kind"] in ("c", "mixed", "assembly") else None,
                      "match_policy": policy, "matching_bytes": len(data) - len(differences),
                      "compiler_flags": m.get("compiler_flags", []) if m["kind"] in ("c", "mixed") else [],
                      "inline_assembly_bytes": m.get("inline_assembly_bytes", 0),
                      "component": m.get("component"),
                      "assembly_ratio_exception": m.get("assembly_ratio_exception"),
                      "differing_bytes": differences,
                      "instructions_bytes": m.get("instructions_bytes", 0),
                      "literal_bytes": m.get("literal_bytes", 0), "padding_bytes": m.get("padding_bytes", 0),
                      "asset_padding_bytes": asset_padding,
                      "compiler_data_normalization": (
                          json.loads((work / (m["name"] + ".compiler-data.json")).read_text())
                          if m.get("compiler_data_policy") else None),
                      "linker_veneers": verified_linker_veneers(m, work, config["rom_base"]),
                      "functions": function_records})
    recovered_c = sum(m["size"] for m in found if m["kind"] == "c" and not m["differing_bytes"])
    nonmatching_c = sum(m["size"] for m in found if m["kind"] == "c" and m["differing_bytes"])
    mixed = sum(m["size"] for m in found if m["kind"] == "mixed")
    mixed_assembly = sum(m["inline_assembly_bytes"] for m in found if m["kind"] == "mixed")
    mixed_instructions = sum(m["instructions_bytes"] for m in found if m["kind"] == "mixed")
    assembly = sum(m["size"] for m in found if m["kind"] == "assembly")
    assets = sum(m["size"] - m["asset_padding_bytes"] for m in found if m["kind"] == "asset")
    padding = (sum(m["size"] for m in found if m["kind"] == "padding") +
               sum(m["asset_padding_bytes"] for m in found))
    original = len(reference) - recovered_c - nonmatching_c - mixed - assembly - assets - padding
    function_bodies = [f for m in found if m["kind"] == "c" for f in m["functions"]
                       if not f["name"].startswith("Compiler")]
    if not nonmatching_c and sha(built) != config["sha256"]:
        raise SystemExit("Built ROM differs from the pinned reference")
    report = {"input_variant": config["id"], "input_sha256": config["sha256"],
              "output_sha256": sha(built), "size": len(built),
              "toolchain": {
                  "agbcc_revision": dependency_revision(ROOT / "vendor/agbcc"),
                  "clang": version_line(["clang", "--version"]),
                  "assembler": version_line([shutil.which("arm-none-eabi-as"), "--version"]),
                  "linker": version_line([shutil.which("arm-none-eabi-ld"), "--version"]),
                  "objcopy": version_line([shutil.which("arm-none-eabi-objcopy"), "--version"]),
                  "python": sys.version.splitlines()[0],
                  "platform": platform.platform(),
              },
              "recovered_c_bytes": recovered_c, "assembly_fallback_bytes": assembly,
              "linker_generated_veneer_bytes": sum(v["size"] for m in found for v in m["linker_veneers"]),
              "mixed_c_span_bytes": mixed, "mixed_c_functions": sum(
                  1 for m in found if m["kind"] == "mixed" for f in m["functions"]
                  if not f["name"].startswith("Compiler")),
              "mixed_inline_assembly_bytes": mixed_assembly,
              "mixed_instruction_bytes": mixed_instructions,
              "mixed_inline_assembly_ratio": (mixed_assembly / mixed_instructions
                                              if mixed_instructions else 0),
              "reconstructed_asset_bytes": assets, "reconstructed_padding_bytes": padding,
              "nonmatching_c_bytes": nonmatching_c,
              "nonmatching_c_matched_bytes": sum(m["matching_bytes"] for m in found if m["kind"] == "c" and m["differing_bytes"]),
              "nonmatching_c_differing_bytes": sum(len(m["differing_bytes"]) for m in found if m["kind"] == "c"),
              "original_byte_inclusion_bytes": original,
              "original_byte_inclusion_classification": "unclassified_code_data_assets_padding",
              "remaining_executable_bytes": None,
              "recovered_c_functions": sum(f["exact_binary_match"] for f in function_bodies),
              "nonmatching_c_functions": sum(not f["exact_binary_match"] for f in function_bodies),
              "linked_function_entries_checked": linked_function_entries,
              "linked_entry_validation_cache_hits": linked_entry_cache_hits,
              "module_cache_hits": module_cache_hits,
              "module_cache_misses": module_cache_misses,
              "reconstructed_asset_modules": sum(m["kind"] == "asset" for m in found),
              "modules": found,
              "disabled_modules": [m["name"] for m in configured_modules if not m.get("enabled", True)],
              "unmatched_regions": []}
    cursor = 0
    for m in modules:
        if m["offset"] > cursor:
            report["unmatched_regions"].append({"start": cursor, "end_exclusive": m["offset"], "size": m["offset"] - cursor})
        cursor = m["offset"] + m["size"]
    if cursor < len(reference):
        report["unmatched_regions"].append({"start": cursor, "end_exclusive": len(reference), "size": len(reference) - cursor})
    started = time.perf_counter()
    INPUT_SESSION.verify()
    add_stage_time(stage_timings, "input_revalidation", started)
    started = time.perf_counter()
    INPUT_SESSION.publish()
    add_stage_time(stage_timings, "cache_receipt_publication", started)
    report["build_performance"] = {
        "schema": "production-throughput-v1",
        "stage_seconds": stage_timings,
        "elapsed_before_publication_seconds": time.perf_counter() - build_started,
        "input_fingerprints": dict(INPUT_SESSION.stats),
        "asset_json": {**ASSET_JSON_CACHE.stats,
                       "retained_bytes": ASSET_JSON_CACHE.bytes,
                       "budget_bytes": ASSET_JSON_CACHE.max_bytes,
                       "retained_entries": len(ASSET_JSON_CACHE.entries)},
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.report.parent.mkdir(parents=True, exist_ok=True)
    if args.extension_config is not None:
        from build_extensions import apply_extensions

        def compile_extension(module):
            work = args.report.parent / "extension-modules" / module["name"]
            work.mkdir(parents=True, exist_ok=False)
            data = compile_module(module, work, config["rom_base"], args.assets_dir,
                                  reference=reference)
            if module["kind"] in ("c", "mixed"):
                check_linked_function_entries(module, work, config["rom_base"])
            return data

        baseline_report = report
        built, extension_report = apply_extensions(
            built, reference, config, args.extension_config, compile_extension)
        report = {"build_mode": "optional-extension", "input_sha256": sha(reference),
                  "output_sha256": sha(built), "size": len(built),
                  "recovery_credit_eligible": False, "baseline_build": baseline_report,
                  "extension": extension_report}
    args.output.write_bytes(built)
    args.report.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({k: report[k] for k in ("output_sha256", "build_mode", "recovery_credit_eligible", "recovered_c_bytes", "nonmatching_c_bytes", "nonmatching_c_differing_bytes", "mixed_c_span_bytes", "mixed_c_functions", "mixed_inline_assembly_bytes", "assembly_fallback_bytes", "reconstructed_asset_bytes", "reconstructed_padding_bytes", "original_byte_inclusion_bytes", "recovered_c_functions", "nonmatching_c_functions", "reconstructed_asset_modules") if k in report}))


if __name__ == "__main__":
    main()
