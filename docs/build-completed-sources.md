# Build the published completed sources

This transitional build compiles **every module** in `config/completed-build.json` from the published C/mixed source, links it at its original address, checks its declared entry points, and requires complete byte equality with the supplied US ROM. Unrecovered code and resources are retained from that private input. This is not a full source-only reconstruction.

## Prerequisites

- Python 3.10 or newer, Clang, Make, and `arm-none-eabi` binutils on `PATH`.
- The pinned `pret/agbcc` submodule; the bootstrap script checks its revision.
- Your own original 16 MiB US AFXE ROM, SHA-256 `43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19`.

```sh
git submodule update --init vendor/agbcc
python3 tools/bootstrap.py
python3 tools/build_completed.py \
  --input /absolute/private/path/ffta-us.gba \
  --output /absolute/private/output/rebuilt.gba \
  --report /absolute/private/output/build-report.json \
  --jobs 2
```

All three paths must be distinct and outside this checkout. Output and report paths must not already exist. ROMs are never downloaded, bundled, or committed. The build refuses a different revision, modified published source/header hash, nonexact module, incorrect entry point, size mismatch, or byte mismatch. No failure falls back to reference bytes for a selected module.

The source index and build manifest are a frozen release pair. Intentional source changes require updating their hashes and then passing the same retail comparison; they do not qualify merely because the index was edited.

Each invocation compiles all selected modules, without module-result cache reuse. Invocation-owned object files are removed afterwards; the small bootstrapped compiler is retained. The JSON report records each compiled span, total compiled/retained bytes, elapsed time and both whole-image hashes. The builder writes one output ROM and verifies its final on-disk SHA-256 before writing a success report. Check `whole_image_identical: true` and `final_file_verification.verified: true`. To recheck an existing ROM, use the verification-only command below; it does not compile or create another image.

```sh
python3 tests/test_build_completed.py
python3 tools/verify_completed_rom.py --rom /absolute/private/output/rebuilt.gba
```

Existing `tools/build_rom.py` is the shared compilation implementation. `build_completed.py` supplies the published completed-only selection and strict private-input composition. Do not use the broader historical `config/retail-us.json` as though every unfinished source and asset had been published.

## Verified release

The [current release validation](../data/completed-build-validation.json) records
the exact module count, original-byte coverage and output hash. Unrecovered
resources remain in the user's private input. The Pages workflow validates public
metadata and scripts only: it does not have a ROM and does not repeat ROM builds.
No ROM, extracted story text or translation resources are distributed.

## PR source-hash checks

`python3 tools/build_source_hashes.py --jobs 4` compiles the frozen release plus
the incremental selections explicitly registered in
[`data/source-build-selections.json`](../data/source-build-selections.json).
Each incremental proof pins its configuration, source files, original spans and
native module/function hashes. Selections must have disjoint ranges and module
identities. Adding source files without a verified selection fails the PR check;
a successful old release build does not validate newly added source implicitly.

Every PR runs this build once, including same-repository PRs. Branch pushes do
not launch a duplicate build; pushes to `main` and manual runs remain supported.
The job summary and PR comment identify each changed selected function as
`match`, `mismatch`, `build error` or `not built`. Headers, metadata and tooling
have no standalone native-function result. These hash checks require no private
ROM and do not establish a whole-ROM comparison. Validated increments are consolidated into the master selection and its native
hash tables; the registry then lists only subsequent increments. The same range
must never occur in both the master and an active registry selection.

## Fixed-address function bindings

Some functions use an `asm/interfaces/<address>.s` file to bind existing
functions and data at their original addresses. The manifest selects this through
`external_symbol_supplement`. The builder accepts only non-emitting `.global`,
`.set`, `.thumb_set`, `.syntax unified` and `.thumb` directives; instructions,
raw bytes, includes and paths outside the source root are rejected. The file hash
participates in the module cache identity and the completed-source input index.
These aliases do not implement or replace a function body.

For an explicit `--build-dir`, prepare its pinned `toolchain/agbcc` before the
build. The default uses the compiler produced by `tools/bootstrap.py`. A missing
compiler is rejected before scheduling module jobs. Do not duplicate bootstraps
per function; reuse the same authenticated compiler.
