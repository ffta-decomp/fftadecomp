> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Whole-game recovery priorities

Baseline: `2e7eac795b1e0a9cef511c3418a32330bdfa7f1e`, 2026-10-19.
This is a system dependency plan, not a gameplay completion percentage or a new
ROM recovery claim. Current owners and capacity belong to the local assignment.

## Active battle campaign

The current user direction narrows new rewriting to one shared battle group,
using [map/reduce recovery](battle-group-recovery.md). Finish and deliver already
claimed functions and running batches first. Then all actors autonomously claim
disjoint small complete battle methods, recover untranslated game-specific
dependencies bottom-up, and advance toward action/effect/resolution/turn consumers.
Complex low-level dependencies keep their existing implementations and receive
typed interface descriptions only. Independent mission/story, economy, save,
engine and presentation expansion is deferred. The ordered roadmap below owns
the subsequent campaigns; concurrent workers stay inside the current group.

## Phase and acceptance

Much of the selected program now has rebuildable C or exact source ASM, and
large resource families have deterministic codecs. System semantics and the
connections between controllers are less complete. Work should now explain and
recover complete gameplay transactions using that existing implementation.
Converting isolated helpers to C, exhaustive engine naming, and removing every
original-byte dependency are not prerequisites for this phase.

A transaction identifies its inputs, dispatch/state transitions, rule and data
consumers, writes, completion/failure conditions, and caller continuation. Keep
unsupported edges explicit. Transaction-led semantic recovery is the active workstream. Use existing entry and responsibility evidence to select bounded rewrite contracts; preserve existing C and exact ASM dependencies. Classify only the unresolved edges needed by the selected transaction. Harness work is justified only by a measured repeated cost. Existing exact ASM remains the fallback for
unresolved boundaries. Prepare compiler structure alongside semantic contracts
and pursue bounded exact matching within contract-ready core families. Measure
semantic delivery and exact matched C delivery separately under
[the execution rules](c-recovery-throughput.md); byte throughput must not promote
unrelated helpers or presentation code above the core systems below.

## System order and remaining contracts

P0 is a demonstrated correctness error invalidating the active group. Otherwise
advance the following groups in order, using small-first bottom-up map work and
coherent reduce within each. Finish existing claimed functions before switching.
Required game-specific dependencies may be recovered before their group's turn;
keep their real ownership and count each native range only once. Do not start an
independent later-group campaign as an empty-queue fallback.

| Order / group | Existing evidence to reuse | Complete contract / remaining work |
| --- | --- | --- |
| 1 / Battle actions and turns — active | CT/turn-manager C and bounded probes; phase, target-application and outcome ASM; ability/effect data | Command/AI choice -> targeting -> damage/healing/status and resource effects -> action/actor/turn continuation; victory/defeat exits remain explicit. |
| 2 / Jobs | Job definitions, job-change and derived-unit-state helpers | Eligibility -> job change -> equipment/stat restrictions and persistent job state. |
| 3 / Abilities and skills | Ability definitions, mastery, exact effect handlers and availability C | Learning/mastery -> usable command -> costs/restrictions -> effect interface and persistent learning. Reuse effects recovered in battle. |
| 4 / Story and authored events | Scene commands, game flags, event resources and exact VM interfaces | Script operands -> game-specific state transitions -> event continuation. Generic VM execution is an interface dependency, not narrative recovery. |
| 5 / Missions, rewards and progression | Mission definitions/accessors, live reward records and progress slots | Acceptance -> conditions -> completion/failure -> rewards/flags -> next mission/event. Reuse story, item and job interfaces. |
| 6 / Items, equipment and economy | Item records, inventory mutation, ownership, equipment replacement and masks | Acquire/use/equip/unequip/buy/sell: quantities, restrictions, derived state and reward/inventory persistence. |
| 7 / World navigation and map rules | Map layouts, terrain/clipping consumers and coordinates | Movement/occupancy -> route and location/event transitions. Rendering and palette work remain outside game-policy scope. |
| 8 / Save and reload policy | Save-byte/flag accessors, compaction, persistent controllers and flash interfaces | Schema ownership -> image construction/validation -> commit/load/failure -> gameplay-state restoration. Hardware transport remains interface-only. |
| 9 / Game menus, input and text decisions | Existing menu/text C, input and command bindings | Game-specific selection, confirmation, cancellation and dispatch decisions. Reuse generic layout/render/font/input transport. |
| 10 / Multiplayer game policy | Existing link-related source/consumer evidence where established | Supported activities, session rules and game-state synchronization; keep unknown activities explicit and serial transport separate. |
| Deferred / Engine, graphics and audio | Exact scheduler/container/runtime/hardware/presentation implementations | Describe complex low-level ABI, effects and layout; retain real existing bodies. No automatic implementation rewrite or new broad resource campaign. |

Group reduce reconciles its bounded native membership, each method's delivery,
dependency closure, production identity and explicit residuals before advancing
the active group. Never call a terminal nonexact method complete or erase its
budget. If a genuine residual blocks group completion, publish the supported
blocker for a priority decision rather than silently spreading workers across
other systems. Group matching closure and natural gameplay proof remain distinct.

## Immediate work boundary

The battle phase controller at ROM `0x92784..0x96b2c`, record consumer at
`0xa433c..0xa52d4`, target-record routine at `0xa23b8..0xa3778`, and the
208-byte bridge at `0xa8194..0xa8264` are supported game-specific scopes.
Selected source proves the direct call spine from `0x92784` through the bridge
and record consumer to the target-record routine; see the
`config/battle-action-chain-01b.json` (implementation-checkout reference).
The reviewed state-58/60 interface shows record-pointer creation followed by a
full-word poll return that retains state 60 or advances to 62. These edges and
bounded arm cases do not prove natural execution, HP/action effects, or victory
and defeat meaning. Use the existing [responsibility guide](asm-responsibility-guide.md)
and source ASM. The phase controller's full 127-slot semantics remain a review
boundary; internal labels sharing its stack frame are not independent C
functions.

The independent save-transaction inventory is deferred during the active battle
campaign. Reuse existing save interfaces when the battle group actually consumes
them. Do not start another resource residual or unrelated text-helper batch.

## Measurement

Report completed transaction stages, resolved dependency edges, remaining
semantic obligations and the exact tested input/state contract. Keep selected
C/ASM/resource bytes as separate build accounts. Current pure C spans total
61,510 bytes over 732 bodies; mixed spans are 256 bytes over three functions;
exact ASM spans total 1,063,992 bytes; reconstructed assets 9,247,442 bytes;
original-byte dependencies 322,455 bytes. These are disjoint manifest/build
accounts, not semantic or gameplay completion percentages. Assets exclude
6,081,561 bytes of reconstructed padding. The executable and system-wide
semantic denominators remain unknown.

The frozen residual worklist still has 168,371 bytes open, separately from
154,058 deferred graphics bytes and 26 bytes of newly retained C-envelope tail.
Keep that ledger, but do not turn residual-byte reduction into the active
whole-game priority. Candidate classification, exact ASM rebuilding, semantic
understanding, controlled equivalence and natural-path coverage are different
claims.

Historical task ledgers preserve evidence; their old `next_probe` or priority
fields do not dispatch work. At most one current task per downstream session.
