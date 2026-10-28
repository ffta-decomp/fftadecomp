typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ManagedWidget {
    u8 unknown_00[8];
    u16 x;
    u16 y;
    u16 unknown_0c;
    u16 height;
    u8 flags;
};
struct SelectionWorkspace {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05;
    u8 saved_primary_mode;
    u8 unknown_07;
    u16 choice;
    u8 saved_input_mode;
    u8 unknown_0b[29];
    void *text_buffer;
};
struct BattleModeRecord;
extern void RestoreManagedBattleRecordMode(struct BattleModeRecord *, u8);
extern void BuildManagedSelectionText(void *, u16, void *, void *);
/* Hook addresses are forwarded/stored here; their invocation ABI is opaque. */
extern void RegisterManagedSelectionHooks(u32, u32);
extern void RestoreManagedWidgetMode(struct ManagedWidget *, u8);
extern void WriteManagedEffectByte(u8);
#define CURRENT_SELECTION (*(struct SelectionWorkspace **)0x0200f438)

void PrepareManagedSelectionTransition(void *state)
{
    struct ManagedWidget *primary;
    struct ManagedWidget *secondary;
    struct SelectionWorkspace *current;
    struct SelectionWorkspace *before_mode_reset;
    u8 *input_state;
    void *buffer;
    int mode;

    primary = (struct ManagedWidget *)((u32)state + 88);
    secondary = (struct ManagedWidget *)((u32)state + 108);
    before_mode_reset = CURRENT_SELECTION;
    input_state = (u8 *)0x0200f390;
    before_mode_reset->saved_input_mode = input_state[32];
    RestoreManagedBattleRecordMode((struct BattleModeRecord *)(input_state + 28), 0);
    current = CURRENT_SELECTION;
    buffer = (void *)0x02003cb0;
    current->text_buffer = buffer;
    BuildManagedSelectionText(buffer, current->choice, (void *)0x030008b0,
                              (void *)0x03000990);
    mode = CURRENT_SELECTION->mode;
    switch (mode) {
    case 3:
        RegisterManagedSelectionHooks(0x08028bbd, 0x08028bdd);
        break;
    case 13:
    case 14:
    case 15:
        RegisterManagedSelectionHooks(0x08028c35, 0x08028c85);
        break;
    default:
        RegisterManagedSelectionHooks(0x08028b95, 0x08028ba9);
        break;
    }
    CURRENT_SELECTION->saved_primary_mode = primary->flags;
    if (primary->y + primary->height <= 64)
        RestoreManagedWidgetMode(primary, 0);
    else
        RestoreManagedWidgetMode(primary, 1);
    if (secondary != 0) {
        if (secondary->x <= 224 && secondary->y <= 64)
            secondary->flags &= 251;
        secondary->flags |= 64;
    }
    WriteManagedEffectByte(2);
}
asm(".thumb_set RestoreManagedBattleRecordMode, 0x08024abd\n"
    ".thumb_set BuildManagedSelectionText, 0x08019a8d\n"
    ".thumb_set RegisterManagedSelectionHooks, 0x08013405\n"
    ".thumb_set RestoreManagedWidgetMode, 0x08017d19\n"
    ".thumb_set WriteManagedEffectByte, 0x080a9479\n");
