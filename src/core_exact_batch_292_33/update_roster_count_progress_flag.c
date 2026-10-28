typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ResidentUnitRecord {
    u8 prefix[4];
    u8 definition_tag;
    u8 remainder[259];
};
struct UnitSavePrefix {
    u8 header[128];
    struct ResidentUnitRecord units[24];
};
extern struct UnitSavePrefix gSaveData;
extern void SetGameFlag(u16 flag, u16 value);
typedef char unit_record_stride_check[sizeof(struct ResidentUnitRecord) == 264 ? 1 : -1];


/* Count the24 resident record tags before updating progression flag0x5a7. */
void UpdateRosterCountProgressFlag(void) __asm__("CoreGlobal36_000D2F2C");
void UpdateRosterCountProgressFlag(void)
{
    s32 count = 0;
    register u8 *save_base __asm__("r0") = (u8 *)&gSaveData;
    register u8 *tag __asm__("r2");
    register u32 record_stride __asm__("r4");
    register s32 remaining __asm__("r1");

    /* Consume the actual initialized native base, then add the observed tag offset. */
    asm("" : "+r"(save_base));
    tag = save_base + 132;
    asm("" : "+r"(tag));
    record_stride = sizeof(struct ResidentUnitRecord);
    asm("" : "+r"(record_stride));
    remaining = 23;
    asm("" : "+r"(remaining));

    do {
        if (*tag != 0)
            ++count;
        tag += record_stride;
        --remaining;
    } while (remaining >= 0);
    if (count > 5)
        SetGameFlag(0x5a7, 0);
    else
        SetGameFlag(0x5a7, 1);
}
