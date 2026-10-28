typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

struct BattleChoiceWidget {
    void *callback;
    void *data;
    u16 x;
    u16 y;
    u16 counter;
    u16 unknown_0e;
    u8 flags;
    u8 selected_position;
    u8 phase;
    u8 unknown_13;
};
struct BattleChoicePayload {
    u8 unknown_000[88];
    struct BattleChoiceWidget widget;
    u8 unknown_06c[56];
};
struct BattleChoicePosition {
    u32 unknown_00;
    u16 x;
    u16 y;
};
struct BattleChoiceInput {
    u16 held;
    u16 pressed;
    u16 repeated;
    u8 unknown_06[10];
};
struct BattleChoiceResult {
    u16 selection_result;
};
extern struct BattleChoiceInput BattleChoiceInput;
extern struct BattleChoiceResult *BattleChoiceResult;
extern void ChoiceRequestDefinition(u32);
extern void ChoiceRouteDefinition(s32, s32);
extern void ChoiceResetInputRepeat(u8 *);

u32 PollBattleBinaryChoice(struct BattleChoicePayload *payload)
{
    struct BattleChoiceWidget *widget = &payload->widget;
    u32 pressed = BattleChoiceInput.pressed;
    u32 repeated = BattleChoiceInput.repeated;

    if ((pressed & 2) != 0) {
        ChoiceRouteDefinition(1, 105);
        BattleChoiceResult->selection_result = 0xffff;
        return 1;
    }
    if ((pressed & 1) != 0) {
        ChoiceRequestDefinition(100);
        BattleChoiceResult->selection_result = widget->selected_position + 1;
        return 1;
    }
    if ((repeated & 192) != 0) {
        struct BattleChoicePosition *position =
            (struct BattleChoicePosition *)((u8 *)payload + 128);
        u8 previous = widget->selected_position;
        u8 selected;
        ChoiceRequestDefinition(109);
        ChoiceResetInputRepeat((u8 *)&BattleChoiceInput);
        selected = previous ^ 1;
        widget->selected_position = selected;
        /* The native index sign-extends the stored byte before scaling by8. */
        position += (s8)selected;
        widget->x = position->x - 6;
        widget->y = position->y + 3;
    }
    return 0;
}

asm(".global BattleChoiceInput\n.set BattleChoiceInput, 0x03000000\n"
    ".global BattleChoiceResult\n.set BattleChoiceResult, 0x0200f438\n"
    ".global ChoiceRequestDefinition\n.thumb_set ChoiceRequestDefinition, 0x08141541\n"
    ".global ChoiceRouteDefinition\n.thumb_set ChoiceRouteDefinition, 0x08141571\n"
    ".global ChoiceResetInputRepeat\n.thumb_set ChoiceResetInputRepeat, 0x080023d1\n");
