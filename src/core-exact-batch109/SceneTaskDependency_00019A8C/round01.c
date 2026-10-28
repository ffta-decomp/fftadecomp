typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void ResolveDialogRecordLocation_08019A50(u32, u8 *, u16 *);
extern void InitializeDialogRecordObject_0801174C(void *, u32, u32, void *, void *,
                                                u32, u32, u32, u32, u32);
extern void SetDialogOutputFlags_0801339C(u32);
void InitializeBattleSelectionDialogRecord(void *object, u16 record_id,
                                           void *first_data, void *second_data)
{
    u8 bank;
    u16 ordinal;
    ResolveDialogRecordLocation_08019A50(record_id, &bank, &ordinal);
    InitializeDialogRecordObject_0801174C(object, bank, ordinal,
        first_data, second_data, 2, 2, 24, 4, 928);
    SetDialogOutputFlags_0801339C(2);
}
asm(".thumb_set ResolveDialogRecordLocation_08019A50, 0x08019a51\n");
asm(".thumb_set InitializeDialogRecordObject_0801174C, 0x0801174d\n");
asm(".thumb_set SetDialogOutputFlags_0801339C, 0x0801339d\n");
