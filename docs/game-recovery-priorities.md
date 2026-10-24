# Game recovery priorities

## Active campaign: save/load and displayable save contents

Save/load is the current first priority. Finish and deliver already owned
functions and preserve running integration before changing source scope.
Contributors claim disjoint complete methods through the existing ownership
workflow; current maintainers coordinate availability. Historical battle work
remains valid, with explicit residuals, and is not declared complete.

The goal is source-proven save formats and game-state interpretation sufficient
for a future tool to display save contents. Recovering a codec alone is not
complete. Editor implementation is a later task.

## Current recovery scope

- Slot selection, signatures/versions, image lengths, checksum/validation,
  encode/decode, reference conversions, save/load outcomes and restoration.
- Units/roster, jobs, levels/stats, abilities/mastery, inventory/equipment and
  quantities, money, missions/quests and rewards, flags and stored world/story
  progression, player/clan fields and other actual stored sections.
- Complete enumerations of stored item, mission, ability/skill, job, unit and
  other referenced ID domains. Trace table bounds/stride and encoded-index rules,
  sentinels, validity, associated text IDs/pointers and the original text decoder.
  Unknown entries remain explicit; guessed names are not resolved identifiers.

Keep encoded file offsets, decoded-image offsets and live RAM addresses distinct.
For each field record width, count/stride, endian/signedness, masks, slot/version
conditions, producer/consumer and source evidence. Catalogue coverage reports
resolved/total entries separately from matched-code bytes; unknown totals stay
unknown. Reuse existing decoded tables and recovered methods instead of creating
new recovery credit for them.

Necessary cross-system saved-data dependencies may be recovered early, retaining
their real semantic owner and counting each native range once. This does not
expand into independent battle/skill/story gameplay rewriting. Confirmed SDK,
flash/SRAM drivers and complex engine implementations remain behind accurate
interfaces. Complexity or a callback label alone does not establish exclusion.

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
| 1 — active | Save/load, saved-field schema and ID/name catalogues |
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

Campaign closure also reconciles every stored section, catalogue mapping,
text lookup, codec/checksum, reference fixup, version/slot branch and explicit
unknown tail/padding. Display coverage and natural persistence are distinct from
code match. Source-only evidence does not claim working editing or hardware.
Keep ROMs, saves, extracted strings/assets and all personal paths out of public
content. Publish only portable tools, source-derived format descriptions and
appropriately licensed methodology through the normal release workflow.
