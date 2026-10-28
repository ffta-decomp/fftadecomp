typedef unsigned char u8;
typedef unsigned int u32;

extern u8 gSaveData[];

/* Opcode 0x1d copies command byte 1 into two adjacent save-image fields. */
u32 SetSceneBytePairFromCommand(void *scene_context, const u8 *command)
{
    u8 *save_base;
    u32 first_offset;
    u32 first_value;
    u8 *first_destination;
    u8 *second_destination;
    u32 second_offset;
    u32 second_value;

    (void)scene_context;
    save_base = gSaveData;
    first_value = command[1];
    first_offset = 0x2190;
    first_destination = save_base + first_offset;
    *(volatile u8 *)first_destination = first_value;
    second_value = command[1];
    second_offset = 0x2191;
    second_destination = save_base + second_offset;
    *(volatile u8 *)second_destination = second_value;
    return 0x110;
}
