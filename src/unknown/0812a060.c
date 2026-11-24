typedef unsigned char u8;
typedef unsigned int u32;
extern u32 CreateSceneGroup(void (*callback)(void), u32 bytes, void *event, void *parent);
extern void SceneModeNineCallback(void);
void StartSceneModeNine(u8 *context) asm("Remaining38_0012A060");
void StartSceneModeNine(u8 *context)
{
    u32 event[7];
    context[6] = 0;
    event[1] = (u32)context;
    CreateSceneGroup(SceneModeNineCallback, 984, event, 0);
}
asm(".thumb_set CreateSceneGroup,0x08121b8d\n.thumb_set SceneModeNineCallback,0x081295c9\n");
