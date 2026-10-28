typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Opcode 0x19 adds its little-endian halfword operand to context word +0. */
u32 AddSceneContextWord00FromCommandHalfword(u8 *scene_context,
                                              const u8 *command)
{
    u16 increment = (u16)(command[1] | ((u16)command[2] << 8));

    *(u16 *)scene_context = (u16)(*(u16 *)scene_context + increment);
    return 0x110;
}
