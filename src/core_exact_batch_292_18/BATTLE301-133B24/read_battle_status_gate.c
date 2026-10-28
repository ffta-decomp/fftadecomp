typedef unsigned char u8;
extern const u8 gBattleStatusGateBits[];
extern unsigned int ReadPackedStatusBit(const u8 *bits, int index, u8 mode);
asm(".global gBattleStatusGateBits\n.set gBattleStatusGateBits,0x08527e1c\n.global ReadPackedStatusBit\n.thumb_set ReadPackedStatusBit,0x08131da5");
unsigned int CoreFrontier_00133B24(unsigned int unused, int index, u8 mode)
{
    return (u8)ReadPackedStatusBit(gBattleStatusGateBits, index, mode);
}
