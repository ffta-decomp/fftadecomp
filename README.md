# FFTA Decompilation Sources and Toolkit

[Open the dashboard](https://ffta-decomp.github.io/fftadecomp/) · [Contributor guide](CONTRIBUTING.md) · [Workflow library](docs/README.md) · [Function catalogue](data/functions.csv) · [Local unpacking](docs/extract-asm.md)

Recovered C/mixed source, reproducible private-ROM builds, and progress reporting for Final Fantasy Tactics Advance (USA).

- [Published source progress](data/published-source-progress.json): verified source coverage, including attributed upstream imports.
- [Recovery ledger](data/progress.json): dated local/peer/integration statistics, separate from source-release coverage.
- [Submodules](data/submodules.json): each `current` record uses the same accounting.
- [Activity ledger aggregates](data/workflow.json): separate local, independent and integration gates.
- [Resource spans](data/resource-addresses.csv).

Exact C combines the validated ROM snapshot and registered local exact spans after range deduplication. Local results do not automatically become integrated C. Bytes include constants/alignment; they are not game-completion percentages. A dedicated scheduler publishes one consolidated snapshot daily at 23:55 Asia/Shanghai without an LLM. Routine internal updates do not publish. Local ledger records remain immediate; updates may be delayed while the host is offline.

This public repository contains completed recovered C/mixed source, aggregate metadata, portable build tools and recovery guidance. It does not distribute ROMs, story/dialogue text, translations, extracted game assets, private task records or private evidence. Historical display artwork credits remain in [assets/ATTRIBUTION.md](assets/ATTRIBUTION.md). The project is unofficial. Original documentation and metadata are [CC BY 4.0](LICENSE).

Daily history comes from `progress.json.dashboard.daily`. Dates use Asia/Shanghai (UTC+8) and original receipt occurrence times. Range unions prevent duplicate recovery credit; pure C and eligible mixed remain separate, and integration is a separate gate. Cumulative curves include dated ledger receipts only. Current baseline bytes without a local delivery date remain explicitly undated rather than being assigned to a historical day. The current day is partial. Revoked receipts disappear on refresh. The percentage denominator is the pinned known original ASM catalogue, not ROM size or whole-game completion.

The workflow library preserves docs/ and tools/ paths. `data/functions.json` and `data/asm-layout.json` publish native identities and reconstruction layout only, with explicit snapshot scope. Use your own pinned ROM to generate the matching ASM directory privately. Public Issue claims require canonical maintainer confirmation. See [CONTRIBUTING.md](CONTRIBUTING.md).

Consumers can explicitly select [optional source/resource build extensions](docs/optional-build-extensions.md)
without editing vendored toolkit code. Extended outputs are separate from
original-ROM recovery results and cannot earn matching credit.

## Published source progress

As of **2026-10-28**, the public build contains **3,694 completed modules / 468,682 original bytes**, covering **36.654% of 1,278,650 known original code bytes**. The complete output matches the original US ROM byte-for-byte when built with your own private reference ROM.

Of the published total, **161,102 bytes / 1,072 functions** are attributed imports from [shubshub/fftadecomp](https://github.com/shubshub/fftadecomp), not independent rewrites. The source index deduplicates all original ranges. Coverage includes function literals/alignment and eligible mixed modules, excludes resources, and is **not gameplay completion**. The denominator combines the historical 1,203,130-byte catalogue with 75,520 verified original bytes present in published modules but missing from that catalogue. See [machine-readable accounting](data/published-source-progress.json) and [build verification](data/completed-build-validation.json).

Browse the rewritten code in [`src/`](src/README.md), or use [`tools/build_completed.py`](tools/build_completed.py) and the [build guide](docs/build-completed-sources.md). No ROM, story/dialogue text or extracted game assets are supplied.

## Acknowledgements and references actually used

| Project / resource | Contribution to this recovery workflow |
| --- | --- |
| [pret/agbcc](https://github.com/pret/agbcc) | Pinned native Thumb compiler; its O2 pass driver, instruction patterns, allocator/reload and literal-pool code ground the compiler-generation guide. |
| [CosmicScribe64/eds-decomp](https://github.com/CosmicScribe64/eds-decomp) | First-divergence/RTL diagnosis and documented register/empty-ASM constraints. These informed the allocation-residual recall; three selected FFTA methods subsequently reached whole exact, without claiming a general speedup multiplier. |
| [pret/pokeemerald](https://github.com/pret/pokeemerald) | Source-organization examples for tasks, callbacks, state ownership, narrow fields and authored battle commands. Its game types and compiler assumptions are not copied as FFTA facts. |
| [hitsmaxft/rea](https://github.com/hitsmaxft/rea) | Evidence-led reverse-engineering structure and bounded, falsifiable hypotheses; adapted in the GBA workflow. |
| [Tonc](https://gbadev.net/tonc/), [libtonc](https://github.com/devkitPro/libtonc), [libgba](https://github.com/devkitPro/libgba), [GBATEK](https://rust-console.github.io/gbatek-gbaonly/) | ARM7TDMI/ARMv4T, BIOS, memory-map and access-width reference checks. Historical FFTA ABI/layout still comes from the original target. |
| [Capstone](https://github.com/capstone-engine/capstone), [GNU Binutils](https://www.gnu.org/software/binutils/), [Unicorn](https://github.com/unicorn-engine/unicorn), [mGBA](https://github.com/mgba-emu/mgba) | Decoding, native assembly/link/extraction, bounded CPU cases and emulator validation infrastructure; these provide different evidence gates. |

The [pinned reference table](vendor/README.md), [47-resource collection](docs/gba-asm-to-c-resources.md), [pokeemerald study](docs/pokeemerald-reconstruction-reference.md) and [EDS study](docs/eds-matching-reference.md) record concrete examples, limitations and upstream links. Other indexed projects are optional references; a clone is not evidence of adoption or a measured gain. Upstream copyrights and licenses remain with their authors. Upstream source notices are preserved where applicable; this repository does not relicense upstream contributions or distribute ROMs or game assets.

### Reproduction validation

The release [validation summary](data/toolkit-validation.json) records two identical clean generated ASM trees: **4,240 paths**, including **4,236 native files reassembled byte-for-byte** and four interface-only files. The [executable walkthrough](docs/reproduce-recovery.md) covers setup, pinned-ROM unpacking, single-method compilation/preflight, independent gates and structured round records. This validates the reference/tool workflow and grants no new game-recovery credit.

Public progress reports project-level output only; worker counts and per-worker performance are not published.

## Source and build quick start

- [`src/`](src/README.md): completed recovered C and explicitly identified mixed modules.
- [`src/completed-index.json`](src/completed-index.json): original ROM entries, sizes and source hashes.
- [`tools/build_completed.py`](tools/build_completed.py): compile the published selection, validate every module, and compose a byte-identical private image.
- [`docs/build-completed-sources.md`](docs/build-completed-sources.md): prerequisites, verification and build scope.

Install Python 3.10+, Clang, Make and `arm-none-eabi` binutils, then:

```sh
git clone --recurse-submodules https://github.com/ffta-decomp/fftadecomp.git
cd fftadecomp
python3 tools/bootstrap.py
python3 tools/build_completed.py \
  --input /absolute/private/path/ffta-us.gba \
  --output /absolute/private/output/rebuilt.gba \
  --report /absolute/private/output/build-report.json \
  --jobs 2
```

Supply your own original **16 MiB US AFXE ROM**, SHA-256 `43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19`. Paths must be outside this checkout; output/report must be new. The builder compiles all published modules, checks their complete generated bytes against the reference, and refuses mismatches. The final report must say `whole_image_identical: true`.

**This is a partial decompilation build, not a fully source-reconstructed game.** Unrecovered code, graphics, audio and story/dialogue text remain in the private input ROM. No story text or translation pack is published or extracted by this build. Source publication and rebuilding do not create additional recovery credit.

Verified on 2026-10-28: **3,694 modules / 468,682 original bytes** compiled with zero module-cache hits; the complete output matched the original US ROM. See the [build validation summary](data/completed-build-validation.json).

## Recovered source code

Completed C and eligible mixed modules are published in [`src/`](src/README.md), with ROM entries, original sizes and source hashes in [`src/completed-index.json`](src/completed-index.json). Use the [completed-source build instructions](docs/build-completed-sources.md) to compile these modules against your own private US ROM and verify byte-identical output. Unrecovered code/resources remain supplied by that ROM.

## Upstream-imported implementations

Locally verified imports from [shubshub/fftadecomp](https://github.com/shubshub/fftadecomp) are explicitly attributed in source headers and [progress JSON](data/upstream-imports.json)/[CSV](data/upstream-imports.csv). They are not counted as independent rewrites. See [provenance and validation](docs/upstream-imports.md); imported and existing spans are deduplicated within the published source build.
