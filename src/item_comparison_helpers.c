typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 GetItemProperty(u16 item_id, u8 property);

int CompareUnsignedBytes(const void *left_value, const void *right_value)
{
    return *(const u8 *)left_value - *(const u8 *)right_value;
}

int CompareUnsignedHalfwords(const void *left_value, const void *right_value)
{
    return *(const u16 *)left_value - *(const u16 *)right_value;
}

u8 ItemProperty07Bit1(u16 item_id)
{
    return (GetItemProperty(item_id, 7) >> 1) & 1;
}
