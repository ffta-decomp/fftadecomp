typedef unsigned char u8;
typedef unsigned int u32;
extern u32 CreateSceneGroup(void (*callback)(void), u32 bytes, void *event, void *parent);
extern void GameImageTransitionCallback(void);
void StartGameImageTransition(u8 *context) asm("Remaining38_0012C510");
void StartGameImageTransition(u8 *context)
{
    u32 event[7];
    context[6] = 0;
    event[1] = (u32)context;
    CreateSceneGroup(GameImageTransitionCallback, 92, event, 0);
}
asm(".thumb_set CreateSceneGroup,0x08121b8d\n.thumb_set GameImageTransitionCallback,0x0812c2b9\n");
