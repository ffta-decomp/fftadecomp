# O2 near-match transfer: preserve the address graph before constraining allocation

Use only after the original complete operations, widths, CFG and call/alias-visible reloads are established. This is one observed whole-exact transfer, not a universal fix or authority to reopen a terminal method.

## Observed sequence

An 80-byte cached-record scan reached these fixed-O2 results:

| Source cause | Complete generated size | Same-offset original bytes | Decision |
| --- | ---: | ---: | --- |
| Initial packed 10-bit field implementation | 88 | 9/80 | Overflow; loop/frame wrong |
| Original bottom-tested loop CFG | 80 | 64/80 | Fit; allocation still differs |
| Explicit state load/byte offset | 80 | 68/80 | State load order repaired; address graph still wrong |
| Initialized embedded-base/slot lifetime constraints | 80 | 71/80 | Address graph repaired; ordinal/mask/offset allocation remains |
| RTL-backed ordinal/offset interval constraints | 80 | 80/80 | Whole exact; zero emitted inline instructions |

A C89 declaration-order failure is retained between the last two nonexact steps. Total: five source causes, six normal compiler starts including that failure, plus one unchanged-source RTL diagnostic. The first exact round occurred 300.866845 seconds after the original recorded start; this is not the later local, independent or integrated gate latency. Preparation before that clock and later handoff/registration costs are not erased. Local5206 and independent5207 now exist; integration remains separate.

## Mechanism to transfer

The original address operations form `offset = index * 4; base = state + 36; slot = base + offset`. An earlier candidate still formed `offset = index * 4 + 36; slot = state + offset`, despite its repaired state-load order. The effective address agrees but the original definition graph does not. A final wrong register therefore does not establish an allocation-only discrepancy.

Preserve the real initialized embedded-array base at its observed definition/use boundary before investigating hard registers. If ordinary C still folds this actual intermediate, a truthful empty read/write operand can expose the required boundary. Do not invent a load, dummy value, volatile RAM object or output-only definition. The example retained separate initialized base, byte offset and slot values; it did not replace logic with instruction ASM.

Only after that graph agreed did existing local/global allocation RTL identify a loop-live ordinal competing with the mask and a short-lived shifted offset. One supported cause bound the initialized ordinal and actual offset at their narrow required uses. The combined formulation matched all80bytes including the literal. This observation does not prove each individual constraint is necessary, that declaration order determines registers, or that the same hard-register names transfer to another function.

## Application decision

1. Compare the earliest original/generated definition, not only the final mismatched operand. Distinguish base-plus-field from induction-plus-field and retain original root reloads.
2. Restore CFG and actual phase/loop lifetimes first. Reuse the existing mismatch/vendor lookup; do not enumerate loop spellings or flag levels.
3. If an allocation cause remains, use existing RTL to identify the actual initialized value, definition/use interval, conflicts and call crossings. Propose one falsifiable change and keep the original budget.
4. Validate complete original instructions, literal/jump tables and alignment. Empty constraints emit zero inline instructions, but may still alter scheduling or distant branches. Fit and same-offset progress do not count as whole exact.

The published failure cases remain important: an R9 context constraint improved a different304-byte method from287 to291 same-offset bytes but did not match it; a real initialized R1 address hypothesis regressed a76-byte method from a prior71-byte best to19same-offset bytes. A truthful constraint is permitted, not guaranteed useful. These terminal tasks remain closed.

For compiler semantics and vendor counterexamples, use the pinned references in [the near-match card](register-allocation-near-match.md), [worker rules10–12](worker-decomp-strategy.md#10-separate-different-phase-lifetimes-before-pinning-registers) and [vendor symptom lookup](vendor-matching-playbook.md).
