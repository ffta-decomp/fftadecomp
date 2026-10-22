# FFTA Recovery Dashboard

[Open the dashboard](https://gh.bhee.online/fftadecomp/)

Automatic hourly reporting for Final Fantasy Tactics Advance (USA): delivery speed first, followed by unified system and module progress.

- [Unified progress](data/progress.json): `dashboard` is the single source for the page, including overview, lane efficiency and all module rows.
- [Submodules](data/submodules.json): each `current` record uses the same accounting.
- [Activity ledger aggregates](data/workflow.json): separate local, independent and integration gates.
- [Resource spans](data/resource-addresses.csv).

Exact C combines the validated ROM snapshot and registered local exact spans after range deduplication. Local results do not automatically become integrated C. Bytes include constants/alignment; they are not game-completion percentages. The task tool publishes without an LLM; updates may be delayed while its host is offline.

This public repository contains aggregate metadata and presentation files, not game code, ROMs, extracted assets, private task records or evidence. Historical display artwork credits remain in [assets/ATTRIBUTION.md](assets/ATTRIBUTION.md). The project is unofficial. Original documentation and metadata are [CC BY 4.0](LICENSE).
