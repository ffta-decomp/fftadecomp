typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

extern void ApplySceneCommandModeValue(void *scene_context, u32 mode,
                                       u32 value);

/* Opcode 0x12 splits command byte 1 by its sign bit. The negative path
 * adds 0x80 with byte wrapping and uses mode 1; the other uses mode 2. */
u32 ApplySignedSceneValueFromCommand(void *scene_context, const u8 *command)
{
    u8 value = command[1];

    if ((s8)value < 0)
        ApplySceneCommandModeValue(scene_context, 1, (u8)(value + 0x80));
    else
        /* Retail reloads the command byte on this path. */
        ApplySceneCommandModeValue(scene_context, 2,
                                   ((volatile const u8 *)command)[1]);
    return 0x115;
}
