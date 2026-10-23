# Recovery workflow library

[Contribute by group](../CONTRIBUTING.md) · [Function list](../data/functions.csv) · [ASM directory metadata](../data/asm-layout.json) · [Progress dashboard](https://gh.bhee.online/fftadecomp/)

| Need | Read / use |
| --- | --- |
| Scope, fixed O2, evidence and publication boundaries | [AGENTS.md](../AGENTS.md) |
| Reproduce setup, unpacking, one local build and gates | [Executable walkthrough](reproduce-recovery.md) |
| Start one original-ASM-driven method | [Workflow](gba-asm-to-c-workflow.md) |
| Recreate the private ASM directory / unpack resources | [Extraction](extract-asm.md) |
| Function IDs, native addresses, spans and grouping | [JSON](../data/functions.json), [CSV](../data/functions.csv) |
| Source forms and concrete counterexamples | [O2 quick reference](o2-reconstruction-quick-reference.md) |
| Compiler passes / allocation / reload behavior | [agbcc O2 guide](agbcc-o2-matching.md) |
| Structural mismatch and plateau diagnosis | [ASM-to-C guide](asm-to-c-migration.md) |
| Successful examples and transfer limits | [Lesson protocol and index](c-recovery-lessons.md) |
| Register constraints / first divergence / RTL | [EDS reference](eds-matching-reference.md) |
| State, callback and source-family organization | [pokeemerald reference](pokeemerald-reconstruction-reference.md) |
| ARMv4T operations and decoder pitfalls | [ISA lookup](gba-asm-to-c-idioms.md) |
| 47 references / 23 pinned project checkouts | [Resource catalogue](gba-asm-to-c-resources.md), [reference pins](../vendor/README.md) |
| Atomic local claims, round metrics and commit receipts | [Workflow CLI](recovery-workflow-cli.md) |
| Group map/reduce and dependencies | [Battle group](battle-group-recovery.md), [system priorities](game-recovery-priorities.md) |

Original documentation is CC BY 4.0. Original tools are MIT. Third-party projects
retain their own licenses. Links marked implementation-checkout reference need
the separate implementation checkout; no private filesystem links are published.
No ROM, generated code, game assets, private logs or credentials are included.
