typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ProcessSceneCommandHandleIndex(u32 handle_index);

/* Opcode 0x5a dispatches the command's one-based handle index. */
u32 ProcessSceneCommandHandleIndexFromCommand(u32 *scene_context,
                                              const u8 *command)
{
    (void)scene_context;
    ProcessSceneCommandHandleIndex((u16)(command[1] - 1));
    return 0x110;
}

/* Retail stores a zero halfword after this function for four-byte alignment. */
__asm__(".hword 0");
