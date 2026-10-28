typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void RetailCall_0804018c(void *record);
void RetailCall_080401f4(void *record, u32 doubled_field);

void CoreRegion_00040264(u32 incoming_r0, u8 *record)
{
    u16 field26;
    u16 doubled_field;

    RetailCall_0804018c(record);
    field26 = *(u16 *)(record + 26);
    doubled_field = (u16)(field26 << 1);
    RetailCall_080401f4(record, (u32)doubled_field);
}

asm(".global RetailCall_0804018c\n.thumb_set RetailCall_0804018c,0x0804018d\n"
    ".global RetailCall_080401f4\n.thumb_set RetailCall_080401f4,0x080401f5\n");
