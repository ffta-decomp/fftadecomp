> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Call boundaries and small records under fixed O2

These are transfers from frozen successful owner lessons, not administrator C
acceptance or newly executed tests. Compiler passes were not traced. Preserve
the exact caller, field and dataflow preconditions before reusing a source form.

| Original evidence | Measured result | First-source question |
| --- | --- | --- |
| `CoreFrontier_0005DF94` passes an already ten-bit value in a full argument register; the original caller performs no further narrowing | A provisional `u16` parameter generated extra shifts. The caller-faithful declaration improved 336 to 800 equal bytes; the method eventually reached 960/960, local credit 740 | Does the original caller narrow this argument, or does the callee merely consume its low bits? Record these separately before choosing the interface |
| The same method invokes a loaded callback pointer; `SceneRegisteredRoot_00023488` also uses a stored callable | Native typed invocation restored the first method's load order (800 to 815 equal). In the second, replacing an artificial four-argument trampoline restored 181 to 216/216 | Is this an ordinary source-proven function pointer with a known ABI, or a special internal entry? Do not add a routine-address argument merely to call a trampoline |
| `CoreFrontier_0005DF94` accesses a byte field in physical two-byte records | The final six differing bytes closed when the actual packed two-byte record restored field-base-before-index addressing. An unpacked struct was four bytes and failed its retained size assertion | What is the compiler's actual record stride, not just the sum of member widths? Assert size and field offsets before the first compile |
| The final continuation query has a different live range from an earlier collector result | A distinct result definition removed a return copy and reduced 964 to 960 bytes | Which values actually overlap in lifetime? A renamed variable with the same definitions is not a new cause |

A full-register caller declaration is not a general replacement for narrow
parameters. Preserve argument extension when the original caller performs it,
return width, the callee's actual consumption, and all direct/indirect call sites.
Ordinary C definitions and declarations must remain compatible. Existing ASM
interfaces must explicitly document any caller/callee width distinction.

The 960-byte method took 1106.538 seconds through freezing, including failed
layout assertions, an incorrect preflight invocation and a proof-path correction.
The 216-byte method took 153.656 seconds through freezing. These are different
methods and workloads; they do not establish a speedup ratio. The useful transfer
is to resolve caller widths, callable representation and physical stride in the
existing first-source map, before spending trials on their allocation symptoms.
