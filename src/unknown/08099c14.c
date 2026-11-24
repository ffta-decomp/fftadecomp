typedef unsigned char u8;
typedef unsigned int u32;
struct ContextNode { u8 unknown[30]; u8 state; };
u32 ExchangeContextNodeByte30(struct ContextNode *node,u32 value) __asm__("CoreConsumer_00099C14");
u32 ExchangeContextNodeByte30(struct ContextNode *node,u32 value)
{
    u32 previous = node->state;
    node->state = value;
    return previous;
}
