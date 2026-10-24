# Pending predicate: shared return is structural, not a whole-match guarantee

- Native `DD650` loads the pending child once, guards null, calls the retained poller and normalizes LOW8 with an unsigned NEG/OR/LSR graph. Its full boundary is32 instruction bytes.
- An early C return moved the zero arm before the poll. Explicit positive/zero definitions of one returned value restored the native branch topology, but still yielded only12/32 same-offset bytes.
- A source-backed full-register alias plus an explicit LOW8 snapshot produced the identical binary. Close that spelling class; the alias rule from EDS `ai_picks.c` did not repair this method's value allocation.
- The remaining native MOV retains the narrowed value in R1 while the result is formed in R0. The candidate destructively narrows R0 and uses R1 for the negative, losing that MOV and adding terminal alignment. Do not mistake the later shifted bytes for separate defects.
- Three source causes consumed3.294133s in local comparisons and473.764964s from qualification to freeze, including unrelated integration/orchestration. The best whole-native ratio stayed below70%; exact ASM remains selected, with zero new C or runtime credit. No fourth permutation or option change is authorized by this note.
- Frozen terminal decision SHA-256:`cbe504f96f358a426ba3f22d2d1e56f1b7c30408ca74d03a46d9e836e802043b`.
