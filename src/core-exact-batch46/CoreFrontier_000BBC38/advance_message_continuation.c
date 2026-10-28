typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct MessageContinuation {
    u8 *node;
    void *message;
    u16 message_id;
    u16 unknown0a;
    u16 state;
    u16 depth;
    u16 continuations[0];
};
extern u32 RetailCall_080bd130(u32 mode);
extern void RetailCall_080d376c(void);
extern u32 RetailCall_080d37f8(void);
extern u32 RetailCall_080d39b0(void);
extern void *RetailCall_080d3508(u32 id, u32 mode, u32 payload);
extern u32 RetailCall_080d3878(void *message);
extern void RetailCall_080d3864(void *message);
extern void RetailCall_080d37ac(void);
extern u32 RetailCall_080d37c4(void);
extern void RetailCall_0809836c(void *node, u32 operation, s32 value, u32 extra);

u8 AdvanceBattleMessageContinuation(struct MessageContinuation *context)
{
    switch (context->state) {
    case 0:
        if ((u8)RetailCall_080bd130(0) == 0) {
            RetailCall_080d376c();
            context->state = 1;
        }
        break;
    case 1:
        if ((u8)RetailCall_080d37f8() == 0)
            break;
        if ((u8)RetailCall_080d39b0() == 0)
            break;
        goto pop_continuation;
    case 3:
        context->message = RetailCall_080d3508(342, 0, 1);
        context->state = 5;
        break;
    case 4:
        if ((u8)RetailCall_080bd130(1) == 0) {
            context->message = RetailCall_080d3508(343, 0, 1);
            context->state = 5;
        }
        break;
    case 2:
        context->message = RetailCall_080d3508(context->message_id, 0,
                                              (u32)context->node);
        context->state = 5;
        break;
    case 5:
        if ((u8)RetailCall_080d3878(context->message)) {
            RetailCall_080d3864(context->message);
            context->message = 0;
            goto pop_continuation;
        }
        break;
    case 6:
        RetailCall_080d37ac();
        context->state = 7;
        break;
    case 7:
        if ((u8)RetailCall_080d37c4() == 0)
            break;
        {
            u8 *node = context->node;
            RetailCall_0809836c(node, 0, (s8)node[31], 0);
        }
pop_continuation:
        context->state = context->continuations[--context->depth];
        break;
    case 8:
        return 0;
    }
    return 1;
}
