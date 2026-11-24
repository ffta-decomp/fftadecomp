typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u32 ResolveSceneKey(void *context,u16 key);
extern void ApplySceneResolvedIndex(void *context,u16 index);
__asm__(".global ResolveSceneKey\n.thumb_set ResolveSceneKey,0x0801784d\n.global ApplySceneResolvedIndex\n.thumb_set ApplySceneResolvedIndex,0x08017735");
void ApplySceneKeyIfResolved(void *context,u16 key)
{
    u32 result=ResolveSceneKey(context,key);
    if ((s16)result >= 0)
        ApplySceneResolvedIndex(context,(u16)result);
}
