typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
struct ActorUnit {
    u8 unknown00[231];
    u8 reset_flags;
    u8 unknowne8[14];
    u8 x, y;
    u8 unknownf8[12];
    u8 selector;
};
struct Actor { struct ActorUnit *unit; u32 record_word; };
struct ListOwner;
struct LinkedNode;
struct ActorListContext { u8 unknown00[16]; struct ListOwner *actors; };
struct ActorCollection { s32 count; struct Actor **next; };
typedef u32 (*ActorCallback)(struct Actor *, struct ActorCollection *);
struct WordVisitor { struct ActorCollection *argument; ActorCallback callback; };
typedef u32 (*NodeVisitor)(struct LinkedNode *, const struct WordVisitor *);
extern void VisitActorNodes(const struct ListOwner *, NodeVisitor, struct WordVisitor *);
extern u32 VisitActorNodeWord(struct LinkedNode *, const struct WordVisitor *);
extern u32 AppendActorPointer(struct Actor *, struct ActorCollection *);
asm(".global VisitActorNodes\n.thumb_set VisitActorNodes,0x080c7cc1\n.global VisitActorNodeWord\n.thumb_set VisitActorNodeWord,0x0809abe9\n.global AppendActorPointer\n.thumb_set AppendActorPointer,0x0809ac21");
/* Original pointer-array extent and live node reloads are preserved. */
void OrderBattleActorsByCoordinates(struct ActorListContext *context)
{
    struct Actor *actors[13];
    struct ActorCollection collection;
    struct WordVisitor visitor;
    ActorCallback callback;
    s32 count, last, index;
    collection.count = 0;
    collection.next = actors;
    callback = AppendActorPointer;
    visitor.argument = &collection;
    visitor.callback = callback;
    VisitActorNodes(context->actors, VisitActorNodeWord, &visitor);
    count = collection.count;
    last = count - 1;
    index = 0;
    while (index < last) {
        s32 next = index + 1;
        if (next < count) {
            struct Actor **first_slot = &actors[index];
            u32 second_slot_offset = next * sizeof(actors[0]);
            struct Actor **second_slot = (struct Actor **)(
                second_slot_offset + (u32)actors);
            s32 remaining = count - next;
            do {
                struct Actor *first = *first_slot;
                struct ActorUnit *first_unit = first->unit;
                u32 first_key = ((u32)first_unit->x << 8) + first_unit->y;
                struct Actor *second = *second_slot;
                struct ActorUnit *second_unit = second->unit;
                u32 second_key = ((u32)second_unit->x << 8) + second_unit->y;
                if ((s32)first_key < (s32)second_key) {
                    *first_slot = second;
                    *second_slot = first;
                }
                ++second_slot;
            } while (--remaining != 0);
        }
        index = next;
    }
    index = 0;
    if (index < count) {
        u32 selector_offset = (u32)&((struct ActorUnit *)0)->selector;
        u32 reset_flags = 255;
        struct Actor **cursor = actors;
        do {
            *((u8 *)(*cursor)->unit + selector_offset) = index;
            {
                struct Actor *actor = *cursor++;
                u8 *flags_cell = &actor->unit->reset_flags;
                u32 current_flags = *flags_cell;
                current_flags |= reset_flags;
                *flags_cell = current_flags;
            }
            ++index;
        } while (index < count);
    }
}
