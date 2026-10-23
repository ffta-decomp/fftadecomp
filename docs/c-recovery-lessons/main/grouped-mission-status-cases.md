> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Restore grouped status cases before changing comparison constants

`SceneRegisteredRoot_0005D534` is a complete 592-byte mission-menu policy
controller. Its original outer dispatch has 13 slots; the 52-byte table is part
of the 168 literal/table bytes, not an additional byte category. The envelope
also contains 412 instruction bytes and 12 alignment bytes.

The first C body preserved the outer table, the case-1/2 shared wait join,
helper-side root reloads, low-halfword waits and signed-halfword selected
index. It matched 590/592 bytes. The sole residual was `CMP 1; BGE` in retail
versus `CMP 0; BGT` generated from an ordinary `choice >= 1` condition.

The original status branches select two discrete groups: cases 1/2 initialize
mode 3; cases 3/4 read the signed selected index after beginning the operation.
Representing those groups with a nested switch restored the original comparison
tree and all 592 bytes. No constant permutation, compiler option, interface or
business-effect change was needed. This is a structural discriminator even
when two predicates are mathematically equivalent.

The initial build also recorded an avoidable metadata rejection: opting into
the dead-switch-pointer policy when this compiler output had no `.rodata`
object. Removing that unnecessary opt-in preserved the strict guard. A switch
alone is insufficient evidence for a compiler-data exception; inspect the
actual retained output rather than preemptively enabling one.

This transfer applies to observed discrete result groups. It does not justify
turning arbitrary numeric thresholds into switches or collapsing repeated
helper calls. Complete local equality, independent mechanical provenance and
production integration are still distinct gates.
