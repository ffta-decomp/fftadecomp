# Displacement-aware assembly diagnosis

Use the maintained [diagnosis guide](../.agents/skills/ffta-decomp/references/mismatch-diagnosis.md#displacement-registers-and-outgoing-arguments)
for optional asm-differ setup, retained-report commands, register/call setup
analysis, shifted blocks and the limits of alignment evidence.

The repository adapters are [asmdiff.py](../tools/asmdiff.py) and
[diagnose_module_build.py](../tools/diagnose_module_build.py). They do not compile
or modify a candidate/report and cannot replace whole-range byte validation.
