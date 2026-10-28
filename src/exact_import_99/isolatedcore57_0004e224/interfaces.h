typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
union InventoryChoiceSlots {
    u32 words[64];
    u16 halfwords[128];
};
struct InventoryChoiceOwner {
    u8 unknown_prefix[0x424];
    /* Physical extent to the next observed field, not an added runtime bound. */
    union InventoryChoiceSlots slots;
    u32 content_ids[0];
};
struct InventoryChoiceState {
    struct InventoryChoiceOwner *owner;
    u16 unknown_4;
    s16 selection;
    u8 mode;
};
typedef char InventoryChoiceSlotSize[(sizeof(union InventoryChoiceSlots) == 0x100) ? 1 : -1];
typedef char InventoryChoiceSlotsOffset[((u32)&((struct InventoryChoiceOwner*)0)->slots == 0x424) ? 1 : -1];
typedef char InventoryChoiceContentOffset[((u32)&((struct InventoryChoiceOwner*)0)->content_ids == 0x524) ? 1 : -1];
typedef char InventoryChoiceSelectionOffset[((u32)&((struct InventoryChoiceState*)0)->selection == 6) ? 1 : -1];
typedef char InventoryChoiceModeOffset[((u32)&((struct InventoryChoiceState*)0)->mode == 8) ? 1 : -1];
extern struct InventoryChoiceState *GetInventoryChoiceState(void *task);
extern const u16 gInventoryFixedContentIds[];
__asm__(".global GetInventoryChoiceState\n.thumb_set GetInventoryChoiceState,0x08005bfd\n.global gInventoryFixedContentIds\n.set gInventoryFixedContentIds,0x08529ee4");
