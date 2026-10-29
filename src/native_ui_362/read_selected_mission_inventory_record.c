typedef unsigned char u8;
extern u8 *MissionInventoryContext asm("0x0201f548");
void *ReadSelectedMissionInventoryRecord(void) asm("CoreRegion_0004E9D0");
void *ReadSelectedMissionInventoryRecord(void)
{
    return *(void **)(MissionInventoryContext+16);
}
