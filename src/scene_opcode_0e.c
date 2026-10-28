typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Opcode 0x0e sets or clears BG0/BG1 enable bits in the IWRAM display
 * control shadow. The shadow is later copied to the hardware register. */
u32 SetBackgroundLayersFromCommand(void *scene_context, const u8 *command)
{
    volatile u16 *shadow;
    register u16 previous __asm__("r1");
    register u16 value __asm__("r0");

    (void)scene_context;
    /* Retail keeps the read value in r1 and the updated value in r0. */
    if (command[1] != 0) {
        shadow = (volatile u16 *)0x03000940;
        previous = *shadow;
        value = 0x0300;
        value |= previous;
    } else {
        shadow = (volatile u16 *)0x03000940;
        previous = *shadow;
        value = previous & 0xfcff;
    }
    *shadow = value;
    return 0x110;
}
