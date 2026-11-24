/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct BattleRecordView { u8 *unit; u8 unknown04[124]; void *context; };
extern u32 RetailCall_080c95a8(u32);
extern u32 RetailCall_0809aa10(const struct BattleRecordView *);
extern u32 RetailCall_08133bc4(const u8 *);
extern struct BattleRecordView *RetailCall_080970e8(void *,const u8 *);
asm(".global RetailCall_080c95a8\n.thumb_set RetailCall_080c95a8,0x080c95a9\n.global RetailCall_0809aa10\n.thumb_set RetailCall_0809aa10,0x0809aa11\n.global RetailCall_08133bc4\n.thumb_set RetailCall_08133bc4,0x08133bc5\n.global RetailCall_080970e8\n.thumb_set RetailCall_080970e8,0x080970e9");

u32 RecordPassesRelatedUnitRule(struct BattleRecordView *record)
{
    struct BattleRecordView *candidate;
    if (!(u8)RetailCall_080c95a8(13) || (u8)RetailCall_0809aa10(record))
        goto rejected;
    if ((u8)RetailCall_08133bc4(record->unit))
        goto accepted;
    candidate=RetailCall_080970e8(record->context,record->unit);
    if (candidate != 0) {
        if ((u8)RetailCall_0809aa10(candidate))
            goto rejected;
        goto accepted;
    } else {
        if ((*(u8 *)0x030028a0 & 8))
            goto accepted;
    }
rejected:
    return 0;
accepted:
    return 1;
}
