# Menu exit callback: follow registration through consumption

- Original `4F938` is a full 16-byte callback, not an entry inferred from an odd literal alone. Selected `50DE8` configures its embedded panel, hides the cursor and passes the callback plus full context to the existing slot registrar.
- The original slot dispatcher loads that saved context into R0, invokes the function and clears the callback slot only for a nonzero LOW16 result. This closes the relevant one-argument ABI without interpreting unspecified callback registers.
- The callback adds28 to the context as an embedded panel address, calls the retained exact-ASM updater and zero-extends only its LOW8 result. It neither dereferences a pointer at28 nor returns an unconstrained full helper result.
- The first normal fixed-O2 source reproduces16/16 instruction bytes, with no literals, alignment, constraints, instruction islands, flag changes or helper-body migration. Register declarations and wrappers do not count as recovery of the updater body.
- This is a bounded literal-to-registration-to-consumer transfer. Apply it only with the actual load/store/call path and complete native boundary; a ROM address match alone proves neither callback ownership nor ABI.
- Local compilation took1.105155s. Qualification-to-freeze was194.109836s, including unrelated delivery/accounting work. No new runtime or natural-menu coverage is claimed; independent peer/production remain separate gates.
- Frozen whole-native proof SHA-256:`1c082e70175a20b9701db9f7ec4e5c5ac8da86f96fd545f0bcbd181340adacaf`.
