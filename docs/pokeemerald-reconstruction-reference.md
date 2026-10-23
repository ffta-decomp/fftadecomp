> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# pokeemerald: source architecture lessons for fixed-O2 recovery

Research reference: [pret/pokeemerald](https://github.com/pret/pokeemerald),
revision `731ad5bfd6e6f265508d0efcca0ba42f9dcf5881`, available locally at
`vendor/pokeemerald`. This is an external recovered-source study, not an FFTA
matching experiment or evidence of FFTA's original source. No speedup has been
measured from these lessons yet. Keep our pinned compiler/preprocessor, fixed
O2, method-only iteration, existing cause budget and full-range exact gate.

Read the relevant row below and its named example; do not read the entire
reference repository for each function. Put any resulting hypothesis and result
in the existing round/lesson record, without another planning or approval gate.
For discrepancy retrieval and register-allocation diagnosis, use the companion
[EDS reference study](eds-matching-reference.md).

## What this adds to our current material

Our [O2 lookup](o2-reconstruction-quick-reference.md),
[structural diagnosis](asm-to-c-migration.md) and
[REA workflow](rea-gba-workflow.md) already cover widths, object layout,
control-flow joins, aliasing, lifetimes and falsifiable experiments. The gap is
connecting those local rules into a consistent source family **before** the
first candidate, instead of rediscovering types and access conventions in each
method.

| Symptom in the original ASM | Reference to inspect | Action before writing C | Discriminator in our own output |
| --- | --- | --- | --- |
| Several consumers address the same record and callback slots | `include/task.h`, `src/task.c` | Reuse one evidence-backed record/interface contract, including callback arguments and field ownership | Correct stride, indirect-call arguments and accesses across calls; names alone cannot change code generation |
| Byte storage but word-sized loop/compare operations | `FuncIsActiveTask`, `FindTaskIdByFunc` in `src/task.c` | Separate storage width, ABI width, working arithmetic type and narrowing point | Missing/extra extensions or signed/unsigned branches at the actual consumer |
| A callback changes a cursor, task or owner | `RunTasks` in `src/task.c` | Identify each pre-call capture and post-call reload separately | The generated load remains on the required side of the call |
| Shift/merge operand decoding with multiple equivalent C spellings | `T1_READ_*`, `T2_READ_*` in `include/global.h` | Infer the active source family's expression/type conventions from original ASM and frozen FFTA siblings | Predicted shift/merge and extension topology, not a speculative global style rule |
| Command operands, wait states and cursor updates are interleaved | `Cmd_jumpifbyte`, `Cmd_return`, selection dispatch in battle sources | Map operand decoding, effects, continuation and cursor ownership separately | Correct fallthrough/branch cursor, helper boundaries and resume behavior |
| A word or pointer is stored in several small slots | Follow-up task functions and word task arguments in `src/task.c` | Recover the logical payload while preserving its physical signed slots and reconstruction sites | The original truncation, extension and merge operations survive |
| Literals/addresses differ despite the expected operation graph | `ld_script.ld`, object rules in `Makefile` | Check object identity, linkage, section and alignment before another expression variation | An identified relocation/placement discrepancy; never excuse a native-byte mismatch |

## 1. Recover shared objects and callable contracts together

In [task.h](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/include/task.h), `TaskFunc` carries a task ID;
the task record holds that callable, active/link/priority bytes and signed
halfword payload slots. The declarations are shared with its implementation.
In [battle_main.c](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/src/battle_main.c), `BattleMainCB1`
invokes a battle-phase callback and then the battler-controller callbacks.
The battle command table in
[battle_script_commands.c](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/src/battle_script_commands.c)
is another, distinct callable interface.

For our active battle group, share proven object offsets, physical stride,
callback prototype and mutation facts from a completed dependency. Keep task,
module and entry identities unchanged. Distinguish a callback's callable ABI
from the contract of the state it reads; a generic function-pointer cast hides
both uncertainties. A complex scheduler or graphics helper still needs only its
real typed interface, not a new implementation.

Do not create or edit a shared header concurrently. Use the existing stable
header snapshot and publication owner; record a genuinely new field/ABI fact
for coordinated adoption. A shared type is not permission to unify different
object lifetimes or force all fixed-address accesses through one accessor.

## 2. A loaded byte does not establish the local variable's type

In [task.c](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/src/task.c), `FuncIsActiveTask` scans with a
byte-sized index; `FindTaskIdByFunc` scans the same array with a signed word
index and narrows the successful result to its byte return type. Their common
record does not require identical local types. This observation is not a paired
ASM experiment and does not prove either spelling for an FFTA loop.

Write down the four distinct questions already implied by our ABI/width rules:
what is stored, what crosses the call boundary, what participates in arithmetic
and comparison, and where is it narrowed? Select the type from those uses and
original signed branches/extensions. Do not infer every local as `u8` from an
`LDRB`, or widen every local because Thumb uses word registers.

`include/gba/types.h` also keeps byte, halfword and word Boolean storage types
separate. A named predicate is not automatically a C `bool` object or a
materialized 0/1 temporary; preserve the original consuming control flow.

## 3. Callback-visible state must retain its actual read sites

`RunTasks` calls the current task before obtaining its next link. Capturing that
link before the callback would introduce a different mutation contract.
Battle selection dispatch likewise obtains the script cursor, calls a command
handler, then saves the resulting cursor back to the selection-script state.

Before coding a comparable FFTA transaction, mark the owner cells a helper may
change and identify which subsequent reads are live versus captured. These are
site-specific facts. Neither cache-all-roots nor reload-all-roots is a valid
default. A changed lifetime can explain distant register allocation differences;
do not start with declaration-order permutations or invented `volatile`.

## 4. Preserve a source family's dialect, not a universal clever expression

[global.h](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/include/global.h) retains two read-macro
families: one merges component bytes with bitwise OR, the other with addition;
their pointer forms also use different result casts. Its adjacent comment
speculates about multiple original programming teams. That explanation remains
a theory, not a fact about this project or FFTA.

The actionable lesson is narrower: algebraic equivalence does not establish
original expression form or intermediate type. For a proven FFTA family,
record its decoded operand widths, promotion, merge operation and final cast.
Reuse that vocabulary in siblings only when their ASM has the same pattern.
Do not import these macros, normalize every merge to one operator, or enumerate
OR/add/cast combinations without a specific differing original operation.

The task payload examples are similarly useful: follow-up pointers and word
arguments occupy two signed halfword slots, with an explicit low-half unsigned
conversion when reconstructed. Logical pointer/word ownership and physical
storage type are separate. Recover our own target's format and ABI; do not copy
Pokemon structures or assume those C expressions are portable to a host.

## 5. Separate command decoding from state effects and continuation

`Cmd_jumpifbyte` decodes a comparison selector, a byte-object pointer, a byte
value and a branch target; it advances to the fallthrough command before
conditionally replacing the cursor. `Cmd_return` delegates cursor restoration
to the script stack. The selection dispatcher saves the command's resulting
cursor rather than inventing its own increment.

For an FFTA command, extract a small operand/continuation map from its original
ASM: operand offsets and widths; pre/post-helper loads; taken/fallthrough/wait/
return cursor definitions; owning context. Use it to write the complete handler
and select existing relevant branch checks. It belongs in the current source
plan, not a new mandatory report. A superficially equivalent late cursor update
can change both alias behavior and code generation. Do not expand the generic
VM engine merely because a battle command uses it.

## 6. Diagnose build context without replacing the toolchain

The upstream [Makefile](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/Makefile) defaults its ordinary
agbcc build to O2, but its preprocessor, preprocessing stage and flags are not
our pinned pipeline. It also contains explicit library/object exceptions.
Its [CI](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/.github/workflows/build.yml) separates the
ordinary checksum comparison from a modern-compiler build without comparison.
This supports recording exact build context, not switching our optimization
levels or importing its flags and compiler exceptions.

The [linker script](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/ld_script.ld) orders text and read-only
data by object; its build rule appends section alignment. A misplaced literal,
object symbol or alignment span needs a section/relocation explanation rather
than speculative C statement ordering. Our complete original envelope remains
the final comparison target; never trim a live epilogue or relabel differences
as padding without source evidence.

Upstream retains preprocessing/assembly intermediates with `KEEP_TEMPS`; use
our existing local artifacts and RTL path for the same diagnostic purpose.
Its [asmdiff.sh](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/asmdiff.sh) limits display to an address
range, but forces Thumb and disassembles binary data indiscriminately. Retain
our mode/boundary-aware local comparison and native-byte gate. Do not introduce
a full-ROM build or whole-ROM disassembly prerequisite for a single method.

Per-object dependency lists are another useful architectural reference in the
Makefile and `tools/scaninc/scaninc.cpp`. They suggest avoiding needless global
invalidation, but a syntax scanner is not proof of a complete dependency
closure. No cache-key or builder change follows from this study; require a
measured repeated cost and dependency-completeness checks first.

## What not to transfer

- Documented register bindings or instruction-free empty ASM constraints can
  express a concrete allocation/lifetime requirement without defeating a full
  native match; see the [EDS constraint guidance](eds-matching-reference.md).
  Do not import an unexplained `BLOCK_CROSS_JUMP` everywhere. `NAKED` and opaque
  function bodies are not C-recovery shortcuts; emitted instructions retain
  explicit mixed-function accounting.
- `BUGFIX`, `UBFIX` and modern-build alternatives are separate behavior/build
  choices. Do not silently fix an original edge case or add an unobserved guard.
- Do not include upstream `global.h`: it contains project-specific macros,
  host/IDE conditionals and data formats. Verify our actual preprocessed input.
- Do not copy game implementation, assets, layouts, names or addresses into
  FFTA. This checkout is research-only, not a build/runtime dependency.

No repository-wide license file was found at this pinned upstream root.
Individual tools have their own notices, which do not license the whole tree.
Preserve the checkout and notices intact; the parent repository should record
the pinned submodule rather than importing its contents as ordinary files.

## Applying and measuring a transfer

Before the next candidate, use the relevant example to fill one missing object,
working-type, expression-family or continuation fact in the existing source
plan. State the expected generated operation and its falsifier. Then perform
the normal one-cause local iteration and submit the reached gate immediately.
Keep plateau diagnosis and failed hypotheses; this reference grants no extra
trials, acceptance or method-budget reset.

Record reference/feature, transferred fact, actual first-pass result and full
decision-to-decision time in the normal lesson. Compare exact original ASM
bytes/hour and iterations across comparable complete methods, including failed
transfers and preparation time. Source resemblance, fewer C lines or scattered
equal bytes do not establish an efficiency gain.
