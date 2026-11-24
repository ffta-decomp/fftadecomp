typedef unsigned char u8;
typedef unsigned int u32;

extern u8 gContentState[];

/* Opcode 0x5d stores two command bytes in the content state. */
u32 SetSceneContentBytesA6A7(void *scene_context, const u8 *command)
{
    (void)scene_context;
    gContentState[0xa6] = command[1];
    gContentState[0xa7] = command[2];
    return 0x110;
}
