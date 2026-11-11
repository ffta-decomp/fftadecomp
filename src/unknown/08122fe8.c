typedef unsigned char u8;
typedef unsigned int u32;

extern void ProcessSceneCommandByte(u32 value, u32 mode, u32 options);

/* Opcode 0x23 forwards its byte operand with the observed (1, 0) mode pair. */
u32 ProcessSceneCommandByteWithMode(u32 *scene_context, const u8 *command)
{
    (void)scene_context;
    ProcessSceneCommandByte(command[1], 1, 0);
    return 0x100;
}
