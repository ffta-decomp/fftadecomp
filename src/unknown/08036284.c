typedef unsigned char u8;
typedef unsigned int u32;

/* Search the 30 twelve-byte records beginning at table offset 0xb0.
 * The record key is byte +3, but the caller's selector is compared as a
 * full word, so values above 255 cannot match. The meaning of the prefix
 * and the key is not yet established by natural scene execution. */
void *FindSceneRecordById(u32 selector, void *table)
{
    register u32 index __asm__("r2") = 0;
    u8 *record = (u8 *)table + 0xb0;

    /* Keep the retail initialization order without emitting an instruction. */
    __asm__ volatile ("" : "+r" (index));
    for (;;) {
        if (record[3] != selector) {
            record += 12;
            ++index;
            if ((int)index <= 29)
                continue;
            return 0;
        }
        return record;
    }
}
