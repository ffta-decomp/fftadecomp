typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleUnitCategoryPair { u16 first; u16 second; };
typedef char pair_size4[(sizeof(struct BattleUnitCategoryPair)==4)?1:-1];
typedef char second_offset2[((u32)&(((struct BattleUnitCategoryPair *)0)->second)==2)?1:-1];
extern const struct BattleUnitCategoryPair gBattleUnitCategoryPairs[];
__asm__(".global gBattleUnitCategoryPairs\n.set gBattleUnitCategoryPairs,0x083a84a4");
/* Both callers use the two output halfwords; the incidentalR0 is not a return. */
void ReadBattleUnitCategoryPair(u8 selector, u16 *first, u16 *second)
    asm("BattleStateDependency_0012F194");
void ReadBattleUnitCategoryPair(u8 selector, u16 *first, u16 *second)
{
    const struct BattleUnitCategoryPair *table;
    const struct BattleUnitCategoryPair *pair;
    table = gBattleUnitCategoryPairs;
    pair = &table[selector];
    *first = pair->first;
    *second = pair->second;
}
