# Verify contributions and imports

Read for external source submissions and upstream adoption. A reported match,
README percentage or an archive containing C does not prove reproducible recovery.

## Inventory before counting

List every file, C definition, exported entry, claimed original span, header,
symbol supplement and verification script. Multiple C variants for one original
entry are implementations of one function, not additional recovered functions.
Distinguish an existing nonexact C from missing C and an already exact selection
from new work. Check current source/index and original-range overlap.

Normalize archive separators safely, including backslash paths and Unicode names.
Reject absolute/traversal paths and escaping symlinks; inspect nested directories
before concluding source is absent. Do not publish submitted text tables or
extracted assets just because they arrived beside permitted original C.

## Reproduce from the actual files

Bind the contribution to a Git commit or archive digest, exact source/dependency
hashes and license notices. Verify that all claimed sources and verifier scripts
exist. Missing paths, undocumented compiler flavors or stale source/report hashes
leave a claim unverified. A wrapper hash is not automatically a child-report pin.

Compile unchanged submitted source under this repository's pinned profile first.
Record every variant's generated extent and complete original-range equality.
Do not summarize several variants as though only their unique entry count was
the number of files examined. Keep any later adaptation separate from the
unchanged baseline, with its own source-bound proof.

Check direct/indirect bindings, Thumb mode and data objects. An explicit
non-emitting symbol supplement may describe verified addresses where supported;
it must not contain instructions, includes or raw bytes. Do not graft a different
project's types, compiler assumptions or entire SDK into FFTA by analogy.

## Adoption and attribution

Adopt only source that passes local complete-range validation and the normal
coherent integration build. Nonexact source can inform a diagnosis but must not
be published as whole exact. Preserve upstream licensing and source notices;
original documentation licensing does not relicense imported code.

Record provenance in both source headers and the existing import metadata:
upstream repository, immutable commit, original path/symbol, target entry/span,
source hash, local adaptation, license and validation result. Update
`data/upstream-imports.json` / CSV according to the existing schema. Deduplicate
original ranges, and report attributed imports separately from independent work.
Do not inflate progress by counting variant files, repeated gates or overlap.

## Deliver a reviewable change

Submit source, required headers/bindings, selection/index updates and compact
hash/results through a PR. Keep ROMs, original extracted ASM, dialogue/text packs,
private paths, credentials and raw local reports out of it. The contribution
claim/24-hour activity policy is in `CONTRIBUTING.md`; this technical skill does
not replace that policy. Include failed/unsupported claims and their limits in
the review summary without presenting them as recovered bytes.
