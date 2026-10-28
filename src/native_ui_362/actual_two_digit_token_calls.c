typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 NativeUnsignedQuotient(u32,u32) asm("RetailCall_08142ab0");
extern u32 NativeUnsignedRemainder(u32,u32) asm("RetailCall_08142b28");
extern void ClearNativeDigitCells(void *,u16) asm("RetailCall_08013a88");
extern void DrawNativeDecimalTokens(void *,void *,u32,u32,u32) asm("RetailCall_0802979c");
void DrawNativeTwoDigitValue(void *,u8 *,u32) asm("CoreClosure31_0005862C");
void DrawNativeTwoDigitValue(void *context,u8 *output,u32 number_input)
{
    u32 number = (u8)number_input;
    u32 quotient = (u8)NativeUnsignedQuotient(number,10);
    u32 remainder;
    if (quotient != 0) {
        DrawNativeDecimalTokens(context,output,quotient,1,0);
    } else {
        ClearNativeDigitCells(output,2);
    }
    output += 64;
    remainder = (u8)NativeUnsignedRemainder(number,10);
    DrawNativeDecimalTokens(context,output,remainder,1,0);
}
__asm__(".global RetailCall_08142ab0\n.thumb_set RetailCall_08142ab0,0x08142ab1\n"
        ".global RetailCall_08142b28\n.thumb_set RetailCall_08142b28,0x08142b29\n"
        ".global RetailCall_08013a88\n.thumb_set RetailCall_08013a88,0x08013a89\n"
        ".global RetailCall_0802979c\n.thumb_set RetailCall_0802979c,0x0802979d\n");
