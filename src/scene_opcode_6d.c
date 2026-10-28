typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 ReadSelectedContentIndex(void);
extern const u8 gContentRecords[];

/* Opcode 0x6d advances the counter for a record with byte +0x22 clear. */
u32 AdvanceSceneCounterWhenContentRecordClear(u16 *scene_counter,
                                              const u8 *command)
{
    u16 record_index = ReadSelectedContentIndex();
    const u8 *record = gContentRecords + (u32)record_index * 40;

    if (record[0x22] == 0) {
        u16 delta = command[1] | (command[2] << 8);
        *scene_counter = (u16)(*scene_counter + delta);
    }
    return 0x110;
}
