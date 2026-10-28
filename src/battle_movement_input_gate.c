typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

enum {
    MOVEMENT_TICK_LAST_VALUE = 40,
    DIRECTION_BUTTON_MASK = 0x00f0,
};

struct BattleMovementInputState {
    u8 unknown_00_to_03[4];
    u8 mode; /* Observed controller states 0, 3, and 4 select distinct paths. */
    u8 unknown_05_to_06[2];
    u8 tick; /* Advances through 40, then wraps; mode 0 skips the update. */
};

extern volatile u8 gSceneRuntimeBase[];
extern void HandleMovementModeThree(struct BattleMovementInputState *state);
extern void UpdateBattleMovementGrid(struct BattleMovementInputState *state);

/* Mode 0 is inactive. Mode 3 delegates to its own handler; other active modes
 * except 4 accept directional input and delegate grid updates. Each active
 * frame advances the observed byte timer. Broader mode meanings remain
 * tentative until the adjacent battle state machine is recovered. */
void UpdateBattleMovementInputGate(struct BattleMovementInputState *state)
{
    register u32 runtime_base __asm__("r0");
    register u16 direction_buttons __asm__("r1");

    if (state->mode != 0) {
        if (state->mode == 3) {
            HandleMovementModeThree(state);
        } else if (state->mode != 4) {
            /* Retail reads the direction halfword from runtime base + 0x14. */
            runtime_base = (u32)gSceneRuntimeBase;
            __asm__ volatile ("ldrh %1, [%0, #20]"
                              : "+r"(runtime_base), "=r"(direction_buttons)
                              :
                              : "memory");
            if ((direction_buttons & DIRECTION_BUTTON_MASK) != 0) {
                state->mode = 1;
                UpdateBattleMovementGrid(state);
            }
        }

        if (state->tick > MOVEMENT_TICK_LAST_VALUE)
            state->tick = 0;
        else
            ++state->tick;
    }
}

/* Retail leaves a zero halfword in this alignment slot. */
__asm__(".hword 0");
