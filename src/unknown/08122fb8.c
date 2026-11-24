typedef unsigned char u8;
typedef unsigned int u32;

extern void ApplySceneCommandBytePair(u32 selector, u32 value);

/* Opcode 0x21 forwards its two argument bytes to an observed scene helper. */
u32 ApplySceneBytePairFromCommand(void *scene_context, const u8 *command)
{
    u32 selector = command[1];
    u32 value = command[2];

    (void)scene_context;
    ApplySceneCommandBytePair(selector, value);
    return 0x110;
}
