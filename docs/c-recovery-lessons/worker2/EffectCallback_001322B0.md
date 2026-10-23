> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# EffectCallback_001322B0: typed ordinary-RAM update after a callback

## Gate and evidence

- Original Thumb envelope: 138 bytes at ROM offset `0x1322B0`, entry `0x081322B1`.
- Gate reached: local whole-function exact under fixed `-O2 -mthumb-interwork`; independent acceptance and production integration remain pending.
- Original ASM SHA-256: `a3c3150ff2ae2054b1948aabcaf51f74bca9c3c432fcce63f5f223c277b99e08`.
- Candidate C SHA-256: `3bb53b128916f5c03e0d1b65d6198069af92deaa1cdc62dc47cae955af72e9aa`.
- Header SHA-256: `0f54db1984318c06388592f69a8aafcdfe3800b87898574186424104c8298baf`.
- Exact candidate binary SHA-256: `51b91dc00b91af6b878855e57d1a8cea8c8b0c5928174a3d2360e9b61bbdd203`.
- Seven source-derived cases passed against retail and candidate, including one row-28 descriptor-root path. A deliberately incorrect memory expectation was rejected. The callback's return is void; incidental `r0` was not compared.
- Full method gross time was 1,389.735 seconds, including source recovery, failed source shapes, fixture correction and execution. No throughput reduction is inferred from one method.

## Original object and source representation

The callback receives an `ApplicationContext *` in `r0`. Its affected-unit pointer is a full 32-bit value at `context + 8`; flags are a `u16` at `context + 0x26`. Predicate results are tested through their low byte. After helper calls, the original reloads callback-visible flags and affected pointers at the observed branch sites. The final effect-22 continuation performs a halfword clear at the reloaded affected pointer plus 212.

Most callback-visible reads retain the `volatile ApplicationContext *` type. On the first branch, after `SetUnitStateE8Bit4` returns, the exact source expresses the flags update as a typed ordinary-RAM field RMW through an `ApplicationContext *` cast:

```c
((ApplicationContext *)(void *)context)->flags |= 0x0100U;
```

This produced the original post-call halfword load, register flow, OR and halfword store. The generated 140-byte `.text` ended in a validated `C046` alignment instruction; strict preflight trimmed that two-byte tail to the selected 138-byte envelope. The internal compiler pass responsible for the changed instruction selection was not isolated; only the C-to-generated-object result is established.

## Failed hypotheses and limits

- A volatile field store with explicit snapshot/value locals caused extra halfword reads and failed the strict terminal-trim gate in three forms.
- Reversing commutative OR operands made no binary change.
- A destination-mask local altered the original value lifetime and generated a shorter, nonmatching body.
- The successful cast is justified here by the ordinary EWRAM context field and the original post-helper access order. It is not evidence to remove `volatile` from MMIO or asynchronously modified state, nor to cast unrelated fields.
- This method had an existing semantic C implementation, so this result adds exact local reconstruction evidence, not new semantic-recovery credit. The bounded cases do not prove natural callback domains or whole-game effect behavior.

## Transfer check

For the next callback, first compare its original ASM and layout for the same narrow pattern: one post-helper `u16` flags RMW in ordinary RAM, no intervening call, with other callback-visible loads kept volatile. If those preconditions hold, test this typed-store representation once against its original envelope and independent cases. Otherwise do not transfer the cast.
