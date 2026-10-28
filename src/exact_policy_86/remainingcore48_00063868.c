/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneRecoveryFrame {
    u16 selector;
    u16 depth;
    u16 continuations[0];
    u8 unknown_04[64];
    void *choice_object;
    u8 unknown_48[12];
    u32 flags;
};
typedef char ChoiceOffset[(unsigned)&((struct SceneRecoveryFrame *)0)->choice_object==68?1:-1];
typedef char FlagsOffset[(unsigned)&((struct SceneRecoveryFrame *)0)->flags==84?1:-1];
extern u32 gSceneFrameAddress;
extern void ResetSceneChoiceObject(void *object);
__asm__(".global gSceneFrameAddress\n.set gSceneFrameAddress, 0x0200f450");
__asm__(".global ResetSceneChoiceObject\n.thumb_set ResetSceneChoiceObject, 0x08066029");
#define QUEUE_CONTINUATION(frame, next) \
    do { \
        (frame)->selector = (next); \
        (frame)->continuations[(frame)->depth++] = (next); \
    } while (0)

void QueueSceneSelectionRecovery(void);
void QueueSceneSelectionRecovery(void)
{
    u32 *reference = &gSceneFrameAddress;
    struct SceneRecoveryFrame *frame;
    u32 continuation;
    ResetSceneChoiceObject(((struct SceneRecoveryFrame *)*reference)->choice_object);
    frame = (struct SceneRecoveryFrame *)*reference;
    continuation = 48;
    QUEUE_CONTINUATION(frame, continuation);
    continuation = 57;
    QUEUE_CONTINUATION(frame, continuation);
    continuation = 59;
    QUEUE_CONTINUATION(frame, continuation);
    frame->selector = 50;
    frame->flags &= ~64;
}
