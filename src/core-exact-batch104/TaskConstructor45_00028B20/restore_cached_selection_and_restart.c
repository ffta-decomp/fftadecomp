typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct TaskNode;
struct CachedSelection {
    u16 choice;
    u16 option;
};
struct ManagedSelectionCacheView {
    s16 result;
    u8 ready;
    u8 cache_active;
    u8 unknown_04[0x444 - 4];
    /* A variable-length observed view; the valid slot count is not established. */
    struct CachedSelection cached[0];
};
struct SelectionPayloadView {
    struct TaskNode *parent;
    u32 unknown_04;
    u8 cache_slot;
    u8 unknown_09[3];
    u8 control_prefix[70];
    u16 choice;
    u8 unknown_84[21];
    u8 option;
    u8 unknown_106[38];
    s16 expected_option;
    u8 next_mode;
    u8 unknown_147;
};
struct SelectionRestartGateView {
    u8 unknown[16];
    s16 expected_option;
    u8 next_mode;
};
struct SelectionCacheValuesView {
    u16 choice;
    u8 unknown[21];
    u8 option;
};
extern struct ManagedSelectionCacheView *gManagedSelection;
extern void SetSelectionControlMode_08017508(void *control, u32 mode);
extern void BeginManagedSelectionMode_080253B0(u8 mode, struct TaskNode *parent);
__asm__(".global gManagedSelection\n.set gManagedSelection,0x0200f438\n.global SetSelectionControlMode_08017508\n.thumb_set SetSelectionControlMode_08017508,0x08017509\n.global BeginManagedSelectionMode_080253B0\n.thumb_set BeginManagedSelectionMode_080253B0,0x080253b1");
typedef char cache_offset_check[(u32)&((struct ManagedSelectionCacheView *)0)->cached == 0x444 ? 1 : -1];
typedef char choice_offset_check[(u32)&((struct SelectionPayloadView *)0)->choice == 82 ? 1 : -1];
typedef char option_offset_check[(u32)&((struct SelectionPayloadView *)0)->option == 105 ? 1 : -1];
typedef char expected_offset_check[(u32)&((struct SelectionPayloadView *)0)->expected_option == 144 ? 1 : -1];
typedef char mode_offset_check[(u32)&((struct SelectionPayloadView *)0)->next_mode == 146 ? 1 : -1];
u32 RestoreCachedSelectionAndRestart(struct SelectionPayloadView *payload) __asm__("TaskConstructor45_00028B20");
u32 RestoreCachedSelectionAndRestart(struct SelectionPayloadView *payload)
{
    if (gManagedSelection->cache_active != 0) {
        struct CachedSelection *cached = &gManagedSelection->cached[payload->cache_slot];
        register struct SelectionRestartGateView *gate __asm__("r1") =
            (struct SelectionRestartGateView *)((u8 *)payload + 128);
        u16 next_option;
        /* The native cursor prepares the +128 gate before reading the cache. */
        __asm__("" : "+r"(gate));
        next_option = (u16)(cached->option + 1);
        if (gate->next_mode != 0 && gate->expected_option == next_option) {
            u32 selected_choice = cached->choice;
            u32 selected_option;
            struct SelectionCacheValuesView *values;
            register u8 *option_target __asm__("r1");
            /* Read the choice before moving the native address cursor. */
            __asm__("" : "+r"(selected_choice), "+r"(gate));
            values = (struct SelectionCacheValuesView *)((u8 *)gate - 46);
            values->choice = selected_choice;
            selected_option = cached->option;
            option_target = &values->option;
            /* Keep the real byte destination in R1 after the option read. */
            __asm__("" : "+r"(option_target) : "r"(selected_option));
            *option_target = selected_option;
            SetSelectionControlMode_08017508(payload->control_prefix, 16);
            BeginManagedSelectionMode_080253B0(payload->next_mode, payload->parent);
            return 1;
        }
        gManagedSelection->cache_active = 0;
    }
    return 0;
}
