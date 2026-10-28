typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleTransitionSavedState {
    u32 unknown00;
    void *owned_buffer;
    u8 unknown08[4];
    u8 transfer_request[28];
    u8 sequence_request[32];
    u8 saved_enable, saved_mask, saved_level, saved_fade;
    u8 unknown4c[72];
};
struct TransitionShadowBytes {
    u8 unknown00[74];
    volatile u8 enable, mask, level, fade;
};
struct TransitionBufferOwner { u8 unknown00[20]; u8 *buffer; };
extern struct TransitionShadowBytes SavedTransitionShadow;
extern struct TransitionBufferOwner SavedTransitionBuffers;
extern void (*const SavedTransitionClear)(void *, u32);
extern void (*const SavedTransitionCopy)(void *, const void *, u32);
extern const u8 TransitionPackedTiles[], TransitionMapRows[];
extern u8 TransitionPaletteDestination[];
extern void *AllocateSavedTransition(u32);
extern void DecodeSavedTransition(void *, const u8 *);
extern void QueueSavedTransitionCopy(void *, const void *, void *, u16);
extern void QueueSavedTransitionSequence(void *, const void *, void *, u16, u16, u16, u16);
extern const u8 *GetSavedTransitionPalette(u32);
typedef char saved_state_size[(sizeof(struct BattleTransitionSavedState) == 148) ? 1 : -1];

struct BattleTransitionSavedState *CreateBattleTransitionSavedState(void)
{
    struct BattleTransitionSavedState *state;
    state = AllocateSavedTransition(148);
    SavedTransitionClear(state, 148);
    state->owned_buffer = AllocateSavedTransition(1920);
    DecodeSavedTransition(state->owned_buffer, TransitionPackedTiles);
    QueueSavedTransitionCopy(state->transfer_request, state->owned_buffer,
                             (void *)0x06009c00, 960);
    QueueSavedTransitionSequence(state->sequence_request, TransitionMapRows,
                                 SavedTransitionBuffers.buffer + 652, 20, 3, 40, 64);
    {
        register struct TransitionShadowBytes *shadow asm("r4") = &SavedTransitionShadow;
        register u32 enable_offset asm("r0");
        register volatile u8 *first_address asm("r0");
        register volatile u8 *enable asm("r12");
        register u32 first_value asm("r1");
        register u8 *first_output asm("r0");
        register u32 zero asm("r3");
        register volatile u8 *mask asm("r5");
        register volatile u8 *level asm("r2");
        register volatile u8 *fade asm("r1");
        register u32 value asm("r0");
        register u8 *saved_cursor asm("r1");
        register u8 *fade_output asm("r4");
        register volatile u8 *enable_write asm("r4");
        /* Retain the observed address/cursor roles; every constrained operand
           is initialized from the real state, shadow object or loaded byte. */
        asm("" : "+r" (shadow));
        enable_offset = 74;
        asm("" : "+r" (enable_offset));
        first_address = (volatile u8 *)(enable_offset + (u32)shadow);
        asm("" : "+r" (first_address));
        enable = first_address;
        asm("" : "+r" (enable));
        first_value = *first_address;
        asm("" : "+r" (first_value));
        first_output = &state->saved_enable;
        asm("" : "+r" (first_output));
        zero = 0;
        asm("" : "+r" (zero));
        *first_output = first_value;
        mask = &shadow->mask;
        asm("" : "+r" (mask));
        value = *mask;
        asm("" : "+r" (value));
        saved_cursor = &state->saved_mask;
        asm("" : "+r" (saved_cursor));
        *saved_cursor = value;
        level = &shadow->level;
        asm("" : "+r" (level));
        value = *level;
        asm("" : "+r" (value));
        ++saved_cursor;
        asm("" : "+r" (saved_cursor));
        *saved_cursor = value;
        fade = &shadow->fade;
        asm("" : "+r" (fade));
        value = *fade;
        asm("" : "+r" (value));
        fade_output = &state->saved_fade;
        asm("" : "+r" (fade_output));
        *fade_output = value;
        enable_write = enable;
        asm("" : "+r" (enable_write));
        (void)*enable_write;
        *enable_write = 68;
        (void)*mask;
        *mask = 59;
        (void)*level;
        *level = zero;
        (void)*fade;
        *fade = 16;
    }
    {
        void (*const *copy)(void *, const void *, u32) = &SavedTransitionCopy;
        u8 *destination = TransitionPaletteDestination;
        const u8 *palette = GetSavedTransitionPalette(10);
        (*copy)(destination, palette, 32);
    }
    return state;
}
asm(".set SavedTransitionShadow,0x03000940\n"
    ".set SavedTransitionBuffers,0x030008b0\n"
    ".set SavedTransitionClear,0x0836d4b8\n"
    ".set SavedTransitionCopy,0x0836d4bc\n"
    ".set TransitionPackedTiles,0x083c2fe0\n"
    ".set TransitionMapRows,0x083c33dc\n"
    ".set TransitionPaletteDestination,0x03003920\n"
    ".thumb_set AllocateSavedTransition,0x08022841\n"
    ".thumb_set DecodeSavedTransition,0x0800543d\n"
    ".thumb_set QueueSavedTransitionCopy,0x08000a99\n"
    ".thumb_set QueueSavedTransitionSequence,0x08000bad\n"
    ".thumb_set GetSavedTransitionPalette,0x080cbabd\n"
    ".thumb_set _call_via_r2,0x0814224d\n"
    ".thumb_set _call_via_r3,0x08142251\n");
