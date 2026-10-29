typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct InputSnapshot { u16 held, pressed, repeated; };
struct ChoiceState { void *owner; u16 flags, current; u8 mode, continuation; u16 choice; };
struct ChoiceView { u8 prefix[16]; u8 selected, count; };
extern struct InputSnapshot KeyState;
extern struct ChoiceView ChoiceView;
extern void RequestDefinitionRoute(int, int);
extern void RequestFixedDefinition(u32);
extern void ResetDialogTextState(void);
extern void RenderDialogRecord(u32, u32);
__asm__(".global KeyState\n.set KeyState,0x03000000\n"
        ".global ChoiceView\n.set ChoiceView,0x020020d0\n"
        ".global RequestDefinitionRoute\n.thumb_set RequestDefinitionRoute,0x08141571\n"
        ".global RequestFixedDefinition\n.thumb_set RequestFixedDefinition,0x08141541\n"
        ".global ResetDialogTextState\n.thumb_set ResetDialogTextState,0x08013365\n"
        ".global RenderDialogRecord\n.thumb_set RenderDialogRecord,0x08011b31");
u32 ProcessChoiceInput(struct ChoiceState *) __asm__("RemainingCore48_00066AD0");
u32 ProcessChoiceInput(struct ChoiceState *state)
{
    register u32 changed __asm__("r5") = 0;
    u32 pressed;
    register u32 decrement_snapshot __asm__("r2");
    u32 confirmed;
    __asm__("" : "+r"(changed));
    pressed = KeyState.pressed;
    decrement_snapshot = pressed;
    __asm__("" : "+r"(decrement_snapshot) : "r"(pressed));
    if (pressed & 2) {
        register u32 old_flags __asm__("r1");
        register u32 result_flags __asm__("r0");
        if (state->mode != 10)
            RequestDefinitionRoute(1, 105);
        ResetDialogTextState();
        state->continuation = changed;
        state->choice = 0xFFFF;
        if (state->mode == 10) {
            register u32 mode_mask __asm__("r2");
            old_flags = state->flags;
            __asm__("" : "+r"(old_flags));
            mode_mask = 256;
            __asm__("" : "+r"(mode_mask) : "r"(old_flags));
            result_flags = mode_mask;
        } else {
            old_flags = state->flags;
            result_flags = 64;
        }
        /* B preserves the old halfword while the mask is the OR destination. */
        __asm__("" : "+r"(result_flags) : "r"(old_flags));
        result_flags |= old_flags;
        __asm__("" : "+r"(result_flags));
        state->flags = result_flags;
        goto handled;
    }
    confirmed = pressed & 1;
    if (confirmed) {
        register u32 result_flags __asm__("r0");
        register u32 mode_mask __asm__("r1");
        if (state->mode != 10)
            RequestFixedDefinition(100);
        ResetDialogTextState();
        state->continuation = changed;
        /* This actual initialized R1 zero precedes the choice halfword write. */
        mode_mask = 0;
        __asm__ __volatile__("" : "+r"(mode_mask));
        state->choice = 0xFFFE;
        if (state->mode == 10) {
            register u32 wide_mask __asm__("r2");
            result_flags = state->flags;
            __asm__("" : "+r"(result_flags));
            wide_mask = 256;
            __asm__("" : "+r"(wide_mask) : "r"(result_flags));
            mode_mask = wide_mask;
        } else {
            result_flags = state->flags;
            mode_mask = 64;
        }
        /* A instead destructively updates the actual loaded flag halfword. */
        __asm__("" : "+r"(result_flags), "+r"(mode_mask));
        result_flags |= mode_mask;
        __asm__("" : "+r"(result_flags));
        state->flags = result_flags;
        goto handled;
    }
    if (pressed & 16) {
        u32 selected;
        changed = 1;
        selected = ChoiceView.selected;
        if ((int)selected < (int)ChoiceView.count - 1)
            ChoiceView.selected = selected + 1;
        else
            ChoiceView.selected = confirmed;
    } else if ((decrement_snapshot &= 32)) {
        register struct ChoiceView *view __asm__("r1");
        u32 selected;
        changed = 1;
        view = &ChoiceView;
        __asm__("" : "+r"(view));
        selected = view->selected;
        if (!selected)
            selected = view->count;
        selected--;
        view->selected = selected;
    }
    if (!changed)
        return 0;
    RequestFixedDefinition(109);
    ResetDialogTextState();
    RenderDialogRecord(9, ChoiceView.selected);
handled:
    return 1;
}
