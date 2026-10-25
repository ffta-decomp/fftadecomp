# Initialized accumulator and ordinary saved-unit lifetimes

- The 176-byte equipped-item property calculation keeps a two-halfword excluded-item OUT object. Property 10 seeds the accumulator from the initial item or unit default; other properties discard the exclusion count before scanning five equipment fields.
- Original definitions keep the zero-initialized accumulator alive across the excluded-item helper. A truthful initialized R6 read/write operand restores that observed phase while the ordinary unit pointer naturally occupies saved R7; no instruction-bearing assembly is emitted.
- Earlier initializer/declaration variants did not restore the full use graph. The separate 130-byte equipment example also proves that hard-binding R7 can omit its callee-save: never infer ABI validity from scattered matching bytes or transfer both bindings blindly.
- Local5327 and independent5328 prove the complete 176-byte span. All six causes and six compiler starts, including failed variants and original clock, remain charged. Production promotion adds no matching trial or old behavior-bank rerun.
- This is a bounded observed allocation transfer, not proof of original source spelling or a general register-ranking rule. A safe checker suggestion needs original definitions/uses, helper effects and generated save/use sets; a lexical byte-count hint cannot establish those obligations.
