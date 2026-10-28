typedef unsigned char u8;
typedef unsigned short u16;
struct ChoiceState { u16 state, count, stack[0]; };
extern struct ChoiceState *gChoiceContext;
extern unsigned int IsChoiceMessageComplete(void);
extern void ReleaseChoiceResource(void *);
__asm__(".global gChoiceContext\n.set gChoiceContext,0x0200f450\n.global IsChoiceMessageComplete\n.thumb_set IsChoiceMessageComplete,0x08011861\n.global ReleaseChoiceResource\n.thumb_set ReleaseChoiceResource,0x08022855");
void WaitMultiplayerChoiceMessage(void)
{
    void *resource;
    struct ChoiceState *state;
    if ((u16)IsChoiceMessageComplete()==0) return;
    resource=*(void **)((u8 *)gChoiceContext+2180);
    if (resource) {
        ReleaseChoiceResource(resource);
        *(void **)((u8 *)gChoiceContext+2180)=0;
    }
    state=gChoiceContext;
    state->state=state->stack[--state->count];
}
