typedef unsigned char u8;
typedef unsigned int u32;

extern void ProcessSceneCommandValue(u32 value);

/* Opcode 0x2a forwards its first byte operand to the shared scene routine. */
u32 ProcessSceneCommandValueFromCommand(u32 *scene_context,
                                        const u8 *command)
{
    (void)scene_context;
    ProcessSceneCommandValue(command[1]);
    return 0x110;
}
