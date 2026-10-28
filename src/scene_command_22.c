typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Opcode 0x16 copies its little-endian halfword into the scene context at +4. */
u32 SetSceneContextWord04FromCommandHalfword(u8 *scene_context,
                                             const u8 *command)
{
    u16 value = (u16)(command[1] | ((u16)command[2] << 8));

    *(u16 *)(scene_context + 4) = value;
    /* Preserve the handler's dispatcher result; its symbolic meaning is open. */
    return 0x114;
}
