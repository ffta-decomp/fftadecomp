# Game implementation by purpose

Completed C/mixed implementation units for the US AFXE source release. The master build selection and `completed-index.json` include every published increment; each selected span is checked against retail. Unrecovered resources still come from the explicitly supplied private ROM.

| Directory | Compilation units |
| --- | ---: |
| `battle/` | 277 |
| `engine/` | 11 |
| `graphics/` | 17 |
| `items/` | 45 |
| `jobs/` | 116 |
| `menus/` | 13 |
| `missions/` | 126 |
| `saves/` | 38 |
| `story/` | 33 |
| `text/` | 36 |
| `unknown/` | 3,259 |
| `world/` | 4 |

Original addresses identify stable files; function and module identities stay in
the build manifest. `unknown/` means subsystem ownership is unproved, not that
code is unfinished. See `config/source-layout.json` for each placement's basis.
Shared multi-entry units remain together.

Shared headers are under `include/`: basic ABI types in `ffta/`, proved subsystem
contracts in their own folders, and site-specific or incomplete bindings under
`interfaces/`. Symbol-only assembler aliases are in `asm/interfaces/`. No object
layouts or function ABIs were merged merely for visual consistency.

Follow [source layout and promotion](../docs/source-layout.md) for new deliveries.
Batch/trial/import provenance belongs in metadata and Git, not production paths.
C and mixed remain separately identified; directory cleanup adds no recovery
credit. Existing source notices and upstream attribution are retained.
