typedef unsigned char u8;
typedef unsigned int u32;

u32 FindUnusedMissionRewardUnitSlot_0803600C(void)
{
    volatile u8 *unit_record;
    int unit_slot_index;

    unit_record = (volatile u8 *)0x02000080;
    for (unit_slot_index = 0; unit_slot_index < 24;) {
        if (unit_record[4] == 0) {
            return (u32)unit_record;
        }
        unit_slot_index++;
        unit_record += 264;
    }
    return 0;
}
