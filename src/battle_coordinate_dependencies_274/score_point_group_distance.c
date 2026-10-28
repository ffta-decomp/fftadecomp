typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
struct UnitPosition { u8 unknown_00[246]; u8 x; u8 y; };
struct BattleOwner { struct UnitPosition *unit; };
struct GroupRecord { struct BattleOwner *owner; u8 unknown_04[804]; };
struct GroupSet { struct GroupRecord records[13]; u16 count; };
struct PointPlanner {
    struct BattleOwner *owner;
    u32 unknown_04[2];
    struct GroupSet *groups[2];
    u8 unknown_20[20];
    u8 positive_first_group;
};
typedef char GroupStride[sizeof(struct GroupRecord)==808?1:-1];
/* Each side contributes a signed inverse Manhattan-distance score. */
s32 ScoreBattlePointByGroupDistance(struct PointPlanner *planner, u8 x, u8 y)
{
    u32 total = 0;
    s8 side = 0;
    do {
        register s32 current_side __asm__("r4") = side;
        struct GroupSet *group;
        s8 index;
        register s32 count __asm__("r1");
        /* The source keeps the signed side live before reading this group. */
        __asm__("" : "+r" (current_side));
        group = planner->groups[current_side];
        index = 0;
        count = group->count;
        /* R1 is the real initial count snapshot, before its later R6 copy. */
        __asm__("" : "+r" (count));
        if (index < (s32)count) {
            s32 query_x = (s8)x;
            s32 query_y = (s8)y;
            struct BattleOwner *owner = planner->owner;
            register s32 limit __asm__("r6") = count;
            /* The retail snapshot is copied into R6 after the owner capture. */
            __asm__("" : "+r" (limit));
            do {
                struct BattleOwner *other = group->records[index].owner;
                if (other != owner) {
                    struct UnitPosition *unit = other->unit;
                    s32 dx = unit->x - query_x;
                    s32 dy;
                    s32 score;
                    if (dx < 0)
                        dx = -dx;
                    dy = unit->y - query_y;
                    if (dy < 0)
                        dy = -dy;
                    score = 32 - (dx + dy);
                    if (planner->positive_first_group) {
                        if (current_side != 0)
                            score = -score;
                    } else {
                        if (current_side == 0)
                            score = -score;
                    }
                    total += score;
                }
                index = (s8)(index + 1);
            } while (index < limit);
        }
        side = (s8)(side + 1);
    } while (side <= 1);
    return total;
}
