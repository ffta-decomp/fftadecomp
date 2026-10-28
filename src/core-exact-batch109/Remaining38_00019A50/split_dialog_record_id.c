typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct DialogRecordRange {
    u8 bank;
    u8 unknown_01;
    u16 first;
    u16 last;
    u16 unknown_06;
};
extern const struct DialogRecordRange DialogRecordRanges[];
__asm__(".global DialogRecordRanges\n.set DialogRecordRanges,0x0836da1c");
/* Failure leaves both output objects untouched. The first output is a byte,
 * and its store precedes the range-base reload and halfword output store. */
void SplitDialogRecordId(u32 raw_id, u8 *bank, u16 *record)
{
    u16 id = (u16)raw_id;
    const struct DialogRecordRange *range = DialogRecordRanges;
    int index = 0;
    do {
        if (range->first <= id && id <= range->last) {
            *bank = range->bank;
            *record = id - range->first;
            break;
        }
        ++index;
        ++range;
    } while (index <= 10);
}
