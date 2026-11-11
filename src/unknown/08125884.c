typedef unsigned int u32;
typedef signed int s32;
extern u32 ReadSceneHandle(s32);
extern void ReleaseSceneHandle(u32);
extern void WriteSceneHandle(s32, u32);
void ClearSceneHandles(void) asm("Scene51_00125884");
void ClearSceneHandles(void)
{
    s32 index = 0;
    do {
        u32 handle = ReadSceneHandle(index);
        if (handle) {
            ReleaseSceneHandle(handle);
            WriteSceneHandle(index, 0);
        }
        index++;
    } while (index <= 15);
}
asm(".thumb_set ReadSceneHandle,0x08121d0d\n.thumb_set ReleaseSceneHandle,0x08121bb9\n.thumb_set WriteSceneHandle,0x08121d21\n");
