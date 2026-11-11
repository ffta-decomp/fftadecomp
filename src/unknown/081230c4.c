typedef unsigned char u8;
typedef unsigned int u32;

extern void ApplySceneCommandByteTriple(u32 selector, u32 operand,
                                        u32 value);

/* Opcode 0x2c forwards its three argument bytes to an observed scene helper. */
u32 ApplySceneByteTripleFromCommand(void *scene_context, const u8 *command)
{
    u32 selector = command[1];
    u32 operand = command[2];
    u32 value = command[3];

    (void)scene_context;
    ApplySceneCommandByteTriple(selector, operand, value);
    return 0x110;
}
