> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Selected ASM responsibility guide

Baseline: commit `0bfa3839b746362fe92830c6a84b52f4c48fa4c9`, retail manifest SHA-256
`f3305168553f66d3230990654809a77a35b89ee871f53148eab07e9c4288ce37`, and US retail
ROM SHA-256 `43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19`.
The companion `config/asm-responsibility-index.json` (implementation-checkout reference)
lists exact selected module spans and repository source hashes.

## Evidence scope

The baseline contains 4,233 selected ASM modules spanning 1,064,872 bytes:
936,556 instruction bytes, 120,304 literal/data bytes, and 8,012 alignment
bytes. The 28,052 dispatch-table bytes are already part of the literal/data
total. Module count is not function count.

The index includes 427 modules / 161,004 span bytes with supported game,
content, engine, or descriptor-binding evidence. This is 15.12% of the selected
ASM span, not a measure of recovered gameplay. The narrow `semantics_reviewed`
subset is 5,342 bytes. Another 1,416 modules / 592,338 bytes have API-only
caller hints; 2,390 modules / 311,530 bytes have no supported responsibility
assignment. Neither group is assigned a business or engine role here.

The responsibility labels describe the evidence level in the index. They do
not prove complete branch semantics, every caller domain, natural runtime
coverage, or a finished game system. Descriptor membership is distinct from
handler-body semantics. A screen controller remains game-specific when it
also calls rendering helpers; a business caller does not turn a generic helper
into game logic.

## Priority business chains

| Chain | Supported entry points and observed role | Open boundary |
| --- | --- | --- |
| Battle actions | `asm/core_battle_callbacks_07/BattleCoreFlow_00092784.s` (implementation-checkout reference) checks turn eligibility and updates battle/unit selection and persistent flags. The related `asm/core_battle_callbacks_07/BattleCoreFlow_000A23B8.s` (implementation-checkout reference), `asm/battle_callback_producers_22/BattleCallbackProducer_000A433C.s` (implementation-checkout reference), and `asm/battle_callback_producers_22/BattleCallbackProducer_000A5B98.s` (implementation-checkout reference) consume unit, inventory, ability, or map-occupancy state. | These are proven game-specific consumers, not a claim that every branch of a complete action/turn chain is understood. Subcase rules, caller domains, and natural battle coverage remain open. |
| AI ability choice | `asm/core_frontier_30/CoreRegion30_000C045C.s` (implementation-checkout reference) consumes the `asm/ai_ability_evaluator.s` (implementation-checkout reference). The evaluator calls three mode adapters at `0xc3870`, `0xc387c`, and `0xc3888` for modes 3, 2, and 1; the adapters at `0x1342a8`, `0x1342b4`, and `0x1342c0` feed `asm/core_battle_dependencies_04/BattleDependency_00133F70.s` (implementation-checkout reference). `asm/core_battle_dependencies_04/BattleDependency_00133E18.s` (implementation-checkout reference) and `asm/core_battle_dependencies_04/BattleDependency_0012ED98.s` (implementation-checkout reference) provide separate gates. | Output capacity, maximum ability ID, full ranking policy, and natural AI action coverage remain unproved. |
| Mission and reward state | `asm/Remaining47_000CFCD0.s` (implementation-checkout reference) scans mission IDs 1–511, resolves special reward codes, copies live 16-byte records, and queues them. `asm/core_frontier_28/CoreRegion_00046A4C.s` (implementation-checkout reference) reads mission definitions/flags and performs weighted selection. `asm/core_frontier_28/CoreRegion_0003197C.s` (implementation-checkout reference) also reads mission properties and persistent flags. | Reward records and bounded consumer behavior are evidenced; downstream grant rules, the complete mission producer domain, save/reload effects, and natural progression remain open. These modules are related consumers, not asserted as one uninterrupted call sequence. |
| Items, equipment, and jobs | `asm/core_frontier_28/CoreRegion_0003E3B4.s` (implementation-checkout reference), `asm/nested_task_state_18/SceneNestedState_00069658.s` (implementation-checkout reference), and `asm/nested_task_state_18/SceneNestedState_0006D664.s` (implementation-checkout reference) operate on game item state. `asm/core_registration_33/CoreRegistration33_000775A8.s` (implementation-checkout reference) reads equipment masks; `asm/core_frontier_27_34/CoreScene34_0007A79C.s` (implementation-checkout reference) refreshes derived unit state; `asm/core_registration_33/CoreRegistration33_00085AA8.s` (implementation-checkout reference) calls `ApplyUnitJobWithFlag`. | Exact shop/menu labels, full item-ID producer bounds, and natural inventory/equipment/job flows remain separate questions. UI/rendering dependencies do not change these game-specific roles. |
| Persistent progress | `asm/core_global_dispatch_36/CoreGlobal36_00138EFC.s` (implementation-checkout reference) compares selected mission-record flags against 300 before state changes. `asm/nested_task_registration_17/SceneNestedTask_000510B0.s` (implementation-checkout reference) branches on and updates persistent flags. | Specific story-screen labels and complete event ordering are not established by these scope labels. |

## VM mechanism versus narrative content

`asm/scene_vm_core_01/RunSceneCommandLoop_08122ABC.s` (implementation-checkout reference)
uses six-byte command descriptors, an indirect handler call, command-length
advancement, and repeat/status handling. The index separately records 31 scene
opcode bindings and six nested battle-script opcode bindings among 236 catalog
bindings over 235 modules. A binding proves table membership only; it does not
explain an opcode's full rule or establish complete story order. Concrete scene
state effects and script resources must be recovered separately.

## Stable engine scope

Audio mixer/track support, graphics and palette helpers, generic scheduler and
callback containers, division/runtime/memory routines, flash/WAITCNT transport,
interrupt drivers, and font-source selection remain identified as engine or
library scope where supported. These exact ASM modules stay available as
dependencies, but receive lower semantic-rewrite priority than battle,
mission, ability, item, equipment, job, and progress rules. Do not infer game
semantics from an API name or propagate an engine label to a client callback.

The audit counted 25,616 selected cross-module direct-call/unconditional-branch
edges and 13,473 PC-relative address loads, but the published index omits the
large raw graph. Indirect calls, conditional transfers, outgoing C-body calls,
and targets outside selected modules are not fully enumerated. A loaded address
alone does not prove dereference or use.

Classification is metadata only: it changes no selected instructions, resource
bytes, original-byte dependency, or gameplay-validation count. Use it to choose
one later business-chain task; it does not authorize bulk C conversion or
relabeling every handler.
