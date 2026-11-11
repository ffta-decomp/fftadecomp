/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct GlobalUnitState { u8 prefix[40]; u16 status; u8 middle[0x3ba4-42]; unsigned flags; };
extern struct GlobalUnitState globalUnitState;
extern u8 UnitField27HasBit5(void *unit);
extern u8 UnitField27HasBit8(void *unit);
extern void CoreMutationDependency_00009AFC(unsigned event);
asm(".global globalUnitState\n.set globalUnitState,0x02000080\n.global CoreMutationDependency_00009AFC\n.thumb_set CoreMutationDependency_00009AFC,0x08009afd\n");
asm(".global UnitField27HasBit5\n.thumb_set UnitField27HasBit5,0x080c8349\n.global UnitField27HasBit8\n.thumb_set UnitField27HasBit8,0x080c8365\n");

int TrySetGlobalUnitStateFlag(void)
{
    if ((globalUnitState.status & 129) &&
        (UnitField27HasBit5(&globalUnitState) || UnitField27HasBit8(&globalUnitState))) {
        CoreMutationDependency_00009AFC(170);
        globalUnitState.flags |= 4;
        return 1;
    }
    return 0;
}
