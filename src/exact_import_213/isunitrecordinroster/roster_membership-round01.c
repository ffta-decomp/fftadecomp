typedef unsigned char u8;
typedef unsigned int u32;
struct RosterRecord { u8 bytes[264]; };
typedef char RosterRecordStride[(sizeof(struct RosterRecord) == 264) ? 1 : -1];
u32 IsUnitRecordInRoster(const void *unit)
{
    int index = 0;
    const struct RosterRecord *record = (const struct RosterRecord *)0x02000080;
    for (; index <= 23; ++record, ++index) {
        if (record == unit)
            return 1;
    }
    return 0;
}
