typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct BattleUnitPosition {
    u8 preceding_fields[248];
    u8 field_248;
};
struct BattleActorPosition {
    struct BattleUnitPosition *unit;
    u8 before_position[4];
    u16 x_fixed;
    u16 elevation_fixed;
    u16 y_fixed;
    u8 before_field_31[17];
    u8 field_31;
};

typedef char ActorField31OffsetCheck[((u32)&((struct BattleActorPosition *)0)->field_31 == 31) ? 1 : -1];
/* This call sends signed words; the real entry consumes their low bytes. */
extern void CommitActorPosition(struct BattleActorPosition *actor, int x, int y);
__asm__(".global CommitActorPosition\n.thumb_set CommitActorPosition,0x08099e69\n");

void SynchronizeBattleActorPosition(struct BattleActorPosition *actor)
{
    int x = (int)((u32)actor->x_fixed << 19) >> 24;
    int y = (int)((u32)actor->y_fixed << 19) >> 24;
    CommitActorPosition(actor, x, y);
    /* The real commit may replace the unit or update the source byte. */
    actor->unit->field_248 = actor->field_31;
}
