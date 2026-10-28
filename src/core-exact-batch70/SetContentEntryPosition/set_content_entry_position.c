typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct BattleUnitPosition {
    u8 preceding_fields[246];
    u8 x;
    u8 y;
};
struct BattleActorPosition {
    struct BattleUnitPosition *unit;
    u8 before_position[4];
    u16 x_fixed;
    u16 elevation_fixed;
    u16 y_fixed;
};

typedef char ActorXOffsetCheck[((u32)&((struct BattleActorPosition *)0)->x_fixed == 8) ? 1 : -1];
extern int ReadActorCellValue(struct BattleActorPosition *actor, int x, int y);
__asm__(".global ReadActorCellValue\n.thumb_set ReadActorCellValue,0x08099c1d\n");

void SetContentEntryPosition(struct BattleActorPosition *actor, s8 x, s8 y)
{
    actor->x_fixed = x * 32 + 16;
    actor->y_fixed = y * 32 + 16;
    actor->elevation_fixed = (u32)ReadActorCellValue(actor, x, y) << 4;
    /* The opaque call and each byte store may change the unit pointer. */
    actor->unit->x = (u8)x;
    actor->unit->y = (u8)y;
}
