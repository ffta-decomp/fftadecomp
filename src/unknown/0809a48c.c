typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct BattleObject;
struct ListOwner;
struct LinkedNode;
struct BattleObjectSlot {
    struct BattleObject *object;
    s16 x;
    s16 y;
    s16 z;
    u8 flags;
    u8 unknown11;
    u8 descriptor_index;
    u8 unknown13[3];
};
struct BattleRegistry {
    u8 unknown0[16];
    struct ListOwner *records;
    u8 unknown20[16];
    u32 flags;
    u8 unknown40[876];
    struct BattleObjectSlot slots[2];
};
typedef void (*ObjectWordCallback)(struct BattleObject *, u32);
typedef u32 (*RecordCallback)(u32, void *);
typedef u32 (*NodeCallback)(const struct ListOwner *, const void *);
struct RecordVisitContext { void *argument; RecordCallback callback; };
extern void UpdateObjectCoordinates(struct BattleObject *, s32, s32, s32);
extern void VisitBattleRecords(struct ListOwner *, NodeCallback, void *);
extern u32 VisitRecordOwner(const struct ListOwner *, const void *);
extern u32 UpdateBattleRecordObject(u32, void *);
__asm__(".global UpdateObjectCoordinates\n.thumb_set UpdateObjectCoordinates,0x0808efcd\n.global VisitBattleRecords\n.thumb_set VisitBattleRecords,0x080c7cc1\n.global VisitRecordOwner\n.thumb_set VisitRecordOwner,0x0809abe9\n.global UpdateBattleRecordObject\n.thumb_set UpdateBattleRecordObject,0x08097f05");
typedef char slot_size_check[sizeof(struct BattleObjectSlot)==16?1:-1];
typedef char slot_start_check[(u32)&((struct BattleRegistry *)0)->slots==916?1:-1];
/* Reload slot fields after opaque callbacks; they are live shared RAM. */
void UpdateBattleActionObjects(struct BattleRegistry *registry)
{
    const ObjectWordCallback *first_callback = (const ObjectWordCallback *)0x08394038;
    const u32 *descriptors = (const u32 *)0x083915cc;
    struct BattleObjectSlot *slot = registry->slots;
    s32 remaining = 1;
    struct RecordVisitContext visit;
    struct BattleObject *object;
    u32 descriptor_word_index;
    u32 record_update_mask;
    RecordCallback record_callback;
    do {
        if (slot->flags & 1) {
            object = slot->object;
            descriptor_word_index = 2 * slot->descriptor_index + 1;
            /* Original forms the complete word index before byte scaling. */
            __asm__("" : "+r"(descriptor_word_index));
            (*first_callback)(object, descriptors[descriptor_word_index]);
            (*(const ObjectWordCallback *)0x08394040)(slot->object, 1);
            UpdateObjectCoordinates(slot->object, slot->x, slot->y, slot->z);
        }
        ++slot;
        --remaining;
    } while (remaining >= 0);
    record_update_mask = 2;
    __asm__("" : "+r"(record_update_mask));
    if ((registry->flags & record_update_mask) == 0) {
        registry->flags ^= 64;
        record_callback = UpdateBattleRecordObject;
        __asm__("" : "+r"(record_callback));
        visit.argument = registry;
        visit.callback = record_callback;
        VisitBattleRecords(registry->records, VisitRecordOwner, &visit);
    }
}

__asm__(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
