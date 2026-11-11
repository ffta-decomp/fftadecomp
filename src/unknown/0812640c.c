typedef unsigned char u8;
typedef unsigned int u32;
extern u32 CreateSceneGroup(void (*callback)(void), u32 bytes, void *event, void *parent);
extern void SceneOpcode13Callback(void);
void StartSceneOpcode13(u8 *context, const u8 *command) asm("SceneActionDependency_0012640C");
void StartSceneOpcode13(u8 *context, const u8 *command)
{
    u32 event[7];
    context[6] = 0;
    event[1] = (u32)context;
    CreateSceneGroup(SceneOpcode13Callback, 180, event, *(void **)(context + 8));
}
asm(".thumb_set CreateSceneGroup,0x08121b8d\n.thumb_set SceneOpcode13Callback,0x08126119\n");
