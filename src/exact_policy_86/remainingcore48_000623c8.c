/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SnapshotWords { u32 first; u32 second; };
struct LiveSelectionState {
    u8 unknown_00[152];
    struct SnapshotWords words;
    u8 unknown_a0[48];
    u8 selection_bytes[20];
    u8 selection_byte;
};
struct SelectionSnapshotFrame {
    u16 selector;
    u8 unknown_02[202];
    u8 selection_bytes[20];
    struct SnapshotWords words;
    u8 selection_byte;
    u8 state_e9;
};
typedef char LiveWordsOffset[(unsigned)&((struct LiveSelectionState *)0)->words==152?1:-1];
typedef char LiveBytesOffset[(unsigned)&((struct LiveSelectionState *)0)->selection_bytes==208?1:-1];
typedef char LiveByteOffset[(unsigned)&((struct LiveSelectionState *)0)->selection_byte==228?1:-1];
typedef char FrameWordsOffset[(unsigned)&((struct SelectionSnapshotFrame *)0)->words==224?1:-1];
typedef char FrameBytesOffset[(unsigned)&((struct SelectionSnapshotFrame *)0)->selection_bytes==204?1:-1];
typedef char FrameByteOffset[(unsigned)&((struct SelectionSnapshotFrame *)0)->selection_byte==232?1:-1];
extern u32 gSceneFrameAddress;
extern struct LiveSelectionState gLiveSelection;
extern const u32 gCopyBytesTarget;
extern void WriteSaveByte(u16 index, u8 value);
extern void ResetSelectionState(void);
extern void RequestSaveGatedMode(u16 mode);
extern void _call_via_r3(void *destination, const void *source, u32 bytes, u32 target);
__asm__(".global gSceneFrameAddress\n.set gSceneFrameAddress, 0x0200f450");
__asm__(".global gLiveSelection\n.set gLiveSelection, 0x020020d0");
__asm__(".global gCopyBytesTarget\n.set gCopyBytesTarget, 0x0836d4bc");
__asm__(".global ResetSelectionState\n.thumb_set ResetSelectionState, 0x080c7261");
__asm__(".global RequestSaveGatedMode\n.thumb_set RequestSaveGatedMode, 0x080c71b5");
__asm__(".global _call_via_r3\n.thumb_set _call_via_r3, 0x08142251");

void CaptureSceneSelectionSnapshot(void);
void CaptureSceneSelectionSnapshot(void)
{
    u32 *reference;
    struct SelectionSnapshotFrame *frame;
    WriteSaveByte(13, 1);
    ResetSelectionState();
    RequestSaveGatedMode(1);
    reference = &gSceneFrameAddress;
    frame = (struct SelectionSnapshotFrame *)*reference;
    frame->words = gLiveSelection.words;
    frame->selection_byte = gLiveSelection.selection_byte;
    {
    const u32 *copy_target = &gCopyBytesTarget;
    _call_via_r3(((struct SelectionSnapshotFrame *)*reference)->selection_bytes,
                 gLiveSelection.selection_bytes, 20, *copy_target);
    }
    ((struct SelectionSnapshotFrame *)*reference)->state_e9 = 0;
    ((struct SelectionSnapshotFrame *)*reference)->selector = 5;
}
