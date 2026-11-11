typedef unsigned char u8;
typedef unsigned int u32;

extern u32 GetJobProperty(u8 job_id, u8 fallback_job_id, u8 selector);
extern u32 GetUnitProperty(const u8 *unit, u8 selector);
extern const void *const gAbilityLists[];

/* Unit offsets and selector meanings are retained until their owning models are recovered. */
const void *SelectUnitAbilityList(const u8 *unit, u8 slot,
                                  u8 *first_out, u8 *second_out)
{
    u32 selected = 0;
    u32 list_index = 0;
    u8 second = 0;
    u8 first = 0;

    switch (slot) {
    case 1:
        first = GetUnitProperty(unit, 37);
        second = GetUnitProperty(unit, 38);
        selected = unit[0x35];
        list_index = unit[6];
        break;
    case 2:
        first = GetJobProperty(unit[8], unit[8], 37);
        second = GetJobProperty(unit[8], unit[8], 38);
        selected = unit[0x36];
        list_index = unit[6];
        break;
    case 3:
        first = GetJobProperty(1, 1, 37);
        second = GetJobProperty(1, 1, 38);
        selected = unit[0x37];
        break;
    }
    if (slot != 3 && selected == 1) {
        first = GetJobProperty(1, 1, 37);
        second = GetJobProperty(1, 1, 38);
        list_index = 0;
    }
    if (first_out)
        *first_out = first;
    if (second_out)
        *second_out = second;
    return gAbilityLists[list_index];
}
