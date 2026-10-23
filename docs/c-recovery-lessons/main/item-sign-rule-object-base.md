> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Item sign rule: retain the physical record base

The complete52-byte original method narrows the item ID to16 bits and avoids
all ROM reads for zero. It tests three ordered bytes at offsets26..28 in a
32-byte item definition against63. A true result makes the observed action
consumer negate its signed amount. The effect caption and natural ID bounds
remain unknown; this is a numeric rule, not a complete item-schema interpretation.

The original has a separate match continuation before the loop and one shared
zero/all-mismatch return. Preserving those joins reproduced the control topology.
The first C form used a numeric ROM pointer; the compiler folded base plus26
into literal0851D19A, producing48 bytes instead of52. A typed fixed-address ROM
object symbol kept0851D180 as the record base and the separate field addition.
The second source produced52/52 original bytes under fixed O2/interworking:
48 instruction and4 literal bytes, with no alignment or retained suffix.

The symbol-only binding emits no instructions; there is no volatile, instruction
island, extra bound or helper port. This transfers the observed object/field and
shared-return structure from the related code61 rule without unifying the two
numeric policies. The allocation result is observed output, not a traced
compiler-pass claim. Two source forms and two actual compiler invocations were
used. Whole native identity and strict selection passed; independent frozen
mechanical verification and production integration are separate gates.
