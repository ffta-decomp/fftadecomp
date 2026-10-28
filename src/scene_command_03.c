typedef unsigned char u8;
typedef unsigned int u32;

extern u32 HasSceneHandle(u32 handle_id);

/* Opcode 0x03 selects a handle and reports whether it is active. */
u32 SelectSceneHandleFromCommand(volatile u8 *scene_context,
                                 const u8 *command)
{
    scene_context[7] = command[1];
    if ((HasSceneHandle(scene_context[7]) << 24) == 0) {
        return 0x110;
    }
    return 0x113;
}
