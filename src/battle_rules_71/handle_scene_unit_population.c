/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ScenePopulationContext { u8 unknown_00[160]; u16 placement_bank; u16 unit_bank; };
typedef char UnitBankOffsetCheck[(unsigned)&((struct ScenePopulationContext *)0)->unit_bank == 162 ? 1 : -1];
extern const struct ScenePopulationContext gScenePopulationContext;
extern void PopulateSceneUnitsAtUniquePositions(u16 unit_bank, u16 placement_bank);
extern void PopulateSceneUnitBank(u16 bank);
extern u16 ReadCurrentContentIndex(void);
extern u8 ReadSaveByte(u16 index);
__asm__(".global gScenePopulationContext\n.set gScenePopulationContext, 0x020020d0");
__asm__(".global PopulateSceneUnitsAtUniquePositions\n.thumb_set PopulateSceneUnitsAtUniquePositions, 0x08124bb5");
__asm__(".global PopulateSceneUnitBank\n.thumb_set PopulateSceneUnitBank, 0x081256d5");
__asm__(".global ReadCurrentContentIndex\n.thumb_set ReadCurrentContentIndex, 0x0800a019");
__asm__(".global ReadSaveByte\n.thumb_set ReadSaveByte, 0x080c95a9");

u32 HandleSceneUnitPopulation(void *unused_state, const u8 *unused_command);
u32 HandleSceneUnitPopulation(void *unused_state, const u8 *unused_command)
{
    u8 progression_mode;
    u32 result;
    if (gScenePopulationContext.unit_bank != 0)
        PopulateSceneUnitsAtUniquePositions(gScenePopulationContext.unit_bank, gScenePopulationContext.placement_bank);
    else
        PopulateSceneUnitBank(ReadCurrentContentIndex());
    progression_mode = ReadSaveByte(13);
    result = 0x110;
    if (progression_mode == 1)
        result += 10;
    return result;
}
