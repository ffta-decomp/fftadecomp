typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct SelectionPhaseWidget {
    void *callback;
    void *data;
    u16 x;
    u16 y;
    u16 counter;
    u16 y_offset;
    u8 flags;
    u8 blink;
    u8 phase;
    u8 unknown_13;
};
struct SelectionPhaseDrawingState {
    u8 unknown[176];
    s16 tile_offset;
};
extern struct SelectionPhaseDrawingState SelectionPhaseDrawingState;
extern const u8 SelectionPhasePlainSprite[];
extern const u8 SelectionPhaseTransformedSprite[];
extern void SubmitSelectionPhasePlain(const u8 *, u32, u32, u32, u32, u32);
extern void SubmitSelectionPhaseTransformed(const u8 *, u32, u32, u32,
                                            u32, u32, u32, u32, u32, u32, u32);

void DrawManagedSelectionPhase(struct SelectionPhaseWidget *widget)
{
    struct SelectionPhaseWidget *draw_widget;
    u32 flags;
    u8 plain;
    {
        register struct SelectionPhaseWidget *captured asm("r3") = widget;
        /* Preserve the branch-specific object alias captured before flags. */
        asm("" : "+r" (captured));
        draw_widget = captured;
    }
    flags = widget->flags;
    asm("" : "+r" (flags));
    {
        register u32 plain_mask asm("r0") = flags & 4;
        asm("" : "+r" (plain_mask));
        plain = plain_mask;
    }
    if (plain != 0) {
        SubmitSelectionPhasePlain(SelectionPhasePlainSprite,
                                  widget->x + 15,
                                  widget->y + widget->y_offset + 1,
                                  SelectionPhaseDrawingState.tile_offset + widget->phase,
                                  0, 0);
    } else {
        u32 horizontal = flags & 8;
        u32 x_offset;
        asm("" : "+r" (horizontal));
        x_offset = 0;
        if (horizontal != 0)
            x_offset = 24;
        SubmitSelectionPhaseTransformed(SelectionPhaseTransformedSprite,
                                        draw_widget->x + x_offset,
                                        draw_widget->y + draw_widget->y_offset, 0,
                                        0, 0, ((u8)flags >> 3) & 1, 0, 0, 0, 0);
    }
}

asm(".global SelectionPhaseDrawingState\n.set SelectionPhaseDrawingState, 0x020020d0\n"
    ".global SelectionPhasePlainSprite\n.set SelectionPhasePlainSprite, 0x0851ba5a\n"
    ".global SelectionPhaseTransformedSprite\n.set SelectionPhaseTransformedSprite, 0x0851ba52\n"
    ".global SubmitSelectionPhasePlain\n.thumb_set SubmitSelectionPhasePlain, 0x08001dad\n"
    ".global SubmitSelectionPhaseTransformed\n.thumb_set SubmitSelectionPhaseTransformed, 0x08001cf1\n");
