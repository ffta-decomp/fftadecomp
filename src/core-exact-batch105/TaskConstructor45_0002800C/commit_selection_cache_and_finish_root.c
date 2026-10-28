typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct TaskNode;
struct CachedSelection {
    u16 choice;
    u16 option;
};
struct ManagedSelectionView {
    s16 result;
    u8 ready;
    u8 cache_active;
    u8 unknown_04[0x444 - 4];
    struct CachedSelection cached[0];
};
struct SelectionPayloadView {
    struct TaskNode *node;
    struct TaskNode *parent;
    u8 cache_slot;
    u8 unknown_09[73];
    u16 choice;
    u8 unknown_84[21];
    u8 option;
    u8 unknown_106[42];
    void *work_buffer0;
    void *work_buffer1;
    void *work_buffer2;
    void *work_buffer3;
};
extern struct ManagedSelectionView *gManagedSelection;
extern void FreeCurrentTaskGroupAllocation_08005B40(void *allocation);
__asm__(".global gManagedSelection\n.set gManagedSelection,0x0200f438\n.global FreeCurrentTaskGroupAllocation_08005B40\n.thumb_set FreeCurrentTaskGroupAllocation_08005B40,0x08005b41");
typedef char work_buffer_offset_check[(u32)&((struct SelectionPayloadView *)0)->work_buffer0 == 148 ? 1 : -1];
typedef char choice_offset_check[(u32)&((struct SelectionPayloadView *)0)->choice == 82 ? 1 : -1];
typedef char option_offset_check[(u32)&((struct SelectionPayloadView *)0)->option == 105 ? 1 : -1];
void CommitSelectionCacheAndFinishRoot(struct SelectionPayloadView *payload) __asm__("TaskConstructor45_0002800C");
void CommitSelectionCacheAndFinishRoot(struct SelectionPayloadView *payload)
{
    /* Each pointer is read after the preceding free; the slots are not cleared. */
    if (payload->work_buffer0 != 0)
        FreeCurrentTaskGroupAllocation_08005B40(payload->work_buffer0);
    if (payload->work_buffer1 != 0)
        FreeCurrentTaskGroupAllocation_08005B40(payload->work_buffer1);
    if (payload->work_buffer2 != 0)
        FreeCurrentTaskGroupAllocation_08005B40(payload->work_buffer2);
    if (payload->work_buffer3 != 0)
        FreeCurrentTaskGroupAllocation_08005B40(payload->work_buffer3);
    {
        register struct ManagedSelectionView **selection_slot __asm__("r1") = &gManagedSelection;
        u32 cache_offset;
        struct ManagedSelectionView *selection;
        struct CachedSelection *cached;
        /* Retain the cell address before indexing, but read its pointer later. */
        __asm__("" : "+r"(selection_slot));
        cache_offset = (u32)payload->cache_slot * 4 + 0x444;
        selection = *selection_slot;
        cached = (struct CachedSelection *)((u8 *)selection + cache_offset);
        cached->choice = payload->choice;
        cached->option = payload->option;
        if (payload->parent == 0)
            selection->ready = 1;
    }
}
