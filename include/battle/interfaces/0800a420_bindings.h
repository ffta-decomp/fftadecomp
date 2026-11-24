typedef unsigned char u8;typedef unsigned short u16;
struct NestedScript {u16 unknown,pc;};
struct Unit {u8 before_counter[257];u8 counter;};
struct Actor {struct Unit *unit;};
extern void *NActorContext(void);extern int NCollectActors(void*,struct Actor**);extern int NUnitHasStatusBit12(const struct Unit*);
asm(".global NActorContext\n.thumb_set NActorContext,0x08096d7d\n.global NCollectActors\n.thumb_set NCollectActors,0x08099cdd\n.global NUnitHasStatusBit12\n.thumb_set NUnitHasStatusBit12,0x080c8299");
