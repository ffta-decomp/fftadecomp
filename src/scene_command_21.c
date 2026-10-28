typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Opcode 0x15 copies its byte operand into the scene context's word at +4. */
u32 SetSceneContextWord04FromCommandByte(u8 *scene_context,
                                         const u8 *command)
{
    *(u16 *)(scene_context + 4) = command[1];
    /* Preserve the handler's dispatcher result; its symbolic meaning is open. */
    return 0x114;
}
