> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Predicate uses and reusable family contracts

Choose a predicate representation from its original consumers before the first
fixed-O2 candidate. Similar mathematical conditions can have different value
lifetimes and branch structure.

## Branch-only predicates versus numeric results

In the complete 268-byte battle overlap method, original comparisons at
`0809CAA2` through `0809CABA` branch directly to the non-overlap or overlap
continuation. There is no separate Boolean result between these comparisons
and their consumers. The implementer initially factored an inline overlap helper;
its materialized Boolean produced 276 bytes and changed the subject register.
Writing the strict comparisons directly at their actual branch consumer removed
that intermediate and produced all 268 original bytes on the second source form.
Claim through frozen completion took 88.771 seconds, including the failed form.
The [owner lesson](../sol_b/CoreRegion30_0009C9E8.md) preserves widths, reloads
and the distinct pending-state versus visitor-return effects. The result has
local and independent mechanical whole-exact proof; production integration is
a separate gate. No compiler pass was traced for this change.

The opposite case is equally important: the original mission range test
materializes a numeric 0/1 and compares it later. Its bounded inline predicate
experiment restored that structure but did **not** achieve whole-function exact
matching. See the [original structural diagnosis](../../asm-to-c-migration.md#diagnose-structural-differences-before-chasing-exact-bytes).
Neither example licenses always inlining predicates or always writing direct
branches. Check whether the original result is stored, returned, passed to a
helper, used arithmetically, or merely consumed by control flow. Predict the
result definition and consumer that should disappear or remain; inspect that
specific emitted region before trying another spelling.

## Reuse contracts, then check each sibling's differences

Two complete effect rules provide a measured preparation example:

| Method | Original span | Claim through frozen completion | Actual preparation difference |
| --- | ---: | ---: | --- |
| 131E0C | 34 B | 72.390 s | Established signed metadata-index ABI and verified the compiler's two terminal alignment bytes outside the native envelope |
| 131EC8 | 34 B | 36.464 s | Reused those established interfaces and alignment treatment; independently confirmed index 4 and its own setter; first compilation matched |

The [representative](../sol_b/EffectCallback_00131E0C.md) and
[transfer](../sol_b/EffectCallback_00131EC8.md) both preserve the metadata call
**before** reloading the context's halfword flags at offset `0x26`; mask `0x10`
suppresses only the subsequent unit-state setter. The unit pointer at context
`+0x08`, the metadata bytes at `+0x10`, and the helper-owned unit bits are different
objects. Keep their observed order, widths and ownership separate. A neighboring
callback that omits the metadata call or suppression test is a counterexample,
not a reason to force it into the template.

Reuse hash-bound helper interfaces and physical layouts, plus the precise
alignment proof when it applies. Still confirm each original constant, callee,
branch polarity, reload and full boundary. A terminal compiler pad is not a live
instruction, literal pool or original padding, and must not enlarge recovered
byte credit. Preserve mandatory ABI repairs even when they produce identical
machine code; identical output does not establish the source contract by itself.

These are observed implementation intervals, not an end-to-end speedup estimate:
source intake, administrator preparation, peer waiting and production integration
remain in the overall delivery clock. Record the original precondition and actual
transfer outcome in the existing source map and lesson. No additional mandatory
report, flag experiment, old-method retry or global helper template is introduced.
