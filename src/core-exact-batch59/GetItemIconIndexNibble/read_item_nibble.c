typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct __attribute__((packed)) ItemNibbleRow {
    u8 packed_nibbles;
    u8 unknown_01;
};
struct ItemNibbleTable {
    u8 unknown_prefix[4];
    struct ItemNibbleRow rows[1];
};
typedef char ItemNibbleRowMustBeTwoBytes[sizeof(struct ItemNibbleRow) == 2 ? 1 : -1];
extern const struct ItemNibbleTable gItemNibbleTable;

u32 ReadItemCategoryHighNibble(u16 item_id)
{
    const u8 *table_bytes = (const u8 *)&gItemNibbleTable;
    u32 byte_offset = (u32)item_id * sizeof(struct ItemNibbleRow);
    byte_offset += sizeof(gItemNibbleTable.unknown_prefix);
    return table_bytes[byte_offset] >> 4;
}

asm(".global gItemNibbleTable\n.set gItemNibbleTable,0x083c7fe4\n");
