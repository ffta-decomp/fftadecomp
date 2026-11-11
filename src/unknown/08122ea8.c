typedef unsigned char u8;
typedef unsigned int u32;

extern void SetIndexedSceneCommandValue(u32 index, u32 value);

/* Opcode 0x1b writes command byte 3 to the indexed scene-value accessor. */
u32 SetIndexedSceneValueFromCommand(void *scene_context, const u8 *command)
{
    u32 index = command[1] | (command[2] << 8);
    u32 value = command[3];

    (void)scene_context;
    SetIndexedSceneCommandValue(index, value);
    return 0x110;
}
