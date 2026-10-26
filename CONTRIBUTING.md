# Contributing by recovery group

[Browse the function catalogue](https://github.com/ffta-decomp/fftadecomp/blob/main/data/functions.csv) · [Workflow](docs/gba-asm-to-c-workflow.md) · [Unpack your own ROM](docs/extract-asm.md)

Battle actions, effects, resolution and turn progression are the active group.
Then come jobs, abilities, story, missions, items/equipment/economy, world rules,
saves, game menus and multiplayer policy. Work on one disjoint complete native
function, starting with its small missing dependencies. A complex engine,
graphics, audio or hardware dependency needs an interface contract, not another
unrelated implementation campaign. Semantic ownership and campaign membership
are separate fields; unclassified does not mean engine or available.

1. Filter `data/functions.csv` by group and inspect the stable native ID, address,
   full range and current snapshot state. The catalogue includes functions and
   module spans; a module boundary is not proof of an independent callable ABI.
2. Open a **Group function claim** issue with the function entry address in the
   title, for example `[Claim] 0x080A23B8 — ResolveBattleTargets`.
   If you are an agent, ask your user to publish the issue; do not silently claim
   work on their behalf. Give the native ID, group, expected
   range and bounded plan. Check existing open claims first. Do not post ROM
   bytes, disassembly, extracted assets, local paths, credentials or private logs.
3. The maintainer checks the canonical current ledger, native aliases, historical
   budgets and active owners before confirming the claim in that issue. A new
   issue, snapshot row or local SQLite claim is a request, not global exclusivity.
   Do not implement a duplicate while awaiting confirmation. Updates/release go
   in the same issue; a maintainer releases the corresponding canonical claim.
4. After confirmation, work in your own private checkout/output directories.
   Preserve the pinned retail revision and fixed O2 toolchain. Reconstruct source
   from original operations, widths, objects, CFG and definition/reload lifetimes.
5. Submit a per-function decision immediately: native identity, source/header/
   toolchain hashes, complete-range result, original/generated/retained bytes,
   emitted ASM instruction bytes, elapsed time and failed causes. Share only
   permitted original work or hash summaries; never upload extracted game content.
6. Whole-exact work uses independent mechanical provenance/range verification;
   nonexact semantic work retains independent behavior/source gates. Production
   identity and integration are separate. Write the measured transferable lesson
   and continue within the group after your claim is closed.

## Claim activity and expiry

Use the organization repository, [ffta-decomp/fftadecomp](https://github.com/ffta-decomp/fftadecomp/issues),
for all claims. Personal-repository mirrors or placeholders do not reserve work.
Check open issues for the same entry and overlapping original range before claiming.
For competing requests for an available range, the earliest valid issue takes
priority, subject to the canonical ownership check above.

Post a progress update in the same issue at least once every 24 hours: what you
tried, the current result or blocker, and the next step. A short substantive
update is enough; reactions, automated pings and unrelated comments do not renew
ownership. The clock starts with the claim issue and is renewed by the claimant's
latest substantive progress update (including a dated issue-body update).

After more than 24 hours without such an update, the claim is considered
abandoned and may be claimed by another contributor. Expiry releases the claim,
not its evidence: preserve prior work and link the old issue when reclaiming.
Before resuming an expired claim, check for a newer owner and request ownership
again; an old issue or local lease must not override a current claim. Maintainers
reconcile the canonical ledger before a replacement starts. This is the public
coordination policy; it does not imply an automated issue closer is installed.

## One shared ledger for a collaborating installation

The published `tools/recovery_workflow.py` records atomic claims, rounds, gates,
Git milestones and completed-clock-hour rates. Use an explicit local database:

```sh
python3 tools/recovery_workflow.py --db build/workflow/ledger.sqlite3 init
python3 tools/recovery_workflow.py --db build/workflow/ledger.sqlite3 status
python3 tools/recovery_workflow.py --db build/workflow/ledger.sqlite3 throughput
```

Follow [CLI usage](docs/recovery-workflow-cli.md) for task specifications, saved
claims, decisions and evidence pins. Separate database copies do not coordinate
contributors globally. Keep databases, claim tokens, reports and generated game
content private. Automatic publisher commands in the implementation guide require
the maintainer's separately configured implementation installation; no such
configuration or private evidence is distributed by this public toolkit.

## Public content boundary

This repository publishes original guidance, portable tools and address/layout
metadata. It is not the private game implementation checkout. Tools reconstruct
local ASM only from a ROM supplied by its user. Do not commit the generated tree,
ROMs, assets, saves, screenshots, private paths, account/session identifiers,
credentials, confidential project details or unrelated commercial material.
Third-party reference projects retain their own licenses; follow pinned links.
