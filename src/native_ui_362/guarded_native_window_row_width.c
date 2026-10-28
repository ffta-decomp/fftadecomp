typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void ApplyNativeWindowRowValue(u8 *,int,u32,u32) asm("RetailCall_0801799C");
void ApplyNativeWindowRowWidth(u8 *,u32,u32) asm("IsolatedCore57_00017B1C");
void ApplyNativeWindowRowWidth(u8 *window, u32 input_row, u32 input_value)
{
    u8 row = input_row;
    u8 value = input_value;
    if (!(*(u16 *)(window + 16) & 1))
        ApplyNativeWindowRowValue(window, (s8)row, value, window[18]);
}
__asm__(".global RetailCall_0801799C\n.thumb_set RetailCall_0801799C,0x0801799D");
