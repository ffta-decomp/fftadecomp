#include "dma_queue.h"
typedef signed int s32;
struct ListContainer;
struct ListNode;
struct TreeNode;
struct Owner;
struct Group;
struct Record;
struct HandleHalfwordView;
struct BattleWorkspaceSlot { u8 unaccessed[44]; };
struct BattleActionWorkspace {
    void *pool;
    struct Owner *owner;
    struct Group *group;
    struct Record *record;
    struct DmaRequest transfer;
    u8 unaccessed_44[30];
    u16 range;
    void *buffer;
    struct ListContainer *slots;
    struct BattleWorkspaceSlot records[32];
    u8 unaccessed_1492[8];
    u8 marker_1500;
    u8 unaccessed_1501[3];
};
typedef char WorkspaceExtent[sizeof(struct BattleActionWorkspace)==1504?1:-1];
typedef char SlotStride[sizeof(struct BattleWorkspaceSlot)==44?1:-1];
typedef char SlotsOffset[(u32)&(((struct BattleActionWorkspace *)0)->records)==84?1:-1];
typedef char RangeOffset[(u32)&(((struct BattleActionWorkspace *)0)->range)==74?1:-1];
typedef char MarkerOffset[(u32)&(((struct BattleActionWorkspace *)0)->marker_1500)==1500?1:-1];
extern void (*const gIWRAMClear)(void *, u32);
extern struct ListContainer *ContainerCreate(void *pool);
extern struct ListNode *AppendListNode(struct ListContainer *, void *value);
extern struct TreeNode *InsertContainerTreeNode(struct ListContainer *, void *payload, s32 key);
extern struct Group *CreateBattleRecordGroup(struct Owner *owner);
extern s32 SelectOwnerRecordRange(struct Owner *, u32 alternate, s32 width);
extern struct Record *CreateBattleGroupRecord(struct Group *);
extern void SetHandleHalfwords(struct HandleHalfwordView *, u16 first, u16 second);
extern void *Allocate_08007138(void *pool, u32 bytes);
extern u32 ReadResourceRecords(const u8 *resource, void *destination, u16 first, u16 limit);
extern const u8 gBattleActionResource[];

void InitializeBattleActionWorkspace(struct BattleActionWorkspace *workspace, void *pool, struct Owner *owner)
{
    s32 ordinal;
    s32 range;
    struct Record *record;
    u16 *range_slot;
    void *buffer;
    gIWRAMClear(workspace, sizeof(struct BattleActionWorkspace));
    workspace->marker_1500 = 1;
    workspace->slots = ContainerCreate(pool);
    ordinal = 0;
register_slot:
    {
        struct ListContainer *slots = workspace->slots;
        struct BattleWorkspaceSlot *slot = &workspace->records[ordinal];
        AppendListNode(slots, slot);
        InsertContainerTreeNode(workspace->slots, slot, ordinal);
    }
    ordinal++;
    if (ordinal <= 31)
        goto register_slot;
    /* Original pool and owner arguments survive the slot-registration callbacks. */
    workspace->pool = pool;
    workspace->owner = owner;
    workspace->group = CreateBattleRecordGroup(owner);
    range = SelectOwnerRecordRange(workspace->owner, 1, 28);
    record = CreateBattleGroupRecord(workspace->group);
    workspace->record = record;
    SetHandleHalfwords((struct HandleHalfwordView *)record, (u16)range, 28);
    range_slot = &workspace->range;
    *range_slot = range;
    buffer = Allocate_08007138(workspace->pool, 0x159c);
    workspace->buffer = buffer;
    ReadResourceRecords(gBattleActionResource, buffer, 0, 0);
    /* Both values are reloaded after resource processing; the range wraps to16bits. */
    QueueDmaCopy32(&workspace->transfer, (u32)workspace->buffer,
                   0x06010000U + ((u32)*range_slot << 5), 80);
}
asm(".global gIWRAMClear\n.set gIWRAMClear,0x0836d4b8\n"
    ".global ContainerCreate\n.thumb_set ContainerCreate,0x080c799d\n"
    ".global AppendListNode\n.thumb_set AppendListNode,0x080c7a75\n"
    ".global InsertContainerTreeNode\n.thumb_set InsertContainerTreeNode,0x080c7ab5\n"
    ".global CreateBattleRecordGroup\n.thumb_set CreateBattleRecordGroup,0x08021b1d\n"
    ".global SelectOwnerRecordRange\n.thumb_set SelectOwnerRecordRange,0x08021c91\n"
    ".global CreateBattleGroupRecord\n.thumb_set CreateBattleGroupRecord,0x08021b9d\n"
    ".global SetHandleHalfwords\n.thumb_set SetHandleHalfwords,0x08021c85\n"
    ".global Allocate_08007138\n.thumb_set Allocate_08007138,0x08007139\n"
    ".global ReadResourceRecords\n.thumb_set ReadResourceRecords,0x08005319\n"
    ".global QueueDmaCopy32\n.thumb_set QueueDmaCopy32,0x08000add\n"
    ".global gBattleActionResource\n.set gBattleActionResource,0x083bc898\n"
    ".global _call_via_r0\n.thumb_set _call_via_r0,0x08142245\n"
    ".global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
    ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n"
    ".global _call_via_r4\n.thumb_set _call_via_r4,0x08142255\n"
    ".global _call_via_r5\n.thumb_set _call_via_r5,0x08142259\n"
    ".global _call_via_r6\n.thumb_set _call_via_r6,0x0814225d\n");
