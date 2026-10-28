typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 DecodeRecordPayload(void *, const void *);
extern u16 ExpandRecordA(void *, const void *);
extern u16 ExpandRecordB(void *, const void *);
asm(".thumb_set DecodeRecordPayload, 0x0800543D\n"
    ".thumb_set ExpandRecordA, 0x08013F21\n"
    ".thumb_set ExpandRecordB, 0x0801407D\n");
u16 SceneTaskDependency_00013E9C(void *destination, const u8 *bank,
    void *scratch, u16 index, u8 *out_a, u8 *out_b)
{
    register const u16 *index_cell asm("r2") = (const u16 *)bank + index;
    const u8 *entry;
    register const u8 *payload asm("r2");
    register u16 header asm("r1");
    u32 alternate;
    u32 compressed;
    u16 result;
    asm("" : "+r"(index_cell));
    entry = bank + *index_cell;
    if (out_b)
        *out_b = (*(const u16 *)entry & 240) >> 4;
    if (out_a)
        *out_a = 0;
    header = *(const u16 *)entry;
    asm("" : "+r"(header));
    alternate = header & 1;
    compressed = (header & 2) >> 1;
    payload = entry + 2;
    asm("" : "+r"(payload));
    if (compressed) {
        DecodeRecordPayload(scratch, payload);
        payload = scratch;
        asm("" : "+r"(payload));
    }
    if (alternate)
        result = ExpandRecordA(destination, payload);
    else
        result = ExpandRecordB(destination, payload);
    if (!compressed && result > 511)
        result -= 512;
    return result;
}
