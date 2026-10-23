> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Transactional recovery workflow ledger

`tools/recovery_workflow.py` stores task claims, round decisions, acceptance
receipts and Git milestone references in SQLite. Workers claim existing tasks
and submit progress through the same CLI. A searchable HTML snapshot and JSON
queries expose the same ledger. It does not compile, validate game C, start a
game service or send messages. A separately authorized daily scheduler creates
and pushes only consolidated public data commits in an isolated checkout.

Only the ledger owns runtime task state after cutover. Assignment documents and
pool records retain scope, source pins and instructions; their old state labels
are migration history. Keep the database and generated reports under ignored
`build/` or an external private evidence directory. Never publish private reports
or use a shared network filesystem for the SQLite database.

## Configure once

```sh
python3 tools/recovery_workflow.py --db build/workflow/ledger.sqlite3 init
```

Pass `--db` before the command, set `FFTA_WORK_DB`, or use ignored
`.local/recovery-workflow.json` containing `{"db": "configured-path"}`. No private
path is built into the tool. `init --epoch <UTC timestamp>` explicitly selects a
measurement epoch; record a cutover boundary instead of resetting a worker's
original claim time. Reopening an existing database preserves its epoch.

An administrator adds a task using `add --actor administrator --file task.json`:

```json
{
  "task_id": "CORE-EXAMPLE-01",
  "module": "ExampleCoreMethod",
  "owner": "main",
  "priority": 10,
  "original_span_bytes": 120,
  "rom_offset": 65536,
  "instructions": "Read the assigned contract and source pins; fixed O2.",
  "owned_source_directory": "build/example/main/"
}
```

Omit `owner` for a shared ready task that either implementation lane may claim.
Reservations preserve disjoint assignments. Each actor can hold one active task;
active spans and module names cannot overlap. `import-pool` accepts the existing
`{"records": [...]}` format, preserves active owners/start timestamps, and freezes
completed historical states. It does **not** infer acceptance from those labels.
Existing differing task records are rejected, never overwritten by a later import.

## Worker loop: claim, record, finish, claim again

Submit each function as soon as its actual gate is reached. Immediately record
an exact binary decision; this alone is not local correctness acceptance. Once
the required local checks pass, freeze the current source/header/binary and
decision receipt, then submit `credit local_exact` without waiting for naming
polish, a lesson, another method, the next hour, peer acceptance or integration.
Record submission success before continuing. Perform the naming closeout and
lesson on the same method clock, attach the final immutable promotion package,
then `finish` and claim the next task. A byte-identical naming revision links to
the same credited binary; do not issue a second credit. A changed result follows
the existing correction/revocation rules. If a submission fails, preserve its
payload and error and retry that submission, not the compiler or passing cases.
Hourly limits apply to consolidated conversation. Submit local records immediately;
public snapshots are published once daily by a separate scheduler. Worker submissions
and administrator supervision do not launch public publication.

```sh
python3 tools/recovery_workflow.py claim --actor main --save build/workflow/main-claim.json
python3 tools/recovery_workflow.py record --claim build/workflow/main-claim.json \
  --round round00 --outcome nonexact --generated-bytes 116 --matching-bytes 80 \
  --summary 'Original branch order restored; allocation remains different.' \
  --next-action 'Test the source-backed snapshot lifetime.' \
  --evidence build/example/round00/report.json
python3 tools/recovery_workflow.py finish --claim build/workflow/main-claim.json \
  --state frozen --summary 'Frozen local result; independent acceptance pending.' \
  --evidence build/example/promotion-ready.json
python3 tools/recovery_workflow.py claim --actor main --save build/workflow/main-claim.json
```

Worker2 uses `--actor worker2`; worker3 uses `--actor worker3`. Each uses its own
claim file and the same database. Unreserved tasks can be claimed by any of the
three implementation lanes; current reservations are preserved. An active claim is resumed
with the same token; a repeated `claim` cannot silently switch methods. No eligible
work returns `task: null`, without stealing a reserved or active task. Saved claim
files carry the actor, task and token, so workers do not copy credentials between
commands. Do not share or commit them.

Numeric priorities are ascending: **lower numbers are claimed first**, with
task ID breaking ties. A new task numbered1081 will wait behind an eligible850
task; a larger number does not mean higher urgency. Follow the current assignment
for source-readiness tiers rather than inferring priority from a task's age,
size, or numbering. Reservations and active-range exclusion still apply.

Administrators may adjust an unclaimed task's runtime ordering or reservation
without rewriting its historical import spec or resetting method evidence:

```sh
python3 tools/recovery_workflow.py schedule --actor administrator \
  --task TASK_ID --expected-priority 1081 --priority 100 \
  --summary 'Demonstrated core family ready before unresolved controller cohort'
```

`schedule` accepts only `ready` tasks and compares the expected priority and
reservation atomically. Supply `--expected-reservation ACTOR` for an existing
reservation, then `--reserve-for ACTOR` or `--clear-reservation` if changing it.
A concurrently claimed or rescheduled task fails unchanged. Runtime task fields
control claiming; the preserved original spec records intake history. Every
change appends an event and grants no delivery credit.

For an explicitly authorized frozen handoff, `requeue --reserve-for ACTOR
--priority N` reserves within the same transaction that makes it ready. Keep the
required `--expected-state`, reason and active token check when applicable.
Do not requeue first and reserve in a separate transaction: another actor could
claim between them. A new claimant's interval is separate from the original
method clock; preserve first-start and handoff time in the method's evidence.

`record --kind progress --summary ...` records a non-decision checkpoint without
resetting the round clock. Round outcomes are `exact`, `nonexact`, `unchanged`,
`compile_failed`, `check_failed`, or `diagnostic`. An exact round is an observation,
not acceptance credit. Failed attempts remain in the wall-clock denominator.

Keep task IDs, module keys and original spans stable when improving source names.
Attach the [naming map](c-recovery-naming.md) with
`record --claim ... --kind progress --summary 'Naming closeout recorded.'
--evidence build/example/naming.json`. Do not reimport a renamed task or rewrite
its immutable spec; the map belongs to the existing task's evidence. Descriptive
aliases do not change claims, indexing, public group IDs or delivery credit.

For richer data, pass `record --claim ... --file round.json`. Payloads may include
`round`, `outcome`, `summary`, `generated_bytes`, `matching_bytes`,
`binary_sha256`, `compile_attempts`, `command_timings_seconds`, `case_ids`,
`reused_case_ids`, `failure_cause`, `next_action`, and `evidence` (file paths).
Identity fields come from the claim/CLI, not the payload. The tool hashes evidence
files and timestamps the event. It computes adjacent decision intervals itself;
caller-supplied cumulative method age is not used as the iteration duration.
Submit immediately after the decision to include command failures and reporting.

Identical CLI round/finish/release retries have deterministic request IDs and
return the original receipt. Other mutations accept `--request-id <stable-id>`;
reusing an ID with changed input fails. Round identities are unique within a task;
use a new phase/round name after an explicit reopening. Correct historical errors
with a new progress/correction event rather than editing old events.

`finish --state blocked` releases execution capacity while preserving the blocker.
`release --summary ...` returns unfinished work to ready. A stale token cannot
write after either transition. Claims never expire automatically: administrator
`requeue` requires a reason, expected current state and, for active work, the
current token supplied during explicit owner handoff. The CLI is cooperative
local coordination, not an authentication boundary between hostile users.

## Record acceptance separately

Use `credit --actor <implementer-or-peer> --task <id> --file credit.json`:

```json
{
  "gate": "local_exact",
  "binary": "build/example/ExampleCoreMethod.bin",
  "evidence": ["build/example/local-whole-method-decision.json"],
  "accounting": {
    "instruction_bytes": 108,
    "literal_bytes": 12,
    "alignment_bytes": 0
  }
}
```

Gates are `local_semantic`, `local_exact`, `peer_semantic`, `peer_exact`, and
`integrated`. Every gate requires pinned evidence and a binary identity. An exact
gate requires the complete original envelope size. Supplied instruction/literal/
alignment accounting must be complete and sum to that envelope; absent accounting
stays unknown. Binary size alone does not validate exactness: the existing build
and independent evidence validators remain authoritative.

Local gates belong to the implementer; peer gates require another actor and the
same binary as the corresponding local credit. The administrator cannot accept C.
Already semantically recovered pool records cannot earn new semantic credit.
Integration is main-only and requires a registered Git commit linked to the task
and same-binary peer acceptance. Each module earns each gate only once. Gate
columns must not be added together as unique recovery bytes.

For backfill, provide `occurred_at` from the actual frozen decision/acceptance
receipt. Recording an old result today must not create today's new output. This
is an explicit evidence assertion, not a timestamp inferred from file mtime.
`revoke --credit-id <id> --summary <reason>` retains history and invalidates that
credit plus downstream credit on the same binary. A corrected claim requires a
new evidence-bearing credit; no silent count correction is allowed.

## Link Git milestones

After the normal validated unsigned commit, main records it:

```sh
python3 tools/recovery_workflow.py commit --actor main --sha <commit-hash> \
  --tasks CORE-EXAMPLE-01 --evidence build/example/completion.json \
  --request-id integration-example-01
```

The tool resolves a real commit in the selected repository and records its full
hash, Git timestamp, subject, task IDs and evidence hashes. It does not alter the
index or worktree. `credit` for integration includes the full registered `commit`
hash and actual-image evidence. One commit may link several tasks. Task IDs,
round numbers, event sequence numbers and Git hashes remain distinct identities.

## Inspect and export

```sh
python3 tools/recovery_workflow.py status
python3 tools/recovery_workflow.py status --actor worker2 --json
python3 tools/recovery_workflow.py history --task CORE-EXAMPLE-01 --limit 30
python3 tools/recovery_workflow.py stats
python3 tools/recovery_workflow.py throughput
python3 tools/recovery_workflow.py throughput --json
python3 tools/recovery_workflow.py report --output build/workflow/dashboard.html
python3 tools/recovery_workflow.py report --format json --output build/workflow/report.json
```

The HTML snapshot has client-side filtering for tasks, actors, rounds and commits;
full evidence is expandable. Regenerate it to refresh; no unattended service runs.
Reports omit claim tokens and escape record text. JSON/HTML writes use atomic
replacement. Queries use indexes; mutations use SQLite `BEGIN IMMEDIATE`, WAL and
a bounded busy timeout. A failed mutation rolls back task, event and request
changes together. Never delete a database/WAL while an actor may be writing it.

Statistics separate retained unique output, output since the configured epoch,
the last two completed absolute clock-hour windows, generated bytes and original envelopes at every gate. The
wall denominator continues to report time, including preparation, failures,
administration and handoffs. Completed decision intervals provide median/p90;
initial preparation and still-open intervals are displayed separately. First-round
exactness is not peer acceptance. Parallel actor times are not added into team
wall time.

`throughput` prints recent delivery and iteration speed without reading candidate
C or running builds. `throughput --json` and `stats` expose the same `throughput`
object; existing stats fields remain compatible with hourly snapshot jobs. HTML
reports display recent production speed, implementer contributions, iteration
latency and pending gates before the task list. Existing hourly report generation
automatically includes these panels; no database migration or service restart is
needed.

Throughput compares the last two completed clock hours in Asia/Shanghai (UTC+08:00),
using adjacent `[start_inclusive, end_exclusive)` bounds with local date and time
labels. A credit exactly at the hour start belongs to that hour; a credit at the
exclusive end belongs to the next hour, and fractional timestamps through
`:59:59.999999` remain in the current hour. Both snapshots within one clock hour
use identical bounds. The unfinished current hour is excluded from comparison
and has no normalized hourly rate. Credit uses its actual `occurred_at`; a
historical backfill cannot inflate a later hour. Revocations remove credit from
both completed windows while retaining audit history. If the configured epoch
begins partway through one of the windows, that first observed window is flagged
and B/hour is normalized to its observed duration; earlier windows have no
fabricated records. Summary counters, actor totals and public exports retain the
same epoch lower bound; retained cumulative history still includes earlier records.
No observed time or a zero previous rate produces an unknown
ratio, not an infinite speedup. A ratio is descriptive; different method sizes,
readiness and small samples prevent causal model or workflow comparisons.

Each gate reports unique methods, original envelope bytes, generated bytes and
original B/hour. `integrated_exact` is a derived subset of `integrated`: the
integrated binary must have same-binary live peer-exact credit, and delivery is
dated at integration. These rows must never be summed. Per-actor output follows
the same-binary local implementer, even after task reassignment; peer reviewers
and the Git committer do not receive another actor's implementation credit.
Every actor uses the same observed wall-time denominator, not active CPU time.

Decision median/p90 use complete intervals whose ending decisions fall in the
window, including intervals crossing the boundary. Initial preparation and open
intervals remain separate. First-round exactness uses the actual first recorded
non-diagnostic attempt, excluding already-active imports with unknown history;
it does not imply acceptance. The tool lists local-exact entries awaiting peer
credit, peer-exact entries awaiting integration, and latest exact rounds lacking
local credit. These are recording/gate gaps, not proof of idle time or acceptance.
Historical frozen imports without round records cannot be detected as exact
automatically. Zero means no registered live credit; owners must backfill missing
receipts using their actual occurrence times.

An already-started imported method has unknown first-attempt status in the new
ledger. Its first newly recorded candidate is excluded from the first-attempt
denominator, rather than being misreported as the method's original first try.

`import-log --actor administrator --file old.jsonl` preserves matching task events
as explicitly labeled legacy history, deduplicated by record content. Malformed
line numbers are reported without editing the source. Legacy acceptance text and
unreconciled timing fields earn no automatic credit or percentile samples. The
latest recorded round timestamp of an imported active task is retained as the
next decision's starting point. Keep original evidence and any pre-cutover metrics
alongside the ledger; independently reconciled gates can be backfilled by their
owners with actual occurrence timestamps.

## Automatic public activity

`public-export` constructs an allowlisted aggregate snapshot from one SQLite read
transaction. Task IDs, module names, addresses, source paths, instructions, event
payloads, evidence and claim tokens never enter the public schema. Classification
rules live in `config/recovery-public-map.json`: a known evidence family **and**
existing semantic source group must agree before assignment to a public submodule.
Uncertain original-inventory entries retain provisional system-only attribution.
A recognized declared system also receives provisional system-only attribution
when task metadata declares `source-contract-required`, a nonempty ownership
purpose, a well-formed original-source SHA-256 pin and nonempty evidence pins.
This metadata fallback does not read or revalidate private source files, create
a submodule ID, or grant semantic acceptance. Unknown systems, incomplete pins
and conflicting known-family rules remain unclassified. Classification does
not create acceptance credit. Submodule partitions must reconcile to global gate
counts before export.

```sh
python3 tools/recovery_workflow.py public-export \
  --public-dir build/public-site \
  --mapping config/recovery-public-map.json \
  --baseline build/private-baseline-map.json \
  --output-dir build/public-preview
python3 tools/recovery_workflow.py publish --config .local/public-progress.json
```

The ignored publication config supplies `repository` (`owner/public-repo`),
`mapping` (mapping file path), and `work_dir` (owned temporary clone/receipt path).
The unified dashboard also requires `baseline` (a private verified ROM-to-module
accounting map) and its `baseline_sha256`. This map is derived from the validated
build report and manifest, not from unintegrated source changes. A new integrated
baseline requires a reconciled, hash-bound map; automated refresh consumes only
registered committed-image receipts and their validated build/manifest metadata.
Set `refresh_integrated_baseline: true` in the publication config to advance
through additive exact integration milestones automatically. Each image must bind
its committed manifest, build report, previous image and registered task list.
A mismatched or unsupported integration fails visibly. Known group membership is
preserved; new modules without subgroup evidence remain explicitly unclassified
in the existing shared accounting remainder. No source analysis or LLM is needed.
The refreshed private registry is saved as `latest-integrated-baseline.json`.
After explicit user authorization, a dedicated scheduler invokes `publish` daily with
no LLM, session reminder or worker message. Authentication uses existing `gh` and
Git credentials; credentials are never written into exported files. The publisher
verifies the configured GitHub repository is public, obtains a fresh `main`
checkout, changes only `data/workflow.json`, `data/progress.json` and
`data/submodules.json`, creates an unsigned data commit, and pushes without force.
It never stages the implementation checkout. A lock prevents overlap; a rejected
push fails visibly and the next scheduled run regenerates from a fresh remote
checkout. Temporary clones are removed; the latest publication receipt is private.
GitHub Pages performs deployment from the public commit.

Keep submission-triggered publication disabled in ignored `.local/recovery-workflow.json`:

```json
{
  "db": "configured-ledger-path",
  "automatic_publication": {
    "enabled": false,
    "config": ".local/public-progress.json"
  }
}
```

This stops worker `credit`, `finish`, `revoke` and `commit` events from launching
public Git operations. Claims, progress and evidence-bearing per-function credits
still commit immediately to the local ledger. Administrator checks must not invoke
`publish`; they observe the same local records without producing public commits.
The legacy coalescing queue remains available for explicitly authorized deployments,
but is not part of the current daily workflow. Disabling enqueue does not cancel an
already running publication; let it finish before replacing its scheduler.

Configure one local scheduler for **23:55 Asia/Shanghai daily**, with no run-at-load
publication and no second hourly fallback. On macOS use a LaunchAgent calendar
interval `{Hour: 23, Minute: 55}` and `RunAtLoad: false`; the calendar uses the host's
local timezone, which must match the intended schedule. On other systems configure
the equivalent daily job explicitly. The command is:

```sh
python3 tools/recovery_workflow.py publish --config .local/public-progress.json
```

Keep scheduler definitions, absolute paths, credentials and logs private. Set the
scheduled job's Git author/committer to a project identity rather than a personal
email. The publisher lock still prevents overlapping scheduled/manual invocations;
remove duplicate triggers instead of removing concurrency protection. Check the
private `latest-publication.json` receipt for success or a concrete failure. A
sleeping/offline host may delay the scheduled update. Explicit toolkit/documentation
releases are separate from daily progress snapshots.

The page reads only `progress.json.dashboard` for its efficiency table, overall
cards, systems and modules. All levels sum the same module rows. Each row combines
verified C in the ROM, exact C available, exact C not yet in that ROM, task states
and last-completed-clock-hour delivery. Original-range union removes overlap between the
verified exact baseline and local exact credits, including duplicate credits for
overlapping ranges. The delivery metric uses the last completed Asia/Shanghai
clock hour with explicit start-inclusive/end-exclusive bounds. Revoked credits disappear on the next export. Unassigned
tasks remain visible under their provisional system instead of disappearing.
The same rows are mirrored as `submodules.json` entries' `current` field for
other consumers; historical snapshot fields remain compatible.

Exact span bytes include associated literal/alignment bytes and are not named
function-body bytes. Local matches are not integrated or independently accepted
merely because they appear in the total. Missing range records are excluded from
the union and counted explicitly. Local, peer and integrated delivery rates stay
separate. Whole-game completion remains unknown without a code denominator.
Site updates can be delayed while the machine is offline; the page displays the
activity timestamp and marks older snapshots.

Worker messaging is independent of data collection: submit every real round and
gate to the ledger, continue to the next owned task, and suppress routine chat
checkpoints. Consolidate conversational updates at most hourly unless the user
asks or a blocking issue requires their action. Do not publish on every round.

## Validation and boundaries

Run `python3 -m unittest discover -s tests -p test_recovery_workflow.py -v`.
Tests cover real concurrent claim processes, reservations/overlap, stale tokens,
retry deduplication, transaction rollback, historical migration, adjacent timing,
independent credit, revocation, real temporary Git commits, and escaped HTML.
No ROM build or game-case rerun is needed for this coordination tool.

Automatic public data commits and the dashboard use matched original ASM span bytes divided by total catalogued original ASM span bytes. The denominator retains already migrated C/mixed code and excludes resource ranges; both sides include in-function literals/alignment. This is a known-code catalogue ratio, not a complete-game executable census. The pinned original ASM catalogue is configured separately from the changing integrated baseline. Missing/invalid denominators remain unknown; no ROM-size fallback. A changed catalogue identity suppresses a misleading byte/percentage-point comparison. The separately pinned integrated amount remains visible; local matches are not silently counted as integrated.

The public `asm_rewrite` metric uses `rewritten_original_asm_bytes / known_original_asm_bytes`. Both sides count original ASM spans; generated C binary sizes never supply the numerator. The historical `c_match` field remains a compatibility alias. Assigned Sol A/B/C lanes are displayed individually alongside main and workers.

`dashboard.daily` reconstructs calendar-day history in Asia/Shanghai (UTC+8)
from the original occurrence timestamps of currently unrevoked ledger credits.
It exports daily new whole-exact matches, pure-C and eligible-mixed original ASM
bytes, and integration bytes as a separate gate. Original-range unions remove
duplicate and overlapping credit within each gate; missing locations are counted
and excluded. Integration requires corresponding exact acceptance. Zero-activity
days remain present and the current day is partial, without a projected rate.

Daily cumulative curves and percentages cover dated ledger receipts only, using
the same pinned known-ASM catalogue denominator and identity as the headline.
They do not backdate the current verified image: current matched bytes without
a registered local delivery date are explicitly undated. Missing older receipts
are unknown historical recovery, not evidence that no recovery occurred. A
revocation recomputes dated history on the next export. An unavailable catalogue
leaves percentages unknown. These statistics do not establish gameplay completion.

### Eligible mixed completion (r72)

The completed original-ASM numerator includes whole-exact pure C and eligible
mixed functions: ordinary inline instruction bytes / total generated instruction
bytes must be strictly below10%. Explicit low-level engine, graphics or audio
exceptions may exceed this ratio, with component, class and reason retained in
private accounting. These exceptions do not raise low-level migration priority.
Pure-C spans, mixed spans and local versus integrated completion remain separate.
Unknown mixed ratios do not acquire completion credit; a partial exact prefix
never qualifies. The exporter reads historical manifest accounting through its
pinned hash, not the changing production manifest.

## Native identity, continuation clocks and migration attribution

Task intake rejects a second registration of the same known ROM offset and
complete original span, even when the task or module name changes. Existing
historical rows, proofs and gate totals remain intact. A different or unknown
span is not automatically the same method; resolve its native boundaries before
claiming new recovery. Check a hash-bound production report before intake:
previously selected whole-exact C is registration, not new matching delivery.

Claims preserve the original `started_at` after a permitted requeue. Each claim
also records its episode timestamp. Round events distinguish elapsed episode
preparation from `since_original_start_seconds`; original failures and handoffs
must remain in end-to-end accounting.

The administrator-only `continue` operation accepts a pinned admission packet
and transfers a blocked task directly to an implementation actor. It requires
unchanged task/native/source identity, state/token and event-history snapshots,
known unexhausted hypothesis budgets, progress strictly above 70%, fewer than
six effective causes, and a new source-backed cause. Complete, credited,
unknown, exhausted or duplicate work cannot continue. This operation preserves
history and original time; it grants no acceptance credit. A packet is not
permission to continue a game task: current execution authorization is still
required. No historical task is automatically requeued by this tool update.

`public-export --migration-attribution audit.json` optionally validates a private
source/range/build-report proof and emits separate registration, new-migration
and unknown totals alongside unchanged raw gate totals. Before/after production
reports, candidate source/binary identities, complete original envelopes and
snapshot chronology must agree. Unknown attribution stays unknown. Rates use
the audit's explicit observation window; an old cohort rate is neither the
current completed-clock-hour rate nor a whole-workflow speedup. The generated public
account contains aggregates, not private source paths or raw proof packets.
