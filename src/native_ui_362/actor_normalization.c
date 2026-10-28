typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 CreateSceneGroup(void (*callback)(void), u32 bytes, void *event, void *parent);
extern void SceneActorEffectCallback(void);
void StartSceneActorEffect(u8 *context, u32 value) asm("Remaining38_0012BCE4");
void StartSceneActorEffect(u8 *context, u32 value)
{
    u32 event[7];
    register u32 actor asm("r1") = (u8)value;
    asm("" : "+r"(actor));
    context[6] = 0;
    event[1] = (u32)context;
    ((u16 *)event)[10] = actor;
    CreateSceneGroup(SceneActorEffectCallback, 68, event, 0);
}
asm(".thumb_set CreateSceneGroup,0x08121b8d\n.thumb_set SceneActorEffectCallback,0x0812b7f1\n");
