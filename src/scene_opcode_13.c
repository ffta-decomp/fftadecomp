typedef unsigned char u8;
typedef unsigned int u32;

extern void ApplySceneCommandContext(void *scene_context, const u8 *command);

/* Opcode 0x13 forwards the scene context and whole command to its helper. */
u32 ApplySceneContextFromCommand(void *scene_context, const u8 *command)
{
    ApplySceneCommandContext(scene_context, command);
    return 0x115;
}
