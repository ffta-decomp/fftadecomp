# Layout request: separate root snapshots across phases

- Original`13108` consumes three LOW8 selectors and one full payload. Its actual root cell is0200918C. Clear halfword58 bit80, store the packed ID and payload, call the existing layout lookup, then reload the root before storing its returned pointer at754.
- Each mode arm first edits byte43 on that post-lookup object, reloads the root for the second byte43 update, then reloads once for both halfword12 and byte11. Preserve the final pair's common object and both stores' order; flag meanings remain neutral.
- One function-wide request variable generated164B with39 same-offset bytes. It tied the pre-call object to all later reload quantities and merged the last byte store, adding address copies and rotating registers.
- Distinct pre-call, post-lookup and branch-local root values recover the observed lifetimes. Root-cell volatility expresses only the proven reload sites; the ordinary fields remain ordinary RAM. No extra load, broad memory barrier or global volatile conversion is added.
- The second fixedO2 source matches156/156:138 instruction,16 literal,2 alignment,20B frame. No initialized constraints, instruction ASM, trim, helper port or flag change.
- Applicable references are pinned EDS phase-local lifetime/allocation examples and the existing near-match decision card. This is an observed source-to-output transfer, not a traced compiler-pass explanation or permission to split a genuinely retained value.
- Two local commands total2.159246s; original qualification-to-freeze is254.238723s, including production closeout and source work. Independent peer, production and natural-domain evidence remain separate.
- Frozen proof SHA-256:`aeeafbb60c385059a649d2b7fefc0d9f95d1a4a5617db06252bb3dc1bd60c2c5`.
