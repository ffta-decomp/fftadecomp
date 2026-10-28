typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ManagedWidget {
    u8 unknown_00[16];
    u8 flags;
};
struct ManagedSelectionWorkspace {
    u8 unknown_00[6];
    u8 saved_primary_mode;
    u8 unknown_07[3];
    u8 saved_input_mode;
};
struct BattleModeRecord;
extern u32 PollManagedSelectionTransition(void);
extern void RestoreManagedBattleRecordMode(struct BattleModeRecord *, u8);
extern void RestoreManagedWidgetMode(struct ManagedWidget *, u8);
extern void RefreshManagedWidget(struct ManagedWidget *);
extern void WriteManagedEffectByte(u8);

u32 FinishManagedSelectionTransitionIfReady(void *state)
{
    struct ManagedWidget *primary;
    struct ManagedWidget *secondary;
    struct ManagedSelectionWorkspace **workspace;
    register struct BattleModeRecord *mode_record asm("r0");

    primary = (struct ManagedWidget *)((u32)state + 88);
    secondary = (struct ManagedWidget *)((u32)state + 108);
    if ((u16)PollManagedSelectionTransition() == 0)
        return 0;
    /* Retail materializes the first argument before the shared cell address. */
    mode_record = (struct BattleModeRecord *)0x0200f3ac;
    asm("" : "+r" (mode_record));
    workspace = (struct ManagedSelectionWorkspace **)0x0200f438;
    RestoreManagedBattleRecordMode(mode_record,
                                  (*workspace)->saved_input_mode);
    RestoreManagedWidgetMode(primary, (*workspace)->saved_primary_mode);
    if (secondary != 0) {
        secondary->flags &= 191;
        RefreshManagedWidget(secondary);
    }
    WriteManagedEffectByte(0);
    return 1;
}

asm(".thumb_set PollManagedSelectionTransition, 0x08011861\n"
    ".thumb_set RestoreManagedBattleRecordMode, 0x08024abd\n"
    ".thumb_set RestoreManagedWidgetMode, 0x08017d19\n"
    ".thumb_set RefreshManagedWidget, 0x08017e29\n"
    ".thumb_set WriteManagedEffectByte, 0x080a9479\n");
