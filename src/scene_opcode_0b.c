typedef unsigned char u8;
typedef unsigned int u32;

extern void ApplySceneThreeByteCommand(void *scene_context, u32 first,
                                       u32 second, u32 third);

/* Opcode 0x0b forwards the three one-byte operands to its scene helper. */
u32 ApplySceneThreeBytesFromCommand(void *scene_context, const u8 *command)
{
    u32 first = command[1];
    u32 second = command[2];
    u32 third = command[3];

    ApplySceneThreeByteCommand(scene_context, first, second, third);
    return 0x115;
}
