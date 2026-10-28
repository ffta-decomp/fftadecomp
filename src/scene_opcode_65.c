typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* The indexed flag accessor returns the same one-byte boolean as GetGameFlag. */
extern u8 IsIndexedSceneFlagSet(u32 flag_index);

/* Opcode 0x65 adds a command delta when the selected scene flag is set. */
u32 AddSceneContextDeltaWhenFlagIsSet(u16 *scene_context,
                                      const u8 *command)
{
    u32 flag_index = (u32)command[1] | ((u32)command[2] << 8);

    if (IsIndexedSceneFlagSet(flag_index) != 0) {
        u16 delta = (u16)(command[3] | ((u16)command[4] << 8));
        scene_context[0] = (u16)(scene_context[0] + delta);
    }
    return 0x110;
}
