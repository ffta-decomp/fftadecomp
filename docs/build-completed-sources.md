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
