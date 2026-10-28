typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*ClearRoutine)(void *,u32);
typedef void (*CopyRoutine)(void *,const void *,u32);
struct BattleRecordWorkspace {
    const void *metadata;
    const u8 *bank;
    u16 transfer_value;
    u8 unknown_0010[14];
    const u8 *bank_entry;
    u8 initial_option;
    u8 unknown_0029[31];
    u8 transfer_request[28];
    void *owned_allocation;
};
extern const u8 gPackedRecordData[];
extern const u32 gRecordBank[];
extern const u8 gRecordMetadata[];
extern u8 gCurrentRecordBytes[32];
extern ClearRoutine const gClearRoutine;
extern CopyRoutine const gCopyRoutine;
extern void *AllocateWorkspace(u32 size);
extern void CallClear(void *,u32,ClearRoutine);
extern void CallCopy(void *,const void *,u32,CopyRoutine);
extern void DecodeRecordData(void *,const void *);
extern void QueueRecordTransfer(void *,u32,u32,u16);
extern const void *GetRecordByteSource(u8 index);
asm(".global gPackedRecordData\n.set gPackedRecordData,0x083c3454\n.global gRecordBank\n.set gRecordBank,0x0841ccb8\n.global gRecordMetadata\n.set gRecordMetadata,0x08420774\n.global gCurrentRecordBytes\n.set gCurrentRecordBytes,0x03003b20\n.global gClearRoutine\n.set gClearRoutine,0x0836d4b8\n.global gCopyRoutine\n.set gCopyRoutine,0x0836d4bc\n.global AllocateWorkspace\n.thumb_set AllocateWorkspace,0x08022841\n.global CallClear\n.thumb_set CallClear,0x0814224d\n.global CallCopy\n.thumb_set CallCopy,0x08142251\n.global DecodeRecordData\n.thumb_set DecodeRecordData,0x0800543d\n.global QueueRecordTransfer\n.thumb_set QueueRecordTransfer,0x08000a99\n.global GetRecordByteSource\n.thumb_set GetRecordByteSource,0x080cbabd");
struct BattleRecordWorkspace *CreateBattleRecordWorkspace(void)
{
    struct BattleRecordWorkspace *workspace = AllocateWorkspace(172);
    CopyRoutine const *copy_cell;
    u8 *byte_destination;
    const void *byte_source;
    const u8 *record_bank;
    const void *record_metadata;
    CallClear(workspace,172,gClearRoutine);
    workspace->owned_allocation = AllocateWorkspace(1984);
    DecodeRecordData(workspace->owned_allocation,gPackedRecordData);
    QueueRecordTransfer(workspace->transfer_request,
                        (u32)workspace->owned_allocation,0x06013c00,992);
    record_bank = (const u8 *)gRecordBank;
    record_metadata = gRecordMetadata;
    workspace->bank = record_bank;
    workspace->metadata = record_metadata;
    workspace->bank_entry = (const u8 *)gRecordBank + gRecordBank[0];
    workspace->transfer_value = 480;
    workspace->initial_option = 6;
    copy_cell = &gCopyRoutine;
    byte_destination = gCurrentRecordBytes;
    byte_source = GetRecordByteSource(13);
    CallCopy(byte_destination,byte_source,32,*copy_cell);
    return workspace;
}
