typedef unsigned short u16;
typedef unsigned int u32;
extern u32 CompilerUnsignedRemainder(u32 value,u32 multiple);
__asm__(".global CompilerUnsignedRemainder\n.thumb_set CompilerUnsignedRemainder,0x08142b29");
u32 RoundUpU16ToMultiple(u16 value,u16 multiple)
{
 u32 remainder=(u16)CompilerUnsignedRemainder(value,multiple);
 u32 result;
 if (remainder) result=(u16)(value+multiple-remainder);
 else result=value;
 return result;
}
