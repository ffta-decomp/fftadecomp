---
name: ffta-decomp
description: Recover FFTA US ARM/Thumb functions as readable C with the pinned agbcc compiler, diagnose native-code mismatches, verify contributions, and integrate byte-identical source builds. Use for ASM-to-C reconstruction and matching in this repository, not for new game mechanics or translation resources.
---

# FFTA ASM-to-C recovery

This repository-level skill travels with the source checkout. Run commands from
its repository root; do not install a second copy globally. The references below
are relative to this skill; command paths are relative to the repository root.
Read only the reference relevant to the current operation.

## Choose the next step

| Current task | Read |
| --- | --- |
| New function, uncertain boundary, helper or stack argument | [Boundary and ABI](references/boundary-and-abi.md) |
| Drafting C, fields, widths, CFG or object lifetime | [Reconstruction rules](references/reconstruction.md) |
| Nonexact output, code displacement, registers or call setup | [Mismatch diagnosis](references/mismatch-diagnosis.md) |
| Reusable observed source shapes and their counterexamples | [Pattern lookup](references/patterns.md) |
| Local build, exact proof, publication manifest or final image | [Verification and integration](references/verification-and-integration.md) |
| External contribution, import, provenance or attribution | [Contribution imports](references/contribution-imports.md) |

## Essential constraints

- Authenticate the user-supplied US ROM with `tools/identify_rom.py`. The target
  SHA-256 is `43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19`.
  Keep ROMs and extracted game content outside tracked source.
- Establish the entire original function, ABI and ordered effects before C.
  A catalogue span, adjacent symbol or similar function is not boundary proof.
- Recover the original operations and compiler input shape. Do not substitute a
  fresh behavioral design or an opaque instruction/byte body.
- Use the pinned normal agbcc with `-O2 -mthumb-interwork` and the existing
  preprocessing/link configuration. Do not search optimization flags.
- Make each effective edit answer one evidence-backed hypothesis with a predicted
  native change. Keep failed hypotheses and actual compiler outcomes. If output
  repeats, find new evidence rather than cycling equivalent spellings.
- Source checkers and aligned ASM are diagnostic hints. Neither proves ABI,
  behavior, whole-function matching, or accepted progress.
- Whole exact means every byte of the established original span at its original
  placement, including owned literals/tables/alignment, with source and build
  input provenance. A fitting prefix or high similarity is insufficient.
- Distinguish pure C, mixed instruction-bearing ASM, nonexact C and retained ASM.
  A locally verified rewrite and its later full-image integration are separate
  results; count each original range once.

## Fast symptom retrieval

```sh
python3 tools/find_matching_rule.py --list
python3 tools/find_matching_rule.py "stack argument"
python3 tools/find_matching_rule.py "代码错位" --limit 1
```

The index returns the matching section rather than loading every guide. Reuse it
while the discrepancy is unchanged. If no rule applies, inspect the original
operation; do not manufacture a fix from the closest keyword.

For a retained local result, diagnose without another compilation:

```sh
python3 tools/check_matching_rewrites.py --build-report "$BUILD_REPORT"
# Optional asm-differ environment: setup is in the diagnosis reference.
build/asmdiff-venv/bin/python tools/diagnose_module_build.py \
  --build-report "$BUILD_REPORT" --output "$NEW_DIAGNOSTIC_DIR"
```

## Completion and transfer

Freeze the final source/header/configuration and local whole-range proof after
readable naming. Reuse unchanged evidence by exact identity. Integrate the
selected source through the completed-source build, write one ROM, and verify
its final on-disk hash; do not rebuild a ROM for every local trial.

When an experiment supplies new reusable knowledge, update the existing topic
and symptom index with its preconditions, observed output and a counterexample.
Add a diagnostic regression if a deterministic rule changes. Do not append a new
workflow manual or convert an unresolved hypothesis into a proven fix.
