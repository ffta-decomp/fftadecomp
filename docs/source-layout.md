# Promote temporary work into stable project source

Organize production code by its responsibility, not by the batch, contributor,
import, experiment or PR that delivered it. Original addresses and module IDs
remain stable in the build selection and provenance records when paths change.

## Locations and ownership

| Material | Location | Lifetime |
| --- | --- | --- |
| Candidate C and local headers | Ignored `build/work/<address>/` | One working candidate and required checkpoints |
| Selected implementation | `src/<subsystem>/<stable-name>.c` | Maintained project source |
| Ownership not established | `src/unknown/<address>.c` | Until evidence supports a subsystem |
| Shared, proved interfaces | `include/<subsystem>/` or existing shared headers | Maintained dependency contract |
| Reusable reconstruction knowledge | Existing repository skill/topic and linked case | Maintained rule with preconditions and failed controls |
| Failed trials and detailed proofs | Existing private evidence/ledger | Retain only required recoverable evidence |
| Compiler output | Ignored `build/` or configured external output | Disposable after consumers finish |

Examples of subsystem ownership include battle, story/progression, inventory,
menus, world, saves, graphics, audio and platform code. Choose from actual calls,
state and consumers; an address band or tentative function name is not proof.
An import's origin belongs in attribution metadata, not a permanent import folder.

Use one independent compilation unit where possible. Preserve established shared
tails, common stack frames and multi-entry ownership; never split them for a
directory convention. Local header layouts may stay beside their compilation
unit. Consolidate shared types only after their ABI is proved.

## Promotion sequence

1. Recover and validate in the temporary working area. Record the reached local
   gate immediately; path cleanup must not delay or erase that gate.
2. The integrator chooses the stable destination and prepares the unchanged C
   and dependency closure. Do not rename functions, rewrite types and reorganize
   files in the same operation. Preserve licenses and attribution.
3. Validate compilation from the final path. Relative includes, assembler file
   directives and `__FILE__` can make a move change compiler inputs. Update the
   production selection, source index, dependency hashes and new proof together;
   never rewrite frozen old proof. Reuse unchanged binary/behavior evidence only
   under its established identity and applicable validation rules.
4. Perform the existing independent and coherent final-image gates. Write one
   image and verify its actual final hash. A path move adds no recovered bytes,
   resets no clock/budget, and grants no acceptance.
5. Run source-layout preflight before publishing, then commit the stable source,
   selection, proof/index and attribution together. Publication authorization
   remains separate. Remove consumed temporary copies only when no pending or
   historical proof consumer needs them and the inputs remain recoverable.

## Commands

The portable implementation is `tools/source_layout.py`; implementation checkouts
may forward to that same implementation. Run from the intended checkout root.

```sh
# Strict inventory: report noncanonical selected C/mixed paths, without moving files.
python3 tools/source_layout.py audit --manifest config/retail-us.json \
  --report build/source-layout-audit.json

# Prepare a final-path unit and a small module fragment; never copies the full manifest.
python3 tools/source_layout.py prepare --manifest config/retail-us.json \
  --module ExistingModule --destination src/graphics/task_layer_rows.c \
  --report build/work/source-relocation.json

# In an existing release branch, unchanged legacy source can remain explicit debt.
python3 tools/source_layout.py audit --manifest config/completed-build.json \
  --baseline-ref BASE_COMMIT
```

`prepare` preserves source bytes, local quoted-header relationships and the original
module configuration except its source path. It refuses conflicting destinations,
unresolved/parent-relative quoted includes and path-sensitive source requiring
manual proof. It keeps old inputs and does not edit production selection, compile,
create a ledger gate or publish. Its `candidate_module` is a relocation proposal,
not an accepted replacement.

Strict audit returns a nonzero status for layout debt. Baseline mode exempts only
an unchanged legacy module identity, path and source bytes at an explicit Git ref.
New or edited implementations must use stable paths. This ratchet permits staged
migration without pretending that old batches were already reorganized. It checks
layout, not correctness or privacy; normal native and publication checks still apply.

## Applying this to an existing tree

Start from the selected build manifest, not a recursive copy of every old `.c`.
The audit report is a work list, not a second source of task state. Group migration
work by proved subsystem and shared dependency closure. Validate one coherent group
before the next; keep original identities and required historical evidence.
Historical one-shot export scripts that name a campaign directory are not the
entry point for new deliveries. Use this promotion path and the existing build
selection/proof writers. PRs describe subsystem changes and original ranges;
batch identifiers remain historical metadata.

## Header boundaries and a maintained tree

Use `config/source-layout.json` to record each selected module's subsystem and
the evidence for that placement. This is architecture metadata, not a task queue.
Keep unclassified implementations under `src/unknown/`; a stable address filename
does not invent a semantic name. Preserve all entries of a shared compilation
unit in one file even if its consumers cross subsystems.

Headers have three distinct responsibilities:

- `include/ffta/`: exact underlying scalar ABI types already used by the source.
- `include/<subsystem>/`: established shared object layouts and interfaces.
- `include/<subsystem>/interfaces/` or `include/abi/interfaces/`: site-specific
  external bindings and partially known layouts. Different views of the same
  address remain separate until their compatibility is proved.

Symbol-only assembler bindings belong in `asm/interfaces/`. Keep their original
symbols and values; moving a binding does not recover the bound function.
Do not merge structures by similar spelling or add qualifiers, declarations,
include-order changes or wrappers to make the tree look uniform.

For a large migration, `tools/source_tree.py` provides the `SourceTree` backend:
reviewed module ownership and optional shared-header destinations are explicit
inputs. It stages final paths while keeping originals, rewrites resolved quoted
includes, and records source/dependency mappings. It only extracts already
present compatible integer typedefs. Compare the complete preprocessed token
streams, preserving literals and every token except those exact equivalent
typedef declarations, then run the complete native and image gates. Token
equivalence alone is not acceptance. Preserve old proof in Git and bind new
proof to the final source closure.

The completed build has one maintained master selection. Once an incremental
selection passes coherent integration, merge its ranges, source index and native
hash targets into that master and remove its active registry entry. Historical
incremental records can remain provenance; they must not become a second build
of the same ranges. The default build must include all published completed code.

After validation, remove consumed old production copies. Preserve unselected
drafts separately under `experiments/`, with their original path/hash and history;
do not accidentally include them in the completed build. Keep only current
invocation-owned compiler output until its consumers finish, then clean it.
