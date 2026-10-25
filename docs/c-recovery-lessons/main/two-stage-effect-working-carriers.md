# Two-stage effect working carriers: bounded successful transfer

- Original `131694` normalizes the signed16 helper return in R0 before copying it, then performs two copied, destructive modulo32 products and arithmetic shifts.
- Pinned `vendor/agbcc/gcc/thumb.md` lines393–408 and652–665 explain extension destinations and the internal MOV+MUL versus matched destructive MUL alternatives.
- Three separately initialized stage-local R0 values, each with one truthful instruction-free read/write operand, reproduce the entire112B:96instruction,12literal,4alignment bytes under fixedO2/interwork.
- Native local5290 and independent peer5291 bind the whole binary `7a9092df19403657f1f01dba3412424bb0adae9da0af5b8773c368e2a35c0ca8`; original3causes/3starts remain charged.
- Consume or preserve all live inputs before writing a fixed home. The `130200` fifth-argument failure is a counterexample to assuming an ordinary prebinding copy makes an overlapping home safe.
- Preserve full versus narrow return ABI: the `1312EC` u8 read/write carrier added real LSL24/LSR24 instructions and overflowed34/30B; it remains closed.
- A generic remainder barrier stayed108B/39same; a separate `12D398` sum barrier restored ADD50-before-SUB yet remained25/140same. These are negative transfers, not reasons to repeat equivalent spellings.
- This is a source/MD/whole-output-backed contextual recipe, not a lexical checker rule or permission to annotate arbitrary arithmetic. No inline instruction, flag change, new semantic discovery or natural-path proof is claimed.
