typedef unsigned char u8;
typedef unsigned int u32;

extern u32 HasSceneHandle(u32 handle_id);

/* Opcode 0x04 stores the wildcard handle and reports scene activity. */
u32 SetSceneHandleWildcardAndCheckActivity(volatile u8 *scene_context,
                                            const u8 *command)
{
    (void)command;
    scene_context[7] = 0xff;
    if ((HasSceneHandle(scene_context[7]) << 24) == 0) {
        return 0x110;
    }
    __asm__ volatile ("" ::: "cc");
    return 0x113;
}
