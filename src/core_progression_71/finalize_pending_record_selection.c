/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SelectionData {
    u8 unknown00[10];
    u8 input_flags;
    u8 unknown11;
    u16 record_code;
    u8 unknown14[0xbac - 14];
    void *next_input_record;
};
struct SelectionContext {
    struct SelectionData *data;
    u8 unknown04[4];
    u8 mode;
    u8 unknown09[7];
    void *task;
    u8 unknown20[182];
    u16 pending;
};
typedef char PointerWidthIsFour[(sizeof(void *) == 4) ? 1 : -1];
extern u32 AdvancePendingInput(void);
extern void ApplyRecordInputFlags(void *, u8);
extern void RefreshRecordCursor(void *);
extern void SetActiveInputRecord(void *);
extern u8 *GetTaskPayload(void *);
extern void SetGameFlag(u16, u8);
/* Declaration-only bindings to verified original direct targets. */
asm(".global AdvancePendingInput\n.thumb_set AdvancePendingInput,0x08011861\n.global ApplyRecordInputFlags\n.thumb_set ApplyRecordInputFlags,0x08017d19\n.global RefreshRecordCursor\n.thumb_set RefreshRecordCursor,0x08017e29\n.global SetActiveInputRecord\n.thumb_set SetActiveInputRecord,0x08013391\n.global SetGameFlag\n.thumb_set SetGameFlag,0x080c9575\n.global GetTaskPayload\n.thumb_set GetTaskPayload,0x08005bfd");


u32 FinalizePendingRecordSelection(struct SelectionContext *context)
{
    u8 *primary = (u8 *)context + 112;
    u8 *secondary = (u8 *)context + 132;
    context->pending = 0;
    if ((u16)AdvancePendingInput() == 0)
        return 0;
    ApplyRecordInputFlags(primary, context->data->input_flags);
    if (secondary != 0) {
        secondary[16] &= 191;
        RefreshRecordCursor(secondary);
    }
    SetActiveInputRecord(context->data->next_input_record);
    if (context->data->record_code == 1145)
        SetGameFlag(1409, 1);
    if (context->mode == 4) {
        u8 *payload = GetTaskPayload(context->task);
        payload[9] &= 247;
    }
    return 1;
}
