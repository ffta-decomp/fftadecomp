/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneTransactionFrame {
    u16 selector;
    u16 depth;
    u16 continuations[0];
    u8 unknown_04[74];
    u16 message;
    u8 unknown_50[4];
    u32 flags;
};
struct SceneTransactionRoot { u32 unknown_00; u32 unknown_04; u32 transaction_value; };
typedef char SceneMessageOffset[(unsigned)&((struct SceneTransactionFrame *)0)->message==78?1:-1];
typedef char SceneFlagsOffset[(unsigned)&((struct SceneTransactionFrame *)0)->flags==84?1:-1];
typedef char TransactionValueOffset[(unsigned)&((struct SceneTransactionRoot *)0)->transaction_value==8?1:-1];
extern struct SceneTransactionFrame *gSceneFrame;
extern struct SceneTransactionRoot gSceneTransaction;
__asm__(".global gSceneFrame\n.set gSceneFrame, 0x0200f450");
__asm__(".global gSceneTransaction\n.set gSceneTransaction, 0x020020d0");
#define QUEUE_CONTINUATION(frame, next) \
    do { \
        (frame)->selector = (next); \
        (frame)->continuations[(frame)->depth++] = (next); \
    } while (0)

void StageSceneTransactionValue(void);
void StageSceneTransactionValue(void)
{
    struct SceneTransactionFrame *frame;
    u32 continuation;
    u32 queue_offset;
    u8 *queue;
    gSceneTransaction.transaction_value = 5000;
    frame = gSceneFrame;
    frame->flags = (frame->flags | 3) & ~4;
    frame->message = 194;
    continuation = 35;
    frame->selector = continuation;
    queue_offset = (u16)frame->depth++ * 2;
    queue = (u8 *)frame->continuations;
    *(u16 *)(queue + queue_offset) = continuation;
    continuation = 51;
    frame->selector = continuation;
    queue_offset = (u16)frame->depth++ * 2;
    queue += queue_offset;
    *(u16 *)queue = continuation;
    frame->selector = 66;
}
