typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef unsigned int u32;
extern u32 ClampMenuRelativeRow(void*,s8); extern u32 UnsignedRemainder(u32,u32);
asm(".global ClampMenuRelativeRow\n.thumb_set ClampMenuRelativeRow,0x08037F0D\n.global UnsignedRemainder\n.thumb_set UnsignedRemainder,0x08142951");
u32 CoreRegion_00037F40(void *object,s8 relative,u16 stride) { u32 doubled_stride; u32 row=(u16)ClampMenuRelativeRow(object,relative); row=(u16)UnsignedRemainder(row,((u8*)object)[23]);
 /* Original completes LOW16 remainder before shifting the independent stride. */
 asm("" : "+r"(row));
 doubled_stride=(u32)stride*2;
 /* Original doubles the independent U16 input into a full-width working value. */
 asm("" : "+r"(doubled_stride)); return (u16)(row*doubled_stride+*(u16*)((u8*)object+28)); }
