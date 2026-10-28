# Recovered game sources

This directory publishes completed C recovery from the US AFXE game. `completed-index.json` records each module's original ROM entry and complete span, source hash, and `c` or `mixed` classification. Internal literal pools and alignment belong to the original span; C source file length is not progress.

The original publication contains committed production source files with completed whole-module coverage. Additional upstream imports are admitted only after fresh whole-function and complete public-build verification, and carry explicit provenance. Files shared with unfinished selected modules are excluded. Nonmatching candidates and external projects' unvalidated code are not included. Necessary headers retain their relative paths under `src/` and `include/`.

`mixed` modules retain explicitly constrained assembly; they are not pure C. Fixed-register declarations and instruction-free constraints may appear in C to preserve the original compiler allocation. Names whose semantics are not established remain provisional.

This is a readable source snapshot with a [verified private-ROM build](../docs/build-completed-sources.md), **not a complete source-only ROM reconstruction**. Original resources, private validation artifacts, ROM images, toolchain binaries and unfinished dependencies are not distributed. The sources target the project's pinned agbcc configuration, not a modern host compiler. Publication and build validation do not invent native-ledger receipts; imported implementation bytes are identified separately in [the provenance index](../data/upstream-imports.json).

Use the contributor workflow in [CONTRIBUTING.md](../CONTRIBUTING.md) before claiming a remaining function. Existing project and upstream notices continue to apply; see [upstream references](../docs/upstream.md).
