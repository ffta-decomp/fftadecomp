typedef unsigned char u8;
typedef unsigned int u32;

/* Opcode 0x14 has no observed side effect and returns the dispatch code. */
u32 ContinueSceneCommand(void *scene_context, const u8 *command)
{
    (void)scene_context;
    (void)command;
    return 0x115;
}
