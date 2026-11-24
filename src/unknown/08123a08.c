typedef unsigned char u8;
typedef unsigned int u32;

extern void QueueSceneAction44WithByte(void *scene_context, u32 value);

/* Opcode 0x5f forwards command byte 1 to its scene-state helper. */
u32 ApplySceneByte5F(void *scene_context, const u8 *command)
{
    QueueSceneAction44WithByte(scene_context, command[1]);
    return 0x115;
}
