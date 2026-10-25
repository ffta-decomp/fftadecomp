# Optional GBA first-draft aid: m2c

For an already owned, source-contract-ready method with nontrivial branches or
stack objects, use the existing `vendor/m2c` GBA target once before manually
reconstructing every expression. Tiny wrappers usually need no decompiler.
From the private project root, put output in the current owned evidence directory:

```sh
python3 vendor/m2c/m2c.py --no-cache -t gba-gcc-c \
  --globals none --stack-structs -f "$function_name" "$original_asm" \
  > "$owned_dir/m2c-draft.c" 2> "$owned_dir/m2c-draft.stderr"
```

Supply proven, parseable declarations with `--context "$context_file"` when
available; unknown helper signatures remain unknown. The GBA target uses APCS,
including hidden struct-return pointers and stack arguments. It does not prove
nonstandard incoming-register contracts. Check inferred OUT widths and call
results against the original contract before using them.

Use the draft to check block edges, definitions and stack offsets. Preserve
original load/store order, widths and joins. If loop structuring hides the
original topology, `--gotos-only` is an optional diagnostic representation, not
a compiler option or permission to try another candidate. An M2C_ERROR or
unresolved input returns to original ASM diagnosis; do not repair guessed ABI
by blindly compiling the draft. Normal compilation remains fixed O2.

This adds no required report, gate, retry budget or old-method reopening. Record
tool time and a useful/incorrect inference in the existing stage/round/lesson.
Evaluate first-local whole-match yield and source-to-local wall time, including
corrections; fast draft generation alone is not a throughput improvement.

Primary references: [m2c usage](https://github.com/matt-kempster/m2c/blob/c632946b8cfbe8fce442b522dba92dfa72f1f317/README.md),
[agbcc argument fixture](https://github.com/matt-kempster/m2c/blob/c632946b8cfbe8fce442b522dba92dfa72f1f317/tests/end_to_end/arguments/agbcc-o2.s).
