typedef unsigned char u8;
typedef unsigned int u32;
extern u32 CreateSceneGroup(void (*callback)(void), u32 bytes, void *event, void *parent);
extern void SceneDisplayCommandCallback(void);
void StartSceneDisplayCommand(u8 *context, const u8 *command) asm("Remaining38_0012C4E4");
void StartSceneDisplayCommand(u8 *context, const u8 *command)
{
    u32 event[7];
    if (command[8])
        context[6] = 0;
    event[1] = (u32)context;
    event[2] = (u32)command;
    CreateSceneGroup(SceneDisplayCommandCallback, 264, event, 0);
}
asm(".thumb_set CreateSceneGroup,0x08121b8d\n.thumb_set SceneDisplayCommandCallback,0x0812bd4d\n");
