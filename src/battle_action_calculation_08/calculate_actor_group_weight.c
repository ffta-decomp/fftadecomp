/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef int s32;
struct Unit { u8 unknown00[246]; u8 x; u8 y; };
struct Actor { struct Unit *unit; };
struct ActorGroups { struct Actor *excluded; u32 unknown04; struct Actor **subtract_group; struct Actor **add_group; u16 subtract_count; u16 add_count; };
typedef char AssertGroupAddOffset[((u32)&((struct ActorGroups *)0)->add_group==12)?1:-1];
typedef char AssertGroupCounts[((u32)&((struct ActorGroups *)0)->add_count==18)?1:-1];
typedef char AssertUnitCoordinates[((u32)&((struct Unit *)0)->x==246)?1:-1];
extern s32 UnitField19IsZero(const void *unit);

/* Opposing actor lists contribute signed coordinate weights with halfword wrapping. */
s32 CalculateActorGroupCoordinateWeight(struct ActorGroups *groups, u8 x, u8 y)
{
    u16 score = 0;
    s32 index;
    for (index = 0; index < groups->add_count; index++) {
        struct Actor *actor = groups->add_group[index];
        if (actor != groups->excluded && (u8)UnitField19IsZero(actor->unit) == 0) {
            struct Unit *unit = actor->unit;
            s32 vertical = unit->y - y;
            s32 horizontal;
            s32 weighted;
            s32 signed_score;
            s32 contribution;
            if (vertical < 0) vertical = -vertical;
            weighted = vertical + 32;
            horizontal = unit->x - x;
            if (horizontal < 0) horizontal = -horizontal;
            contribution = weighted - horizontal;
            signed_score = (s16)score;
            score = signed_score + contribution;
        }
    }
    for (index = 0; index < groups->subtract_count; index++) {
        struct Actor *actor = groups->subtract_group[index];
        if (actor != groups->excluded && (u8)UnitField19IsZero(actor->unit) == 0) {
            struct Unit *unit = actor->unit;
            s32 vertical = unit->y - y;
            s32 horizontal;
            s32 weighted;
            s32 signed_score;
            s32 contribution;
            if (vertical < 0) vertical = -vertical;
            weighted = vertical + 32;
            horizontal = unit->x - x;
            if (horizontal < 0) horizontal = -horizontal;
            contribution = weighted - horizontal;
            signed_score = (s16)score;
            score = signed_score - contribution;
        }
    }
    return (s16)score;
}
