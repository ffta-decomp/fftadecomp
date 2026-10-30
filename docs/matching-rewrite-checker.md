# Source-form diagnostics

Use [check_matching_rewrites.py](../tools/check_matching_rewrites.py) with the
[diagnosis guide](../.agents/skills/ffta-decomp/references/mismatch-diagnosis.md).
It reports deterministic source/ASM hints and counterexamples without changing
source or compiling. Exit zero means scanning succeeded, not that a candidate
is ABI-correct, semantically equivalent or byte-identical.

```sh
python3 tools/check_matching_rewrites.py candidate.c --json
python3 tools/check_matching_rewrites.py --build-report "$BUILD_REPORT"
```

Keep reusable rules in the skill references and regression fixtures in tests.
