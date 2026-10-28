typedef unsigned char InitU8;
typedef unsigned short InitU16;
typedef unsigned int InitU32;

/* Clear the two initialized fields in four records with a 12-byte stride.
 * The other bytes in each record are left untouched.
 */
void InitializeFourRecordHeaders(void *storage)
{
    volatile InitU8 *record = (volatile InitU8 *)storage;
    register InitU32 cleared_value asm("r2") = 0;
    register int remaining asm("r1") = 3;

    do {
        *(volatile InitU32 *)record = cleared_value;
        *(volatile InitU16 *)(record + 4) = (InitU16)cleared_value;
        record += 12;
        --remaining;
    } while (remaining >= 0);
}
