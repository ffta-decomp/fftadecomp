# Reconstruct the compiler input

Use ordinary readable C expressing the original operations. Choose physical data
representation and control-flow structure before translating individual opcodes.
The pattern lookup contains observed examples; none is a universal template.

## Widths and destructive arithmetic

Storage width, promoted working value, helper ABI and returned width are separate.
Preserve sign/zero extension, truncation sites, wrapping, sentinels, signed shifts
and signed/unsigned branch predicates. A u8 field may feed a signed int dispatch
and a separately narrowed helper argument. Widening every field or casting only
the final result can change both behavior and code generation.

For normalization/subtraction/multiplication, map the original definition and
last use of each operand. A destructive product carrier or sign-extension result
may need a distinct real lifetime. Equivalent casts can disappear during RTL
expansion. Do not introduce signed-overflow assumptions as a matching shortcut.

## Objects and address formation

Model actual packed records and real fixed-address objects. Numeric base-plus-
field expressions may fold into a different literal; an existing verified symbol
can preserve the object identity. Symbol-only bindings do not implement helpers.
Packed bitfields require target layout evidence and generated-access checks.
Raw masked bits and an extracted logical field are different operations: a raw
AND-28 predicate must not silently become a shifted three-bit value.

Distinguish a byte offset, an ordinal, an element pointer and a loaded value.
Preserve whether scale precedes base definition, a field address precedes zero,
or a loaded source precedes formation of a destination. Renaming equivalent
expressions does not create a new definition/use boundary.

## Snapshots, reloads and ordered effects

Retain original pre-call snapshots and post-call reloads at their own sites.
Neither caching all roots nor globally adding volatile is a reconstruction rule.
A captured output pointer and a reloaded live context can coexist after one call.
Two reads yielding equal fixture values are not proof they observe the same
memory state. Do not move loads across a callback without original evidence.

A typed ordinary-RAM RMW can differ from an explicit volatile snapshot/store.
Transfer it only where the original width and lack of intervening mutation are
established. Do not remove volatile from MMIO or asynchronous state by analogy.
Preserve untouched bits and byte/halfword stores; a word clear is not equivalent
when the original exposes three independent writes.

## Control flow, phases and loops

Recover each incoming definition at a shared tail, including branches entering
a result-setting instruction before a store. Keep distinct state meanings,
terminal states, fallthroughs and phase-specific helper effects. Discrete grouped
status cases may need nested switches; mathematical range tests can generate a
different comparison tree. Early returns, shared returns and goto are choices
justified by the observed CFG, not general style preferences.

Preserve induction width, overflow, loop continuation, found-value snapshots and
post-loop uses. A scan cursor and retained found object are separate lifetimes.
A pointer walk can replace a scaled ordinal during loop optimization; inspect
where that divergence begins before changing syntax. Do not add guards to the
original all-empty or wrapping behavior under the name of cleanup.

C does not promise left-to-right evaluation of function arguments. Reconstruct
observable setup phases through real data dependencies and statement boundaries;
do not infer an evaluation order from argument spelling alone. Fix wrong targets,
widths and missing arguments before tuning register homes.

## Registers and truthful constraints

Only diagnose allocation after operations, ABI, CFG, objects and lifetimes agree.
Use the earliest conflicting definition rather than forcing the last visibly
wrong register. Declaration order and variable names are not assignment rules.
Inspect retained compiler passes if available; no broad compiler-option search.

An initialized fixed-register value and an instruction-free empty ASM operand may
express a demonstrated lifetime requirement. Constraints/clobbers must describe
real inputs and effects. Empty output-only ASM cannot manufacture a value; dummy
uses, fake memory effects and uninitialized carriers are invalid.

The pinned compiler expands a read/write operand as output plus input: six `+r`
operands require twelve slots, beyond MAX_RECOG_OPERANDS=10. Splitting into two
three-operand statements can repair syntax but does not prove ordering or ABI
safety. In particular, ordinary saved copies can still coalesce onto r7 before a
fixed r7 assignment. Verify the actual emitted argument values and stack layout.

Fixed r7 also interacts with this backend's frame-pointer assumptions. An empty
ASM statement may affect estimated lengths/branch shortening despite emitting
no instruction. Treat both as constrained experiments, not free barriers.
Instruction-bearing inline ASM is mixed source and must remain identified.
Never hide a function in raw opcodes or original-byte inclusion.

## C89 and readable naming

Declare block locals before statements, including empty ASM. A real nested block
can introduce later locals; C99 for-loop declarations are unsupported. Inspect
the exact preprocessed .i when headers, typedefs or conditional macros matter.
The host preprocessor's pointer-size macros are not the target ABI.

Name functions by supported actions/objects, and distinguish queries from writes.
Use neutral offset/role names where meaning is unknown. Preserve export/linkage
identity; do not add an executable wrapper solely to rename a function. Naming
changes must retain source-bound whole-range proof. If their binary changes,
check why rather than assuming cosmetic edits cannot affect old compilers.
