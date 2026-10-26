# FFTA Recovery Atlas and Toolkit

[Open the dashboard](https://ffta-decomp.github.io/fftadecomp/) · [Contributor guide](CONTRIBUTING.md) · [Workflow library](docs/README.md) · [Function catalogue](data/functions.csv) · [Local unpacking](docs/extract-asm.md)

Daily reporting for Final Fantasy Tactics Advance (USA): delivery speed, daily decompilation history, and unified system and module progress.

- [Unified progress](data/progress.json): `dashboard` is the single source for the page, including overview, lane efficiency and all module rows.
- [Submodules](data/submodules.json): each `current` record uses the same accounting.
- [Activity ledger aggregates](data/workflow.json): separate local, independent and integration gates.
- [Resource spans](data/resource-addresses.csv).

Exact C combines the validated ROM snapshot and registered local exact spans after range deduplication. Local results do not automatically become integrated C. Bytes include constants/alignment; they are not game-completion percentages. A dedicated scheduler publishes one consolidated snapshot daily at 23:55 Asia/Shanghai without an LLM. Worker submissions and administrator checks do not publish. Local ledger records remain immediate; updates may be delayed while the host is offline.

This public repository contains aggregate metadata and presentation files, original portable tools and recovery guidance, not game implementation code, ROMs, extracted assets, private task records or evidence. Historical display artwork credits remain in [assets/ATTRIBUTION.md](assets/ATTRIBUTION.md). The project is unofficial. Original documentation and metadata are [CC BY 4.0](LICENSE).

Daily history comes from `progress.json.dashboard.daily`. Dates use Asia/Shanghai (UTC+8) and original receipt occurrence times. Range unions prevent duplicate recovery credit; pure C and eligible mixed remain separate, and integration is a separate gate. Cumulative curves include dated ledger receipts only. Current baseline bytes without a local delivery date remain explicitly undated rather than being assigned to a historical day. The current day is partial. Revoked receipts disappear on refresh. The percentage denominator is the pinned known original ASM catalogue, not ROM size or whole-game completion.

The workflow library preserves docs/ and tools/ paths. `data/functions.json` and `data/asm-layout.json` publish native identities and reconstruction layout only, with explicit snapshot scope. Use your own pinned ROM to generate the matching ASM directory privately. Public Issue claims require canonical maintainer confirmation. See [CONTRIBUTING.md](CONTRIBUTING.md).

## Acknowledgements and references actually used

| Project / resource | Contribution to this recovery workflow |
| --- | --- |
| [pret/agbcc](https://github.com/pret/agbcc) | Pinned native Thumb compiler; its O2 pass driver, instruction patterns, allocator/reload and literal-pool code ground the compiler-generation guide. |
| [CosmicScribe64/eds-decomp](https://github.com/CosmicScribe64/eds-decomp) | First-divergence/RTL diagnosis and documented register/empty-ASM constraints. These informed the allocation-residual recall; three selected FFTA methods subsequently reached whole exact, without claiming a general speedup multiplier. |
| [pret/pokeemerald](https://github.com/pret/pokeemerald) | Source-organization examples for tasks, callbacks, state ownership, narrow fields and authored battle commands. Its game types and compiler assumptions are not copied as FFTA facts. |
| [hitsmaxft/rea](https://github.com/hitsmaxft/rea) | Evidence-led reverse-engineering structure and bounded, falsifiable hypotheses; adapted in the GBA workflow. |
| [Tonc](https://gbadev.net/tonc/), [libtonc](https://github.com/devkitPro/libtonc), [libgba](https://github.com/devkitPro/libgba), [GBATEK](https://rust-console.github.io/gbatek-gbaonly/) | ARM7TDMI/ARMv4T, BIOS, memory-map and access-width reference checks. Historical FFTA ABI/layout still comes from the original target. |
| [Capstone](https://github.com/capstone-engine/capstone), [GNU Binutils](https://www.gnu.org/software/binutils/), [Unicorn](https://github.com/unicorn-engine/unicorn), [mGBA](https://github.com/mgba-emu/mgba) | Decoding, native assembly/link/extraction, bounded CPU cases and emulator validation infrastructure; these provide different evidence gates. |

The [pinned reference table](vendor/README.md), [47-resource collection](docs/gba-asm-to-c-resources.md), [pokeemerald study](docs/pokeemerald-reconstruction-reference.md) and [EDS study](docs/eds-matching-reference.md) record concrete examples, limitations and upstream links. Other indexed projects are optional references; a clone is not evidence of adoption or a measured gain. Upstream copyrights and licenses remain with their authors. This archive does not relicense or distribute their game code, ROMs or assets.

### Reproduction validation

The release [validation summary](data/toolkit-validation.json) records two identical clean generated ASM trees: **4,240 paths**, including **4,236 native files reassembled byte-for-byte** and four interface-only files. The [executable walkthrough](docs/reproduce-recovery.md) covers setup, pinned-ROM unpacking, single-method compilation/preflight, independent gates and structured round records. This validates the reference/tool workflow and grants no new game-recovery credit.
