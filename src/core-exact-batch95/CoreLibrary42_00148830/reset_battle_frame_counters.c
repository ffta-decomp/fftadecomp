typedef unsigned char u8;
typedef unsigned int u32;
struct FrameCounterState {
    u8 unknown_000[448];
    u32 field_1c0;
    u32 field_1c4;
    u32 field_1c8;
    u32 field_1cc;
};

void ResetBattleFrameCounters(void) __asm__("CoreLibrary42_00148830");
void ResetBattleFrameCounters(void)
{
    register struct FrameCounterState *state __asm__("r3") =
        (struct FrameCounterState *)0x03005f30;
    register u32 *destination __asm__("r0");
    register u32 zero __asm__("r1");
    register u32 *sentinel_address __asm__("r2");
    register u32 sentinel __asm__("r0");
    /* Native writes four words in this order, retaining one zero value. */
    __asm__("" : "+r"(state));
    destination = &state->field_1cc;
    __asm__("" : "+r"(destination));
    zero = 0;
    __asm__("" : "+r"(zero));
    *destination = zero;
    destination = &state->field_1c0;
    __asm__("" : "+r"(destination));
    *destination = zero;
    sentinel_address = &state->field_1c8;
    __asm__("" : "+r"(sentinel_address));
    sentinel = 65535;
    __asm__("" : "+r"(sentinel) : "r"(sentinel_address));
    *sentinel_address = sentinel;
    destination = &state->field_1c4;
    __asm__("" : "+r"(destination));
    *destination = zero;
}
