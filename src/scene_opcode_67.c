typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 gSaveData[];

/* Opcode 0x67 adds a delta while the content counter exceeds its threshold. */
u32 AdvanceSceneCounterBeforeContentLimit(u16 *scene_counter,
                                          const u8 *command)
{
    register const volatile u8 *ram_base __asm__("r0") = gSaveData;
    register u32 content_counter_offset __asm__("r1") = 0x21b4;

    /* Retail forms the content-counter address from two ROM constants. */
    __asm__ volatile("" : "+r"(ram_base), "+r"(content_counter_offset));
    if (ram_base[content_counter_offset] > command[1]) {
        u16 delta = command[2] | (command[3] << 8);
        *scene_counter = (u16)(*scene_counter + delta);
    }
    return 0x110;
}
