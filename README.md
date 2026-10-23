# FFTA Recovery Dashboard

[Open the dashboard](https://gh.bhee.online/fftadecomp/)

Automatic hourly reporting for Final Fantasy Tactics Advance (USA): delivery speed, daily decompilation history, and unified system and module progress.

- [Unified progress](data/progress.json): `dashboard` is the single source for the page, including overview, lane efficiency and all module rows.
- [Submodules](data/submodules.json): each `current` record uses the same accounting.
- [Activity ledger aggregates](data/workflow.json): separate local, independent and integration gates.
- [Resource spans](data/resource-addresses.csv).

Exact C combines the validated ROM snapshot and registered local exact spans after range deduplication. Local results do not automatically become integrated C. Bytes include constants/alignment; they are not game-completion percentages. The task tool publishes without an LLM; updates may be delayed while its host is offline.

This public repository contains aggregate metadata and presentation files, not game code, ROMs, extracted assets, private task records or evidence. Historical display artwork credits remain in [assets/ATTRIBUTION.md](assets/ATTRIBUTION.md). The project is unofficial. Original documentation and metadata are [CC BY 4.0](LICENSE).

Daily history comes from `progress.json.dashboard.daily`. Dates use Asia/Shanghai (UTC+8) and original receipt occurrence times. Range unions prevent duplicate recovery credit; pure C and eligible mixed remain separate, and integration is a separate gate. Cumulative curves include dated ledger receipts only. Current baseline bytes without a local delivery date remain explicitly undated rather than being assigned to a historical day. The current day is partial. Revoked receipts disappear on refresh. The percentage denominator is the pinned known original ASM catalogue, not ROM size or whole-game completion.
