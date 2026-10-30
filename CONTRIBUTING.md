# Contributing

[Function catalogue](data/functions.csv) · [Decomp skill](.agents/skills/ffta-decomp/SKILL.md) · [Build completed source](docs/build-completed-sources.md)

## Claim a complete function

Check the current source index, catalogue and open issues for the same entry and
overlapping ranges. A selected ASM row can already have a completed contribution;
a module span is not proof of an independent function. Prefer game-specific logic
and its actual dependencies, preserving existing work and original identity.

Open a claim in [ffta-decomp/fftadecomp](https://github.com/ffta-decomp/fftadecomp/issues)
with the entry address in its title, for example
`[Claim] 0x080A23B8 — ResolveBattleTargets`. Include the native identity, complete
range, intended scope and current source status. An agent should ask its user
to publish the issue. Wait for collision/ownership confirmation before duplicating
an existing claim. Personal-repository mirrors do not reserve work.

Post a substantive progress update in the same issue at least every 24 hours:
what changed, current result or blocker, and next step. Reactions and automated
pings do not renew it. More than 24 hours without an update is considered
abandonment, allowing another contributor to claim the range. Link prior work
when reclaiming and check for a new owner before resuming an expired claim.
There is no implied automatic issue-closing service.

## Reconstruct and validate

Follow the repository skill for original ASM/ABI mapping, readable C, the fixed
compiler profile, displacement/register/argument diagnosis and full-range proof.
Keep failed causes and input hashes; a fit, partial match or behavior fixture
success is not whole exact. Clearly identify instruction-bearing mixed source.

Submit C and required headers/bindings, original entry/range, build configuration,
source/dependency/toolchain identities, complete-range result and a compact
transfer lesson with limits. Verify the final frozen inputs mechanically before
selection, then use one coherent final-image build. See the
[verification guide](.agents/skills/ffta-decomp/references/verification-and-integration.md).

For external source, follow the [import guide](.agents/skills/ffta-decomp/references/contribution-imports.md).
Preserve source notices and immutable upstream attribution. Multiple variants of
one entry and repeated validation do not add distinct recovered bytes.

## Public content

This repository contains completed recovered source, build tools and progress
metadata. Unrecovered code/resources come from the user's private reference ROM
in the transitional build. Do not upload ROMs, extracted ASM, dialogue/text packs,
assets, saves, local reports, private paths, credentials or account identifiers.
Only share source you have permission to publish. Third-party code retains its
license; original documentation/metadata and original tools have their stated
repository licenses.
