# Recovered game sources

This directory publishes completed C recovery from the US AFXE game. `completed-index.json` records each module's original ROM entry and complete span, source hash, and `c` or `mixed` classification. Internal literal pools and alignment belong to the original span; C source file length is not progress.

Only committed production source files with completed whole-module coverage are included. Files shared with unfinished selected modules are excluded. Nonmatching candidates and external projects' unvalidated code are not included. Necessary headers retain their relative paths under `src/` and `include/`.

`mixed` modules retain explicitly constrained assembly; they are not pure C. Fixed-register declarations and instruction-free constraints may appear in C to preserve the original compiler allocation. Names whose semantics are not established remain provisional.

This is a readable source snapshot, **not a standalone or complete ROM build**. Original resources, private validation artifacts, ROM images, toolchain binaries and unfinished dependencies are not distributed. The sources target the project's pinned agbcc configuration, not a modern host compiler. Publication does not add new recovery credit.

Use the contributor workflow in [CONTRIBUTING.md](../CONTRIBUTING.md) before claiming a remaining function. Existing project and upstream notices continue to apply; see [upstream references](../docs/upstream.md).
