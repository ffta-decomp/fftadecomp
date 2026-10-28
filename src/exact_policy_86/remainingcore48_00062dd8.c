/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneSelectionFrame {
    u16 selector;
    u16 depth;
    u16 continuations[0];
    u8 unknown_04[73];
    u8 state_4d;
    u8 unknown_4e[14];
    u32 result;
};
struct LiveSelectionState { u8 unknown_00[18]; u8 state_12; };
typedef char ResultOffset[(unsigned)&((struct SceneSelectionFrame *)0)->result==92?1:-1];
typedef char StateOffset[(unsigned)&((struct SceneSelectionFrame *)0)->state_4d==77?1:-1];
extern u32 gSceneFrameAddress;
extern struct LiveSelectionState gLiveSelection;
extern void CommitSceneSelection(u32 result);
__asm__(".global gSceneFrameAddress\n.set gSceneFrameAddress, 0x0200f450");
__asm__(".global gLiveSelection\n.set gLiveSelection, 0x020020d0");
__asm__(".global CommitSceneSelection\n.thumb_set CommitSceneSelection, 0x08066049");

void CommitSceneSelectionAndContinue(void);
void CommitSceneSelectionAndContinue(void)
{
    u32 *reference = &gSceneFrameAddress;
    struct SceneSelectionFrame *frame;
    u32 continuation;
    CommitSceneSelection(((struct SceneSelectionFrame *)*reference)->result);
    ((struct SceneSelectionFrame *)*reference)->state_4d = 10;
    gLiveSelection.state_12 = 0;
    frame = (struct SceneSelectionFrame *)*reference;
    continuation = 16;
    frame->selector = continuation;
    frame->continuations[frame->depth++] = continuation;
    frame->selector = 49;
}
