# Reproduce the ASM directory locally

This toolkit contains address/layout metadata and original tools, not a ROM or
an extracted ASM tree. Supply your own USA retail ROM, SHA-256:

`43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19`

## Setup and unpack

Python 3.10+ is required. Install the pinned decoder in an isolated environment;
install ARM binutils for optional native-byte verification. The setup below does
not install or select a candidate C compiler.

```sh
python3 -m venv .venv
. .venv/bin/activate
python3 -m pip install -r tools/requirements-extract.txt
python3 tools/identify_rom.py "$RETAIL_ROM"
python3 tools/extract_asm.py --rom "$RETAIL_ROM" --output "$PRIVATE_OUTPUT/asm-tree"
python3 tools/extract_resources.py --rom "$RETAIL_ROM" --output-dir "$PRIVATE_OUTPUT/resources"
```

Set `RETAIL_ROM` to your own read-only input and `PRIVATE_OUTPUT` to a private
location outside the source checkout. ASM output must be a new directory. Do not
upload the generated content or the identifier's local path output. Resource
extraction preserves original English content and unknown codes; it does not
perform translation or localization.

For a selected native-byte check with `arm-none-eabi-as` and
`arm-none-eabi-ld` available:

```sh
python3 tools/extract_asm.py --rom "$RETAIL_ROM" \
  --file asm/nested_task_dependencies_19/SceneTaskDependency_00021A3C.s \
  --verify --output "$PRIVATE_OUTPUT/asm-method-check"
```

Omit `--file` to generate/check all listed paths. Verification assembles and
links each file at its native placement and compares its complete generated
span with the pinned retail input. It never builds a whole ROM. One sequential
assembler/linker job is used; coordinating installations must acquire their
shared compiler slot before launching verification. `report.json` remains local.

## What matches

`data/asm-layout.json` is the source of truth for the exported ASM file tree,
labels, interface aliases, native ranges, modes and code/data segmentation.
Generation reproduces the listed `asm/` paths. The generated instruction text
uses canonical decoding and explicit labels; historical hand-written comments,
formatting and semantic annotations are not reproduced. Native-byte identity is
a separate check, never inferred from equal filenames or decoder success.

The historical source tree contains both selected source assembly and older
reference/probe/interface files. Extraction is reconstruction of a reference
view, not a claim that every generated file is a currently selected body or a
new recovery. Unknown module/function boundaries in the function catalogue stay
unknown. No generated ASM, literal values or ROM bytes are distributed here.

## Safety and sharing

The extractor rejects the wrong revision, invalid/traversing paths, overlapping
input/output locations and existing output trees. It records explicit native boundary symbols; any assembler section alignment after the end is excluded from the declared interval, never silently treated as function bytes. It generates into a temporary
sibling and publishes the directory only after all requested files succeed.
Keep reference ROMs and saves. Delete only your own inactive generated outputs.
Use public catalogue IDs, addresses and hashes in claim issues; never attach
ROMs, unpacked code/assets, machine paths, credentials or private logs.
