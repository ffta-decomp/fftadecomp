typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void CreateSceneActionRecord(u32 *scene_context, u32 record_index,
                                    u32 record_argument, u32 record_mode);

/* Opcode 0x27 forwards its three raw operands to the scene-action builder. */
u32 CreateSceneActionFromCommand(u32 *scene_context, const u8 *command)
{
    u8 record_index = command[1];
    u16 record_argument = (u16)(command[2] | ((u16)command[3] << 8));
    u8 record_mode = command[4];

    CreateSceneActionRecord(scene_context, record_index, record_argument,
                            record_mode);
    return 0x115;
}
