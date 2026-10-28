typedef unsigned char u8;
typedef unsigned int u32;

extern void CreateSceneCommandActionRecord(u32 *scene_context,
                                           u32 parameter_one,
                                           u32 parameter_two,
                                           u32 parameter_three);

/* Opcode 0x25 forwards three command bytes to the scene-action record builder. */
u32 CreateSceneActionFromParameters(u32 *scene_context, const u8 *command)
{
    u8 parameter_one = command[1];
    u8 parameter_two = command[2];
    u8 parameter_three = command[3];

    CreateSceneCommandActionRecord(scene_context, parameter_one, parameter_two,
                                   parameter_three);
    return 0x115;
}
