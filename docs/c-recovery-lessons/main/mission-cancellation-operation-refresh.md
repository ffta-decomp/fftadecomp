> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Mission cancellation and operation-list refresh: 204 B exact

The original entry clears the selection byte, conditionally clears participant
halfword 22 and resets the selected mission, then regenerates scene-specific
operations. The participant field meaning remains tentative; this is not reward
or assignment commit recovery.

Use the source-backed context view and distinguish the operation-array pointer
captured before the resolver/enumerator from the live context used to store the
returned count byte. Reload the context after reset and chooser creation. Keep
the selector result narrowing at its original low-byte observation, the six
runtime arguments, and the final array/count pair from one post-call root.

The first fixed `-O2 -mthumb-interwork` formulation reproduces all 204 original
bytes: 172 instruction bytes and 32 literal bytes, without instruction-bearing
inline assembly or helper migration. Native single-entry, section, provenance
and selection checks pass. No individual compiler pass was diagnosed and no new
runtime coverage is claimed. Whole-byte identity avoids duplicate behavior banks;
independent mechanical verification and production identity remain separate gates.

The observed claim-to-local-decision interval was 82.253221 seconds. Naming and
package closeout remain in the complete method clock. No failed formulation or
speedup claim. Transfer only where the original shows these same capture/reload
sites; do not apply blanket volatile or cached-root rules.
