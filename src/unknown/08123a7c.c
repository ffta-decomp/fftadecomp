typedef unsigned char u8;
typedef unsigned int u32;

extern void ResetSceneViewState(void *scene_context, const u8 *command);

/* Opcode 0x63 invokes the observed scene-view reset. */
u32 ResetSceneViewFromCommand(void *scene_context, const u8 *command)
{
    ResetSceneViewState(scene_context, command);
    return 0x114;
}
