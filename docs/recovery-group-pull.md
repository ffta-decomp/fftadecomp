# Automatic intake within a recovery group

`recovery_group_pull.py` uses the existing workflow SQLite ledger. It does not
create a replacement queue or mark unknown code ready. At a method boundary,
contributors pull from the maintainer-selected group instead of waiting for a
function assignment:

```sh
python3 tools/recovery_group_pull.py --actor ACTOR --group GROUP_ID \
  --save build/workflow/ACTOR-group-pull.json
```

The ignored `.local/recovery-workflow.json` supplies group defaults:

```json
{
  "db": "PATH_TO_EXISTING_LEDGER",
  "group_pull": {
    "groups": {
      "GROUP_ID": {
        "pool": "PATH_TO_CURRENT_POOL_SYMLINK",
        "refresh": {
          "catalog": "public/data/functions.json",
          "seed_group": "CATALOG_GROUP_ID",
          "output_root": "EXTERNAL_EVIDENCE_DIRECTORY"
        }
      }
    }
  }
}
```

An explicit `--pool` or `--db` can override defaults. Add `exclusions` and
`dispositions` paths under `refresh` when those maintained indexes are used.
Keep local configuration, pools, receipts and source-qualified private evidence
outside public version control. The saved receipt has mode0600; stdout omits
tokens. Existing compiler and SDK exclusion rules still apply.

## Returned phases

- `implementation`: the actor resumes its existing task, or atomically acquires
  and promotes an eligible group-native source lease. Use the returned task
  with the ordinary workflow record/credit/finish commands. Original clocks and
  prior attempts remain intact.
- `qualification`: the actor receives an exclusive complete-range source
  question with pinned original ASM and caller evidence. Establish responsibility,
  ABI, CFG, field layouts and helper contracts before adding a native task.
  Unknown targets stay unknown; a call edge is a lead, not proof of game ownership.
- `blocked`: inspect reason counts and coverage. A bounded pool is not the whole
  game. Busy/reserved work is never stolen, and a missing old lesson does not
  prohibit establishing a new source contract.

Ready native tasks and source leases are selected in the existing transaction.
Independent processes cannot acquire overlapping original ranges under aliases.
A lease does not establish eligibility: reread the current range, credits and
selected representation after acquisition, and exclude prior exact recovery.

For a source contract that really is ready, use the existing `add --file SPEC
--lease RECEIPT` and `claim --task TASK --lease RECEIPT` path. Record the original
qualification start in the spec. Do not create a new task to reset old budgets.

For a source-only conclusion, freeze the result and close it through the tool:

```sh
python3 tools/recovery_group_pull.py --actor ACTOR --group GROUP_ID \
  --disposition interface_only --lease build/workflow/ACTOR-group-pull.json \
  --evidence EXTERNAL_RESULT --summary REASON \
  --save build/workflow/ACTOR-qualification-close.json
```

Use `out_of_scope` or `blocked` when that is the actual finding. The tool pins
the result, appends a disposition and releases the owned lease in one transaction.
The next actor skips that closed source question; no C credit is created.

## Bounded replenishment

The pool builder reads declared catalogue functions and original direct-call
edges, including explicit group tasks already present in the ledger. Completed
or blocked tasks may supply original call edges; their implementation budgets
remain closed. Only complete declared ranges enter qualification. Known SDK,
selected exact C, historical native overlaps and pinned dispositions are excluded.

When the provided pool is depleted, the CLI can build one immutable revision
outside the ledger transaction and retry once. It freezes the live manifest
bytes used for that revision and atomically replaces a current-pool symlink.
Old receipts retain their resolved immutable revision. Ordinary pulls do not
rebuild the pool; busy/reserved or cross-group work does not trigger replenishment.
There is no polling daemon, automatic ROM build or recursive retry loop.

Local, independent and integrated whole-exact original-byte gates remain separate.
Qualification, interfaces, source indexes and task activity contribute zero
matched C bytes. Full-ROM builds remain coherent integration gates.
