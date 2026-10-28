#ifndef RECOVERED_POOL_ABI_H
#define RECOVERED_POOL_ABI_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define GET16(address) ((u16)((address)[0] | ((u32)(address)[1] << 8)))
#define PUT16(address, value) do { \
    u32 stored_value = (u32)(value); u8 *stored_address = (address); \
    stored_address[0] = (u8)stored_value; \
    stored_address[1] = (u8)(stored_value >> 8); \
} while (0)
#define NODE_AT(pool, index) ((index) ? (pool) + (u32)(index) * 4U : (u8 *)0)
#define NODE_INDEX(pool, node) ((node) ? (u16)(((u32)(node) - (u32)(pool)) >> 2) : 0U)
enum PoolField { FREE_HEAD=0, FREE_MEDIAN=2, FREE_COUNT=4, CAPACITY_WORDS=6 };
enum NodeField { PHYSICAL_PREVIOUS=0, PHYSICAL_NEXT=2, STATE_TAG=4,
                 SIZE_WORDS=6, FREE_PREVIOUS=8, FREE_NEXT=10 };
enum NodeTag { FREE_TAG=0x7370, ALLOCATED_TAG=0x616c };
extern void (*const gClearMemory)(void *, u32);
extern void FindIndexedTreeNeighbors(void *, u32, u8 **, u8 **);
extern void RecoveredInitializeIndexedTreeFreeHead(void *);
void DetachFreePoolBlock_08006DA0(u8 *, u8 *);
void InsertFreePoolBlock_08006E28(u8 *, u8 *);
u8 *AllocatePoolBlockWords_08006EC0(u8 *, u32);
void CoalesceReleasedPoolBlock_08006FCC(u8 *, u8 *);
u8 *InitializePool_080070C8(u8 *, u32);
void *Allocate_08007138(void *, u32);
void Free_08007170(void *, void *);
u32 GetPoolAllocationSize_0800717C(u32, const u8 *);
#endif
