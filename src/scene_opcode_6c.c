typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void *ResolveSceneCommandHandle(u32 handle);
extern u8 SceneCommandRecordBlocksUpdateB(const void *unit);
extern u8 UnitStateE8HasBit6(const void *unit);
extern u8 UnitStateE9HasBit0(const void *unit);
extern u8 UnitStateE9HasBit3(const void *unit);
extern u8 UnitStateE9HasBit4(const void *unit);

/* Opcode 0x6c advances the counter only when all five gates are clear. */
u32 AdvanceSceneCounterForAvailableUnit(u16 *scene_counter, const u8 *command)
{
    const void *unit = ResolveSceneCommandHandle(command[1]);

    if (unit != 0) {
        /* The retail call reloads r0 from the saved unit pointer. */
        __asm__ volatile("" ::: "r0");
        if (SceneCommandRecordBlocksUpdateB(unit) == 0 &&
            UnitStateE8HasBit6(unit) == 0 &&
            UnitStateE9HasBit0(unit) == 0 &&
            UnitStateE9HasBit3(unit) == 0 &&
            UnitStateE9HasBit4(unit) == 0) {
            u16 delta = command[2] | (command[3] << 8);
            *scene_counter = (u16)(*scene_counter + delta);
        }
    }
    return 0x110;
}
