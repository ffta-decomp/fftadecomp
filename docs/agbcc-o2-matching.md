> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Matching C with the pinned agbcc O2 compiler

Use this guide to predict an original Thumb instruction pattern before editing C.
A semantically correct implementation is not necessarily a reconstruction of the
original compiler input. Matching requires the original object layout, C integer
conversions, expression graph, control-flow joins, alias information and live
ranges to survive this particular compiler's passes.

## Actual build, not a generic GCC O2 recipe

The pin is `pret/agbcc` commit
`da598c1d918402c42c0c0d7128ba14567f3175e9`, version
`2.9-arm-000512`. `tools/bootstrap.py` builds its normal `gcc/Makefile` target;
`old_agbcc` and the separate ARM compiler are not the production compiler.
The audited binary SHA-256 is
`e3d0587078cf090b0e465e0b417c8ec9c73fdf88238e8fb3a8af62edd4d202a2`.
A changed binary invalidates these code-generation observations until checked.

The method pipeline in `tools/build_rom.py` is:

1. Host Clang preprocesses with `-E -P -x c -nostdinc`, project include paths,
   and the module's `-D`/`-U` options.
2. agbcc compiles that exact `.i` with `-O2 -mthumb-interwork`.
3. GNU `arm-none-eabi-as` assembles with `-mcpu=arm7tdmi -mthumb-interwork`;
   linking fixes symbols and placement, then extraction produces the compared span.

The host preprocessor does **not** receive `-O2` or a GBA target. In the measured
host environment, `__SIZEOF_POINTER__` and `__SIZEOF_LONG__` are 8, `__LP64__` is
1, while `__arm__`, `__thumb__` and `__OPTIMIZE__` are undefined. agbcc still uses
32-bit target pointers and words. This is a conditional-header hazard, not proof
that an existing game header is affected. Inspect the `.i` if conditional
compilation changes a type or body; host macro values are not target ABI evidence.

Do not rely on the builder's missing-flags fallback: candidates must explicitly
record the fixed profile. Keep CPU, ABI, interworking, preprocessing and placement
identities with each result. The chosen configuration is not proof of the original
ROM's compiler version or optimization level for every translation unit.

## What this O2 actually does

The authoritative list is `vendor/agbcc/gcc/toplev.c:3595`, not a modern GCC manual.
O1 already enables jump threading, deferred pops and frame-pointer omission.
O2 additionally enables extended CSE across branches, global CSE, expensive
optimizations, strength reduction, repeated loop optimization, CSE after loops,
caller saves, forced memory operands into registers, register-move optimization,
and strict aliasing. Automatic general function inlining is enabled at O3;
explicit `static inline` can still inline at O2. None of this authorizes flag trials.

The relevant order is:

`RTL expansion -> jump cleanup -> CSE -> GCSE -> loops -> CSE2 -> flow/liveness
-> combine -> regmove -> local allocation -> global allocation/reload
-> hard-register CSE -> final cross-jumping -> Thumb reorganization -> emission`.

This fork's `rest_of_compilation` has no standalone instruction-scheduling pass
call. Do not label every instruction-order difference a scheduling problem.
First locate the pass that changes the expression, branch or live range.

## Measured source-shape results

The administrator's 30-function synthetic corpus is
[tools/fixtures/agbcc_o2_shapes.c](../tools/fixtures/agbcc_o2_shapes.c).
The fixed-profile normal and `-da` diagnostic compilations emitted identical
608-byte `.text` sections. Twelve assertions checked the observations below.
These are code-generation observations, not recovered game functions or behavior
acceptance. The external study receipts retain tool/source hashes and commands.

| Original feature or observed mismatch | Measured cause | Source rule |
| --- | --- | --- |
| Record stride 70 versus generated stride 72 | `struct { u8 bytes[70]; }` has size72; packed has size70. The backend rounds ordinary structures to32-bit boundaries. | Recover physical packing and assert sizes/offsets with target-compatible assertions before matching loops. Do not add guessed packing globally. |
| Two byte loads plus OR versus only a high-byte load | Explicit byte composition loses its unused low-byte load at `combine`. A packed `u16` field retains both loads in this corpus, including masked and branch uses. | Recover the logical field type as well as physical accesses. Check `.combine`; a correct source type is not a universal promise that every caller preserves the same loads. |
| Table base plus field offset versus one folded address | A numeric fixed base folds `base+69` in initial RTL; an external table symbol preserves a separate offset in the measured expression. | Reconstruct actual global objects and linker-bound symbols. Do not replace all objects with integer-address macros or invent an accessor to hide folding. Check each use site. |
| Two source tests become one mask comparison | `(x&1)&&(x&2)` and `(x&3)==3` produce the same final pattern in the minimal sample. | Parentheses and equivalent boolean spelling may disappear before useful RTL. Repeating such spelling changes is not a new hypothesis. |
| Boolean initialization order differs | A direct interval comparison and an explicit numeric-result inline helper retain different initialization order. | Preserve the original evaluation/truncation point and value lifetime only where the ASM supports it; validate transfer per complete method. |
| Different tail-call merging | Two early-return calls merge into one call at `jump2`; an explicit result variable/shared return retains two calls in this sample. | Match incoming edges and result lifetime. “One return is always closer” is false. |
| Spills, saved high registers, larger frame | Low-register constraints, cross-call liveness and reload act after expression and CFG optimization. | Establish widths/CFG first. Then inspect live ranges and stack-slot roles; source declaration order is not a register assignment contract. |
| Literal locations/PC-relative offsets move | `thumb_reorg` creates constant pools after allocation and jump optimization; final branch shortening follows. | Fix the earlier instruction/CFG cause before chasing literal ordering or raw same-offset byte counts. |

A packed-field probe succeeding does not overturn a failing whole-method result.
Inlining, surrounding operations, types and expression modes can change later
passes. Transfer only a measured rule with its preconditions.

## Width, aliasing and call-lifetime probes

The worker independently compiled four paired synthetic examples on the same
profile. Its u16 loop keeps an increment truncation (LSL/LSR16) and indexed
address calculation; the u32 loop advances a pointer by2. Their behavior is only
comparable in the stated nonwrapping domain. A pre-helper snapshot loads before
BL and preserves its value; an explicit post-helper read loads after BL. These
are different memory-observation contracts, not interchangeable speed tricks.

The typed-cast versus character-byte example establishes different access widths,
not an isolated causal test of strict-alias optimization. Its invalid type-punning
case must never be copied into game C. The call-lifetime pair also passes different
helper arguments, so it is illustrative, not a controlled equivalence experiment.
Initial RTL differences alone do not prove which later optimization caused a
final mismatch. Follow the relevant operation across passes within each probe.

Dump file modification time is not pass order: the `.combine` file can finish
writing after `.mach`. Use `toplev.c` execution order. A dump hash difference only
locates a changed artifact; it does not identify a semantic or allocation cause.

## Thumb addressing limits need separate diagnosis

`gcc/thumb.h:808` rejects REG+REG memory addresses before reload completes.
Its comment explains the shortage of guaranteed low reload registers. It permits
those addresses afterward. `reload1.c:reload_combine` recognizes a narrow pattern
involving a preceding constant assignment and an in-place addition; it is not a
general optimizer for every `base + index` expression.

The fixed O2 corpus emits `add` followed by `ldrb` for `p[i]`, and analogous
separate address calculations for unsigned halfword and word indexing. It also
emits `mov r2,#0; ldrsh r0,[r1,r2]` for a signed-halfword load. Therefore
“agbcc never emits register-offset instructions” is false, and the appearance of
`ldrsh`/`ldrsb` does not prove a dynamic array index. Those signed Thumb forms use
register offsets even for zero or constant fields.

The 23 original core envelopes sampled in this study cover8,120 bytes and contain
23 decoded register-offset memory instructions. Example roles differ:
`0x0803892C` combines a running workspace address with a constant0x916;
`0x0809B838` is a signed field read with offset24;
`0x0809B858` is a signed byte read with offset0. They must not share one guessed
source template. Site records are retained in the private study index.

If a structurally correct source still cannot express an original addressing
pattern, reduce that pattern to a tiny fixed-profile experiment and inspect
address legitimation and reload. Record a possible backend/version limitation.
Do not keep permuting game C or silently patch the production compiler. Neither a
failed minimal probe nor the existence of other matched functions identifies the
ROM's complete original toolchain.

## First-divergence procedure

Before editing, record one hypothesis as:
`original site -> intended source object/type/expression -> responsible pass
-> predicted instruction change -> behavioral obligations`.

1. Confirm the `.i`, target field layout, argument/result widths and original
   CFG joins. Compare original operations and def-use chains, not only instruction
   positions. An early extra instruction shifts subsequent bytes.
2. If final ASM does not distinguish the competing causes, or an equivalent
   spelling has already emitted the same binary, produce one diagnostic dump
   from the same frozen source/header and fixed configuration. A small localized
   difference with a source-backed prediction can proceed directly to one
   candidate; effect 92 closed three address instructions without a dump.
   `-da` is diagnostic output, not another optimization profile.
   It covers `.rtl`, `.jump`, `.cse`, `.gcse`, `.loop`, `.cse2`, `.flow`,
   `.combine`, `.regmove`, `.lreg`, `.greg`, `.jump2`, and `.mach` in this fork.
3. If the wrong expression exists in `.rtl`, fix type/object/AST expansion.
   If CSE/GCSE changes it, inspect common values, aliases and branch structure.
   If `.loop` changes it, inspect induction width, stride, bound and reloads.
   If `.combine` removes an access/extension, inspect mode and the value's uses.
4. If the structure survives until `.lreg`/`.greg`, inspect cross-call lifetime,
   simultaneous live values, register classes and reload. Do not invent
   `volatile`, padding or assembly barriers to force a register.
5. If only `.jump2` or `.mach` differs, examine shared tails, barriers and literal
   pool placement. State which earlier property constrains the final arrangement.
6. Make one supported change, compile only the method, then run the relevant
   independent cases for a changed fitting binary. Preserve the failed hypothesis
   and its exact pass. Unchanged binaries can reuse identity-bound results.

Use focused dump excerpts for the affected function/basic block; do not load
whole-program RTL. A failed hypothesis should remove a class of future trials.
Measure time to a useful diagnosis as well as time to whole-function acceptance.
A structural improvement still earns zero exact-C bytes until the complete
original function matches and its acceptance gates are met.

The [recent attempt patterns](o2-rewrite-attempt-patterns.md) distinguish the
descriptor-root CSE address fold, initial-RTL signed operand modes and effect-91
loop induction rewrite. These are different causes; do not label them all
register allocation or apply one accessor/cast rule to all three.

## Reproduce the synthetic corpus

Use a new owned directory under `build/`. Run the same preprocessing helper as
production, then the pinned compiler:

```text
clang -E -P -x c -nostdinc -I include -I build/generated \
  tools/fixtures/agbcc_o2_shapes.c -o build/<owned>/shapes.i
build/toolchain/agbcc -O2 -mthumb-interwork \
  build/<owned>/shapes.i -o build/<owned>/normal.s
build/toolchain/agbcc -O2 -mthumb-interwork -da \
  build/<owned>/shapes.i -o build/<owned>/diagnostic.s
arm-none-eabi-as -mcpu=arm7tdmi -mthumb-interwork \
  build/<owned>/normal.s -o build/<owned>/normal.o
```

Assemble the diagnostic output with the same assembler, extract `.text` with
`objcopy`, and compare those sections. The synthetic corpus has unresolved
external symbols/calls: object text identity checks diagnostic neutrality only,
not linked-ROM equivalence. Generated files stay outside tracked source.

## Primary references

- [Pinned O2 defaults and pass driver](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/toplev.c).
- [Pinned Thumb ABI, layout and address legality](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/thumb.h).
- [Pinned instruction patterns](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/thumb.md),
  [reload implementation](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/reload1.c),
  and [prologue/literal-pool output](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/thumb.c).
- [Contemporary GCC2.95.3 optimization documentation](https://gcc.gnu.org/onlinedocs/gcc-2.95.3/gcc_2.html#SEC10)
  is background; the pinned fork's source decides actual behavior.
- [Upstream addressing discussion](https://github.com/pret/agbcc/issues/92) contains
  an author's correction and a maintainer's warning that agbcc does not cover all
  real-game compiler variants. Its broad initial claim is not adopted here.
