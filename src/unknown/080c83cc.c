typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

enum {
    UNIT_POOL_RECORD_ID_OFFSET = 4,
    UNIT_POOL_RECORD_STRIDE = 0x108,
    UNIT_POOL_A_COUNT = 12,
    UNIT_POOL_B_COUNT = 24
};

extern u8 gUnitPoolA[];
extern u8 gUnitPoolB[];

/* Search the two observed unit pools in retail priority order. */
u8 *FindUnitPoolRecordById(u32 requested_id)
{
    register u8 *record __asm__("r1");
    u8 unit_id = (u8)requested_id;
    register s32 slot __asm__("r2");
    /* Retail holds each pool limit in r4 while scanning with a signed compare. */
    register s32 slot_limit __asm__("r4");

    /* Keep the retail search's shared found and not-found exits explicit. */
    if (unit_id > 1)
        goto search_pool_a;
    goto not_found;

found_record:
    return record;

search_pool_a:
    record = gUnitPoolA;
    slot_limit = UNIT_POOL_A_COUNT;
    slot = 0;
    do {
        if (record[UNIT_POOL_RECORD_ID_OFFSET] == unit_id)
            goto found_record;
        ++slot;
        record += UNIT_POOL_RECORD_STRIDE;
    } while (slot < slot_limit);

    record = gUnitPoolB;
    slot_limit = UNIT_POOL_B_COUNT;
    slot = 0;
    do {
        if (record[UNIT_POOL_RECORD_ID_OFFSET] == unit_id)
            goto found_record;
        ++slot;
        record += UNIT_POOL_RECORD_STRIDE;
    } while (slot < slot_limit);

not_found:
    return 0;
}
