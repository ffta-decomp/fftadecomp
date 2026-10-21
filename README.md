# fftadecomp

Public recovery statistics and resource-address metadata for **Final Fantasy Tactics Advance (USA / AFXE)**. This repository publishes recovery data and its static presentation. It does not contain the game, extracted assets, decompiled code, build tools or implementation designs.

Snapshot: **2026-10-21**. This is a standalone progress-data project, not an official Square Enix project or a fork of another similarly named repository.

[**Open the Recovery Atlas →**](https://gh.bhee.online/fftadecomp/)

## Recovery snapshot

[![FFTA recovery snapshot: reconstructed resources, source ASM and readable C rewrite progress](assets/recovery-snapshot.svg)](data/progress.json)

<details>
<summary>Exact figures and measurement definitions</summary>

| Measurement | Verified snapshot | Denominator / interpretation |
| --- | ---: | --- |
| Reconstructed resource bytes | 9,247,442 B | 55.1190% of the 16,777,216-byte ROM; total resource size is not established |
| Selected resource spans | 4,987 | May contain shared resources or collections; not an in-game object count |
| Resource-span storage | 9,289,571 B | Includes 42,129 B of embedded padding, excluded from resource bytes above |
| Selected source ASM spans | 937,514 B | 5.5880% of the ROM; total executable-code size is not established |
| ASM instruction bytes | 829,252 B | Included in the span total above |
| ASM literals/tables | 101,184 B | Included in the span total above |
| ASM alignment/padding | 7,078 B | Included in the span total above |
| Selected ASM modules | 3,967 | Modules are not function counts |
| Selected readable C rewrite spans | 167,634 B | 933 C modules / 1,020 compiled entries; 0.9992% of ROM storage, not a code-completion percentage |
| C output matching retail exactly | 28,376 B | 597 function bodies match every byte |
| C output with pinned differences | 139,258 B | 423 entries; 17,510 same-offset matches and 121,748 differing byte positions |
| Mixed C/ASM spans | 10,520 B | Seven modules / nine generated entries; 26 ASM instruction bytes, separately counted from pure C |
| Original-byte dependencies | 364,873 B | Includes retained suffixes, data and padding; not unknown executable bytes |

</details>

These are reconstruction and storage measurements. The C figures distinguish exact output from readable C output that still differs from retail; pinned differences are byte-comparison results, not claims that behavior is complete. The total executable-code denominator is unknown, so the C span share must not be read as the percentage of code rewritten or gameplay completed. Relocated C bodies and retained assembly suffixes are accounted for separately.

## Data

- [Progress summary](data/progress.json)
- [Resource address table — CSV](data/resource-addresses.csv)
- [Resource address table — JSON](data/resource-addresses.json)

Resource tables expose only synthetic snapshot IDs, ROM offsets, GBA addresses, exclusive end offsets and byte counts. They contain no resource payloads, filenames, decoding rules or function addresses. GBA addresses use base `0x08000000`. The table covers selected reconstructed spans only; omitted ranges must not be assumed unused or unknown. IDs are snapshot identifiers, not original game IDs.

Counts were reconciled against a validated reconstruction report and the selected source/resource inventories. The C counts are tied to the pinned retail input, candidate image and build-report hashes in `data/progress.json`; they distinguish exact C output from nonmatching C output with pinned byte differences. Address spans were checked for overlap; resource bytes plus embedded padding equal their listed spans. Public data alone does not reproduce the private build validation.

## Publication boundary

Published recovery content consists of aggregate statistics, system inventory counts and resource-address metadata. The static dashboard also includes presentation files and attributed third-party title artwork; see [display credits](assets/ATTRIBUTION.md). Game source code, ASM listings, ROMs, extracted graphics, audio, dialogue, saves, design documents, private paths, conversations, prompts and task records are excluded. This repository starts with an independent history.

## License

The original documentation and published metadata in this repository are available under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/). This license does not grant rights to the game or its assets.

## Daily updates

Update the verified files in `data/` and the README snapshot together. Pushes deploy the dashboard automatically; a daily scheduled deployment republishes the committed snapshot without changing its date. No private repository is connected. Reference categories follow the [FFSKY FFTA guide](http://ffta.ffsky.cn/); ROM record counts are not playable-content counts.
