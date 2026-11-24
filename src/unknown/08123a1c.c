typedef unsigned char u8;
typedef unsigned int u32;

extern void QueueSceneAction08(void *scene_context);

/* Opcode 0x60 queues scene action 0x08 for the current context. */
u32 ProcessSceneState60(void *scene_context, const u8 *command)
{
    (void)command;
    QueueSceneAction08(scene_context);
    return 0x115;
}
