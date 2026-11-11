typedef unsigned char u8;
typedef unsigned int u32;

extern void ApplySceneCommandValue(void *scene_context, u32 value);

/* Opcode 0x11 passes command byte 1 to the observed scene helper. */
u32 ApplySceneValueFromCommand(void *scene_context, const u8 *command)
{
    ApplySceneCommandValue(scene_context, command[1]);
    return 0x115;
}
