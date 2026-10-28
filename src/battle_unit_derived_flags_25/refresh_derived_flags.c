#include "derived_flags.h"
/* Refresh observed bits in source order, with original callback reloads. */
void CoreConsumer_00098130(struct DerivedFlagNode *node)
{
    u32 first_value;
    u32 second_value;
    u32 final_flags;
    if (HasE8Bit7(node->unit)) node->flags |= 0x2000;
    else node->flags &= ~0x2000u;
    if (HasE9Bit3(node->unit)) node->flags |= 0x1000;
    else node->flags &= ~0x1000u;
    if (HasE9Bit1(node->unit)) node->flags |= 0x4000;
    else node->flags &= ~0x4000u;
    if (HasE9Bit0(node->unit)) node->flags |= 0x20;
    else node->flags &= ~0x20u;
    first_value = ReadUnitField(node->unit,19);
    second_value = ReadUnitField(node->unit,20);
    if (first_value <= (second_value >> 2) || HasE9Bit7(node->unit)) node->flags |= 0x8;
    else node->flags &= ~0x8u;
    if (HasEABit2(node->unit)) node->flags |= 0x400;
    else node->flags &= ~0x400u;
    if (HasE9Bit4(node->unit)) node->flags |= 0x20000;
    else node->flags &= ~0x20000u;
    if (*(const u16 *)(node->unit + 24) == 0) node->flags |= 0x10;
    else node->flags &= ~0x10u;
    if (HasE8Bit6(node->unit)) {
        node->flags |= 0x40;
        /* Replace the earlier bit3 result only on this branch. */
        if (HasEDBit4(node->unit)) node->flags |= 0x8;
        else node->flags &= ~0x8u;
    } else node->flags &= ~0x40u;
    if (HasEABit7(node->unit) || HasEBBit2(node->unit)) node->flags |= 0x80;
    else node->flags &= ~0x80u;
    if (HasEABit5(node->unit)) node->flags |= 0x100;
    else node->flags &= ~0x100u;
    if (HasEABit6(node->unit)) node->flags |= 0x200;
    else node->flags &= ~0x200u;
    if (HasE9Bit6(node->unit) || HasE9Bit5(node->unit) || HasECBit1(node->unit)) node->flags |= 0x800;
    else node->flags &= ~0x800u;
    RetailCall_0809801c(node);
    /* Later writes override earlier status choices. */
    if (node->flags & 0x2000) node->status = 14;
    final_flags = node->flags;
    if (final_flags & 0x1000) node->status = 5;
    if (final_flags & 0x40) node->status = 15;
}
