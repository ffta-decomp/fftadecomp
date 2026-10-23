> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Effect application root: model the fixed RAM object and its typed tail

`ActionDependency_0013388C`, entry `0x0813388D`, is 228 bytes: 216 instruction
bytes and 12 literal bytes. The fixed O2/interwork reconstruction reproduces the
complete envelope. This is matching refinement of existing semantic C, not new
semantic or integrated recovery.

## Original structure

The root clears flags bit 0x20 before its compatibility gate. After the indirect
callback it reloads the descriptor selector; selector 70 adds bit 0x200. A flags
0x100 guard skips the kind/application/notification group. The kind query may run
twice, with low-byte comparisons and short circuiting. Positive selected amounts,
negative signed descriptor metadata, and other kinds have three original apply
callsites joining at notification. The normalizer and two unit refresh calls
reload the affected and actor pointers separately. Preserve these boundaries.

## Measured address-model cause

A constant C pointer to `0x0200F3F0` plus raw byte arithmetic for the amount
produced an extra `0x0200F410` literal and a 232-byte output, four bytes over the
original. Equivalent halfword indexing and a pure inline accessor emitted the
same binary. An unchanged-source dump placed the first folded amount-base
constant in CSE insn161; it was absent from initial RTL. This was not a late
register-allocation diagnosis or a reason to switch optimization levels.

Declare the actual fixed RAM object by a symbol-only address binding, then use
its address. The declaration emits no instructions and does not bind a register.
This removes the constant-pointer CSE fold but initially produces a different
224-byte indexed load. A typed view with a 32-byte prefix and a signed-halfword
trailing array restores the original base/index computation and all 228 bytes.
Use the pinned compiler's GNU zero-length trailing member: a one-element array
would assert an unjustified bound for a byte-sized selector. No sizeof/allocation
uses this view, and no logical slot capacity is claimed.

Do not generalize this to artificial accessors or arbitrary array views. Both
the fixed transaction object and amount base/width/stride come from original
loads. No volatile, register binding, barrier, dummy operation or flag change
was used. The last declaration repair emitted identical code to the preceding
exact candidate.

## Evidence limits and cost

Nine candidate-side root cases pass against frozen independent retail evidence:
eight real unchanged callbacks and the rejected pre-gate path. Expected memory,
declared interfaces, entry counts and custom callback oracles remain. Only
source-declared root argument counts are compared; scratch registers are not
invented arguments. These controlled cases do not establish natural gameplay
or every amount/metadata branch. Complete machine-code equality is separately
verified. Final binary SHA-256:
`b1a2ee4c8cefef5b7581b6599971145c0e7a1a78a4e47f2b1c344ca282824d5c`.

The initial 232-byte result and unsupported equivalent expressions remain in
history. The method was briefly blocked, then reopened after direct user
self-selection authorization. Whole-method time must include that gap from the
original start; the new claim clock is not a new delivery denominator. No
fivefold or cross-method savings claim is made. Independent peer acceptance and
production integration are pending.
