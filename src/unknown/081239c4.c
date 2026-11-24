typedef unsigned char u8;
typedef unsigned int u32;

extern void QueueSceneActionB0WithWord(void *scene_context, u32 value);

/* Opcode 0x5c forwards its little-endian 16-bit operand. */
u32 ApplySceneWordFromCommand(void *scene_context, const u8 *command)
{
    u32 value = command[1] | (command[2] << 8);
    QueueSceneActionB0WithWord(scene_context, value);
    return 0x110;
}
