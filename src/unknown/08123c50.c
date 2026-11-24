typedef unsigned char u8;
typedef unsigned int u32;

/* Opcode 0x6b has no observed side effect. */
u32 ContinueSceneCounterCommand(void *scene_context, const u8 *command)
{
    (void)scene_context;
    (void)command;
    return 0x110;
}
