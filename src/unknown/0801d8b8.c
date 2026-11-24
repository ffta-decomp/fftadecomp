typedef unsigned char u8;
typedef unsigned int u32;
struct SharedPhaseState {
    u8 unknown_0000[552];
    u8 condition;
    u8 selector;
};
extern struct SharedPhaseState gSharedPhaseState;
asm(".global gSharedPhaseState\n.set gSharedPhaseState,0x02007f40");
u32 IsSharedStateSelectorThree(void)
{
    register const u8 *state_bytes asm("r1") = (const u8 *)&gSharedPhaseState;
    register u32 condition_offset asm("r2") = 552;
    register u32 selector_offset asm("r2");
    register const u8 *read_address asm("r0");
    /* The original keeps base, independent offsets and read addresses separate. */
    asm("" : "+r" (state_bytes), "+r" (condition_offset));
    read_address = state_bytes + condition_offset;
    asm("" : "+r" (read_address));
    if (*read_address != 0) {
        selector_offset = 553;
        asm("" : "+r" (selector_offset));
        read_address = state_bytes + selector_offset;
        asm("" : "+r" (read_address));
        if (*read_address == 3)
            return 1;
    }
    return 0;
}
