typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct BattleObject;
struct ListOwner;
struct UnitKindView { u8 unknown0[4]; u8 kind; };
struct BattleRegistry { u8 unknown0[16]; struct ListOwner *records; u8 unknown20[16]; u32 flags; };
struct BattleActorView {
    struct UnitKindView *unit;
    u8 unknown4[4];
    u16 x;
    s16 y;
    u16 z;
    u16 x_offset;
    u16 z_offset;
    u8 unknown18[30];
    u32 flags;
    u8 unknown52[2];
    u16 state;
    u8 unknown56[28];
    struct BattleObject *primary_object;
    struct BattleObject *secondary_object;
    u8 unknown92[36];
    struct BattleRegistry *registry;
};
struct CoordinateSearch {
    u32 unaccessed_word;
    s8 x, y;
    u16 unaccessed_padding;
    struct BattleActorView *found;
};
typedef void (*ObjectWordCallback)(struct BattleObject *, s32);
typedef u32 (*NodeVisitor)(void *, void *);
extern void UpdateObjectCoordinates(struct BattleObject *, s32, s32, s32);
extern s32 ReadAdmissibleBattleCell(s32, s32);
extern void VisitBattleRecords(struct ListOwner *, NodeVisitor, void *);
extern u32 SelectActorAtCoordinates(void *, void *);
__asm__(".global UpdateObjectCoordinates\n.thumb_set UpdateObjectCoordinates,0x0808efcd\n.global ReadAdmissibleBattleCell\n.thumb_set ReadAdmissibleBattleCell,0x0809d79d\n.global VisitBattleRecords\n.thumb_set VisitBattleRecords,0x080c7cc1\n.global SelectActorAtCoordinates\n.thumb_set SelectActorAtCoordinates,0x0809abb1\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
typedef char registry_offset_check[(u32)&((struct BattleActorView *)0)->registry==128?1:-1];
/* Keep the observed first halfword load out of combine's commuted PLUSmem.
 * The initialized HI operand constraint emits no instructions. */
#define READ_COORD_OFFSET(field) ({ u16 offset_value = (field); __asm__("" : "+r"(offset_value)); offset_value; })
/* Original post-callback X operand occupies R5 while R2 becomes signed Y. */
#define READ_POST_X(field) ({ register u32 post_x __asm__("r5"); \
    __asm__("ldrh %0,%1" : "=l"(post_x) : "m"(field)); post_x; })
/* Preserve the original signed-cell extraction and distinct live reloads. */
u32 UpdateBattleActorObjects(struct BattleActorView *, struct BattleRegistry *)
    __asm__("CoreClosure31_00097F04");
u32 UpdateBattleActorObjects(struct BattleActorView *input, struct BattleRegistry *registry)
{
    register struct BattleActorView *actor __asm__("r4") = input;
    u32 flags;
    u32 secondary_gate;
    u32 kind;
    u32 state;
    s32 cell_value;
    s32 actor_y;
    s32 found_y;
    struct CoordinateSearch search;
    register struct BattleActorView *found __asm__("r0");
    u32 query_x;
    u32 query_y;
    struct BattleRegistry *search_registry;
    __asm__("" : "+r"(actor));
    flags = actor->flags;
    if (flags & 1)
        goto done;
    if ((flags & 0x20000) && (registry->flags & 64))
        goto done;
    UpdateObjectCoordinates(actor->primary_object,
                            (s16)(READ_COORD_OFFSET(actor->x_offset) + actor->x), actor->y,
                            (s16)(READ_COORD_OFFSET(actor->z_offset) + actor->z));
    secondary_gate = actor->flags & 0x8000;
    if (secondary_gate)
        goto done;
    kind = actor->unit->kind;
    if (kind == 31) goto done;
    if (kind == 64) goto done;
    if (kind == 65) goto done;
    if (kind == 66) goto done;
    if (kind == 67) goto done;
    if (kind == 68) goto done;
    if (kind == 69) goto done;
    if (kind == 70) goto done;
    state = actor->state;
    if (state == 0) goto done;
    if (state == 12) goto done;
    if (state == 16) goto done;
    if (state == 128) goto done;
    cell_value = ReadAdmissibleBattleCell((s32)((u32)actor->x << 19) >> 24,
                                         (s32)((u32)actor->z << 19) >> 24);
    query_x = actor->x >> 5;
    query_y = actor->z >> 5;
    search_registry = actor->registry;
    /* This branch carries the zero gate value; do not initialize unused words. */
    search.found = (struct BattleActorView *)secondary_gate;
    search.x = query_x;
    search.y = query_y;
    VisitBattleRecords(search_registry->records, SelectActorAtCoordinates, &search);
    /* Actual initialized query result read; SI memory operand carries the
     * compiler's real SP8 address, not a hard-coded stack offset. */
    __asm__("ldr %0,%1" : "=l"(found) : "m"(search.found));
    if (found != 0 && found != actor) {
        actor_y = actor->y;
        found_y = found->y;
        found_y += 48;
        if (actor_y > found_y)
            cell_value = found_y >> 4;
    }
    if (actor->flags & 4)
        goto done;
    (*(const ObjectWordCallback *)0x08394040)(actor->secondary_object, -2);
    UpdateObjectCoordinates(actor->secondary_object,
                            (s16)(READ_COORD_OFFSET(actor->x_offset) + READ_POST_X(actor->x)),
                            (s16)((u32)cell_value << 4),
                            (s16)(READ_COORD_OFFSET(actor->z_offset) + actor->z));
done:
    return 1;
}
