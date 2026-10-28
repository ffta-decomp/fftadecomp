/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u32 RetailCall_080c7ea4(const u8 *,u32);
extern u32 RetailCall_0812f704(const u8 *,u32);
extern u32 RetailCall_08002804(void);
extern s32 RetailCall_08142950(s32,s32);
asm(".global RetailCall_080c7ea4\n.thumb_set RetailCall_080c7ea4,0x080c7ea5\n.global RetailCall_0812f704\n.thumb_set RetailCall_0812f704,0x0812f705\n.global RetailCall_08002804\n.thumb_set RetailCall_08002804,0x08002805\n.global RetailCall_08142950\n.thumb_set RetailCall_08142950,0x08142951");

s32 CalculateRandomizedUnitValue(const u8 *unit)
{
    s16 base=RetailCall_080c7ea4(unit,22);
    s16 modifier=RetailCall_0812f704(unit,1);
    u32 random=RetailCall_08002804();
    s32 adjusted=(base+modifier)/16-5;
    s16 value=adjusted+RetailCall_08142950((s16)random,11);
    if (value<=0)
        value=1;
    return value;
}
