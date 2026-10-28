typedef unsigned int u32;
struct ListNode;
struct ListContainer { void *pool; struct ListNode *head; void *tree; };
typedef char ContainerSize12[sizeof(struct ListContainer) == 12 ? 1 : -1];
typedef char HeadAt4[(u32)&((struct ListContainer *)0)->head == 4 ? 1 : -1];
typedef char TreeAt8[(u32)&((struct ListContainer *)0)->tree == 8 ? 1 : -1];
extern void *AllocateListContainer(void *pool, u32 size);
__asm__(".global AllocateListContainer\n.thumb_set AllocateListContainer,0x08007139");
/* Retain the original successful-allocation precondition. */
struct ListContainer *ContainerCreate(void *pool)
{
    struct ListContainer *container = AllocateListContainer(pool, 12);
    container->pool = pool;
    container->head = 0;
    container->tree = 0;
    return container;
}
