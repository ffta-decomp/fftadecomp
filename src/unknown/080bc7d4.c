typedef unsigned char u8;
typedef unsigned int u32;

extern void RetailCall_080bacf0(void *context, u32 argument0, u32 argument1,
    u32 argument2, u8 argument3) __asm__("0x080bacf0");

void CoreFrontier_000BC7D4(u32 argument0, u32 argument1, u32 argument2,
    u32 argument3) {
    u8 narrowed_argument3 = (u8)argument3;
    RetailCall_080bacf0((void *)0x020100c8, argument0, argument1, argument2,
        narrowed_argument3);
}
