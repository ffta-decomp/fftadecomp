# Define a ROM row bank before its index arithmetic

- Native `CoreRegion_0004BB10`:74B =70 instruction +4 literal bytes; fixed O2/interwork, no instruction-bearing ASM or retained retail tail.
- Preserve four ordered first-match key comparisons and direct byte-valued returns; unknown row/key domains stay unknown.
- A unified result local generated72B with38 same-offset bytes. Direct per-match returns retained72B and improved to53/74; neither was whole-exact.
- Defining the actual typed ROM-bank pointer before `row = rows + id` restored the early bank load and key lifetimes, including the original saved register:74 native bytes plus a terminal2B compiler NOP.
- The existing declared terminal-alignment trim removed only that NOP after BX. Strict module checks then verified74/74B:three source causes plus one metadata-only invocation.
- This is observed source-definition-order output, not compiler-pass attribution or a universal pointer-declaration rule. Historical sort and shared-return examples guided the questions.
- Local native equality remains separate from independent peer and production integration; no natural menu/table-domain coverage or speedup claim.
- Source-lease `2026-10-24T18:51:25.670959+00:00` to local proof `2026-10-24T18:59:09.450108+00:00`: 463.779149s gross including production-integration preemption. Earlier world qualification is preserved separately.
- Frozen source SHA-256 `89351f7153dbd387f7375ec5f5885eebfd34bb845b2b5907bc91387de1913b9d`; report `265dd8a24016af52253134d9db52ce12847bf0291554ed60aa79ae0cdd876bcb`; native binary `0411eb4ddc72eb0567e4dabd0e420ab23eec25f9b9ea9430097de141f9aeb144`.
