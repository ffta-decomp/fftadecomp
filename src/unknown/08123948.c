typedef unsigned char u8;
typedef unsigned int u32;

extern void StartSceneCommandTask(void);

/* Opcode 0x57 starts the scene task through the retail helper at 0x080d376c. */
u32 StartSceneCommandTaskFromCommand(u32 *scene_context, const u8 *command)
{
    (void)scene_context;
    (void)command;
    StartSceneCommandTask();
    return 0x116;
}

/* Retail stores a zero halfword after this function for four-byte alignment. */
__asm__(".hword 0");
