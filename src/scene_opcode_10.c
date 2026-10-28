typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 gContentState[];

/* Opcode 0x10 writes command bytes 1–2 as a halfword at content-state +0xa4. */
u32 SetSceneStateHalfwordFromCommand(void *scene_context, const u8 *command)
{
    register u8 *state_base __asm__("r3");
    u16 value;

    (void)scene_context;
    state_base = gContentState;
    /* Retail loads the state base before reading either command byte. */
    __asm__ volatile("" : "+r"(state_base));
    value = command[1] | (command[2] << 8);
    *(volatile u16 *)(state_base + 0xa4) = value;
    return 0x110;
}
