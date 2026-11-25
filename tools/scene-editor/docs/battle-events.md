# Snowball Battle event trial

The battle form saves a declarative event under `snowball.goblin`. The
current fixture previews a once-per-battle rule, an opponent with 3 HP
and 1 attack, a line of dialogue, and victory on that opponent's defeat.
The host preview exercises this rule as data. An unfinished event draft
blocks the complete-ROM export.

## Native experiments

- **Damage hook.** The editor's standalone listener probe is built for the
  pinned US ROM. It redirects the native HP update to a Thumb routine in
  expanded ROM space, filters to Snowball Battle, Mewt's unit record, the
  observed normal attack phase and a strict HP decrease, and executes a
  trace marker. It then performs the displaced store and resumes the native
  KO helper. The probe keeps no persistent state and makes no gameplay
  changes by design.
- **Victory target.** The native battle script for this encounter already
  checks whether the specified unit's HP is below 1 and queues the original
  post-battle scene. The second probe copies the nested script directory to
  expanded space and changes this selector to another existing unit in the
  encounter. This probe tests retargeting an existing unit.
- **Still open.** Binding a new Goblin to the real combatant pool, map
  occupancy and turn order, opening and closing its dialogue safely during
  battle, and latching the rule after its first use. The victory route also
  needs an activation guard while the new combatant is absent. The complete
  scenario has yet to run through settlement. A direct mGBA probe using
  a copy of an existing combatant registered a new actor at an empty tile
  with 3/3 HP and base attack 1, but emitted invalid memory reads and
  writes. That call sequence is excluded from the editor's ROM export.

## Evidence

Both hit paths were replayed in mGBA from a cold boot of the exact
browser-exported listener ROM. Ritz hit Mewt for 1 HP (8 → 7), reaching the
probe marker once. Ritz hit another unit for 1 HP (10 → 9), without
reaching it. The target's native state and the tested post-action screen
matched retail in the compared replay.

The separate original-outcome test used a normal attack from a controlled
1-HP setup. Retail queued the post-battle scene after Mewt reached 0 HP.
With the who-to-check selector changed, Mewt reached 0 HP and the encounter
continued. Using the same attack path against the replacement target,
with the replacement target pre-set to 1 HP for this test, queued the
post-battle scene. These tests establish the named effect of the selector.

From the editor directory, the diagnostic commands are:

```sh
node tools/scene.mjs battle-probe /path/to/FFTA_US.gba /outside/listener.gba
node tools/scene.mjs battle-probe /path/to/FFTA_US.gba /outside/victory.gba --victory
```

For source verification, assemble `runtime/snowball_hit_probe.s` as
ARM7TDMI Thumb and extract its `.text` section. Its 80 bytes have SHA-256
`ef160582e6ebdcfb372d3f7d458bd43a03e0a8767ac326b392b484e0b636e43b`.
The browser and CLI emit identical probe ROMs from matching local inputs.
