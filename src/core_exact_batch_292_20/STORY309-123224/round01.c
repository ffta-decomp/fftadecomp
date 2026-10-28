typedef unsigned char u8;
typedef unsigned int u32;
extern void InstantiateSceneDescriptor(const u8 *descriptor);
__asm__(".global InstantiateSceneDescriptor\n.thumb_set InstantiateSceneDescriptor,0x08125445");
u32 SpawnEntityFromScriptDescriptor(void *context, const u8 *command) __asm__("Scene51_00123224");
u32 SpawnEntityFromScriptDescriptor(void *context, const u8 *command)
{
    InstantiateSceneDescriptor(command + 1);
    return 0x110;
}
