typedef unsigned char u8;
typedef unsigned int u32;

extern u32 ReadUnitField(const u8 *unit, u8 selector);
extern u32 GetJobProperty(u8 job, u8 fallback, u8 property);

u32 FindJobMatchingUnitProperty12(const u8 *unit)
{
    int first = 2;
    int last = 115;
    int current;

    switch (ReadUnitField(unit, 3)) {
    case 1: first = 2; last = 12; break;
    case 2: first = 13; last = 19; break;
    case 3: first = 20; last = 27; break;
    case 4: first = 28; last = 35; break;
    case 5: first = 36; last = 43; break;
    }

    current = first;
    while (current <= last) {
        if ((u32)(current - 80) > 2 && current != 85) {
            u8 recorded_value = unit[54];
            u8 job = (u8)current;
            if (recorded_value == GetJobProperty(job, job, 12))
                return job;
        }
        current++;
    }
    if (ReadUnitField(unit, 3) == 1) {
        u8 recorded_value = unit[54];
        if (recorded_value == GetJobProperty(77, 77, 12))
            return 77;
    }
    return 0;
}
