> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Evidence-based names without changing task identity

Use meaningful names while reconstructing original ASM. After a successful
local rewrite, complete one naming pass before freezing the promotion package
and finishing the task. This is implementer work, not administrator C review.
Submit the initial matching decision and evidence-bearing local gate immediately
when reached; naming does not defer that progress. Keep its snapshot immutable
and link the final naming package to the same stable task and binary credit.

## Stable identity and readable source

Keep the ledger task ID, module key, original entry/span, manifest identity,
evidence paths, claim and credit identities unchanged. A descriptive name is
metadata associated with that identity, never a new task or new delivery credit.
Preserve existing linkage and callers. Use a descriptive C identifier with an
existing toolchain-supported symbol-name binding when that preserves the legacy
export without instructions. Otherwise retain the export and record the proposed
semantic name beside its declaration and in the naming map. Do not introduce a
wrapper or modify shared aliases just to rename an entry. Main owns any later
production symbol migration and must preserve old lookup compatibility.

Follow established local naming conventions. Prefer a concrete action and owned
object for functions; distinguish queries, predicates and mutations. Derive
parameter, local and field names from the original def-use chain, callers,
memory ownership and checked effects. Distinguish a pointer from its loaded
value, an ordinal from a byte offset, and a pre-call snapshot from a reload.
Do not label an unexplained mask as a named game status merely because a caller
is battle-related. Use a neutral role or offset-based name when its meaning is
unknown. Mark proposed interpretations as inferred rather than confirmed.

## One bounded closeout pass

1. Reuse the method's existing source map and checks. Do not begin a new broad
   investigation solely to find a more attractive name. Record unresolved names.
2. Rename identifiers and clarify short comments only. Preserve types, scopes,
   declaration order, expressions, CFG, object layout and lifetimes. Naming is
   not permission to simplify or merge recovered branches.
3. If source changed, run one normal fixed-O2 method build/preflight and compare
   its complete bytes, layout and linkage against the preceding frozen result.
   Rebind source/header hashes to the renamed package. Byte-identical output and
   unchanged relevant dependencies permit exact reuse of recorded cases. Changed
   output requires the relevant checks; revert a naming-induced codegen change
   instead of starting a matching search for spelling. No full-ROM build is
   required solely for this pass.
4. Save `naming.json` in the existing owned method evidence directory. Include
   the stable task/module/entry, original export, final C identifier, and scoped
   old-to-new parameter/local/field mappings. Each interpretation records
   `observed`, `inferred` or `unknown`, a short basis and existing evidence IDs.
   Include before/after source hashes, binary equality result, naming elapsed
   time, reused case identities and unresolved naming or linkage obligations.
5. Attach this map using the existing ledger progress event and frozen package;
   include the useful naming lesson in the owned method lesson. Record the
   subsequent genuine build decision normally. Naming metadata is not a new
   acceptance gate and does not reset any clock.

Independently accepted packages remain immutable. A later naming pass creates
a new source-bound package for the normal independent gate; byte identity alone
does not grant independent source acceptance. Do not rewrite historical packages
or mass-rebuild older work for this instruction. Apply it to active work at its
normal closeout and to subsequent methods.
