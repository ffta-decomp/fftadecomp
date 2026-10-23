> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Physical inventory fields and typed mutation sequences

Two fixed-O2 inventory methods reached full local byte identity with separate mechanical verification: the44-byte selected mission-inventory discard and the160-byte randomized saved-stock removal. This note consolidates their implementers' frozen successful lessons. It grants no new acceptance and does not establish natural gameplay coverage.

## An array field is a source hypothesis, not interchangeable pointer spelling

The original160-byte method scans20 halfwords, collects occupied ordinal bytes, performs four complete shuffle passes, caps the requested count after those passes, clears the chosen slots in order and then compacts the stock. Preserve signed16 RNG normalization and the full signed remainder in the address calculation. Nonempty stock still shuffles and compacts when the requested count is zero; no negative-index or empty-request guard was invented.

The first source's precomputed halfword cursor emitted152 bytes with19 equal bytes at their original offsets. The frozen owner diagnosis records a folded save-base-plus7996 literal, changed scan updates and changed stack-address lifetimes. Representing the actual20-halfword field at offset0x1F3C and indexing it produced160/160 exact bytes. The original separate base/offset constants, ordinal/pointer updates, outer-pass lifetime, swaps and return were recovered together. The source change was confined to this representation; the compiler profile stayed fixed.

Before transferring this form, prove the physical field, element width and observed scan domain. Compare the original address definition and ordinal uses with the candidate's first divergent sequence. An existing indexed loop that already fails is not grounds for another equivalent cast. A different frozen56-byte removal scan changed80 to56 to80 bytes through loop forms without reaching identity: indexing is not a universal fix. The observed160-byte result is source-to-output evidence; the precise responsible compiler pass was not traced.

## Keep the actual mutation widths and captured allocation

The44-byte discard writes a byte identity, a byte flags field and a halfword mission link separately. The original four-byte record layout and asserted offsets justify those stores. A generic word clear would erase the source operation distinction.

Its selection accessor supplies the record pointer. A subsequent100-byte allocation is passed unchanged to the existing compaction/dispatch helper, survives that call, and is then freed before mode4 refresh. Preserving that captured allocation lifetime reproduced the saved-register use without forcing a register or replacing helper bodies. This is a specific game-record mutation, not a rule to migrate every allocation wrapper.

## Measured scope and transfer cost

| Complete original method | Formulations | Claim to frozen packet | Result |
| --- | ---: | ---: | --- |
| Selected mission-inventory discard,0004D7E8 | 1 | 140.409s | 44/44 local exact |
| Randomized saved-stock removal,00128E40 | 2 | 263.556s | 160/160 local exact |

These durations include preparation and closeout. The shuffle's two decisions were140.308s and66.939s from their preceding boundary; they are not compiler timings. The204 original bytes include declared literals/alignment and are not newly generated instruction bytes. Mechanical verification and production integration are separate gates. No controlled speedup or cross-model conclusion follows from these two methods.
