# Menu extent: preserve the shared result joins

- Original `66ED8` configures a panel's mode record, cursor, row callbacks and selection continuation. Four embedded objects remain distinct; the signed record row is passed as signed16 at one call and unsigned8 at another.
- A persistent second byte-view owner initially spilled selection and generated432B. One actual panel owner and the observed byte flag access restored the36B frame and420B envelope. This is object/lifetime evidence, not a general alias-removal rule.
- The record's scaled index plus local table offset is defined before the root load. The buffer word is loaded before the count halfword. Restoring both orders improved326 to385 same-offset bytes while preserving the complete420B envelope.
- The remaining mismatch was a CFG/value-definition issue: duplicated source assignments let the compiler preload448 and subtract192 for256. Original mode4 full-word count+1 and other-mode count tests instead converge on separate256/448 result blocks.
- Explicit shared positive/zero result joins recovered420/420 bytes:376 instruction,40 literal,4 alignment. Keep the full addition; do not invent a wrapping u16 sentinel or omit the mathematically dead branch. No instruction ASM, initialized constraint, helper rewrite, trim or flag change.
- Reused references: the existing EDS source-evaluation/lifetime cases and project offset-before-root/phase-local snapshots. This is one proven source/CFG transfer, not a generic register-forcing prescription. The first three failures were reconciled before the supported fourth cause.
- Four local commands total4.300839s; original qualification-to-freeze1019.986035s includes source work and context recovery. Independent peer and production evidence remain separate; no natural row-domain claim.
- Frozen proof SHA-256:`050e52499b60d7d4527226bc90a56e31587c07d4653292eedbb0b9dc1b300a09`.
