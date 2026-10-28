typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 ReadSaveByte(u16 index);
extern void WriteSaveByte(u16 index, u8 value);
extern void SetContentStateFlag40(void);

/* Opcode 0x61 consumes save byte 13 when set and advances scene state. */
u32 ConsumeSceneSaveFlagFromCommand(u8 *scene_context, const u8 *command)
{
    (void)command;
    if (ReadSaveByte(13) == 1) {
        WriteSaveByte(13, 0);
        *(u16 *)(scene_context + 4) = 16;
        SetContentStateFlag40();
        return 0x11b;
    }
    return 0x110;
}
