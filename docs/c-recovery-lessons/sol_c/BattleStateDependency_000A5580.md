> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Battle result feedback: 1042 B pure C exact

Local_exact749; independent mechanical and production gates pending. Full original span includes842 instruction bytes,196 literal/table bytes and4 alignment bytes. Stable export is unchanged; descriptive alias ApplyBattleResultFeedback stays metadata. Enum interpretations remain tentative.

Original evidence: actor result records have44-byte stride, halfword flags/results and signed effect IDs; actor coordinates are signed16 with five fractional bits. The loop reloads the byte count. Callbacks require fresh actor and flags; category calls are deliberately repeated. Separate result branches share effect and cumulative sound tails.

Three source forms: first1044 generated/1001 equal, removing early actor snapshots1044/1026, explicit zero-first property branch1044/1042. Existing trailing two-byte section metadata yields strict1042/1042, without removing original instructions. Strict preflight passed. Claim-to-local decision174.891s includes preparation, all trials and metadata verification.

At the96% checkpoint the full original, C and generated assembly were inspected. An actor local evaluated before effect ID changed argument-load order; direct typed field arguments restored the original order. The final ternary placed the helper branch first and added a jump; zero-first if/else restored the original fallthrough. Compiler pass responsibility is untraced: these are measured final-output effects, not a pass attribution. No flags changed and no behavior bank reran.

Transfer only when original load order and branch placement support it. Actor snapshots needed across callbacks must remain; never mechanically remove all locals. The first draft already recovered all three switch tables using actual complete category cases. No speedup or gameplay coverage claim follows from one exact method.
