typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct SelectionBlinkWidget {
    void *callback;
    const u8 *data;
    u16 x;
    u16 y;
    u16 counter;
    u16 unknown_0e;
    u8 flags;
    u8 blink;
    u8 phase;
    u8 unknown_13;
};
struct SelectionDrawingState {
    u8 unknown[176];
    s16 tile_offset;
};
extern struct SelectionDrawingState SelectionDrawingState;
extern const u8 SelectionBlinkSprite[];
extern u32 ReadManagedSelectionShiftedByte(const u8 *);
extern void SubmitSelectionPlainSprite(const u8 *, u32, u32, u32, u32, u32);
extern void SubmitSelectionTransformedSprite(const u8 *, u32, u32, u32,
                                             u32, u32, u32, u32, u32, u32, u32);

void AdvanceAndDrawManagedSelectionBlink(struct SelectionBlinkWidget *widget)
{
    if ((widget->flags & 64) == 0) {
        widget->counter = (widget->counter + 1) & 7;
        if (widget->counter == 0)
            widget->blink ^= 1;
    }
    if ((widget->flags & 4) != 0)
        SubmitSelectionPlainSprite(SelectionBlinkSprite, widget->x,
                                   widget->y - widget->blink,
                                   SelectionDrawingState.tile_offset, 0, 0);
    if ((widget->flags & 8) != 0) {
        u16 y = (u8)ReadManagedSelectionShiftedByte(widget->data) * 8 + 8 + widget->y;
        u32 draw_y = y;
        register u32 blink asm("r4");
        /* Finish the native truncation before the final blink read. */
        asm("" : "+r" (draw_y));
        blink = widget->blink;
        draw_y += blink;
        /* Complete Y before preparing the remaining outgoing arguments. */
        asm("" : "+r" (draw_y) : "r" (blink));
        /* The native Y wraps before the fresh blink-byte addition. */
        SubmitSelectionTransformedSprite(SelectionBlinkSprite, widget->x,
                                         draw_y, 0,
                                         0, 0, 0, 1,
                                         SelectionDrawingState.tile_offset, 0, 0);
    }
}

asm(".global SelectionDrawingState\n.set SelectionDrawingState, 0x020020d0\n"
    ".global SelectionBlinkSprite\n.set SelectionBlinkSprite, 0x0851ba62\n"
    ".global ReadManagedSelectionShiftedByte\n"
    ".thumb_set ReadManagedSelectionShiftedByte, 0x08017b49\n"
    ".global SubmitSelectionPlainSprite\n"
    ".thumb_set SubmitSelectionPlainSprite, 0x08001dad\n"
    ".global SubmitSelectionTransformedSprite\n"
    ".thumb_set SubmitSelectionTransformedSprite, 0x08001cf1\n");
