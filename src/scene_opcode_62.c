typedef unsigned char u8;
typedef unsigned int u32;

extern void QueueSceneAction108(void *scene_context, const u8 *command);

/* Opcode 0x62 queues action 0x108 and returns an alternate code for byte 8. */
u32 QueueSceneAction108FromCommand(void *scene_context, const u8 *command)
{
    QueueSceneAction108(scene_context, command);
    return command[8] ? 0x115 : 0x110;
}
