typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct IndicatorNode {
    u8 unknown_000[17];
    u8 visible;
    u8 unknown_012[6];
    struct IndicatorNode *next;
};
struct IndicatorContext {
    u8 unknown_000[448];
    struct IndicatorNode *head;
    u8 unknown_1c4[4];
    u8 current_mode;
    u8 attributes;
    u8 requested_mode;
    u8 flags;
    u8 unknown_1cc[4];
    u16 field_1d0;
};
typedef void (*ClearIndicatorBytes)(void *, u32);
extern void UpdateIndicatorModeOne(struct IndicatorContext *, u32);
extern void UpdateIndicatorModeTwo(struct IndicatorContext *, u32);
__asm__(".global UpdateIndicatorModeOne\n.thumb_set UpdateIndicatorModeOne, 0x080bcb2d\n"
        ".global UpdateIndicatorModeTwo\n.thumb_set UpdateIndicatorModeTwo, 0x080bcc71\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

void AdvanceBattleIndicatorMode(struct IndicatorContext *input)
    __asm__("Source52_000BCDF8");
void AdvanceBattleIndicatorMode(struct IndicatorContext *input)
{
    register struct IndicatorContext *context __asm__("r5") = input;
    register u8 *mode_address __asm__("r4");
    register s32 entry_mode __asm__("r0");
    u32 all_inactive;
    /* Keep the native context and current-mode address across real updates. */
    __asm__("" : "+r"(context));
    mode_address = (u8 *)context + 456;
    __asm__("" : "+r"(mode_address));
    entry_mode = *mode_address;
    /* Retain the initialized signed dispatch value and explicit default arm. */
    __asm__("" : "+r"(entry_mode));
    switch (entry_mode) {
    case 0: {
        register u8 *requested_address __asm__("r0") = (u8 *)context + 458;
        register u32 requested_mode __asm__("r1");
        /* The initialized R0 address and R1 value retain native formation. */
        __asm__("" : "+r"(requested_address));
        requested_mode = *requested_address;
        if (requested_mode != 1) {
            /* Keep the two native accepted values as separate comparisons. */
            __asm__("" : "+r"(requested_mode));
            if (requested_mode != 2)
                return;
        }
        *mode_address = (u8)requested_mode;
        {
            register u16 *transition_field __asm__("r0") = &context->field_1d0;
            /* The native final address reuses R0 instead of the dead context. */
            __asm__("" : "+r"(transition_field));
            *transition_field = (u16)requested_mode;
        }
        return;
    }
    case 1: {
        register u32 maintain_mode __asm__("r1");
        register u8 *requested_address __asm__("r6");
        struct IndicatorNode *node;
        u32 mode_after;
        u32 requested_after;
        /* Preserve the observed dispatch value, not a substituted case constant. */
        __asm__("" : "+r"(entry_mode));
        maintain_mode = 0;
        __asm__("" : "+r"(maintain_mode));
        requested_address = (u8 *)context + 458;
        __asm__("" : "+r"(requested_address));
        if (entry_mode == *requested_address)
            maintain_mode = 1;
        UpdateIndicatorModeOne(context, maintain_mode);
        mode_after = *mode_address;
        requested_after = *requested_address;
        if (mode_after == requested_after)
            return;
        {
            register struct IndicatorNode **head_address __asm__("r0") = &context->head;
            /* Form the native head-cell address before the scan accumulator. */
            __asm__("" : "+r"(head_address));
            all_inactive = 1;
            node = *head_address;
        }
        while (node != (struct IndicatorNode *)0) {
            if (node->visible != 0)
                all_inactive = 0;
            node = node->next;
        }
        break;
    }
    case 2: {
        register u32 maintain_mode __asm__("r1");
        register u8 *requested_address __asm__("r6");
        struct IndicatorNode *node;
        u32 mode_after;
        u32 requested_after;
        __asm__("" : "+r"(entry_mode));
        maintain_mode = 0;
        __asm__("" : "+r"(maintain_mode));
        requested_address = (u8 *)context + 458;
        __asm__("" : "+r"(requested_address));
        if (entry_mode == *requested_address)
            maintain_mode = 1;
        UpdateIndicatorModeTwo(context, maintain_mode);
        mode_after = *mode_address;
        requested_after = *requested_address;
        if (mode_after == requested_after)
            return;
        {
            register struct IndicatorNode **head_address __asm__("r0") = &context->head;
            /* Form the native head-cell address before the scan accumulator. */
            __asm__("" : "+r"(head_address));
            all_inactive = 1;
            node = *head_address;
        }
        while (node != (struct IndicatorNode *)0) {
            if (node->visible != 0)
                all_inactive = 0;
            node = node->next;
        }
        break;
    }
    default:
        return;
    }
    if (all_inactive != 0) {
        register u8 *requested_address __asm__("r6") = (u8 *)context + 458;
        register u32 saved_requested_mode __asm__("r4");
        /* These callee-saved values survive the real full-context clear. */
        __asm__("" : "+r"(requested_address));
        saved_requested_mode = *requested_address;
        {
            register ClearIndicatorBytes clear_bytes __asm__("r2") =
                *(ClearIndicatorBytes *)0x0836d4b8;
            register struct IndicatorContext *clear_context __asm__("r0");
            /* Preserve native callback, context, then size argument formation. */
            __asm__("" : "+r"(clear_bytes));
            clear_context = context;
            __asm__("" : "+r"(clear_context) : "r"(clear_bytes));
            clear_bytes(clear_context, 536);
        }
        *requested_address = (u8)saved_requested_mode;
    }
}
