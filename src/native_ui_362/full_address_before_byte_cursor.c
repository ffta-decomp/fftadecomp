typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef char GbaAddressWidth[(sizeof(u32)==sizeof(u8 *))?1:-1];
extern u32 UnsignedDivide(u32,u32) asm("RetailCall_08142AB0");
extern u32 UnsignedRemainder(u32,u32) asm("RetailCall_08142B28");
void FormatNativeTwoCodeUnits(u32,u16) asm("CoreRegion_00035CAC");
void FormatNativeTwoCodeUnits(u32 output_address,u16 value)
{
    u16 base=0x8118;
    u16 code;
    u8 *output=(u8 *)output_address;
    if (value>9) code=UnsignedDivide(value,10)+base;
    else code=base;
    *output++=code>>8;
    *output++=code;
    code=UnsignedRemainder(value,10);
    code+=base;
    *output++=code>>8;
    *output++=code;
    *output=0;
}
__asm__(".global RetailCall_08142AB0\n.thumb_set RetailCall_08142AB0,0x08142AB1\n"
        ".global RetailCall_08142B28\n.thumb_set RetailCall_08142B28,0x08142B29");
