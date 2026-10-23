> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Local module compilation and comparison

[tools/compare_module_build.py](../tools/compare_module_build.py) compiles one
existing selected C, mixed, or assembly module through the pinned
`build_rom.compile_module` path. It checks the retail revision and declared
function entries, emits external ELF/binary/disassembly/symbol/diff artifacts,
and never edits the selected manifest or composes a ROM. It does not traverse
assets or rebuild dependencies.

Use the pinned retail ROM and selected manifest explicitly:

```sh
python3 tools/compare_module_build.py \
  --retail /path/to/reference-retail-us.gba \
  --config config/retail-us.json \
  --module ReadSaveByte \
  --output-dir /path/outside/repository/read-save-byte
```

`--module` names one module already present in the config. The optional
`--candidate-module` JSON may override only existing code-build metadata:
`source`, `kind`, `functions`, `compiler_flags`, `external_symbols`,
`external_exclude_symbols`, `trailing_alignment_bytes`, `linker_veneer_policy`,
and `compiler_data_policy`. The selected ROM
offset and size are fixed and cannot be overridden. When converting a selected
assembly module to C or mixed C, omitted external-symbol settings default to
the normal C build behavior (`external_symbols: true`, no exclusions), and
omitted trailing alignment defaults to zero. Explicit candidate metadata is
preserved. A relative candidate source is resolved from the repository root,
while an absolute path supports an external draft. Candidate JSON example:

```json
{
  "source": "/path/to/draft.c",
  "kind": "c",
  "functions": [
    {"name": "ReadSaveByte", "offset": 824744, "size": 16}
  ],
  "compiler_flags": ["-O2", "-mthumb-interwork"],
  "external_symbols": true,
  "external_exclude_symbols": [],
  "trailing_alignment_bytes": 0
}
```

The output directory must be new or empty and outside the repository. Compiler
working files are isolated under `build/local-modules/` and removed when that
invocation finishes. The report follows the shared `local-module-build-v1`
shape (`retail_sha256`, `manifest_sha256`, and one-element `segments`) so the
paired-case runner can overlay only a bounded segment on its private retail
image. The segment records reference/generated sizes, binary SHA-256,
function entries, entry validation, byte-level differences, ELF, disassembly,
symbols, toolchain versions, compiler options, and phase timings.

The paired-case runner pins its emulator dependency without installing project
dependencies. Use the same environment for its tests and external fixture banks:

```sh
uv run --no-project --with unicorn==2.1.4 python -m unittest \
  discover -s tests -p 'test_run_module_cases.py' -v

uv run --no-project --with unicorn==2.1.4 python tools/run_module_cases.py \
  --retail /path/to/reference-retail-us.gba \
  --build-report /path/to/local-build/report.json \
  --cases /path/to/private/module-cases-v1.json \
  --output /path/to/private/paired-report.json
```

`fits` means the generated binary does not extend past the declared module
span. A short candidate is still reported with its missing generated tail; a
long candidate is reported with `fits: false` and overflow offsets, but is
never overlaid onto neighboring bytes. Invalid retail hashes, malformed
spans, out-of-module function entries, unresolved/shifted linked entries and
output-path collisions fail the command. A local match or mismatch is not a
full ROM build, runtime behavior proof, or gameplay coverage.

The focused test suite uses the real selected `ReadSaveByte` C module and
`Startup` assembly module, then checks an intentionally changed C candidate,
alignment-trimmed output hashing, assembly-to-C metadata defaults, immutable
module bounds, wrong revision, wrong entry, and an oversized trial:

```sh
python3 -m unittest discover -s tests -p 'test_compare_module_build.py' -v
```

Before extracting `.text`, the local wrapper inspects the linked ELF section
table and rejects any nonempty allocated or loadable section outside `.text`;
otherwise data such as `.rodata` could be silently omitted from the reported
binary. The regression test emits a four-byte static lookup and verifies the
rejection. Independent review reproduced the guard against the known bad
D21A8 reward candidate ELF: its 276-byte `.text` plus 12-byte `.rodata` was
rejected, while the corrected 344-byte aligned-halfword candidate with only
`.text` loadable was accepted. This guards local fit claims without changing
the full linker or build pipeline.

## Initial local comparison

On the pinned US retail revision, the selected `ReadSaveByte` module rebuilt
24/24 bytes and `RetailIrqDispatcher` rebuilt 344/344 bytes. A deliberately
changed `ReadSaveByte` candidate produces an address-by-address diff. These
are local compile checks only; they do not alter recovered-byte accounting or
replace the required full build at a later integration milestone.

## Assembly-to-C trial

The 64-byte selected `CoreFrontier_0013ADF0` assembly module was also compiled
from an isolated C candidate with `-O2 -mthumb-interwork`. The conversion used
the default external-symbol link path and zero trailing alignment. It generated
56 bytes, fit the selected span, and matched 13 bytes at the same offset. The
other 43 generated bytes differ, and 8 retail bytes have no generated output;
all offsets are recorded in the external local-build report. This confirms
the tool can exercise an actual assembly-to-C candidate without changing its
selected address or size. It is a compile/link/diff demonstration, not a
semantic equivalence claim or an integrated recovery-count increase.

The report was also consumed by `run_module_cases.py` using three external
bounded vectors (empty input, one seeded byte, and `123456789`). The retail and
C candidate both matched independent `zlib.crc32` return-value oracles in all
three cases. This confirms report/binary overlay compatibility and these test
vectors only; the report keeps `natural_coverage` false.

The reviewed bank then passed 47/47 paired cases in 15.90 seconds: 37 cases
execute the CRC candidate, while the other ten cover unchanged byte-access,
table and selector interfaces. They are not 47 CRC cases. A deliberately wrong
candidate that XORs the CRC return with one still fits its 64-byte envelope,
but fails all four zero-length CRC oracle cases. In the first case retail
returns zero and the candidate returns one. These checks measure local
compilation and bounded CPU execution only.

The candidate's `byte_count` parameter is a full `u32`, matching the retail
entry ABI. Its loop index remains `u16`, as in the retail instructions; inputs
at or above 65,536 bytes can wrap that index and fail to terminate. That input
boundary is documented rather than hidden by narrowing or truncating the
candidate parameter, and the bounded vectors do not test it.

## Structural matching experiments

Follow the [migration diagnosis workflow](asm-to-c-migration.md#diagnose-structural-differences-before-chasing-exact-bytes) before changing control flow to work around a compiler or linker restriction.
The opt-in `tools/compiler_data_policy.md` (implementation-checkout reference) permits only
a proven unreferenced agbcc switch pointer; local and full builds still reject
other nonempty allocated sections outside `.text`. Policy evidence is included
in the report and cache. A local match increase does not replace behavioral
or final-image acceptance.
