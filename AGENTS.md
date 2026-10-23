# Project and target

Recover the supplied US Final Fantasy Tactics Advance as a reproducible native
GBA project with readable C, necessary ARM/Thumb assembly and original English
resources. Do not modify unrelated projects or their active processes. A host wrapper, booting image or ROM
copy is not complete recovery. Keep system logic, data and gameplay evidence
separate for battle, progression/story, jobs/abilities, inventory/economy, menus,
saves and supporting engine systems.

The active retail SHA-256 is
`43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19`.
Validate the input with `python3 tools/identify_rom.py <rom>` and
`config/retail-us.json` before ROM analysis/builds. Refuse unknown revisions. The
older Chinese translation is inactive; recover English text, scripts and fonts.

CJK extraction, conversion, translation and localized resource packs belong to
the independent external resource project. Such builds must explicitly select
private scripts/configuration. Never infer private paths, auto-discover localized
content or add localization-specific rules/tools to the public build flow. Keep
only generic engine and resource-format interfaces here. Investigate existing
upstream work, preserve licenses and prefer submodules for adopted dependencies.

# Contributor coordination

Read [CONTRIBUTING.md](CONTRIBUTING.md) and the public native-function catalogue
before requesting a disjoint function through a public Issue. A maintainer confirms
canonical ownership before implementation. Public metadata is a dated snapshot,
not a promise that every row is available. Keep local setup, private assignments,
account/session information and machine paths outside this repository.

# ASM-driven C recovery

Follow [the execution rules](docs/c-recovery-throughput.md),
[ASM-to-C diagnosis](docs/asm-to-c-migration.md) and
[REA/GBA workflow](docs/rea-gba-workflow.md).

1. Establish the complete original ARMv4T entry/mode, ROM offset and GBA/Thumb
   addresses (including the Thumb mode bit). Confirm all returns, shared tails, branches, literal/jump tables and
   alignment using original ASM, neighboring entries and callers. Do not guess
   boundaries or partition a shared stack frame.
2. Before C, record the ABI, helper arguments/returns (including stack arguments),
   preserved registers, direct/indirect relationships and uncertainties, object
   layouts, widths/signedness, CFG, read/call/store
   order, alias/reload effects and compiler-shape hypothesis. Unknown semantic
   names remain tentative. Reuse real C/exact-ASM helpers through typed bindings;
   declarations are not recovered helper bodies or production stubs.
3. Reconstruct readable C from those operations, not a fresh behavioral design.
   Preserve overflow, truncation, sentinels, lifetimes and site-specific access
   order. Distinguish ordinary RAM, alias/callback-visible state and MMIO before
   choosing qualifiers. Use descriptive evidence-backed names, or neutral names
   where meaning is unknown. Preserve task/module/linkage identity.
4. Use the pinned `agbcc` **fixed O2** configuration and existing CPU/ABI/interwork
   settings. No optimization-level/flag search or historical mass rebuild. Use
   existing method/module build entry points backed by `tools/build_rom.py`;
   full-ROM builds are coherent integration gates, not iteration prerequisites.
   Keep test-only patches out of the production manifest and image.
   Pin source/header, manifest and complete toolchain inputs (agbcc revision/flags,
   preprocessor, binutils, Python and host); retain the actual
   manifest snapshot, not just a hash of a mutable shared path.
5. Change one source-backed cause, predict its generated effect, compile locally
   and record the decision. Diagnose ABI/frame/CFG/order/width before allocation
   and placement. A fit or scattered equal bytes is not a whole-function match.
   Do not replace source diagnosis with spelling permutations or global volatile.
6. Preserve every failed command/hypothesis and all elapsed time. Ordinary matching
   has three distinct source hypotheses; an actual match above70% may receive up
   to three more supported trials. After three failures on a near-exact plateau
   (at least95% or at most16 unmatched bytes), the owner must reread the complete
   original/C/generated ASM and explain a falsifiable cause before another edit.
   Technical repairs do not invent new hypotheses or reset clocks. A terminal
   method needs a supported explicit continuation, not renamed retries.

Bounded finite-choice screening is optional. Reuse hash-bound results;
model labels are provisional and never establish boundaries, ABI or acceptance.
Extract exact calls/branches/literals locally; do not classify the whole project
before implementing a proven core method. Never expose credentials.

# Acceptance and delivery

- **Whole exact:** complete original instructions, literals, jump tables and
  alignment match at original entry/placement with pinned retail, source/header
  and toolchain provenance. A different implementation actor mechanically checks
  the frozen full-range proof; the legacy `peer_exact` receipt must explicitly
  identify `whole_exact_mechanical`. Do not duplicate human C review or unchanged
  behavior banks. Confirm production-linked bytes at integration. Prefixes,
  retained original instructions, relocation, uncertain boundaries and source
  changes without provenance do not qualify.
- **Nonexact semantic:** preserve pinned differences and retained retail bytes.
  Independent source-derived ABI/effect oracles and relevant paired execution
  remain necessary before acceptance. Controlled helpers and coverage limits are
  explicit. Cover relevant returns, mutations, callback/continue/advance paths
  and changed actors, not only repeated slot-zero returns. Preserve negative
  controls. Changed binary/dependencies need relevant checks; unchanged evidence
  is reused by exact identity, including changed-input-only deltas.
- **Mixed:** an explained instruction-bearing island uses `kind: mixed` with
  exact `inline_assembly_bytes` and component ownership. Complete byte-identical
  mixed below10% inline instruction bytes counts as completed migration; exclude
  literals/alignment/veneers from the ratio and keep pure C separate. Engine,
  graphics and audio may exceed this only with source-backed ownership and
  `assembly_ratio_exception`; they remain lower priority. No opaque ASM bodies,
  opcode dumps or original-byte inclusion disguised as C. Readable source ASM
  likewise needs explicit instructions/labels/data and exact retail comparison.
- **Compiler constraints:** fixed-register locals and instruction-free empty
  ASM constraints are permitted when the readable C fully expresses the original
  logic and the annotation explains a concrete allocation/lifetime requirement.
  Operands must have valid definitions and truthful constraints/clobbers; empty
  output-only ASM must not fabricate a value. Freeze and verify the resulting
  complete native bytes with the pinned normal compiler. Record the constraint
  in the method lesson/proof; it does not invalidate a whole-function match or
  add instruction-bearing ASM bytes. Actual emitted inline instructions remain
  subject to the mixed rule. No opaque ASM replacement or compiler override.
- Record each decision and reached local gate immediately through the CLI, before
  optional cleanup, lessons, hourly reports, peer gates or integration. Progress
  text and `finish` alone do not submit a credit. Rejected proof stays rejected;
  repair producer provenance separately from independent verification.
- Apply [naming closeout](docs/c-recovery-naming.md) and the implementer's
  [lesson protocol](docs/c-recovery-lessons.md), preserving first-result/gate
  times. Pin final naming changes; reuse identical binary evidence without new
  recovery credit. Transfer lessons only under their recorded conditions.
- Exact and semantic delivery, integrated identity, natural gameplay/replay and
  physical hardware evidence are distinct. A tested emulator path proves only
  that input/coverage. Do not infer complete gameplay from rebuilt bytes.

# Measurement, publication and storage

The primary rate/ratio uses deduplicated **matched original ASM envelope bytes**,
not C output bytes. Report local, independent and integrated gates separately;
never sum them. Keep pure C, mixed/inline ASM, source ASM, literals/alignment,
resources and retained original inclusion separate. Original-byte inclusion is
a build-dependency measure, not remaining executable code; unknown denominators
stay unknown. Source lines, cases, veneers and repeated builds are not recovery.

Include preparation, qualification, failures, naming, administrator work, recovery
and handoffs in wall time. Report complete method/decision latency, median/p90,
first-pass outcomes and cumulative/trailing-hour rates with sample boundaries.
Unknown time stays unknown. Compare like gates/cohorts; do not claim model or
workflow speedup from unlike tasks or compiler-stage timing alone. The authorized
30-minute check compares adjacent complete hours and acts on declines; it does
not authorize empty polling, duplicate tests or candidate C review.

Use English code/repository prose. Update `docs/status.md` and `docs/progress.md`
for coherent recovery/integration milestones, with spans, counts, denominators,
ROM hash, evidence and limits. Data publication uses the existing authorized
automation. Otherwise do not publish or push without explicit authorization.
Commit unsigned with explicit coherent paths; preserve unrelated dirty work.
Run relevant JSON checks and `git diff --check`; ROM checks apply to changed
recovery/build inputs. Documentation-only cleanup does not require a ROM build.

Keep ROMs, assets, saves, captures, credentials and private paths outside tracked
source. Use configured external evidence/output roots and root `build/` caches.
Before another full image, use owner-scoped retention to retire unnecessary
inactive generated ROMs. Preserve retail references, saves, active/pending images,
required baselines and hash-bound evidence. Never clean another lane's live work.

For resource-tool changes, use the revision-validating extractor into clean
external directories; compare two clean independent runs for deterministic
hashes and exact parse/serialize
round trips. A changed known field/pixel must expose its ROM offset. General
resource expansion must not displace ready core ASM-to-C delivery.
When link multiplayer enters scope, separate game-session/synchronization policy
from serial transport and scheduling; register references alone prove neither.
