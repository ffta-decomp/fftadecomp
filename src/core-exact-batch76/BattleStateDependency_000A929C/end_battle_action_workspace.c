typedef unsigned char u8;
struct BattleActionWorkspace {
    void *allocation_pool;
    void *source_context;
    void *owned_list;
    void *list_entry;
    u8 unaccessed_16[60];
    void *transient_allocation;
    void *records;
    u8 unaccessed_84[1416];
    u8 active;
};
typedef char BattleActionWorkspaceSize[(sizeof(struct BattleActionWorkspace) == 1504) ? 1 : -1];
extern struct BattleActionWorkspace gBattleActionWorkspace;
extern void ReleaseWorkspaceAllocation(void *pool, void *allocation);
extern void RemoveWorkspaceListEntry(void *list, void *entry);
extern void DestroyWorkspaceList(void *list);
extern void ClearWorkspaceRecordList(void *records);
extern void FreeWorkspaceRecordTree(void *records);
extern void DestroyWorkspaceRecordContainer(void *records);
extern void NotifyWorkspaceOwner(void);
void EndBattleActionWorkspace(void)
{
    struct BattleActionWorkspace *workspace = &gBattleActionWorkspace;
    ReleaseWorkspaceAllocation(workspace->allocation_pool, workspace->transient_allocation);
    workspace->transient_allocation = 0;
    workspace->active = 0;
    RemoveWorkspaceListEntry(workspace->owned_list, workspace->list_entry);
    DestroyWorkspaceList(workspace->owned_list);
    ClearWorkspaceRecordList(workspace->records);
    FreeWorkspaceRecordTree(workspace->records);
    DestroyWorkspaceRecordContainer(workspace->records);
    NotifyWorkspaceOwner();
}
asm(".global gBattleActionWorkspace\n.set gBattleActionWorkspace,0x0200F9E8\n"
    ".global ReleaseWorkspaceAllocation\n.thumb_set ReleaseWorkspaceAllocation,0x08007171\n"
    ".global RemoveWorkspaceListEntry\n.thumb_set RemoveWorkspaceListEntry,0x08021bd5\n"
    ".global DestroyWorkspaceList\n.thumb_set DestroyWorkspaceList,0x08021b55\n"
    ".global ClearWorkspaceRecordList\n.thumb_set ClearWorkspaceRecordList,0x080c79b5\n"
    ".global FreeWorkspaceRecordTree\n.thumb_set FreeWorkspaceRecordTree,0x080c79e1\n"
    ".global DestroyWorkspaceRecordContainer\n.thumb_set DestroyWorkspaceRecordContainer,0x080c7909\n"
    ".global NotifyWorkspaceOwner\n.thumb_set NotifyWorkspaceOwner,0x0802d715\n"
);
