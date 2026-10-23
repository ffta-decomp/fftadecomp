> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Mission queue timer transitions: preserve scan and byte-object lifetimes

`CoreFrontier_000CF51C`, Thumb entry `0x080CF51D`, original envelope 370 bytes.
Fixed `-O2 -mthumb-interwork`, agbcc revision
`da598c1d918402c42c0c0d7128ba14567f3175e9`.
The round05 candidate reproduces all 370 bytes, including the original literal
and alignment placement. No mixed code or relocated body is used. A separate
compiler terminal NOP follows the function and is excluded by the explicit
2-byte trailing-alignment declaration; no live instruction is trimmed.

## Observed source structure

- Keep the initial head used for the null guard separate from the traversal
  iterator established afterwards. This restored the original initial register
  allocation without changing global reload timing.
- Model the record's actual packed three-bit status field. It reproduced the
  original left/right shifts and masked field update; an algebraically equivalent
  raw-byte representation generated a different instruction sequence.
- Each of the original two pool searches has its own short-lived scan cursor.
  Assign a separate removed-node output only on the found path. Reusing that
  output as the induction cursor merged two lifetimes and changed allocation.
  Preserve the two searches and their distinct entries into the shared unlink.
- Compare the byte timer object and decrement that object directly. A separate
  local timer used as the arithmetic source merged the promoted comparison value
  and byte-update value. The original keeps the comparison in r1 while updating
  through r0. Direct byte-object read/modify/write reproduced that copy.

The final instruction-level observations are verified by exact comparison.
The initial-RTL/CSE explanation of the last timer change is a mechanism
hypothesis, not a newly instrumented pass observation. Earlier unchanged-source
RTL diagnosis located initial head/iterator lifetime formation; it did not
establish a universal byte-arithmetic compiler rule.

## Evidence and failures

Local source SHA-256:
`07ce0d2844e9caeeaad8ba5cf010c59b97ae169fd08a721898dbf802d738cad9`.
Binary SHA-256:
`472e988a3daa77100e84decd32f9519e5efc52034938b8dcf321c313eb9ec70d`.
The local report captures header, compiler, binutils and native dependency pins.
Five frozen independent direct cases pass, with full expected memory and helper
call order preserved; the original IWRAM clear executes. Void r0 is not compared.
Independent peer acceptance and production integration remain pending. This is
not new semantic recovery or proof of natural gameplay coverage.

The complete first candidate generated 360 bytes; head lifetime kept 360, timer
local width alone was binary-identical and reused its prior cases, packed status
made 364, separate scan/output made 370 executable bytes, and direct object
update made the 370-byte body wholly exact. Preserve the failed metadata attempt
and the 372-byte preflight rejection preceding verified NOP classification.
No optimization-level changes or compiler modifications were used.

## Transfer boundary

Use these forms only when original object widths, scan/output def-use and
post-helper reloads support them. This is ordinary game RAM; it is not a rule
for MMIO, asynchronous memory or arbitrary removal of volatile. The pool-owner
invariant remains unproved: retain the original null-on-search-failure behavior,
not a new guard. The next mission reward method should be mapped from its own
halfword/object accesses before transferring a representation.

Full elapsed through the local exact decision: 1095.276 seconds; eight candidate
command attempts plus one unchanged-source diagnostic. Local exact output rate
1216.132 original bytes/hour; independently accepted and integrated output are zero.
Lesson/freeze preparation remains charged in the subsequent checkpoint. No
measured cross-method time saving is claimed.

Original span classification: 156 Thumb instructions / 332 instruction bytes,
36 literal bytes and 2 internal alignment bytes = 370 bytes. The separately
trimmed compiler terminal NOP is outside this original envelope.
