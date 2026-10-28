typedef unsigned char u8;
typedef unsigned int u32;

extern void ProcessSceneCommandWithMode(void *scene_context,
                                        const u8 *command, u32 mode);

/* Opcode 0x07 starts a scene command with no operand and mode 1. */
u32 ProcessSceneCommandWithDefaultMode(void *scene_context, const u8 *command)
{
    (void)command;
    ProcessSceneCommandWithMode(scene_context, 0, 1);
    return 0x115;
}
