typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct DialogBackingData {
    u8 unknown_00[16];
    u8 *tile_data;
};
struct ManagedDialogObject {
    struct DialogBackingData *first_data;
    void *second_data;
    u8 active;
    u8 unknown_09;
    u8 selector;
    u8 initialized;
    u16 format;
    u8 x;
    u8 y;
    u8 unknown_10;
    u8 height;
    u16 tile_index;
    u8 unknown_14[2];
    u16 scale_x;
    u16 scale_y;
    u8 width;
    u8 unknown_1b;
    u8 flag_252;
    u8 layout_columns;
    u8 layout_rows;
    u8 unknown_1f;
    u16 output_flags;
    u8 unknown_22[6];
    u8 pending;
    u8 unknown_29[727];
    u8 *tile_address;
    u8 unknown_304[1168];
};
struct DialogRecordInput {
    u8 prefix_byte;
    u8 padding[3];
    u16 record;
};
extern struct ManagedDialogObject *ManagedDialogObject;
extern void (*const ManagedDialogClearCallback)(void *, u32);
extern u8 ManagedDialogReadFlag(u16);
extern const u8 *ManagedDialogResolveStyle(struct ManagedDialogObject *, u32, u16 *, u8 *);
extern void ManagedDialogPrepareText(const u8 *, const u8 *, u32);

void InitializeManagedDialogObject(struct ManagedDialogObject *object,
                                  u8 selector, u32 record_input,
                                  struct DialogBackingData *first_data,
                                  void *second_data, u16 x, u16 y,
                                  u8 width, u8 height, u16 tile_index)
{
    struct DialogRecordInput input;
    const u8 *prefix = 0;
    u16 *record = &input.record;
    const u8 *bank;

    *record = record_input;
    ManagedDialogObject = object;
    ManagedDialogClearCallback(object, 1940);
    ManagedDialogObject->x = x;
    ManagedDialogObject->y = y;
    ManagedDialogObject->first_data = first_data;
    ManagedDialogObject->second_data = second_data;
    ManagedDialogObject->unknown_1f = 12;
    ManagedDialogObject->layout_columns = 5;
    ManagedDialogObject->layout_rows = 1;
    ManagedDialogObject->selector = selector;
    ManagedDialogObject->scale_x = 4096;
    ManagedDialogObject->scale_y = 32768;
    ManagedDialogObject->width = width;
    ManagedDialogObject->height = height;
    ManagedDialogObject->tile_index = tile_index;
    ManagedDialogObject->tile_address =
        ManagedDialogObject->first_data->tile_data + ((u32)tile_index << 5);
    ManagedDialogObject->initialized = 1;
    ManagedDialogObject->output_flags = 1;
    ManagedDialogObject->pending = 1;
    ManagedDialogObject->flag_252 = ManagedDialogReadFlag(0x252);
    bank = ManagedDialogResolveStyle(ManagedDialogObject, selector,
                                     record, &input.prefix_byte);
    if (input.prefix_byte != 0)
        prefix = &input.prefix_byte;
    ManagedDialogPrepareText(bank, prefix, *record);
    ManagedDialogObject->active = 0;
}

asm(".global ManagedDialogObject\n.set ManagedDialogObject, 0x0200918c\n"
    ".set ManagedDialogClearCallback, 0x0836d4b8\n"
    ".thumb_set _call_via_r2, 0x0814224d\n"
    ".global ManagedDialogReadFlag\n.thumb_set ManagedDialogReadFlag, 0x080c9541\n"
    ".global ManagedDialogResolveStyle\n.thumb_set ManagedDialogResolveStyle, 0x08018029\n"
    ".global ManagedDialogPrepareText\n.thumb_set ManagedDialogPrepareText, 0x08011cd1\n");
