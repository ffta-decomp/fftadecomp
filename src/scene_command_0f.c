typedef unsigned char u8;
typedef unsigned int u32;

extern void CreateSceneEventRecord(u32 *scene_context, const u8 *command);

/* Opcode 0x0f asks the scene runtime to create an event from this command. */
u32 CreateSceneEventFromCommand(u32 *scene_context, const u8 *command)
{
    CreateSceneEventRecord(scene_context, command);
    return 0x115;
}
