> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Fullword zero lifetime and small-block allocation

Method: `CoreRegion_00038820`, pending acquisition initializer. The complete
56-byte envelope is locally exact: 42 instruction bytes, 12 literal bytes and
2 alignment bytes, with no retained suffix. The fixed profile is
`-O2 -mthumb-interwork`, agbcc revision
`da598c1d918402c42c0c0d7128ba14567f3175e9`.

## Gate and source evidence

The original performs a byte count clear, then sixteen ID-only halfword clears.
The workspace pointer is reloaded in each iteration; other record fields remain
untouched. A single fullword zero feeds the byte store and initial signed loop
ordinal. The successful source separates the immutable cleared-count value from
the subsequently incremented ordinal. Both uses correspond to real operations;
there are no dummy uses, forced registers, volatile barriers or assembly.

The frozen G41 round01 source/report/compile-input hashes and exact allocation
receipts accompany the promotion package. Binary SHA-256:
`38fa0bf3b6a11d9bdc860f2522bdf366ffb0170c659bf15a964c568c78ffca0a`.
Two carried-RAM lifecycle scenarios pass 46 candidate invocations, reusing the
frozen retail outputs and their custom state, queue and inventory assertions.
Independent implementation acceptance and production integration are pending.
This is not new semantic recovery or natural gameplay evidence.

## First responsible mechanism

The earlier 51/56 candidate has two local quantities. The loaded workspace and
count address coalesce: four references over six half-instruction lifetime units
produce priority 13333. The global pointer-cell quantity has three references
over ten units, priority 3000. Local allocation therefore gives the context r0
and the cell r1, opposite the original prefix.

A separate fullword zero snapshot creates a third local quantity. The pinned
small-three-quantity comparison network compares fixed quantity IDs during each
exchange; its resulting order is cell, context/count, zero. The cell now receives
r0, context/count r1 and zero r2. These quantities and ordering are reconstructed
from the frozen dumps and exact allocator source, not an instrumented build.

Two SImode zero definitions still exist through local allocation. In the global
allocation/reload dump, the ordinal definition is deleted because r2 already
contains the same fullword zero. A preceding attempt with a separate QImode zero
restored prefix allocation but retained a second SImode zero initialization.
The successful fullword source representation removes that actual difference.

## Failures and transfer limits

Old pointer spelling and declaration permutations converged to the same 51/56
binary and were not rerun. The G41 stored-byte/read-back attempt generated
56 bytes but only 28 same-offset bytes, including a redundant zero instruction;
it passed the same 46 lifecycle invocations. The next source correction produced
56/56 exact bytes. Observational dumps were checked against unchanged assembly.

This result is specific to the pinned allocator, register modes and small-block
quantity count. It is not permission to add unused variables to manipulate
allocation. Transfer only when the original has a fullword value shared by an
initial narrow store and a later mutable value, and verify its actual def-use,
mode and compiler passes. The numerical allocator receipt is required before
attributing a register choice to declaration order.

## Measured cost

G41 used two candidate builds and two unchanged-output diagnostic compilations.
The first local build took 1.909873 seconds; its candidate lifecycle took
0.695308 seconds. The exact candidate lifecycle took 0.688984 seconds. Complete
gross and decision-to-decision times are pinned in the G41 decision receipt,
including analysis, prior-artifact recovery and uninstrumented gaps. Historical
G39 work is preserved separately; neither compiler time nor these two trials
establishes a workflow speedup.

Next application: inspect initialization and loop-seed modes before introducing
a shared loop variable. Test the rule on a different source-backed method and
record success or a counterexample rather than assuming universal benefit.
