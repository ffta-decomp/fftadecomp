# Verify locally and integrate once

## Setup and original extraction

Use Python 3.10+, Clang, Make and ARM GNU binutils. From this repository root:

```sh
git submodule update --init vendor/agbcc
python3 -m venv build/decomp-venv
build/decomp-venv/bin/python -m pip install -r tools/requirements-extract.txt
python3 tools/bootstrap.py
python3 tools/identify_rom.py "$RETAIL_ROM"
build/decomp-venv/bin/python tools/extract_asm.py --rom "$RETAIL_ROM" \
  --file "$ASM_FILE" --verify --output "$NEW_PRIVATE_ASM_DIR"
```

RETAIL_ROM is the user's private original 16 MiB US input. The generated ASM
output must be outside the checkout. Choose ASM_FILE from the native catalogue;
prove its actual boundary/ABI before treating it as an independent C entry.
Bootstrap pins normal agbcc and does not build a ROM. Reports must also bind
actual host preprocessor, compiler binary, binutils and relevant configuration.

## Prepare and build one function

For a new draft, put C and required headers in ignored `build/work/`. Set
NATIVE_ID to an exact catalogue ID and METHOD_SYMBOL to the exported C identifier.
The preparation command creates one ignored local manifest; reuse it for later
rounds. It does not modify production selection.

```sh
python3 tools/prepare_public_method.py --native-id "$NATIVE_ID" \
  --symbol "$METHOD_SYMBOL" --source build/work/candidate.c \
  --asm-tree "$NEW_PRIVATE_ASM_DIR" --asm-file "$ASM_FILE"
python3 tools/build_function.py --retail "$RETAIL_ROM" \
  --config "build/public-methods/$NATIVE_ID/manifest.json" \
  --module "$METHOD_SYMBOL" \
  --candidate-module "build/public-methods/$NATIVE_ID/candidate-module.json" \
  --output-dir "$NEW_PRIVATE_BUILD_DIR"
```

The output directory must be new or empty, outside the checkout. Missing helper
address bindings may require extracting `asm/external_thumb_symbols.s` separately
and placing that generated interface under ignored `asm/`; see `docs/extract-asm.md`.
Bindings still require original ABI evidence. Use `--help` for exact supported
metadata; do not assume an old report supports a newer policy automatically.

`build_function.py` composes local compilation/comparison with strict selection
preflight. A nonexact result or unsupported policy is not a successful exact
gate even if compilation returned zero. Inspect its status and reports.
`compare_module_build.py` alone supplies comparison artifacts and is not strict
acceptance. Neither command composes a complete game ROM for a local trial.

## Whole-function proof

Require all of the following, bound to the same final source:

- Authenticated retail revision, original offset/span, mode and declared entries.
- Generated size and every original byte equal, including owned literals/tables
  and alignment. No overflow, unexplained retained suffix or neighboring overlay.
- Linked ELF entries/FUNC ranges, relevant sections, relocations and any explicit
  alignment/veneer/data policy. Unexpected allocated sections must not be ignored.
- Actual source and transitive headers, symbol bindings, effective module config,
  tool sources/toolchain and generated artifacts authenticated by their captures.
  A hash of a mutable path alone does not preserve a build input.

Do not mutate an old report to match changed tools or metadata. A provenance
repair is a new explicit source-bound validation or supported append-only proof,
not permission to bypass a strict rejection. Unsupported mixed/preflight cases
must stay distinct from accepted pure C.

Keep nonexact semantic evidence separate: independent source-derived return,
mutation, ABI/callback and negative cases cover only their stated inputs. The
optional `tools/run_module_cases.py` runner uses `tools/requirements-behavior.txt`.
A few fixtures, a boot or a visually aligned block is not whole-function exact
or whole-game behavior proof.

## Freeze readable source and select production

Complete evidence-backed naming and commit the final C, necessary headers and
symbol-only bindings. Preserve original entry/module identity; do not add wrappers
or executable veneers for a cosmetic rename. Source changes require new bound
proof even when unchanged binaries permit reusing applicable behavior evidence.

The following selection/build commands apply to the published source checkout.
If its release manifest/index are absent, use that checkout; do not substitute a
broader historical manifest or fabricate a completed-source selection.

For a published exact module, update the corresponding records in
`config/completed-build.json` and `src/completed-index.json` together. Follow an
existing entry's schema for functions, source/dependency hashes and build inputs;
source lists must include the actual dependency closure. Do not merely edit a
hash to accept a candidate. Validate the exact final files through the same
compiler and complete retail comparison. Imported attribution is separate metadata.

## One coherent image and final hash

Follow `docs/build-completed-sources.md` for complete prerequisites and scope:

```sh
python3 tools/build_completed.py --input "$RETAIL_ROM" \
  --output "$NEW_PRIVATE_ROM" --report "$NEW_PRIVATE_BUILD_REPORT" --jobs 2
python3 tools/verify_completed_rom.py --rom "$NEW_PRIVATE_ROM"
```

Input, output and report paths must be distinct and outside the checkout. Output
and report must not exist. The build compiles every selected module, retains
unrecovered gaps/resources from the private input, writes one image and verifies
its actual on-disk hash before success. No selected-module failure may silently
fall back to retail bytes. Check `whole_image_identical` and
`final_file_verification.verified`; the US target hash is in the skill entry.
Verification-only rechecks that image without compiling or writing another ROM.

Do not represent this transitional build as a source-only reconstruction. Run
`tools/update_source_progress.py` after intentional selection changes and inspect
its output; deduplicate original ranges and separate C, mixed, imports and
retained resources. Percentages describe a pinned catalogue, not gameplay
completion. An unchanged selection does not need a new ROM build for guide edits.

## Compact evidence and cleanup

Keep source in Git and one compact validation summary with commit, original span,
source/dependency/toolchain identities, full-range result, final image hash and
limits. Retain exact active/pending proof inputs until their validation and
integration obligations finish. Source hashes without recoverable files are not
sufficient evidence.

Reuse the bootstrapped compiler and one current working-output slot when safe.
Do not copy full source trees, manifests and ROMs for every round. After successful
integration, remove consumed temporary objects, generated ROM copies and redundant
diagnostic outputs that are no longer required. Never remove the user's reference,
saves, active work, pending proof artifacts or another checkout's files. Cleanup
must not invalidate a still-needed report; keep its required inputs or a supported
compact, recoverable source-bound record first.
