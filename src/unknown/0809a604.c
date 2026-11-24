typedef unsigned char u8;
typedef signed int s32;
struct BattleQueryContext;
extern s32 QueryBattleCoordinateCandidates(struct BattleQueryContext *, u8, u8,
                                           u8, void *);
__asm__(".global QueryBattleCoordinateCandidates\n.thumb_set QueryBattleCoordinateCandidates, 0x080989ad");

/* The existing query owns the selector rules and all candidate writes. */
s32 CollectBattleCoordinateCandidates(struct BattleQueryContext *context,
                                      u8 first_coordinate, u8 second_coordinate,
                                      u8 selector, void *candidates)
    __asm__("CoreFrontier_0009A604");
s32 CollectBattleCoordinateCandidates(struct BattleQueryContext *context,
                                      u8 first_coordinate, u8 second_coordinate,
                                      u8 selector, void *candidates)
{
    return QueryBattleCoordinateCandidates(context, first_coordinate,
                                           second_coordinate, selector,
                                           candidates);
}
