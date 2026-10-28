typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 ReadSaveByte(u16 index);

/* Opcode 0x6e advances the counter when save byte 13 equals one. */
u32 AdvanceSceneCounterWhenSaveFlagSet(u16 *scene_counter, const u8 *command)
{
    if (ReadSaveByte(13) == 1) {
        u16 delta = command[1] | (command[2] << 8);
        *scene_counter = (u16)(*scene_counter + delta);
    }
    return 0x110;
}
