# Nested-record flag policy: preserve the full parameter and void return

- Original `EDB80` retrieves a full nested-record word, moves it into argument4, then calls the existing collection policy with selector5, mode1 and no excluded record. The retained policy clears flag bit0 on collected records; no helper body or natural list bound is newly recovered.
- The original POP into R0 restores saved LR before BX. The wrapper is void; do not invent a result from the last helper call. Keep the nested pointer word full32 rather than narrowing it with the u8 selector/mode arguments.
- The first fixed-O2 C source reproduces all22 native instruction bytes. Its raw text additionally ends with a2-byte C046 NOP after BX; the strict preflight correctly rejects this before explicit `trailing_alignment_bytes=2` metadata and a newly pinned report admit the unchanged source.
- Reuse the existing exact terminal-alignment family proof. Do not shorten an instruction, literal or original span to fit, and do not reuse a report after effective metadata changes. The accepted C contains no instruction ASM or constraints.
- The two local comparisons total2.547306s; source-lease-to-freeze is262.537991s. The failed preflight and two orchestration errors remain preserved. Independent peer/production are separate; no natural gameplay or hardware coverage is claimed.
- Frozen whole-native proof SHA-256:`150a4715e814bb308fa47ed888d0d37a7fde0ccf87a8fd6f442fc760d4412a2d`.
