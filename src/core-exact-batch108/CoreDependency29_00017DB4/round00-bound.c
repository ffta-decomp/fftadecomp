typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SelectionData { u8 unknown_00[19]; u8 width_units, height_units; };
struct SecondarySelectionWidget {
    void *callback; struct SelectionData *data;
    u16 width, height, x, y; u8 flags, counter, state;
};
extern void (*const ClearWidgetCallbackCell)(void *, u32);
extern u32 ReadSelectionDataExtra(struct SelectionData *);
extern void UpdateSelectionBoundaryFlags(struct SecondarySelectionWidget *);
void InitializeSecondarySelectionWidget(struct SecondarySelectionWidget *widget,
                                         struct SelectionData *data, void *callback, u8 flags)
{
    if (callback == 0) {
        ClearWidgetCallbackCell(widget, 20);
    } else {
        u32 width;
        widget->callback = callback;
        widget->data = data;
        widget->flags = flags == 0 ? 17 : flags;
        widget->state = 0;
        widget->y = 0;
        width = ((u8)ReadSelectionDataExtra(data) + data->width_units) << 3;
        widget->width = width;
        if (widget->flags & 32) widget->width = width - 8;
        widget->height = ((u32)data->height_units << 3) - 4;
        widget->counter = 0;
        widget->x = 0;
        widget->y = 0;
        UpdateSelectionBoundaryFlags(widget);
    }
}
asm(".set ClearWidgetCallbackCell, 0x0836d4b8\n");
asm(".thumb_set ReadSelectionDataExtra, 0x08017b45\n");
asm(".thumb_set UpdateSelectionBoundaryFlags, 0x08017e29\n");
asm(".thumb_set _call_via_r2, 0x0814224d\n");
