/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneContinuationFrame {
    u16 selector;
    u16 depth;
    u16 continuations[0];
    u8 unknown_04[73];
    u8 mode;
    u8 unknown_4e[3];
    u8 state_51; /* Scene byte +0x51; broader state-bit meaning is unresolved. */
    u8 unknown_52[10];
    s32 selection_result;
};
struct SceneSelectionRoot { u32 current_record; s32 selected_object; u32 unknown_08; u16 transaction_mode; };
typedef char SceneModeOffset[(unsigned)&((struct SceneContinuationFrame *)0)->mode==77?1:-1];
typedef char SceneDisplayOffset[(unsigned)&((struct SceneContinuationFrame *)0)->state_51==81?1:-1];
typedef char SceneResultOffset[(unsigned)&((struct SceneContinuationFrame *)0)->selection_result==92?1:-1];
typedef char TransactionModeOffset[(unsigned)&((struct SceneSelectionRoot *)0)->transaction_mode==12?1:-1];
extern struct SceneContinuationFrame *gSceneFrame;
extern struct SceneSelectionRoot gSceneSelection;
__asm__(".global gSceneFrame\n.set gSceneFrame, 0x0200f450");
__asm__(".global gSceneSelection\n.set gSceneSelection, 0x020020d0");
#define QUEUE_CONTINUATION(frame, next) \
    do { \
        (frame)->selector = (next); \
        (frame)->continuations[(frame)->depth++] = (next); \
    } while (0)

void PrepareSceneSelectionContinuation(void);
void PrepareSceneSelectionContinuation(void)
{
    struct SceneSelectionRoot *selection = &gSceneSelection;
    struct SceneContinuationFrame **reference;
    struct SceneContinuationFrame *frame;
    u32 continuation;
    selection->transaction_mode = 16;
    reference = &gSceneFrame;
    (*reference)->mode = 11;
    (*reference)->state_51 = 144;
    frame = *reference;
    frame->continuations[frame->depth++] = frame->selector;
    continuation = 30;
    QUEUE_CONTINUATION(frame, continuation);
    continuation = 55;
    QUEUE_CONTINUATION(frame, continuation);
    frame->selector = 49;
}
