> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Signed script index with an unsigned range guard

`CoreScript94_0000A4F8` is a complete 108-byte nested conditional handler.
The original subtracts one from a selected-unit byte, keeps the shifted result,
checks its unsigned byte against 11, then sign-extends that same shifted value
for a 264-byte record stride. Its script-PC update is a separate shared tail;
the enclosing dispatcher adds the descriptor length afterwards.

The first C draft stored an unsigned byte and cast it to signed only for the
record lookup. It generated an additional left shift before sign extension:
112 bytes against the 108-byte original. A signed-byte local, with an unsigned
cast only at the range guard, restored the original shared value lifetime and
all 108 bytes under fixed `-O2 -mthumb-interwork`.

The address-relative typed view retains the selected byte at +168 and the unit
bank at +0xef4. Predicate calls remain ordered and short-circuited, and their
returns are tested through their low bytes. The helper at `080c8348` is the
existing bit-5 predicate; an earlier intake bit-7 label was not used as a source
contract. No helper implementation or runtime test framework changed.

This is a source-width/lifetime rule for the observed unsigned guard followed
by signed indexing. It does not justify globally changing byte signedness,
assuming arbitrary indices are valid, or calling an isolated source baseline
production recovery. Local complete binary identity and subsequent production
adoption are separate gates.
