typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ProcessSceneCommandWithMode(u32 *scene_context,
                                        const u8 *command,
                                        u32 mode);
extern u8 gSceneRuntimeBase[];

/*
 * The retail handler checks a global scene halfword before dispatching this
 * command. The field's higher-level meaning is not yet established.
 */
u32 ProcessSceneCommandWhenStateAllows(u32 *scene_context, const u8 *command)
{
    u8 *runtime_base = gSceneRuntimeBase;
    volatile u16 *scene_runtime_state;

    /* Retain the base-plus-offset load used by the retail Thumb routine. */
    __asm__ volatile("" : "+r" (runtime_base));
    scene_runtime_state = (volatile u16 *)(runtime_base + 0x96);

    if (*scene_runtime_state == 3)
        return 0x110;

    ProcessSceneCommandWithMode(scene_context, command, 0);
    return 0x115;
}
