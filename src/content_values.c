typedef unsigned char u8;
typedef unsigned short u16;

/* The 40-byte record stride and pointer at +0x1c are established by the
 * retail loads. The record extent and field identities remain provisional. */
struct ContentRecord {
    u8 unknown_at_00[28];
    const u8 *values;
    u8 unknown_at_20[8];
};

extern u8 GetGameFlag(u16 flag);
extern u16 ReadCurrentContentIndex(void);
extern const struct ContentRecord gContentRecords[];
extern u8 gContentState[];

u8 ReadContentValue0(void)
{
    if (GetGameFlag(0x253)) {
        return gContentState[0xa6];
    } else {
        u16 index = ReadCurrentContentIndex();
        const struct ContentRecord *record = &gContentRecords[index];
        return record->values[0];
    }
}

u8 ReadContentValue1(void)
{
    if (GetGameFlag(0x253)) {
        return gContentState[0xa7];
    } else {
        u16 index = ReadCurrentContentIndex();
        const struct ContentRecord *record = &gContentRecords[index];
        return record->values[1];
    }
}
