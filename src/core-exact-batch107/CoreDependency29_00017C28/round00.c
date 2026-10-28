typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ManagedWidgetData { u8 unknown_00[20]; u8 height_units; };
struct ManagedSelectionWidget {
    void *callback; struct ManagedWidgetData *data;
    u16 width, height, x, y; u8 flags, counter, state;
};
extern u32 GetManagedWidgetWidth(struct ManagedSelectionWidget *);
void InitializeManagedSelectionWidget(struct ManagedSelectionWidget *widget,
                                     struct ManagedWidgetData *data,
                                     void *callback, u8 flags)
{
    widget->callback = callback;
    widget->data = data;
    widget->counter = 0;
    widget->flags = flags == 0 ? 3 : flags;
    widget->state = 0;
    widget->y = 0;
    widget->x = 0;
    widget->height = 0;
    widget->width = 0;
    if (data != 0) {
        widget->width = GetManagedWidgetWidth(widget);
        widget->height = ((u32)widget->data->height_units << 3) + 4;
    }
}
asm(".thumb_set GetManagedWidgetWidth, 0x08017bf5\n");
