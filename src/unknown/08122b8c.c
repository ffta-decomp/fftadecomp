typedef unsigned char u8;
typedef unsigned int u32;

extern u32 ReleaseSceneHandle(u32 handle);

/* Opcode 0x02 releases and clears the scene handle stored at context +8. */
u32 ReleaseSceneContextHandle(u32 *scene_context, const u8 *command)
{
    (void)command;
    ReleaseSceneHandle(scene_context[2]);
    scene_context[2] = 0;
    return 0x11e;
}
