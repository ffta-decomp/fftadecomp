# Verified upstream adoption — 2026-10-30

Compared [shubshub/fftadecomp main](https://github.com/shubshub/fftadecomp/tree/823b3f46b1038a95772e1e00897dcd0a7052a444) with [PR #20](https://github.com/shubshub/fftadecomp/pull/20), pinned at `43f7f78cfe893ab4d99d2004e0740459589bfb5c`.

| Original function coverage | Functions | Original bytes |
| --- | ---: | ---: |
| Upstream main | 2,630 | 272,826 |
| Upstream PR #20 | 2,722 | 285,742 |
| PR-only addition over main | 92 | 12,916 |
| Newly validated and adopted here | 62 | 9,788 |

Of the new imports, 17 are already on upstream main and 45 are from the unmerged PR. Against our previously published 520,056 original bytes, the address-union overlap with the PR is 275,950 bytes; 244,106 bytes are unique to our source coverage and 9,792 bytes are unique to upstream. Module counts and upstream function counts have different granularity.

All 62 imports were freshly compiled with the pinned local agbcc at fixed `-O2 -mthumb-interwork`, linked at the original addresses, checked for full ELF function size and linked entries, and compared byte-for-byte against the US retail reference. Exact functions already present were retained. The `0x080CD7F0` envelope overlaps an existing whole exact combined C module and a four-byte companion; that package remains unchanged. The remaining four upstream-only bytes are not counted as imported C.

Three older nonexact C selections at `0x08038820`, `0x0809D2F8`, and `0x080A82C0` are replaced with full exact C. Their original complete sizes are 56, 176, and 208 bytes. The existing production image changes at 247 byte positions, all inside those three envelopes; all other production bytes remain identical. The private transitional production image still includes other nonexact code and is not identical to retail. The completed-only public build has its own retail hash verification.

Source headers retain repository, original path, full commit and source hash. The machine-readable [adoption manifest](../data/upstream-imports-20261030.json) records each function and its prior selection. Existing contributor notices are preserved; no additional license grant is inferred. Upstream report source hashes were stale for these candidates, so only immutable Git blobs and the fresh local native/ELF proofs establish acceptance.

This adoption adds no independently authored recovery or native-ledger credit, and preserves the interrupted workers' IDs, histories, budgets and clocks. No story text, game assets or ROMs are included.
