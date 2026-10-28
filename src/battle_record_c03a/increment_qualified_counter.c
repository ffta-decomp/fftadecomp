/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct Actor { void *unit; } Actor;
typedef struct BattleCounterMemory { u8 unknown0[0x3c9e]; u8 ordinary_count; u8 reserved_count; } BattleCounterMemory;
extern BattleCounterMemory BattleCounters;
extern u8 ReadSaveByte(u16);
extern s32 UnitField27HasBit15(const void *);
extern u32 ActorUsesFirstTwoRecords(Actor *);
__asm__(".global BattleCounters\n.set BattleCounters,0x02000000");
__asm__(".global ActorUsesFirstTwoRecords\n.thumb_set ActorUsesFirstTwoRecords,0x0809aa11");
#define OFF(T,F) ((u32)&(((T *)0)->F))
typedef char counter_offset[OFF(BattleCounterMemory,ordinary_count)==0x3c9e?1:-1];

static inline void IncrementCounterByte(u32 offset)
{
    u8 *counter=(u8 *)&BattleCounters+offset;
    s32 value=*counter+1;
    if(value>99) value=99;
    *counter=value;
}
void IncrementQualifiedBattleCounter(Actor *,Actor *);
void IncrementQualifiedBattleCounter(Actor *actor,Actor *affected)
{
    if((u8)ReadSaveByte(13)==0) return;
    if((u8)UnitField27HasBit15(affected->unit)==0) return;
    if((u8)ActorUsesFirstTwoRecords(actor)) IncrementCounterByte(0x3c9f);
    else IncrementCounterByte(0x3c9e);
}
