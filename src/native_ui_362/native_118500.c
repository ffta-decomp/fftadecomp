typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {u16 phase,pad;void *record;u8 *completion;} Event;
typedef struct {s16 x,y;void *child;u32 untouched;u8 *completion;void *record;} ChildWork;
extern void ReadRecordPosition(void *,s16 *,s16 *) __asm__("0x080D8C58");
extern void *CreateSceneChild(u32,s32,s32,u32,u32,u32,u32,u8 *,void *) __asm__("0x08116480");
extern void *PollChild(void *) __asm__("0x081164E8");
u32 RemainingBand43_00118500(void *parent,Event *event,ChildWork *work)
{
    switch(event->phase) {
    case 0:
        work->record=event->record;
        work->completion=event->completion;
        *work->completion=0;
        ReadRecordPosition(work->record,&work->x,&work->y);
        work->y-=4;
        break;
    case 1:
        break;
    case 256:
        work->child=CreateSceneChild(2,work->x,work->y,6,7,987,986,work->completion,parent);
        ++event->phase;
        break;
    case 257:
        work->child=PollChild(work->child);
        if(!work->child) event->phase=2;
        break;
    }
    return 0;
}
