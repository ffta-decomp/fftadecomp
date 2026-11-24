#include "ffta/unsigned_types.h"
typedef signed int s32;
struct TreeNode;
struct ListNode;
struct Container { void *pool; struct ListNode *head; struct TreeNode *root; };
struct Owner { void *pool; u32 unknown4; struct Container *container; u16 lower, upper, alternate_lower, alternate_upper; };
struct Record { u16 preceding[9]; u16 order; u16 previous_order; };
struct Iterator { u16 lower, upper; struct Record **array, **cursor; u32 unknown12; s32 count; u32 unknown20; struct Owner *owner; };
struct SelectionContext { struct Iterator *iterator; struct Container *container; };
typedef u32 (*SelectionVisitor)(struct ListNode *, struct SelectionContext *);
typedef void (*MemoryClear)(void *, u32);
typedef char IteratorSize28[sizeof(struct Iterator) == 28 ? 1 : -1];
typedef char OwnerAt24[(u32)&((struct Iterator *)0)->owner == 24 ? 1 : -1];
extern void ClearSelectionTree(struct Container *);
extern u32 CountOwnerList(const struct Container *);
extern void *AllocateIteratorMemory(void *, u32);
extern void FreeIteratorMemory(void *, void *);
extern void VisitOwnerList(struct Container *, SelectionVisitor, struct SelectionContext *);
extern u32 SelectRecordForIterator(struct ListNode *, struct SelectionContext *);
extern u32 CountSelectionTree(struct Container *);
extern u32 CollectSelectionTree(struct Container *, struct TreeNode **);
extern void CopyTreeNodeWords(struct TreeNode *, struct Record **, u32 *);
__asm__(".global ClearSelectionTree\n.thumb_set ClearSelectionTree,0x080c79e1\n.global CountOwnerList\n.thumb_set CountOwnerList,0x080c7b09\n.global AllocateIteratorMemory\n.thumb_set AllocateIteratorMemory,0x08007139\n.global FreeIteratorMemory\n.thumb_set FreeIteratorMemory,0x08007171\n.global VisitOwnerList\n.thumb_set VisitOwnerList,0x080c7cc1\n.global SelectRecordForIterator\n.thumb_set SelectRecordForIterator,0x08022165\n.global CountSelectionTree\n.thumb_set CountSelectionTree,0x080c7b21\n.global CollectSelectionTree\n.thumb_set CollectSelectionTree,0x080c7b9d\n.global CopyTreeNodeWords\n.thumb_set CopyTreeNodeWords,0x080c7b79\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
struct Iterator *BuildBattleRecordIterator(struct Owner *entry_owner, u32 alternate)
{
    register struct Owner *entry __asm__("r0") = entry_owner;
    register u32 bounds_mode __asm__("r4") = alternate;
    struct Owner *owner;
    struct Iterator *iterator;
    struct Iterator *result;
    struct SelectionContext selection;
    u32 key;
    register s32 count __asm__("r6");
    s32 index;
    struct Record **cursor;
    /* Preserve both defined incoming values until the original mode snapshot. */
    __asm__("" : "+r" (bounds_mode), "+r" (entry));
    owner = entry;
    ClearSelectionTree(owner->container);
    count = CountOwnerList(owner->container);
    /* Both original count lifetimes occupy r6; retain this defined helper result. */
    __asm__("" : "+r" (count));
    if (count == 0) {
        result = 0;
        goto finished;
    }
    iterator = AllocateIteratorMemory(owner->pool, 28);
    (*(const MemoryClear *)0x0836d4b8)(iterator, 28);
    iterator->owner = owner;
    if (bounds_mode != 0) {
        iterator->lower = owner->alternate_lower;
        iterator->upper = owner->alternate_upper;
    } else {
        iterator->lower = owner->lower;
        iterator->upper = owner->upper;
    }
    selection.iterator = iterator;
    selection.container = owner->container;
    VisitOwnerList(selection.container, SelectRecordForIterator, &selection);
    count = CountSelectionTree(owner->container);
    iterator->count = count;
    if (count <= 0) {
        ClearSelectionTree(owner->container);
        FreeIteratorMemory(owner->pool, iterator);
        result = 0;
        goto finished;
    }
    iterator->array = AllocateIteratorMemory(owner->pool, count * 4);
    CollectSelectionTree(owner->container, (struct TreeNode **)iterator->array);
    for (index = 0; index < count; index++) {
        register struct Record **array __asm__("r0") = iterator->array;
        u32 byte_offset;
        u32 entry_address;
        struct Record **entry;
        /* Original live array base precedes the independent index shift. */
        __asm__("" : "+r" (array));
        byte_offset = (u32)index * 4;
        /* The actual fullword offset becomes the entry address before dereference. */
        entry_address = byte_offset;
        entry_address += (u32)array;
        entry = (struct Record **)entry_address;
        CopyTreeNodeWords((struct TreeNode *)*entry, entry, &key);
    }
    ClearSelectionTree(owner->container);
    iterator->cursor = iterator->array;
    cursor = iterator->array;
    for (index = 0; index < iterator->count; index++) {
        struct Record *record = *cursor++;
        record->previous_order = record->order;
    }
    result = iterator;
finished:
    return result;
}
