typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct DialogTextContext {
    u8 unknown_000[17];
    u8 layout_height;
    u8 unknown_012[8];
    u8 width_tiles;
    u8 unknown_01b[37];
    u8 pending;
    u8 unknown_041[703];
    u32 unknown_300;
    u32 unknown_304;
    u8 *current_text;
    u8 encoded_text[512];
    u8 scratch[1];
};
extern struct DialogTextContext *ActiveDialogTextContext;
extern u16 DialogBufferDecodeRecord(u8 *, const u8 *, u8 *, u16, u8 *, u8 *);
extern u32 DialogBufferMeasureWidth(const u8 *, u8);

void PrepareManagedDialogText(const u8 *bank, const u8 *prefix, u32 record_input)
{
    register const u8 *saved_bank asm("r8") = bank;
    u16 record;
    u8 prefix_length;
    u8 metadata;
    /* Preserve the actual bank pointer while the prefix cursor is active. */
    asm("" : "+r" (saved_bank));
    record = (u16)record_input;
    prefix_length = 0;
    if (prefix != 0) {
        const u8 *cursor = prefix;
        while (*cursor != 0)
            ActiveDialogTextContext->encoded_text[prefix_length++] = *cursor++;
    }
    DialogBufferDecodeRecord(ActiveDialogTextContext->encoded_text + prefix_length,
                             saved_bank, ActiveDialogTextContext->scratch,
                             record, 0, &metadata);
    if (ActiveDialogTextContext->width_tiles == 0)
        ActiveDialogTextContext->width_tiles =
            DialogBufferMeasureWidth(ActiveDialogTextContext->encoded_text, 1) >> 3;
    if (ActiveDialogTextContext->layout_height == 0 ||
        ActiveDialogTextContext->layout_height < metadata * 2)
        ActiveDialogTextContext->layout_height = metadata * 2;
    ActiveDialogTextContext->current_text = ActiveDialogTextContext->encoded_text;
    /* The roles of these two preserved words remain tentative. */
    ActiveDialogTextContext->unknown_304 = ActiveDialogTextContext->unknown_300;
    ActiveDialogTextContext->pending = 0;
}

asm(".global ActiveDialogTextContext\n.set ActiveDialogTextContext, 0x0200918c\n"
    ".global DialogBufferDecodeRecord\n.thumb_set DialogBufferDecodeRecord, 0x08013e9d\n"
    ".global DialogBufferMeasureWidth\n.thumb_set DialogBufferMeasureWidth, 0x080144f5\n");
