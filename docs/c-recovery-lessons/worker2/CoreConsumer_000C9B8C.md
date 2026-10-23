> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Unit property growth: 628-byte first-candidate match

`CoreConsumer_000C9B8C` increments unit byte9 with low-byte wrap and clears byte10 before an existing bypass query. Its low-byte result can return success immediately. Otherwise the function reloads byte9; above50 it stores50 and99 to the two bytes and returns zero. Seven sequential growth blocks then act only on nonzero values, and the normal result is one.

The fields at26,30,32,34,36,38 are unsigned halfwords; field210 is signed. Keep each original block explicit. Snapshot each full-width property41..47 result as signed32 across signed division by10, immediately add the quotient to the freshly reloaded field and storelow16, then take the original growth snapshot modulo10. Only a nonzero full-width remainder calls RNG. Narrow RNG to signed16 before modulo, and its remainder again to signed16 before comparing against the full signed growth remainder. Reload the field after helpers and wrap additions before the final999 clamp. The clamp for field210 is signed; the others are unsigned.

Ordinary typed fields and one growth local reproduced all628 bytes on the first fixed-O2 compile, including624 instruction bytes and the four-byte999 literal. There is no extra terminal alignment to reclaim. No new helper bodies, loop abstraction, volatile accesses or semantic stubs were introduced. Declarations bind existing exact implementations.

This is complete local machine identity, not a new gameplay-domain test or production integration. The physical full unit size, precise bypass policy and individual field game labels remain outside this method's proven contract. Transfer the ordered snapshot/reload and signed-width discipline, not an assumption that every unit stat shares a type.

Actual claim-to-frozen-packet wall time: 194.009914 seconds.
