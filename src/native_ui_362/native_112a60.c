typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u16 phase,padding;u8 *completion;} Event;
typedef struct {u32 untouched[2];u8 *completion;void *child,*aux;} CompletionWork;
extern void *CreateSceneChild(u32,u32,u32,u32,u32,u32,u32,u8 *,void *) __asm__("0x08116480");
extern void *CreateAux(const void *,u32,u32,u32,void *) __asm__("0x080DFD8C");
extern void *PollChild(void *) __asm__("0x081164E8");
u32 RemainingBand43_00112A60(void *parent,Event *event,CompletionWork *work)
{
    switch(event->phase) {
    case 0:
        work->completion=event->completion;
        *work->completion=0;
        break;
    case 1:
        break;
    case 256:
        work->child=CreateSceneChild(1,120,104,6,7,894,893,work->completion,parent);
        work->aux=CreateAux((const void *)0x083A33DC,1,4,0,parent);
        ++event->phase;
        break;
    case 257:
        work->child=PollChild(work->child);
        if(!work->child) event->phase=2;
        break;
    }
    return 0;
}
