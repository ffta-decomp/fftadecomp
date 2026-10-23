> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Actor-row cleanup: preserve the halfword access class

`CoreMutationDependency_000A53E4` / `ClearActorSelectionAndApplyRowFlags` locally matches its complete 252-byte original envelope under fixed O2/interwork:246 instruction,4 literal,2 alignment bytes. Production integration is a separate gate.

The original clears bit0, sets bit5, and conditionally sets bit8 with LDRH/STRH on unit+40. The first candidate represented individual u16 bitfields; agbcc narrowed those to byte accesses and emitted244B. The second used an ordinary u16 flags field and the original masks, preserving all three separate object reloads. It emitted252/252 exact bytes without flags, volatile, register binding or instruction-bearing ASM. Bitfields were the wrong access class here, even though the logical bit operations agree in simple cases.

Retain the two separate marked-node drain loops, low8 predicate, full32 row flag mask0x800, modes176/106,44-byte stride and live byte count+704. The count location is not an array-capacity proof. The helper can mutate row/actor pointers; each loop condition reloads them, and the final continuation reloads the actor after state updates.

Initial preparation82.232s; second decision28.496s. Gross delivery includes pin/freezing work recorded by the task ledger. No runtime bank or gameplay completion claim was added: the r59 exact path checks final source/header/toolchain/artifact pins and every original byte. This lesson transfers only when the original uses a complete ordinary halfword mask operation; it does not authorize narrowing MMIO, asynchronous state or a source-proven packed field.
