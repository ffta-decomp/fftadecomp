typedef unsigned char u8;
/* The table role is not yet established. Only its observed 30-by-12 layout
 * and the tested byte-1 bit predicate are named here. */
#define STATUS_RECORD_TABLE ((const u8 *)0x02002cc0)

u8 CountStatusRecordsWithBits0And1(void)
{
    int count = 0;
    u8 bit_0 = 1;
    const u8 *record = STATUS_RECORD_TABLE;
    u8 bit_1 = 2;
    int index = 29;
    u8 flags;

    while (index >= 0) {
        flags = record[1];
        if ((bit_0 & flags) != 0) {
            /* Keep the second mask in r0 and preserve flags in r1, as in
             * the retail loop. This constraint emits no instructions. */
            register int matched_bit_1 __asm__("r0") = bit_1;
            matched_bit_1 &= flags;
            if (matched_bit_1 != 0)
                count++;
        }
        record += 12;
        index--;
    }
    return count;
}
