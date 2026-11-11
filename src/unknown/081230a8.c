typedef unsigned char u8;
typedef unsigned int u32;

extern void ProcessSceneCommandFields(u32 first, u32 second, u32 third,
                                      u32 fourth);

/* Opcode 0x2b passes four command bytes to the shared field processor. */
u32 ProcessSceneCommandFieldsFromCommand(u32 *scene_context,
                                         const u8 *command)
{
    (void)scene_context;
    ProcessSceneCommandFields(command[1], command[2], command[3], command[4]);
    return 0x110;
}

/* Retail stores a zero halfword after the function for four-byte alignment. */
__asm__(".hword 0");
