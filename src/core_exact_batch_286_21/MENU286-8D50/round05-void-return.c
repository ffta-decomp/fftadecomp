typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void RetailCall_08142250(u8 *destination, u32 source_address, u32 count, u32 source_word);
void RetailCall_08017424(u32 first, u32 second, u32 third, u32 fourth,
                         u32 stack4, u32 stack5, u32 stack6, u32 stack7,
                         u32 stack8, u32 stack9, u32 stack10, u32 stack11);
void RetailCall_08013b7c(u8 *first, u8 *second, u32 third);
void RetailCall_08016c90(u8 *record, u32 selected_byte);
u32 RetailCall_080098f4(u32 callback, u32 argument);
extern u8 Menu286_8D50_UnknownBase[];

void CoreFrontier_00008D50(void)
{
    u32 *root_slot = (u32 *)0x02009188u;
    u8 *record_root = (u8 *)*root_slot;
    u8 *record_a = record_root + 0x2b4u;
    u8 *record_b = record_root + 0x2c4u;
    const u32 *source_word_base = (const u32 *)0x0836d4bcu;
    const u8 *copy_source = (const u8 *)0x0836d4c4u;
    u32 source_word = *source_word_base;

    RetailCall_08142250(record_a, (u32)copy_source, 16u, source_word);

    record_a[2] = (u8)(record_a[2] + 2u);
    record_a[3] = (u8)(((u32)record_a[3] << 1) + 8u);

    {
        u8 *argument_root = (u8 *)*root_slot;
        u32 second = *(u32 *)(*(u32 *)(argument_root + 24u) + 20u);
        u32 third = *(u32 *)(*(u32 *)(argument_root + 28u) + 20u);
        RetailCall_08017424((u32)record_b, second, third, record_a[0],
                            record_a[1], record_a[2], record_a[3],
                            *(u16 *)(record_a + 6u), 32u, 5u, 1u, 12u);
    }

    Menu286_8D50_UnknownBase[174] = (u8)(record_b[19] - 5u);
    RetailCall_08013b7c(record_a, record_b, 0x02003cb0u);
    RetailCall_08016c90(record_b, record_a[8]);

    {
        u32 result = RetailCall_080098f4(0x08008dfdu, 0u);
        u8 *result_root = (u8 *)*root_slot;
        result_root[32] = (u8)result;
    }
}

asm(".global Menu286_8D50_UnknownBase\n.set Menu286_8D50_UnknownBase,0x020020D0\n"
    ".global RetailCall_08142250\n.thumb_set RetailCall_08142250,0x08142251\n"
    ".global RetailCall_08017424\n.thumb_set RetailCall_08017424,0x08017425\n"
    ".global RetailCall_08013b7c\n.thumb_set RetailCall_08013b7c,0x08013b7d\n"
    ".global RetailCall_08016c90\n.thumb_set RetailCall_08016c90,0x08016c91\n"
    ".global RetailCall_080098f4\n.thumb_set RetailCall_080098f4,0x080098f5\n");
