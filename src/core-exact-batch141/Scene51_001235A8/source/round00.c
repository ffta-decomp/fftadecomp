typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 LoadSceneCoordinatePath(u16 path_id, u8 slot);
u32 LoadScenePathFromCommand(void *unused_context, const u8 *command)
{
    u16 path_id = command[1] | (command[2] << 8);
    u8 slot = command[3];
    LoadSceneCoordinatePath(path_id, slot);
    return 0x110;
}
asm(".global LoadSceneCoordinatePath\n.thumb_set LoadSceneCoordinatePath,0x08124df1\n");
