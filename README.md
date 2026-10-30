# FFTA Decompilation Sources and Toolkit

[Open the dashboard](https://ffta-decomp.github.io/fftadecomp/) · [Contributor guide](CONTRIBUTING.md) · [Decomp skill](.agents/skills/ffta-decomp/SKILL.md) · [Function catalogue](data/functions.csv) · [Local unpacking](docs/extract-asm.md)

Recovered C/mixed source, reproducible private-ROM builds, and progress reporting for Final Fantasy Tactics Advance (USA).

- [Published source progress](data/published-source-progress.json): verified source coverage, including attributed upstream imports.
- [Recovery progress](data/progress.json): dated validation and integration statistics, separate from source-release coverage.
- [Submodules](data/submodules.json): each `current` record uses the same accounting.
- [Validation summaries](data/workflow.json): function validation and integration results.
- [Resource spans](data/resource-addresses.csv).

Progress uses deduplicated original code ranges, including function-owned constants/alignment. Source coverage, local validation and integration are distinct; none is a gameplay-completion percentage. See the linked machine-readable summaries for their exact scope and dates.

This public repository contains completed recovered C/mixed source, aggregate metadata, portable build tools and recovery guidance. It does not distribute ROMs, story/dialogue text, translations, extracted game assets, private task records or private evidence. Historical display artwork credits remain in [assets/ATTRIBUTION.md](assets/ATTRIBUTION.md). The project is unofficial. Original documentation and metadata are [CC BY 4.0](LICENSE).

Dashboard history and published-source coverage use their own dated metadata. Undated ranges remain undated, and each original range is counted once.

The [repository-level skill](.agents/skills/ffta-decomp/SKILL.md) is the maintained ASM-to-C, diagnosis, verification and integration guide. It is included in the checkout and does not require a global skill installation. [Documentation](docs/README.md) links specialized setup and reference material.

Consumers can explicitly select [optional source/resource build extensions](docs/optional-build-extensions.md)
without editing vendored toolkit code. Extended outputs are separate from
original-ROM recovery results and cannot earn matching credit.

## Published source progress

Latest [source synchronization](data/source-sync-20261030.json): **62 verified upstream functions / 9,788 original bytes added**. The [comparison](data/upstream-comparison-20261030.json) includes main and PR #20; attribution is preserved per source and function.

As of **2026-10-30**, the public build contains **3,961 completed modules / 535,438 original bytes**, covering **41.801% of 1,280,908 known original code bytes**. The complete output matches the original US ROM byte-for-byte when built with your own private reference ROM.

Of the published total, **170,910 bytes / 1,136 functions** are attributed imports or adaptations from [shubshub/fftadecomp](https://github.com/shubshub/fftadecomp), not independent rewrites. The source index deduplicates all original ranges. Coverage includes function literals/alignment and eligible mixed modules, excludes resources, and is **not gameplay completion**. The denominator combines the historical 1,203,130-byte catalogue with 77,778 verified original bytes present in published modules but missing from that catalogue. See [machine-readable accounting](data/published-source-progress.json) and [build verification](data/completed-build-validation.json).

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

The [pinned reference table](vendor/README.md), [resource collection](docs/gba-asm-to-c-resources.md), [source-shape guide](.agents/skills/ffta-decomp/references/reconstruction.md) and [diagnosis guide](.agents/skills/ffta-decomp/references/mismatch-diagnosis.md) record concrete examples, limitations and upstream links. Other indexed projects are optional references; a clone is not evidence of adoption or a measured gain. Upstream copyrights and licenses remain with their authors. Upstream source notices are preserved where applicable; this repository does not relicense upstream contributions or distribute ROMs or game assets.

### Recovery workflow

Use the [skill](.agents/skills/ffta-decomp/SKILL.md) for original boundaries and ABI, fixed-profile C, diagnostic rules, full-range proof, contribution imports and one-image integration. The [extraction validation](data/toolkit-validation.json) records the separately tested private-ROM unpacking tools.

## Source and build quick start

- [`src/`](src/README.md): completed recovered C and explicitly identified mixed modules.
- [`src/completed-index.json`](src/completed-index.json): original ROM entries, sizes and source hashes.
- [`tools/build_completed.py`](tools/build_completed.py): build one private ROM and verify its final on-disk SHA-256.
- [`tools/verify_completed_rom.py`](tools/verify_completed_rom.py): verify an existing ROM without recompilation or a second output.
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
