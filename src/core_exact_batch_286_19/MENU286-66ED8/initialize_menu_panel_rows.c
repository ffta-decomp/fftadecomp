typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct MenuPanel {
    u8 *definitions;
    u16 flags;
    u8 unknown_06[2];
    u8 mode;
    u8 unknown_09;
    u8 row_count;
    s8 alternate_index;
    u8 unknown_0c;
    u8 cursor_initialized;
};
struct MenuModeRecord { u16 count; s8 row; u8 unknown_03; };
#define HALF(p, offset) (*(u16 *)((u8 *)(p) + (offset)))
#define BYTE(p, offset) (*((u8 *)(p) + (offset)))
#define POINTER(p, offset) (*(void **)((u8 *)(p) + (offset)))
extern const u8 AlternateCursorLeft[], AlternateCursorRight[];
extern const u8 ModeThreeHandler[], ModeFourHandler[], ModeFiveHandler[], ModeSixHandler[];
extern const u8 SelectionPrimaryCallback[], SelectionMoreCallback[];
extern void SetCursorDescriptor(void *, const void *, s16, s16);
extern void SetControllerData(void *, void *, u16, u16);
extern void SetSelectionCallbackContext(void *, void *, void *);
extern u32 QueryVisibleRows(u8 *);
extern void ApplySelectionFields(void *);
extern void SetRowAttribute(u8 *, u32, u32);
extern void DrawMenuRow(u8 *, s16);
extern void MarkMenuRow(u8 *, u8, u8);
extern void BindControllerCallbacks(void *, void *, void *);
extern void SetSelectionRow(u8 *, u32);
extern void UpdateControllerWidgets(u8 *);
extern void RestoreSelectionFlags(void *, u8);
void InitializeMenuPanelRows(struct MenuPanel *)
    __asm__("RemainingCore48_00066ED8");
void InitializeMenuPanelRows(struct MenuPanel *panel)
{
    u8 *text = ((u8 *)panel) + 36;
    u8 *descriptor = ((u8 *)panel) + 20;
    u8 *list = ((u8 *)panel) + 80;
    u8 *selection = ((u8 *)panel) + 112;
    void *more_callback = 0;
    struct MenuModeRecord *record;
    u32 mode = panel->mode;
    u32 item_count;
    u32 record_offset;
    u8 *definition_root;
    void *buffer;
    u32 text_extent;
    int initial_count;
    int row;
    void *callback;

    record_offset = mode * 4;
    record_offset += 0xa04;
    definition_root = panel->definitions;
    record = (struct MenuModeRecord *)(definition_root + record_offset);
    if (mode == 4) {
        int alternate_offset = (int)panel->alternate_index * 4;
        alternate_offset += 0xa24;
        record = (struct MenuModeRecord *)(definition_root + alternate_offset);
        panel->cursor_initialized = 1;
        SetCursorDescriptor(((u8 *)panel) + 188, AlternateCursorLeft, 196, 8);
        SetCursorDescriptor(((u8 *)panel) + 204, AlternateCursorRight, 12, 8);
    }
    buffer = POINTER(panel, 156);
    item_count = HALF(descriptor, 14);
    if (panel->mode == 4) {
        /* The original tests the full working addition, without u16 wrap. */
        if (item_count + 1 != 0)
            goto has_rows;
        goto no_rows;
    }
    if (item_count == 0)
        goto no_rows;
has_rows:
    text_extent = 256;
    goto set_text_extent;
no_rows:
    text_extent = 448;
set_text_extent:
    SetControllerData(text, buffer, text_extent, HALF(descriptor, 4));
    switch (panel->mode) {
    case 3:
        callback = (void *)ModeThreeHandler;
        goto register_common;
    case 4:
        callback = (void *)ModeFourHandler;
        goto register_common;
    case 5:
        callback = (void *)ModeFiveHandler;
register_common:
        SetSelectionCallbackContext(list, callback, panel);
        break;
    case 6:
        SetSelectionCallbackContext(list, (void *)ModeSixHandler, panel);
        break;
    default:
        break;
    }
    HALF(list, 26) = record->count;
    initial_count = (int)QueryVisibleRows(list);
    panel->row_count = (u8)initial_count;
    row = 0;
    if (row < initial_count) {
        do {
            DrawMenuRow(((u8 *)panel), (s16)row);
            row++;
        } while (row < panel->row_count);
    }
    ApplySelectionFields(list);
    SetRowAttribute(list, (s8)record->row, 11);
    if (panel->mode == 5) {
        row = 0;
        if (row < panel->row_count) {
            do {
                MarkMenuRow(((u8 *)panel), (u8)row, 1);
                row++;
            } while (row < panel->row_count);
        }
    }
    if (BYTE(list, 22) < HALF(descriptor, 4))
        more_callback = (void *)SelectionMoreCallback;
    else
        panel->flags |= 16;
    BindControllerCallbacks(text, (void *)SelectionPrimaryCallback, more_callback);
    SetSelectionRow(selection, (u8)record->row);
    UpdateControllerWidgets(text);
    if (BYTE(panel, 4) & 1)
        RestoreSelectionFlags(((u8 *)panel) + 112, 1);
}
__asm__(".global AlternateCursorLeft\n.set AlternateCursorLeft,0x0851BA72\n"
        ".global AlternateCursorRight\n.set AlternateCursorRight,0x0851BA7A\n"
        ".global ModeThreeHandler\n.set ModeThreeHandler,0x080674B1\n"
        ".global ModeFourHandler\n.set ModeFourHandler,0x08067505\n"
        ".global ModeFiveHandler\n.set ModeFiveHandler,0x08067529\n"
        ".global ModeSixHandler\n.set ModeSixHandler,0x08067575\n"
        ".global SelectionPrimaryCallback\n.set SelectionPrimaryCallback,0x08017E81\n"
        ".global SelectionMoreCallback\n.set SelectionMoreCallback,0x08017F05\n"
        ".global SetCursorDescriptor\n.thumb_set SetCursorDescriptor,0x08017FA9\n"
        ".global SetControllerData\n.thumb_set SetControllerData,0x08016211\n"
        ".global SetSelectionCallbackContext\n.thumb_set SetSelectionCallbackContext,0x08017AC5\n"
        ".global QueryVisibleRows\n.thumb_set QueryVisibleRows,0x08017B51\n"
        ".global ApplySelectionFields\n.thumb_set ApplySelectionFields,0x08017AD9\n"
        ".global SetRowAttribute\n.thumb_set SetRowAttribute,0x08017AF5\n"
        ".global DrawMenuRow\n.thumb_set DrawMenuRow,0x080676F9\n"
        ".global MarkMenuRow\n.thumb_set MarkMenuRow,0x08067E49\n"
        ".global BindControllerCallbacks\n.thumb_set BindControllerCallbacks,0x08015D59\n"
        ".global SetSelectionRow\n.thumb_set SetSelectionRow,0x08017FB1\n"
        ".global UpdateControllerWidgets\n.thumb_set UpdateControllerWidgets,0x08016235\n"
        ".global RestoreSelectionFlags\n.thumb_set RestoreSelectionFlags,0x08017D19\n");
