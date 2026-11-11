typedef unsigned char u8;typedef unsigned short u16;
struct NestedScript {u16 unknown,pc;};
/* Current/maximum name only their comparative use; the precise unit stat is unproved. */
struct Unit {u8 prefix[4],present,before_value[19];u16 current_value,maximum_value;};
extern struct Unit *NResolveUnit(u8);extern int NUnitHasStatusBit8(const struct Unit*),NUnitHasStatusBit5(const struct Unit*);
asm(".global NResolveUnit\n.thumb_set NResolveUnit,0x08125579\n.global NUnitHasStatusBit8\n.thumb_set NUnitHasStatusBit8,0x080c8365\n.global NUnitHasStatusBit5\n.thumb_set NUnitHasStatusBit5,0x080c8349\n.global __divsi3\n.thumb_set __divsi3,0x081426b9");
