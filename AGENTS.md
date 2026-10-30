# Repository policy

Recover Final Fantasy Tactics Advance (USA) as readable native source. For
ASM-to-C reconstruction, matching, contribution validation and integration, use
the [repository-level skill](.agents/skills/ffta-decomp/SKILL.md). Its references
are loaded by task; do not require reading the whole documentation library.

## Technical invariants

- Authenticate the user-supplied 16 MiB US ROM with `tools/identify_rom.py`. Target
  SHA-256: `43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19`.
- Establish whole original boundaries, ABI, layouts and ordered effects. Preserve
  ARM/Thumb mode, widths, CFG, aliases and real definition/use lifetimes.
- Use the pinned normal agbcc profile, `-O2 -mthumb-interwork`. Do not search flags
  or hide implementations in raw bytes. Diagnostic similarity is not acceptance.
- Verify complete original-range bytes and captured source/build inputs. Keep
  pure C, mixed source, nonexact source and retained original code distinct.
- Integrate coherently using the [completed-source build](docs/build-completed-sources.md),
  write one image and verify the final file hash. No selected-module failure may
  fall back to reference bytes. Local proof and integrated proof are separate.
- Record new reusable knowledge in its existing skill topic, with preconditions
  and a counterexample; update the symptom index and diagnostic tests as needed.

## Contribution and publication

Follow [CONTRIBUTING.md](CONTRIBUTING.md), including entry-address claim issues
and the 24-hour progress-update policy. Check current source and overlapping
claims before work; dated catalogue rows are not an availability guarantee.

Use English code/prose. Preserve unrelated files and active work. Stage coherent
explicit paths. Publish only when authorized. Run relevant tests and
`git diff --check`; guide-only edits do not require a ROM build.

Keep ROMs, extracted ASM, story/dialogue text, translations, assets, saves, local
reports, credentials and machine-specific configuration outside tracked source.
Localization and mod builds must be explicit extensions, separate from original
US matching results. Preserve attribution and licenses for adopted source.

Keep source in Git, reuse safe build outputs, and remove consumed temporary
artifacts after validation. Preserve active/pending proof inputs and the user's
original data; do not clean other checkouts or unrelated processes.
