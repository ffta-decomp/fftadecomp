# FFTA Scene Editor

[Open the editor on GitHub Pages](https://ffta-decomp.github.io/fftadecomp/scene-editor/)

Edit scenes and dialogue for Final Fantasy Tactics Advance (USA) in a browser.
The editor reads a ROM selected on your device, saves declarative project JSON,
and exports a separate ROM. English and Simplified Chinese are available. The
site ships one offline-capable HTML file and needs no game inputs for its build.

## Current tools

- **Story and index** browse scene links, read dialogue in script order, and
  repair, duplicate, or add scene entries.
- **Cutscene** authors the opening cast, dialogue, movement, and facing.
  Goblin Patrol demonstrates the opening, encounter, victory, and continuation.
- **Dialogue and script** edit text or native tokens, add dialogue pages, and
  inspect or edit known scene instructions.
- **Changes and Agent data** review changes, save the project, and export
  a catalog, a diff, or an edited ROM.
- **Battle event** previews a draft and exposes retail-only diagnostics.
  Runtime unit spawning remains experimental.

## Input compatibility

| Input | Available tools |
| --- | --- |
| Verified 16 MiB US retail, game code `AFXE` | All tools |
| 16 MiB US data mod that passes the native engine and scene layout checks | Scene index, dialogue, and script editing |
| A ROM previously exported by this editor | Tools for its original input profile |
| Engine hacks, relocated scene archives, or other game revisions | Identification and compatibility report |

A project records the complete SHA-256 of its input. Reopening an exported
ROM reconstructs that same input in memory and verifies a byte-identical rebuild.
A compatible data mod retains its own bytes and identity. The editor's build
requires no pre-applied patch, original ROM file, private pack, or game assets.

## Develop

Use Node.js 22 or newer.

```sh
cd tools/scene-editor
npm test
npm run build
node tools/scene.mjs inspect /path/to/input.gba
FFTA_US_ROM=/path/to/retail.gba npm test
```

Open `dist/ffta-scene-editor.html` to use the offline build. The repository's
Pages workflow builds the same file at `_site/scene-editor/index.html`.

See [module integration](docs/modules.md), [Agent integration](docs/agent.md),
[project schema](schemas/project.schema.json), and
[battle diagnostics](docs/battle-events.md). Original software follows the
[repository tool license](../LICENSE).
