typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

/* Identity only: neither candidate address nor the unit is dereferenced. */
u32 UnitIsInContextSlots(const void *context, const void *unit)
{
    s32 index = 0;
    const u8 *slot = (const u8 *)context + 64;
    for (; index < 2; ++index) {
        if (slot == unit)
            return 1;
        slot += 264;
    }
    return 0;
}
