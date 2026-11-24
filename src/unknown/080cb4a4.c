typedef unsigned char u8;
typedef unsigned int u32;
/* Mission properties 42/44/53 use zero as no item and the other byte values
 * as the contiguous item-ID range beginning at 376. */
u32 DecodeRecordByte(u32 encoded_item)
{
    u32 item_byte=(u8)encoded_item;
    u32 result;
    if (item_byte != 0)
        result=item_byte+375;
    else
        result=0;
    return result;
}
