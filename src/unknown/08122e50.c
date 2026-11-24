typedef unsigned char u8;
typedef unsigned int u32;

extern void SetSceneRuntimeControlByte(u32 value);
extern void HandleSceneRuntimeModeFour(void);
extern void HandleSceneRuntimeModeEight(void);

/* The two mode-specific helper effects still need a wider call-site survey. */
u32 SelectSceneRuntimeModeFromCommand(u32 *scene_context, const u8 *command)
{
    (void)scene_context;
    SetSceneRuntimeControlByte(command[1]);
    if (command[1] == 4)
        goto handle_mode_four;
    if (command[1] == 8)
        HandleSceneRuntimeModeEight();
    goto finish;

handle_mode_four:
    HandleSceneRuntimeModeFour();
finish:
    return 0x11d;
}
