typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*ClearRoutine)(void *, u32);
typedef void (*CopyRoutine)(void *, const void *, u32);
struct DmaRequest;
struct BattleSnapshotDefinition {
    u8 unknown_0000[34];
    u8 category;
};
struct BattlePhaseSnapshot {
    u16 cleared_halfwords[161];
    u8 unknown_0322[334];
    void *allocation;
    u8 copy_request[28];
    u8 sequence_request[28];
    const struct BattleSnapshotDefinition *definition;
    void *owned_payload;
    u16 saved_first, saved_second;
    u8 saved_bytes[4];
    const void *phase_table;
    u8 unknown_0736[72];
};
struct BattleStateView {
    u8 unknown_0000[18];
    volatile u16 first_reset, second_reset;
    u8 unknown_0022[52];
    volatile u8 first, second, third, fourth;
};
struct TransferState {
    u8 unknown_0000[20];
    u32 destination;
};
extern struct BattleStateView gBattleState;
extern struct TransferState gTransferState;
extern const u8 gDefaultPhaseTable[], gCategoryFivePhaseTable[];
extern const u8 gSnapshotContentBank[];
extern const u32 gSequenceSources[];
extern const volatile u32 gSequenceMetadata[];
extern u8 gPaletteDestination[];
extern ClearRoutine const gClearRoutine;
extern CopyRoutine const gCopyRoutine;
extern void *AllocateSnapshot(u32);
extern void CallClear(void *, u32, ClearRoutine);
extern void CallCopy(void *, const void *, u32, CopyRoutine);
extern void LoadSnapshotContent(const void *, void *, u16, u16);
extern const void *GetPaletteBank(u8);
extern void QueueDmaCopy32(struct DmaRequest *, u32, u32, u16);
extern void QueueDmaSequence16(struct DmaRequest *, u32, u32, u16,
                              u16, u16, u16);
extern void StageDmaChannelTransfer(u32, u32, u32, u32);
asm(".global gBattleState\n.set gBattleState,0x03000940\n.global gTransferState\n.set gTransferState,0x030008b0\n.global gDefaultPhaseTable\n.set gDefaultPhaseTable,0x08394088\n.global gCategoryFivePhaseTable\n.set gCategoryFivePhaseTable,0x08394096\n.global gSnapshotContentBank\n.set gSnapshotContentBank,0x083c1834\n.global gSequenceSources\n.set gSequenceSources,0x08394058\n.global gSequenceMetadata\n.set gSequenceMetadata,0x08394070\n.global gPaletteDestination\n.set gPaletteDestination,0x03003920\n.global gClearRoutine\n.set gClearRoutine,0x0836d4b8\n.global gCopyRoutine\n.set gCopyRoutine,0x0836d4bc\n.global AllocateSnapshot\n.thumb_set AllocateSnapshot,0x08022841\n.global CallClear\n.thumb_set CallClear,0x0814224d\n.global CallCopy\n.thumb_set CallCopy,0x08142251\n.global LoadSnapshotContent\n.thumb_set LoadSnapshotContent,0x08005319\n.global GetPaletteBank\n.thumb_set GetPaletteBank,0x080cbabd\n.global QueueDmaCopy32\n.thumb_set QueueDmaCopy32,0x08000add\n.global QueueDmaSequence16\n.thumb_set QueueDmaSequence16,0x08000bad\n.global StageDmaChannelTransfer\n.thumb_set StageDmaChannelTransfer,0x08000d49");

struct BattlePhaseSnapshot *CreateBattlePhaseSnapshot(
    const struct BattleSnapshotDefinition *definition)
{
    struct BattlePhaseSnapshot *snapshot = AllocateSnapshot(808);
    u8 category;
    CopyRoutine const *copy_cell;
    register u8 *palette_destination asm("r4");
    u32 clear_cursor;

    CallClear(snapshot, 808, gClearRoutine);
    snapshot->saved_bytes[0] = gBattleState.first;
    snapshot->saved_bytes[1] = gBattleState.second;
    snapshot->saved_bytes[2] = gBattleState.third;
    snapshot->saved_bytes[3] = gBattleState.fourth;
    snapshot->saved_first = gBattleState.first_reset;
    snapshot->saved_second = gBattleState.second_reset;
    snapshot->phase_table = gDefaultPhaseTable;
    if (definition->category == 5)
        snapshot->phase_table = gCategoryFivePhaseTable;
    snapshot->definition = definition;
    gBattleState.first = 68;
    gBattleState.second = 59;
    gBattleState.third = 0;
    gBattleState.fourth = 16;
    gBattleState.first_reset = 0;
    gBattleState.second_reset = 0;

    snapshot->allocation = AllocateSnapshot(1472);
    category = definition->category;
    LoadSnapshotContent(gSnapshotContentBank, snapshot->allocation, category, 1);
    QueueDmaCopy32((struct DmaRequest *)snapshot->copy_request,
                   (u32)snapshot->allocation, 0x06009c00, 368);
    {
        register u32 request_offset asm("r2") = 688;
        struct DmaRequest *request;
        /* Materialize the observed request address before the other arguments. */
        asm("" : "+r"(request_offset));
        request = (struct DmaRequest *)((u8 *)snapshot + request_offset);
        QueueDmaSequence16(request,
                       gSequenceSources[category],
                       gTransferState.destination + 774,
                       (u16)(gSequenceMetadata[category] >> 3), 4,
                       (u16)(gSequenceMetadata[category] >> 2), 64);
    }
    copy_cell = &gCopyRoutine;
    palette_destination = gPaletteDestination;
    CallCopy(palette_destination, GetPaletteBank(12), 32, *copy_cell);
    {
        register u32 palette_step asm("r7") = 512;
        /* The second palette destination retains this defined offset in r7. */
        asm("" : "+r"(palette_destination), "+r"(palette_step));
        palette_destination += palette_step;
    }
    CallCopy(palette_destination, GetPaletteBank(11), 32, *copy_cell);

    /* Preserve the post-helper reverse clear, including halfword zero. */
    {
        register u32 clear_value asm("r1") = 0;
        register u32 clear_offset asm("r2") = 320;
        /* Both defined operands have the original short-lived clear-loop roles. */
        asm("" : "+r"(clear_value), "+r"(clear_offset));
        clear_cursor = (u32)snapshot + clear_offset;
        do {
            *(u16 *)clear_cursor = (u16)clear_value;
            clear_cursor -= 2;
        } while ((s32)clear_cursor >= (s32)(u32)snapshot);
    }
    StageDmaChannelTransfer(3, (u32)snapshot, 0x04000018, 0x20400001);
    return snapshot;
}
