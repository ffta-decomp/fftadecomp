typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void *ResolveSceneCommandHandle(u32 handle);
extern u8 UnitField27HasBit13(const void *unit);
extern u8 UnitField27HasBit15(const void *unit);

/* Opcode 0x64 advances the scene counter for a usable selected unit. */
u32 AdvanceSceneCounterForUsableUnit(u16 *scene_counter, const u8 *command)
{
    const void *unit = ResolveSceneCommandHandle(command[1]);

    if (unit != 0 && UnitField27HasBit13(unit) == 0 &&
        UnitField27HasBit15(unit) == 0) {
        u16 delta = command[2] | (command[3] << 8);
        *scene_counter = (u16)(*scene_counter + delta);
    }
    return 0x110;
}
