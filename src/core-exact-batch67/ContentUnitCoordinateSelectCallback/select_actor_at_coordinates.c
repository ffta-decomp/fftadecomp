typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Only the coordinate prefix is accessed; this is not a complete unit layout. */
struct UnitCoordinateView { u8 unknown_00[246]; u8 x, y; };
struct BattleActorRecord { struct UnitCoordinateView *unit; };
struct CoordinateSearch {
    u32 unaccessed_word;
    s8 x, y;
    u16 unaccessed_padding;
    struct BattleActorRecord *found;
};
extern u32 ReadListOwnerPayloadWord(const void *list_node);
int ContentUnitCoordinateSelectCallback(void *list_node,
                                        struct CoordinateSearch *search)
{
    struct BattleActorRecord *record =
        (struct BattleActorRecord *)ReadListOwnerPayloadWord(list_node);
    int requested_x = search->x;
    struct UnitCoordinateView *unit = record->unit;
    if (requested_x == unit->x && search->y == unit->y) {
        search->found = record;
        return 0;
    }
    return 1;
}
asm(".global ReadListOwnerPayloadWord\n.thumb_set ReadListOwnerPayloadWord,0x080C7B75\n");
