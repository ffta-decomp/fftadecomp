typedef unsigned char u8;
typedef unsigned int u32;
struct Record { u8 pad[31]; signed char direction; };
extern void *AllocateTemporary(u32) __asm__("RetailCall_0800a654");
extern void FreeTemporary(void *) __asm__("RetailCall_0800a668");
extern u32 CollectBattleRecords(u32, struct Record **, void *) __asm__("RetailCall_080dcd08");
extern void ApplyRecordDirection(struct Record *, int) __asm__("RetailCall_080de278");
void RestoreBattleRecordDirections(u8 selector, struct Record *excluded, void *filter) __asm__("RemainingBand43_000DE2D0");
void RestoreBattleRecordDirections(u8 selector, struct Record *excluded, void *filter)
{
    struct Record **records = AllocateTemporary(96);
    u8 count = CollectBattleRecords(selector, records, filter);
    u8 index;
    for (index = 0; index < count; index++) {
        if (excluded && records[index] == excluded)
            continue;
        ApplyRecordDirection(records[index], records[index]->direction);
    }
    FreeTemporary(records);
}

/* Original Thumb call-site identities; aliases emit no instructions. */
__asm__(".global RetailCall_0800a654\n.thumb_set RetailCall_0800a654, 0x800a655");
__asm__(".global RetailCall_0800a668\n.thumb_set RetailCall_0800a668, 0x800a669");
__asm__(".global RetailCall_080dcd08\n.thumb_set RetailCall_080dcd08, 0x80dcd09");
__asm__(".global RetailCall_080de278\n.thumb_set RetailCall_080de278, 0x80de279");
