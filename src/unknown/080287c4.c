typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
u32 TaskConstructor45_000287C4(u8 *request)
{
    u8 *choices = *(u8 **)(request + 152);
    if (choices != 0) {
        register u32 address __asm__("r0") = (int)*(s16 *)*(u8 **)0x0200F438;
        /* The native signed index is the 32-bit address accumulator before base addition. */
        __asm__("" : "+r"(address));
        address += (u32)choices;
        if (*(u8 *)(address - 1) == 0)
            return 1;
    }
    return 0;
}
