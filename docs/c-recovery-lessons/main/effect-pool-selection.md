> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Effect 92: typed tail access preserves the original address association

`EffectCallback_001337F4`, entry `0x081337F5`, is 152 bytes: 132 instruction
bytes, 16 literal bytes and four internal alignment bytes. The second fixed
O2/interwork candidate is identical to the complete original envelope. Existing
semantic C is not credited again; independent acceptance and integration remain
pending.

## Original dataflow

Context bit0x10 rejects before any other effect. Pool count at RAM base+0x3c33
zero sets context bit0x100 and returns. Otherwise set unit+40 bit0x40, then
snapshot unit byte260 before calling random. Normalize the random return's low
halfword as signed16; reload pool count after that call for signed modulo.
Select the first byte at base+0x3c34+2*remainder and call the existing three-arg
choice helper with the saved unit slot and zero mode.

Reload context+4 after that helper. A current counter byte259 above8 skips the
progress query. Otherwise query progression13; low-byte one skips increment.
For other returns, reload the unit and counter again before the byte increment.
There is no post-query clamp: a helper may retarget to a byte255, which wraps to0.

## Matching change

The first source used raw byte arithmetic for the selected choice. It fit the
full 152 bytes, with five differing bytes in three instructions. At0x08133848
it added the runtime base to the scaled index first, then loaded/added0x3c34.
The original first forms the choice-field base and then adds the scaled index.
Using the source-proven trailing field `runtime->choice_bytes[selected * 2]`
restores those instructions and all152 bytes. No header, flag or ABI change was
needed. The field is an old-GCC zero-length trailing-array view, not a claim
about the logical number of entries. Signed synthetic remainder/address cases
are separately tested; no natural negative-index producer domain is claimed.

This transfers the previous descriptor-root object-layout observation only
because original loads establish this field base and byte stride. It does not
justify inventing arrays or changing arithmetic to improve scattered matches.
No pass diagnostic was needed to locate the three visible instructions; no
specific internal-pass cause is claimed here.

## Validation and limits

Two existing independent direct/root cases pass using frozen retail evidence
and its corrected ABI adapter. Eleven new source-derived paired cases cover
empty/blocked pools, counter0/8/9, low8 flag contrast, RNG changes to count/slot,
post-choice unit replacement, post-flag retarget/wrap and a signed-negative
remainder address. Their full context/unit/pool memory and helper-call arguments
are asserted. These additions are implementer-authored and await peer review.
A real LSL1-to-LSL2 instruction mutant changes the empty-pool flag from0x100 to
0x200 and is rejected by the memory oracle. An initial negative-control command
failed before execution because it omitted the pinned Unicorn environment; the
corrected command and failure are both retained.

Final binary SHA-256:
`8703f1c1e7f521c117276d8f59eb264455a4bcd6c344dbf9e457eca28ff51254`.
Two candidate compilations were used, with no optimization switching or full
build. Frozen timing records include source work, custom-case preparation,
failed commands and publication, not just compiler time. No natural gameplay,
physical hardware or measured fivefold throughput improvement is claimed.
