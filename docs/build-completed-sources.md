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

Each invocation compiles all selected modules, without module-result cache reuse. Invocation-owned object files are removed afterwards; the small bootstrapped compiler is retained. The JSON report records each compiled span, total compiled/retained bytes, elapsed time and both whole-image hashes. Check `whole_image_identical: true`; independently `cmp` or `shasum -a 256` the two ROMs if desired.

```sh
python3 tests/test_build_completed.py
cmp /absolute/private/path/ffta-us.gba /absolute/private/output/rebuilt.gba
```

Existing `tools/build_rom.py` is the shared compilation implementation. `build_completed.py` supplies the published completed-only selection and strict private-input composition. Do not use the broader historical `config/retail-us.json` as though every unfinished source and asset had been published.

## Verified release

The [2026-10-28 validation](../data/completed-build-validation.json) compiled all 3,694 modules (468,682 original bytes), with zero module-cache hits. Every selected span matched; independent `cmp` confirmed that the resulting 16 MiB image is identical to the original US ROM. Eleven focused builder/provenance tests passed. No ROM, extracted story text or translation resources are distributed.
