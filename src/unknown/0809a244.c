typedef unsigned int u32;
struct ContextNode { u32 unknown[9]; u32 flags; };
void SetContextNodeFlag16(struct ContextNode *node,u32 enabled) __asm__("sub_0809A244");
void SetContextNodeFlag16(struct ContextNode *node,u32 enabled)
{
    u32 flags = node->flags & ~16u;
    node->flags = flags;
    if (enabled == 0) node->flags = flags | 16;
}
