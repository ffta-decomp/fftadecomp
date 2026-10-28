typedef unsigned char u8;
typedef unsigned int u32;
struct BattleTargetListCount {
    u8 preceding_fields[704];
    u8 count;
};

typedef char TargetCountOffsetCheck[((u32)&((struct BattleTargetListCount *)0)->count == 704) ? 1 : -1];
void SetBattleTargetRowCount(struct BattleTargetListCount *list, u32 count)
    __asm__("CoreRegion30_000A8800");

/* Native storage truncates to the count byte; no row capacity is inferred. */
void SetBattleTargetRowCount(struct BattleTargetListCount *list, u32 count)
{
    list->count = count;
}
