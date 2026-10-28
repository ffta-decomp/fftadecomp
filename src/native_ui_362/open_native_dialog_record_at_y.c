typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern void SplitNativeDialogRecordId(u32,u8 *,u16 *);
extern void InitializeNativeDialogRecord(void *,u32,u32,void *,void *,u32,u32,u32,u32,u32);
extern void SetNativeDialogOutputFlags(u16);
__asm__(".global SplitNativeDialogRecordId\n.thumb_set SplitNativeDialogRecordId,0x08019A51\n"
        ".global InitializeNativeDialogRecord\n.thumb_set InitializeNativeDialogRecord,0x0801174D\n"
        ".global SetNativeDialogOutputFlags\n.thumb_set SetNativeDialogOutputFlags,0x0801339D\n");
void OpenNativeDialogRecordAtY(void *,u16,void *,void *,u16)
    __asm__("SceneTaskDependency_00019AE4");
void OpenNativeDialogRecordAtY(void *object,u16 record_id,
                               void *first_data,void *second_data,u16 y_input)
{
    u8 bank;
    u16 ordinal;
    /* The original resolver owns these independent byte/halfword OUTs.
       As in native, unmapped IDs do not receive invented default values. */
    SplitNativeDialogRecordId(record_id,&bank,&ordinal);
    InitializeNativeDialogRecord(object,bank,ordinal,first_data,second_data,
                                 2,(s16)y_input,24,4,928);
    SetNativeDialogOutputFlags(2);
}
