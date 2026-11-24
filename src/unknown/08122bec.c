typedef unsigned int u32;
extern void ClearSceneHandles(void *, const void *);
u32 HandleSceneOpcode5(void *context, const void *command) asm("Scene51_00122BEC");
u32 HandleSceneOpcode5(void *context, const void *command)
{
    ClearSceneHandles(context, command);
    return 272;
}
asm(".thumb_set ClearSceneHandles,0x08125885\n");
