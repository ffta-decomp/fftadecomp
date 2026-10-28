typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct BattleContext { u8 unknown_00[16]; void *primary_actors; };
struct CoordinateSearch {
    u32 unaccessed_word;
    s8 x, y;
    u16 unaccessed_padding;
    void *found;
};
extern void WalkActorList(void *, void *, struct CoordinateSearch *);
asm(".global WalkActorList\n.thumb_set WalkActorList,0x080c7cc1");

void *FindBattleActorAtRecordPosition(struct BattleContext *context, s32 x, s32 y)
{
    struct CoordinateSearch search;
    search.found = 0;
    search.x = x;
    search.y = y;
    WalkActorList(context->primary_actors, (void *)0x0809ab7d, &search);
    return search.found;
}
