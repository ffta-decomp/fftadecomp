typedef unsigned char u8;
typedef unsigned int u32;

extern u8 gSaveData[];
extern u8 ResolveSceneSelectorByte(u32 command_value);
extern void ApplyResolvedSceneSelector(u32 selector);

/* Opcode 0x1e stores a resolved selector, clears an observed save-image
 * byte, then passes the reloaded selector to the second retail helper. */
u32 ResolveSceneSelectorFromCommand(void *scene_context, const u8 *command)
{
    u8 selector;

    (void)scene_context;
    selector = ResolveSceneSelectorByte(command[1]);
    gSaveData[0x1f69] = selector;
    gSaveData[0x3c2b] = 0;
    ApplyResolvedSceneSelector(*(volatile u8 *)&gSaveData[0x1f69]);
    return 0x110;
}
