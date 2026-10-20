# fftadecomp

Public recovery statistics and resource-address metadata for **Final Fantasy Tactics Advance (USA / AFXE)**. This repository publishes data only. It does not contain the game, extracted assets, decompiled code, build tools or implementation designs.

Snapshot: **2026-10-20**. This is a standalone progress-data project, not an official Square Enix project or a fork of another similarly named repository.

## Recovery snapshot

| Measurement | Verified snapshot | Denominator / interpretation |
| --- | ---: | --- |
| Reconstructed resource bytes | 9,247,442 B | 55.1190% of the 16,777,216-byte ROM; total resource size is not established |
| Selected resource spans | 4,987 | May contain shared resources or collections; not an in-game object count |
| Resource-span storage | 9,289,571 B | Includes 42,129 B of embedded padding, excluded from resource bytes above |
| Selected source ASM spans | 1,038,226 B | 6.1883% of the ROM; total executable-code size is not established |
| Selected ASM modules | 4,187 | Modules are not functions; spans may include literals and alignment |

These are reconstruction and storage measurements. They do **not** describe gameplay completion, complete semantic understanding, or the percentage of code rewritten in C. Detailed code-rewriting progress is not published here.

## Data

- [Progress summary](data/progress.json)
- [Resource address table — CSV](data/resource-addresses.csv)
- [Resource address table — JSON](data/resource-addresses.json)

Resource tables expose only synthetic snapshot IDs, ROM offsets, GBA addresses, exclusive end offsets and byte counts. They contain no resource payloads, filenames, decoding rules or function addresses. GBA addresses use base `0x08000000`. The table covers selected reconstructed spans only; omitted ranges must not be assumed unused or unknown. IDs are snapshot identifiers, not original game IDs.

Counts were reconciled against a validated reconstruction report and the selected resource inventory. Address spans were checked for overlap; resource bytes plus embedded padding equal their listed spans. Public data alone does not reproduce the private build validation.

## Publication boundary

Only aggregate recovery statistics and resource-address metadata are included. Source code, ASM listings, ROMs, graphics, audio, dialogue, saves, design documents, private paths, conversations, prompts and task records are excluded. This repository starts with an independent history.

## License

The original documentation and published metadata in this repository are available under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/). This license does not grant rights to the game or its assets.
