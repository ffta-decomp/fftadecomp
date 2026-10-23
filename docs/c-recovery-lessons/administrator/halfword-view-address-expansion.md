> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Halfword views: diagnose address grouping before another cast

The inventory-selection method at0004E224 reached306/306 original bytes as pure C on its sixth and final source trial. Five earlier formulations remain frozen. Local exact gate936 is a new result; mechanical verification and production integration are separate. This note summarizes the frozen successful implementer's lesson and the pinned compiler source, not a new administrator acceptance.

## A discriminator for the four remaining bytes

The original mode5 loads a halfword from owner+0x424 with four-byte stride. Modes3/4/6 load full words from the same physical range, and mode8 reads a different halfword table with two-byte stride. The separately observed0x524 field bounds the overlapping slot region. Preserve the signed index and selection sentinel; no global runtime-domain claim follows from this layout.

The best earlier306-byte body had302 equal bytes. Its word-aligned union-member representation associated owner with the scaled index before adding0x424. Retail materialized owner+0x424 before the scaled index. An early base-pointer local changed tail sharing with mode8; indexed-address casts and scalar-word aliases repeated a failed binary. Those observations closed the spelling hypotheses; they did not justify another equivalent cast.

The successful form models the proven overlapping region as word and halfword arrays. Word modes index the word view; mode5 indexes the halfword view at twice the signed slot index. The physical address and load width remain unchanged. The dynamic halfword array reference exposes a different alignment fact during address expansion, without defining an early pointer or forcing a register. One candidate restored the predicted constant-before-index order and the complete original306-byte output.

## Compiler source explains the predicted distinction

Pinned agbcc revision: da598c1d918402c42c0c0d7128ba14567f3175e9. In vendor/agbcc/gcc/expr.c, get_inner_reference reduces inferred alignment using the current reference type after the accumulated offset becomes nonconstant (around4087). A halfword member inside a word-aligned object can retain different alignment information from a dynamic halfword array reference.

In expand_expr (around5490–5510), an address-expansion shortcut requires inferred alignment to equal the access mode's alignment, alongside conditions on block memory, bit size and bit position. It can materialize the constant component before adding the dynamic offset. The frozen implementation diagnosis connected this condition to the original halfword-versus-word address grouping, and the sole candidate produced the predicted bytes.

Evidence level is compiler-source-derived prediction plus observed whole output. No before/after RTL dump identified a measured first divergent pass. Do not turn the explanation into a claim that alignment alone guarantees the shortcut in every expression.

## Transfer conditions and stopping rules

Use this discriminator only when original source evidence establishes overlapping access widths, the physical extent, element stride and constant/index ordering. Inspect the type through which the dynamic offset enters the expression before changing casts or declaration order. Keep the actual helper/reload and shared-return boundaries.

Do not invent array capacity or dummy members, alter alignment attributes, add volatile, force registers, or widen a load to obtain the desired sequence. A single-width record, different stride, MMIO access or different callback lifetime needs its own source contract. This is one completed method, not an instruction to replace every union with arrays.

The original envelope comprises162 instruction bytes,140 literal/table bytes and4 internal alignment bytes. The ELF function is306 bytes; raw text is308 because of a separately verified two-byte postfunction NOP. No original instruction, literal, table or internal alignment was omitted.

The final actor took139.356 seconds from its claim to the exact decision and310.024 seconds through publication. The full original claim-to-publication clock is1448.123 seconds, including earlier failures and the handoff. These are measured costs, not evidence that a different model is generally faster. No compiler-profile change, extra runtime bank or full-ROM build was used for this closure.
