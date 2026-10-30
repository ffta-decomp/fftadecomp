# Diagnose the first causal mismatch

Start from a retained local build. No diagnostic below compiles a candidate,
rewrites a report or grants exact acceptance. A scan returning exit zero means
the scan completed, not that the candidate is correct.

## Compare structure before same-offset byte counts

Classify the first meaningful difference: wrong operation/ABI/width; frame and
OUT objects; CFG and shared definitions; reload/lifetime; allocation; then final
placement/pools. A single inserted instruction or moved block can create hundreds
of positional mismatches. More aligned lines is not more recovered original bytes.

For deterministic source hints:

```sh
python3 tools/check_matching_rewrites.py "$CANDIDATE_C" --json
python3 tools/check_matching_rewrites.py --build-report "$BUILD_REPORT"
```

The checker recognizes specific lexical/instruction patterns: C89 declarations,
width/conversion questions, operand-limit expansion, stack-formal/fixed-register
risk, destructive carriers and repeated output. It is not a C compiler or a
complete ABI/dataflow verifier. Explicit source/ASM inputs are useful for older
report formats; inspect `--help`. No finding is not proof of validity.

## Code displacement and call setup

When blocks are alike but shifted, keep the raw positional result and inspect
aligned instruction addresses/deltas. Find the first insertion or changed CFG
edge before rewriting every differing byte. Unique moved windows are hints, not
proved blocks. For register differences, trace the earliest conflicting value
definition; do not globally rename registers. For call setup, check actual
callee identity, r0-r3 definitions and stack stores, then their dependencies.
Equal setup text in a different order can still carry different values.

Use the retained report with `tools/diagnose_module_build.py`; the optional setup
and exact command follow. No fresh compilation is required for this view.

## Displacement, registers and outgoing arguments

Install only the optional diagnostic dependency, once:

```sh
git submodule update --init vendor/asm-differ
python3 -m venv build/asmdiff-venv
build/asmdiff-venv/bin/python -m pip install -r tools/asmdiff-requirements.txt
```

The adapter uses simonlindholm/asm-differ (Unlicense) pinned at
`0dd09af8f8008f1f880327cf0aca3b26d2562ea2`. GNU ARM objdump must be available.
The required compiler submodule remains independent of this optional dependency.

```sh
build/asmdiff-venv/bin/python tools/diagnose_module_build.py \
  --build-report "$BUILD_REPORT" --output "$NEW_DIAGNOSTIC_DIR"
```

Use `--module NAME` for multi-segment reports. The command authenticates pinned
binaries/sizes, disassembles both at the original address and creates a new
output directory containing `diagnosis.json`, `alignment.json`, `alignment.txt`
and regenerated dumps. The report includes:

- Same-offset counts alongside shifted equal-text runs with both addresses and
  displacement, plus unique out-of-order instruction-window candidates.
- Register-operand differences and surrounding instructions.
- Aligned calls with explicit targets and nearby r0-r3 definitions/SP-store
  candidates; setup order versus setup content differences remain distinct.
- Insertions/deletions and parser normalization counts.

A setup window stops at branches, calls or data and covers at most ten preceding
instructions. It is not a complete reaching-definition analysis. Equal setup
multisets can still compute different values. A changed target is not diagnosed
as an argument permutation. Raw targets are preserved before upstream rendering
normalizes branch offsets. Register aliases such as sl/r10 are normalized only
for the appropriate detail comparison.

Use `tools/asmdiff.py` directly for `--algorithm difflib`, `--objdump`, or the
explicit `--full-elf-text` diagnostic view. The default checks declared terminal
trimming against pinned ELF FUNC ranges. Full-ELF view can inspect a frozen
nonexact artifact without changing its report, original span or acceptance.
Neither path authorizes trimming a return/literal or silently selecting new bytes.

Repeated sequences align ambiguously; unique windows are not proved basic blocks.
Raw disassembly may decode data as instructions. Mixed ARM/Thumb inputs or parser
errors fail rather than produce plausible scores. Reference artifact equality
is not fresh authentication against retail; that remains a separate exact gate.

## Compiler pass localization

The normal pipeline uses host Clang preprocessing, pinned agbcc
`-O2 -mthumb-interwork`, ARM7TDMI assembly and original-address linking. The pinned
agbcc revision is `da598c1d918402c42c0c0d7128ba14567f3175e9` (2.9-arm-000512).
Use the actual bootstrap/build manifest as authority for tools and options.

The useful pass order is expansion, jump cleanup, CSE/GCSE, loops/CSE2,
flow/combine/regmove, local/global allocation and reload, hard-register CSE,
final cross-jumping, Thumb reorganization and emission. This fork has no standalone
instruction-scheduling pass in that driver. Dump modification time is not pass
order. A hash difference locates an artifact, not a causal mechanism.

| First divergent pass | Investigate |
| --- | --- |
| Initial RTL | Type, object identity, conversion and expression expansion |
| CSE/GCSE | Common values, branch facts, aliases and definition points |
| Loop passes | Induction width, stride, bounds and post-loop value uses |
| Combine | Access width, extensions and what consumers actually use |
| Local/global allocation, reload | Simultaneously live values, register classes, stack slots |
| Final jump/Thumb reorganization | Shared tails, constraints, pools and branch shortening |

Prefer existing pass evidence. If an unchanged-input `-da` investigation is
necessary, keep it separate from the fixed production profile and verify output
neutrality; a dump flag is not a new accepted build profile. Consult pinned
[toplev.c](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/toplev.c),
[thumb.md](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/thumb.md),
[reload1.c](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/reload1.c)
for the specific mechanism; modern GCC behavior is not a substitute.

## One hypothesis, one predicted consequence

Keep `original site | cause | predicted output change | source/binary hash |
observed result | counterexample` with the change. If two forms generate the same
binary, close that equivalence class. A different variable name is not new
compiler evidence. If the prediction fails, retain the failure and reconsider
its preconditions. On a plateau, reread the full original/C/generated function,
map all residuals and separate structural causes from register symptoms.

Optional m2c drafts can help a nontrivial CFG when its context and ABI are known;
they are hypotheses, not boundary or semantic proof. Reference implementations
likewise supply ideas, not FFTA facts. Consult one relevant example instead of
reading an entire historical corpus or cloning every reference project.
