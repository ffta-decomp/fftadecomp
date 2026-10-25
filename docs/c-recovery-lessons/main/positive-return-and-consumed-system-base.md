# Positive early returns and consumed store-base definitions

## Positive return ownership after cleanup

- The complete 70-byte ability-source predicate allocates a record buffer, collects source mastery entries, narrows the count, queries receiver incompleteness, snapshots the LOW16 result across freeing the buffer, and returns a boolean. Existing helper ABI and implementations remain unchanged.
- A direct positive nonzero early return restores the original BNE target ownership, zero fallthrough and shared epilogue: 67/70 becomes 70/70 with no constraints or inline instructions. The assigned-boolean join, explicit goto and isolated byte-return forms remain counterexamples; labels and boolean spelling alone did not transfer.
- This reuses the published positive-return family only where original branches and cleanup/result lifetimes support it. Five conservative causes and five actual starts remain charged, including the original four attempts. All 70 native bytes are instructions; a separate compiler NOP lies outside the function and receives no native credit.

## Consume the actual initialized system store base

- A separate complete 236-byte scene-script lifecycle controller uses a persistent pending script ID and flag, captures created handles through reloaded global state, advances phases, and clears/queues content before cleanup. It performs one dispatch per invocation; existing helper contracts and alias reloads stay unchanged.
- Three ordinary source forms produced identical 233/236 output. The only difference exchanged the base and zero registers for the actual active-byte clear. An initialized real system pointer, passed through one truthful instruction-free read/write operand and consumed by that store, restores all three operand bytes. The zero remains an ordinary value.
- This requires the incoming callback argument to be dead and the step pointer to be safely preserved. Live-input home overlap and narrow-normalization range loss remain counterexamples. A fabricated observer or output-only pointer is unsupported. Four source causes and four actual starts remain charged; the complete envelope has 170 instruction, 60 literal (including 20 dispatch-table) and 6 alignment bytes.
- Checker coverage remains contextual: the branch case needs original positive-arm ownership plus the across-free snapshot; the store case needs the same literal/store/zero with swapped operands, a real consumed base and live-input evidence. Frozen positive and negative forms support bounded guidance, not automatic rewriting from register names or byte counts. No compiler replay is needed to publish these lessons.

## Transfer to a three-way signed clamp

- The separate 58-byte unit-property clamp reads fullword property 32, conditionally adds equipment property 15 with unsigned wrapping, then clamps its signed interpretation to zero through one hundred. Helper ABI, snapshots and return width remain unchanged.
- Its original upper BGT targets the constant return while the variable return falls through. A direct positive upper guard restores all five remaining bytes (53/58 to 58/58), without constraints or inline instructions. Inverse guards, goto, assigned-result and physical-R0 joins remain failed counterexamples.
- This is a bounded transfer from the independently accepted 70-byte positive-return case, not a rule for arbitrary boolean or clamp ordering. Six causes and six actual starts remain charged; all 58 native bytes are instructions and the outside compiler NOP is excluded. Checker support would need the actual original/generated branch ownership and proven values, not lexical polarity alone.

- Current checker limits explicitly exclude CFG, alias and RTL value-flow analysis. Instruction-register differences alone cannot establish original source-arm ownership, whether a real store consumes the constrained base, or whether an incoming argument is live. These retained cases therefore remain scoped manual guidance, not safe automatic register or guard rewrites.
