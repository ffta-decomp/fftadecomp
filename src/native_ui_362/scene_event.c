typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 CreateSceneGroup(void (*callback)(void), u32 bytes, void *event, void *parent);
extern void SceneOpcode5CCallback(void);
void StartSceneOpcode5C(u8 *context, u32 value) asm("Remaining38_0012B7D0");
void StartSceneOpcode5C(u8 *context, u32 value)
{
    u32 event[7];
    event[1] = (u32)context;
    ((u16 *)event)[10] = value;
    CreateSceneGroup(SceneOpcode5CCallback, 176, event, 0);
}
asm(".thumb_set CreateSceneGroup,0x08121b8d\n.thumb_set SceneOpcode5CCallback,0x0812b5f9\n");
