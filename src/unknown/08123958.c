typedef unsigned char u8;
typedef unsigned int u32;

extern void ClearSceneCommandTaskState(void);

/* Opcode 0x58 clears task state through the retail helper at 0x080d37ac. */
u32 ClearSceneCommandTaskStateFromCommand(u32 *scene_context,
                                          const u8 *command)
{
    (void)scene_context;
    (void)command;
    ClearSceneCommandTaskState();
    return 0x117;
}
