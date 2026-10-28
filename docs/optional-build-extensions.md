# Optional build extensions

`tools/build_rom.py --extension-config /external/extension.json` explicitly
selects an optional source/resource extension. The normal command without this
argument retains its original build and acceptance behavior. Localization rules,
game resources and optional feature implementations stay in the consuming
project; they are not installed into this toolkit or a vendored dependency.

The published-source entry point `tools/build_completed.py` accepts the same
`--extension-config` and external `--build-dir` options. Its ordinary complete
source/index/reference checks run first; optional changes are applied only
after the published baseline has rebuilt exactly.

The manifest uses `schema: "build-extension-v1"`, the complete authenticated
`reference_sha256`, and a nonempty `sources` list of `{path, sha256}` pins.
Paths are relative to the manifest directory or explicitly absolute. Every
selected file is checked before an extension source compiler is invoked.

`source_replacements` selects complete, enabled C/mixed/ASM modules by their
existing `module` name. Each record supplies a pinned `source`, the complete
original envelope's `reference_sha256`, and an optional `fill_byte` (default 0).
The original compiler profile, module address, envelope and declared function
entries remain in force. A shorter generated body is padded explicitly;
overflow, duplicate modules, disabled/non-source modules, shifted function
entries, and overlapping replacement ranges fail. The upstream files remain
untouched: the external source path is selected only for this build.

`fragments` supplies locally built code or encoded resources with `path`,
`sha256`, `rom_offset`, the original range's `reference_sha256`, and an explicit
`kind` of `code`, `resource`, or `data`. Ranges must fit the existing image.
Identical resource overlaps are allowed; conflicting fragments and overlaps
with source replacement envelopes fail. This is a build interface, not a
whole-ROM binary-diff import or an automatic resource discovery mechanism.
The consuming project owns source-to-fragment provenance and semantic tests.

Extensions run in the same build before the requested output is published.
The report marks the result `build_mode: "optional-extension"` and
`recovery_credit_eligible: false`, and nests the unchanged original build report
under `baseline_build`. The extended image has its own actual output hash.
Baseline recovery counts must never be applied to the changed output as new
matching credit. Optional features require their own runtime acceptance.

Keep extension manifests, compiled fragments, ROMs and resource packs external.
Submit needed generic interface changes upstream rather than patching vendor.

`--project-root` explicitly selects a separate, read-only implementation checkout;
the toolkit's own directory remains the default. `--build-dir` selects an external
directory for compiler binaries, generated headers, caches and intermediate files.
These options let consumers keep vendored sources unchanged. Source archives may
retain a dependency's 40-character upstream commit in `SOURCE_REVISION`; a normal
Git checkout continues to report its actual revision. Source hashes and actual
compiler binary fingerprints remain separate from this provenance label.
