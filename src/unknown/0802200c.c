typedef unsigned char u8;
typedef unsigned int u32;
struct StorageHandle { void *storage; };
struct BattlePooledNode {
    u32 unknown_0000;
    void *owned_allocation;
    u8 unknown_0008[16];
    struct StorageHandle *handle;
};
extern void FreePooledAllocation(void *storage,void *allocation);
asm(".global FreePooledAllocation\n.thumb_set FreePooledAllocation,0x08007171");
void ReleaseBattlePooledNode(struct BattlePooledNode *node)
{
    FreePooledAllocation(node->handle->storage,node->owned_allocation);
    FreePooledAllocation(node->handle->storage,node);
}
