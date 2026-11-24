typedef unsigned char u8;
typedef unsigned short u16;

/* The low identity bit survives both mode-dependent byte5 updates. */
void ApplyAuxiliaryMissionRecordState(u8 *record, u16 mode)
{
    record[2] |= 64;
    record[3] |= 128;
    if (mode != 0)
        record[5] = (record[5] & 1) | 200;
    else
        record[5] &= 1;
}
