typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
/* Minimum accessed payload prefix, not its allocation size. */
struct BattleCoordinatePayload {
    u8 unknown_00[8];
    s16 fixed_x;
    u16 unknown_0a;
    s16 fixed_y;
};
struct BattleCoordinateSearch {
    u32 unknown_00;
    s8 x;
    s8 y;
    u16 unknown_06;
    struct BattleCoordinatePayload *found;
};
extern struct BattleCoordinatePayload *GetCoordinateNodePayload(void *node);
int SelectBattlePayloadAtCoordinates(void *node, struct BattleCoordinateSearch *search)
{
    struct BattleCoordinatePayload *payload;
    payload = GetCoordinateNodePayload(node);
    if (search->x == (payload->fixed_x >> 5) &&
        search->y == (payload->fixed_y >> 5)) {
        search->found = payload;
        return 0;
    }
    return 1;
}
asm(".global GetCoordinateNodePayload\n.thumb_set GetCoordinateNodePayload,0x080c7b75\n");
