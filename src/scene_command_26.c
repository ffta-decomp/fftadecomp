typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void SetIndexedFlagState(u32 flag_index, u32 enabled);

/* Opcode 0x1a sets or clears an indexed scene-state bit. */
u32 SetSceneFlagFromCommand(u8 *scene_context, const u8 *command)
{
    u16 flag_index = (u16)(command[1] | ((u16)command[2] << 8));
    u8 enabled = command[3];

    (void)scene_context;
    SetIndexedFlagState(flag_index, enabled);
    return 0x110;
}
