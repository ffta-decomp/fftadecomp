typedef unsigned char u8;
typedef unsigned int u32;

extern void HandleSceneCommandZero(void);
extern void ResolveSceneHandleValue(u32 value);

/* Opcode 0x22 selects one of two retail routines from command byte +1. */
u32 SelectSceneRoutineFromCommand(u32 *scene_context, const u8 *command)
{
    (void)scene_context;
    if (command[1] == 0) {
        HandleSceneCommandZero();
    } else {
        ResolveSceneHandleValue(command[1]);
    }
    return 0x114;
}
