# Game recovery priorities

## Active campaign: SAV file format and stored-data associations

Recover the representation used to parse and write a supplied SAV, its logical
images and persisted field/identifier associations. Preserve running jobs and
existing evidence, then checkpoint unrelated source work at a safe boundary.
Do not continue a successful UI or gameplay family merely because it reads saved
RAM. Existing global recovery credit and original method clocks remain valid.
A Web editor is outside the current implementation scope.

## Three delivery gates

1. Pin an actual supplied SAV and establish its capacity/container, physical
   bank/sector layout, slot/header discovery, newest-valid-copy rules, checksum
   coverage and logical-image assembly. CPU aperture addresses are not host-file
   offsets; synthetic images do not establish the supplied file's layout.
2. Decode assembled images and references into a field schema. Reuse the proven
   item, unit, job, ability and mission catalogues; preserve unknown IDs, spare
   bits, opaque bytes and alternative slots. Keep file, encoded-image and
   decoded-image offsets separate.
3. Prove unchanged-file parse/serialize identity, then a bounded known-field
   edit with the required checksum/reference/metadata updates. Preserve unrelated
   bytes and slots and verify acceptance through the game read path. Record the
   tested version and slot; this does not prove physical flash durability.

## Scope and classification boundaries

Every new task must identify the exact SAV byte region, validation/codec step,
reference conversion or stored-ID association gap and its parser/writer consumer.
Stored names and option bits are schema data. Naming editors, confirmation
windows, settings interaction, cursor/render controllers and general gameplay
calculations are excluded. A call from a save screen is not format evidence.
Runtime snapshots count as format work only when their serialization or logical
image role is established, not merely because their inputs are persisted fields.
Large save/restore-controller matching and physical flash-driver migration are
not prerequisites for a host-independent format implementation. Reuse existing
C/ASM and accurate driver interfaces; preserve terminal matching budgets.

The reviewed 3,802-original-byte cohort has the following responsibility split.
This is a classification correction, not new delivery or a whole-SAV denominator.

| Responsibility | Original bytes | SAV-format credit |
| --- | ---: | --- |
| Proven format operations | 1,330 | Retained in the format subset |
| Naming UI: `12A084`, `12A5BC`, `12B59C` | 1,614 | Excluded; owner is menus/naming |
| Adjacent settings logic | 858 | Excluded; stored option-bit schema is separate |

Preserve all original native identities, credit dates and global totals. Do not
count UI, runtime snapshot or gameplay results as SAV-format progress. Report
format evidence, stored-field/ID associations and matched original ASM bytes
separately. Each checkpoint identifies its actor/task, functional category,
exact byte region or codec step, concrete artifact, input class (actual SAV,
controlled image or source-only), reached gate and remaining blocker. No overall
SAV percentage is supported until its actual file/schema denominator is known.

## Source anchors and limits

Reuse the implementation checkout's existing save/restore-controller and
game-image-transition evidence; those private implementation packages are not
bundled with this toolkit. Save-controller ROM range
`0x138efc..0x139c70` and restore-controller `0x139c70..0x13adf0` are existing
recovered entry points, not automatically available new tasks. Check native
history and prior matching budgets before implementation.

Ordinary encoded-image extent `0x2fc4`, extended extent `0x3ca8`, and a restore
copy of `0x3ca8` bytes are different facts. The ordinary restore's extra3300-byte
scratch tail is not proven persistent save data; do not zero or omit it based on
assumptions. Reference conversion and failure-path restoration require their
actual source contracts. Controlled roundtrips, natural gameplay persistence,
flash durability and physical hardware remain separate evidence.

## Group order

| Priority | Group |
| --- | --- |
| 1 — active | SAV file format, persisted-field schema and stored-ID/name associations |
| 2 | Battle actions, effects, resolution and turns |
| 3 | Jobs and job changes |
| 4 | Abilities, skills and mastery |
| 5 | Story and authored events |
| 6 | Missions, rewards and progression |
| 7 | Items, equipment and economy |
| 8 | World navigation and map rules |
| 9 | Game menus, input and text decisions |
| 10 | Multiplayer game policy |
| Deferred | Complex engine, graphics, audio, SDK/runtime and hardware bodies |

Source-proven correctness blockers and pending mechanical/production gates retain
precedence at safe boundaries. Work bottom-up within the active campaign, using
small dependency-ready methods followed by real consumers. No fixed size quota,
whole-group reservation, empty-queue polling or renamed terminal retries.
The [battle map/reduce guide](battle-group-recovery.md) remains a reusable method,
not a competing current campaign. Later groups are not empty-queue fallbacks.

## Delivery and completion

Use the pinned fixedO2 method build and [ASM-driven worker strategy](worker-decomp-strategy.md).
Whole exact means complete native identity, with independent mechanical proof
and production-linked confirmation. Preserve existing cause budgets, original
clocks and all failed attempts. Source/data contracts earn no matched-C credit.
[Throughput](c-recovery-throughput.md) uses unique matched original ASM envelope
bytes; local, independent and integrated gates are reported separately.

Campaign closure requires the three file-format gates and reconciliation of
stored sections, reference/ID mappings, checksums, versions/slots and unknown
tails/padding. Reuse frozen source contracts without redoing their catalogues.
Source-only evidence does not claim working file edits or hardware success.
Keep ROMs, saves, extracted strings/assets and all personal paths out of public
content. Publish only portable tools, source-derived format descriptions and
appropriately licensed methodology through the normal release workflow.
