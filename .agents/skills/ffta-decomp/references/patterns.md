# Pattern lookup and counterexamples

These consolidate historical source-shape observations. The stated result is an
observation for that original function, not a current integration status or a
universal compiler rule. Transfer only after checking the original site's ABI,
objects and effects. Keep measured output effects distinct from pass-traced causes.

## Widths and physical layouts

| Original operation / observed case | Useful source question | Counterexample / limit |
| --- | --- | --- |
| A 70-byte record stride | Is the actual record packed? The pinned backend rounded an ordinary 70-byte struct to 72 in a synthetic probe | Do not add guessed packing to unrelated objects |
| Packed 10/10/11/11/11/11-bit fields crossing bytes; 0x12EBD0, 306-byte local exact observation | Recover bit positions, assignment order and untouched bits before representing the fields | Ordinary u16 flags needing LDRH/STRH are not logical bitfields |
| Raw bits 2..4 tested with AND 28 | Preserve a raw masked value | Extracting a shifted three-bit logical field changed the loop shape |
| Independent scalar OUT addresses | Keep independently observed stack objects distinct | A genuine pointer-indexed array must remain an array |
| Signed operands normalized before arithmetic; 222-byte value classifier | Give each real sign-extension its observed definition point, then wrap the result | Casting only the final result or adding arbitrary temporaries did not express those lifetimes |
| Word and halfword views of one slot range at word stride | Confirm an overlapping view and dynamic-reference alignment before using it | A cast is not proof of overlap, stride or extent; early base locals changed tails |

## Captures, reloads and ordinary RAM

| Original operation / observed case | Useful source question | Counterexample / limit |
| --- | --- | --- |
| Destination captured before helper; live context read afterward; 204-byte cancellation | Keep captured destination and post-call context distinct | Caching every root or globally making it volatile changes memory observations |
| Source bytes loaded after helper, before destination address; 114-byte coordinate copy | Separate the copy's actual new definitions from prior command operands | Merely moving loads while reusing an earlier carrier still failed |
| One post-helper u16 flags RMW in ordinary RAM; 0x1322B0, 138-byte local exact observation | A typed field RMW preserved the observed load/OR/store | Explicit volatile snapshots added reads; reversed OR operands were identical. Not transferable to MMIO/asynchronous state |
| Sequential threshold calculations share scratch but context survives calls; 0x1326AC, 552-byte local exact observation | Preserve each computation's lifetime and callback-visible reload sites | Declaration permutations and qualifier changes alone repeated output |
| Byte counter update after a helper; opposite category scan directions | Preserve the actual byte store, wrap direction and post-sound reload | A generic modulo helper or copied sibling bounds can change behavior |

## Address definitions and linkage

| Original operation / observed case | Useful source question | Counterexample / limit |
| --- | --- | --- |
| Table base and field offset retained as separate definitions; 228-byte descriptor | Bind the verified object symbol and use its actual typed field | Numeric macros and inline accessors can still fold base+offset |
| Narrowed ID scaled before record base is loaded | Keep scaled offset, record pointer and field access at their own definitions | Correct symbol linkage alone can fix the literal but leave wrong lifetimes |
| Post-selection definition record feeds a second table | Materialize the actual record at its observed point | Two names for an identical expression do not create a phase boundary |
| Two verified helper aliases fixed a 584-byte derived-flags candidate to 572-byte exact | Check target, mode, prototype and direct/indirect call form before tuning syntax | Declaration-only bindings are not helper implementations or instruction ASM |

## CFG, returns and loops

| Original operation / observed case | Useful source question | Counterexample / limit |
| --- | --- | --- |
| Discrete statuses 1/2 and 3/4 with distinct effects; 592-byte mission operation | Preserve grouped switch cases and nested dispatch | Equivalent range predicates changed CMP/branch shape |
| Branches enter MOV-result before a common store; 688-byte continuation | Map exact incoming instruction and definition | Treating the target as the following store omitted a state assignment |
| Predicate has full-word 100/0 return joining in r0; 22-byte callbacks | Reconstruct helper-result test and shared physical return carrier | Early returns also match some siblings; one spelling is not universal |
| Scan cursor dies on success but found record survives unlink/calls | Separate real cursor, found snapshot and subsequent ordinal | Renaming pointers with identical definitions coalesced to the same output |
| Scaled ordinal became a second pointer in loop optimization | Inspect induction rewriting and later uses | One 154-byte effect grew to 160 when a continuation moved; this is unresolved evidence, not a fix |
| Several distinct stat blocks have no original backward edge | Retain per-stat fields, widths and narrowing sites | A generic loop merges site differences and can change signed clamp behavior |

## Register residuals and syntax

A 44-byte slot lookup closed a previously isolated register-role inversion by
binding its initialized slot-base pointer to r2 and consuming it with a truthful
empty read/write constraint. The lookup, calls and narrowing remained in readable
C; the constraint emitted no instruction. A fixed declaration alone was not the
measured formulation. The initial declaration-after-ASM error was a C89 syntax
failure, not evidence against the lifetime hypothesis.

Transfer this only when operations, ABI, CFG and placement already agree and the
specific allocation inversion is supported. A changed frame, extra load/move or
remaining mismatch falsifies closure. Do not pin an entire function by analogy.

A separate stack-argument experiment restored high-register saves but overwrote
a fifth argument through fixed r7. Ordinary prebinding copies still coalesced.
Six read/write operands also exceeded the compiler's ten-operand expansion limit;
two groups of three repaired syntax but did not repair the ABI. The checker
reports these risks; it never certifies their absence or auto-rewrites source.

## Section alignment and false progress

A 306-byte body inside a 308-byte ELF section may have a two-byte C046 suffix
outside all FUNC ranges. That requires explicit section/function/pool evidence;
it is not a general permission to remove the last two bytes. Original owned
alignment and literals remain part of whole matching. Scattered equal bytes,
a fitting shorter prefix, semantic fixture success and imported verification
claims cannot replace complete original-range byte equality and input pins.
