/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneRollbackFrame {
    u16 selector;
    u16 depth;
    u16 continuations[0];
    u8 unknown_04[74];
    u16 message;
    u8 unknown_50;
    u8 state_51;
    u8 unknown_52[2];
    u32 flags;
    s32 selected_object;
    s32 selection_result;
};
struct RefundState { u8 unknown_0000[0x1f64]; u32 money; };
typedef char MessageOffset[(unsigned)&((struct SceneRollbackFrame *)0)->message==78?1:-1];
typedef char StateOffset[(unsigned)&((struct SceneRollbackFrame *)0)->state_51==81?1:-1];
typedef char FlagsOffset[(unsigned)&((struct SceneRollbackFrame *)0)->flags==84?1:-1];
typedef char ResultOffset[(unsigned)&((struct SceneRollbackFrame *)0)->selection_result==92?1:-1];
/* The observed GBA cell stores a 32-bit address. A word view retains its
 * source-proven alias/reload relationship with the scene's word writes. */
extern u32 gSceneFrameAddress;
extern struct RefundState gRefundState;
__asm__(".global gSceneFrameAddress\n.set gSceneFrameAddress, 0x0200f450");
__asm__(".global gRefundState\n.set gRefundState, 0x02000000");
#define QUEUE_CONTINUATION(frame, next) \
    do { \
        (frame)->selector = (next); \
        (frame)->continuations[(frame)->depth++] = (next); \
    } while (0)

void ResolveSceneSelectionOrRollback(void);
void ResolveSceneSelectionOrRollback(void)
{
    u32 *reference = &gSceneFrameAddress;
    struct SceneRollbackFrame *initial = (struct SceneRollbackFrame *)*reference;
    if (initial->selection_result == -1 || initial->selected_object == -1) {
        struct SceneRollbackFrame *refund;
        struct SceneRollbackFrame *reset;
        u32 continuation;
        u32 first_continuation;
        u16 *queue;
        initial->message = 192;
        initial->state_51 = 16;
        refund = (struct SceneRollbackFrame *)*reference;
        if (refund->flags & 64) {
            gRefundState.money += 5000;
            refund->flags &= ~64;
        }
        reset = (struct SceneRollbackFrame *)*reference;
        first_continuation = 48;
        queue = reset->continuations;
        queue[0] = first_continuation;
        reset->continuations[1] = 57;
        reset->selector = 59;
        reset->depth = 3;
        queue[2] = 59;
        continuation = 52;
        reset->selector = continuation;
        queue += (u16)reset->depth++;
        *queue = continuation;
        reset->selector = 51;
    } else {
        initial->selector = initial->continuations[--initial->depth];
    }
}
