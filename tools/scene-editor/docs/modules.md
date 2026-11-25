# Editor modules

The browser shell owns the ROM session, scene selection, language, project
history, and export. Panels register by stable ID in `src/app.mjs`, and
`src/ui/panels.mjs` validates registration. A panel owns its UI and sends
declarative edits through the shell. The cutscene and battle-event panels
show this pattern. Built-in panels can declare a required profile and an
optional scene to select when opened. The offline build follows static
relative imports under `src/`.

ROM identification and scene decoding live in `src/rom.mjs` and
`src/profile.mjs`. The browser, CLI, and Agent bridge share the planner
and exporter in `src/project.mjs`. Opening rules lower to native scene
and encounter resources in `src/opening.mjs`. Diagnostics are independent
of the normal exporter. Project keys and numeric native IDs provide the
stable interchange contract. Changes to their meaning require a format
migration.

Jobs, abilities, items, and formations are the next module boundaries for
AIO-style coverage. For each module, use the corresponding native readers
and writers from the decompilation to verify table boundaries, field widths,
and pointers. Add a resource-specific codec and validation before registering
its panel. Keep formation templates and save records separate. The AIO
editor is a functional reference. This project's routines, UI, and project
format are independently authored.

For a hack with different code or relocated resources, add a profile only
after verifying its engine and asset layout with a private fixture. Declare
which module operations the profile can use. Bind imported edits to the
input's full digest. Verify that a no-op export, the module's write ranges,
and reopening a modified export all preserve the hack's unrelated data.
