typedef unsigned char u8;
typedef unsigned int u32;

extern void QueueSceneAction44(void *scene_context);

/* Opcode 0x5e queues scene action 0x44 for the current context. */
u32 ProcessSceneState5E(void *scene_context, const u8 *command)
{
    (void)command;
    QueueSceneAction44(scene_context);
    return 0x115;
}
