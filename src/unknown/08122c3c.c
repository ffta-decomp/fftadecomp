typedef unsigned char u8;
typedef unsigned int u32;

/* Opcode 0x08 initializes four bytes in the IWRAM display shadow. */
u32 InitializeSceneDisplayShadow(void *scene_context, const u8 *command)
{
    volatile u8 *shadow = (volatile u8 *)0x03000940;

    (void)scene_context;
    (void)command;
    (void)shadow[0x4a];
    shadow[0x4a] = 0;
    (void)shadow[0x4b];
    shadow[0x4b] = 3;
    (void)shadow[0x4c];
    shadow[0x4c] = 16;
    (void)shadow[0x4d];
    shadow[0x4d] = 0;
    return 0x100;
}
