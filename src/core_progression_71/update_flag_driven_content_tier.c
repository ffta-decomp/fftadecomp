/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
struct ProgressionSaveState {
    u8 unknown_0000[0x1f6a];
    u8 content_tier;
    u8 cycle_index;
    u8 unknown_1f6c[0x104f];
    u8 cycle_counter;
};
struct ProgressionRuntimeContext { u8 unknown_000[0x4dd]; u8 stage; };
extern struct ProgressionSaveState gSaveData;
extern u8 GetGameFlag(u16 flag);
extern s32 SignedModulo(s32 dividend, s32 divisor);
extern void RegenerateTierContent(void) __asm__("0x080cbf34");
#define LIVE_PROGRESSION_CONTEXT (*(struct ProgressionRuntimeContext **)0x03002810)

/* The numeric flag-to-tier ordering is proven; content names remain unknown. */
void UpdateFlagDrivenContentTier(void)
{
    u8 previous_tier = gSaveData.content_tier;
    u8 last_flag;
    if (GetGameFlag(529))
        LIVE_PROGRESSION_CONTEXT->stage = 3;
    else if (GetGameFlag(518))
        LIVE_PROGRESSION_CONTEXT->stage = 2;
    else
        LIVE_PROGRESSION_CONTEXT->stage = 1;

    if (GetGameFlag(54))
        gSaveData.content_tier = 6;
    else if (GetGameFlag(533))
        gSaveData.content_tier = 5;
    else if (GetGameFlag(529))
        gSaveData.content_tier = 4;
    else if (GetGameFlag(524))
        gSaveData.content_tier = 3;
    else if (GetGameFlag(521))
        gSaveData.content_tier = 2;
    else {
        last_flag = GetGameFlag(518);
        if (last_flag)
            gSaveData.content_tier = 1;
        else
            gSaveData.content_tier = last_flag;
    }
    gSaveData.cycle_index = SignedModulo(gSaveData.cycle_counter - 1, 20);
    if (previous_tier != gSaveData.content_tier)
        RegenerateTierContent();
}
