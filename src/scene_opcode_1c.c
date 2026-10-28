typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 gSaveData[];

/* Opcode 0x1c appends one command halfword to an observed save-image queue.
 * The byte count wraps after 255; the previous count selects the slot. */
u32 AppendSceneHalfwordFromCommand(void *scene_context, const u8 *command)
{
    u32 value;
    u8 *save_base;
    volatile u8 *queue_count;
    u32 previous_count;
    u32 next_count;
    u32 entry_offset;
    u32 table_offset;
    u8 *table;
    u8 *entry;

    (void)scene_context;
    value = command[1] | (command[2] << 8);
    save_base = gSaveData;
    queue_count = (volatile u8 *)(save_base + 0x219c);
    previous_count = *queue_count;
    next_count = previous_count + 1;
    *queue_count = next_count;
    /* Keep the retail byte-narrowing operation before the slot address. */
    __asm__ volatile("" : "+r"(previous_count));
    entry_offset = (u8)previous_count << 1;
    table_offset = 0x2194;
    table = save_base + table_offset;
    entry_offset += (u32)table;
    entry = (u8 *)entry_offset;
    *(volatile u16 *)entry = value;
    return 0x110;
}
