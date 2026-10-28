typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*CopyRoutine)(void *, const void *, u32);
struct LivePayloadSourceView {
    u8 unknown_0000[0x3c32];
    u8 first;
    u8 second;
    u8 payload[8];
};
extern struct LivePayloadSourceView gLivePayloadSource;
extern u8 gBattlePayloadScratch[12];
extern u8 gBattlePayloadContext[];
extern CopyRoutine const gCopyBytesRoutine;
extern void CallCopyRoutine(void *, const void *, u32, CopyRoutine);
extern void InitializePayloadOperation(void *, const void *, u16, u8);
asm(".global gLivePayloadSource\n.set gLivePayloadSource,0x02000000\n.global gBattlePayloadScratch\n.set gBattlePayloadScratch,0x02015960\n.global gBattlePayloadContext\n.set gBattlePayloadContext,0x020158b4\n.global gCopyBytesRoutine\n.set gCopyBytesRoutine,0x0836d4bc\n.global CallCopyRoutine\n.thumb_set CallCopyRoutine,0x08142251\n.global InitializePayloadOperation\n.thumb_set InitializePayloadOperation,0x080c5d61");

void BeginBattlePayloadOperation(u8 mode)
{
    u8 *scratch = gBattlePayloadScratch;
    const struct LivePayloadSourceView *source = &gLivePayloadSource;
    u8 inverse_mode;
    u32 second_byte_offset;
    CopyRoutine const *copy_cell;
    scratch[0] = source->first;
    second_byte_offset = 0x3c33;
    scratch[1] = ((const u8 *)source)[second_byte_offset];
    copy_cell = &gCopyBytesRoutine;
    CallCopyRoutine(scratch + 2, (const u8 *)source + second_byte_offset + 1, 8, *copy_cell);
    /* The operation receives twelve bytes; its final two retain prior contents. */
    inverse_mode = 0;
    if (mode == 0)
        inverse_mode = 1;
    InitializePayloadOperation(gBattlePayloadContext, scratch, 12, inverse_mode);
}
