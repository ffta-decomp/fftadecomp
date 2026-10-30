# Recovery documentation

Start with the [repository-level decomp skill](../.agents/skills/ffta-decomp/SKILL.md).
Its short entry routes to maintained technical topics; historical guide paths
remain as links to those topics. You do not need to read every document.

| Need | Reference |
| --- | --- |
| Recover a function or diagnose a mismatch | [Skill](../.agents/skills/ffta-decomp/SKILL.md) |
| Find one source-shape rule | `python3 tools/find_matching_rule.py SYMPTOM` |
| Decode ARMv4T / Thumb operations | [ISA lookup](gba-asm-to-c-idioms.md) |
| Recreate original ASM privately | [Extraction](extract-asm.md) |
| Build completed sources and check one final ROM | [Build guide](build-completed-sources.md) |
| Verify an external submission | [Import guide](../.agents/skills/ffta-decomp/references/contribution-imports.md) |
| Explicit downstream build extensions | [Extensions](optional-build-extensions.md) |
| Claim a function / submit a PR | [Contributing](../CONTRIBUTING.md) |
| Addresses, ranges and current publication | [Catalogue](../data/functions.csv), [source index](../src/completed-index.json) |
| Platform references and licenses | [Resources](gba-asm-to-c-resources.md), [reference pins](../vendor/README.md) |

Use English repository prose. Do not publish ROMs, extracted dialogue/assets,
private paths or local evidence. Original documentation is CC BY 4.0; original
tools are MIT. Third-party source retains its original license.
