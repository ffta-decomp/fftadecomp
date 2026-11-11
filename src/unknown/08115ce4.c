typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *object;u8 *completion;} Event;
typedef struct Work {s16 x,y;void *child;u32 unknown8;u8 *completion;void *object;} Work;
void RetailCall_080d8c58(void *,s16 *,s16 *);void *RetailCall_08116480(u32,s32,s32,u32,u32,u32,u32,u8 *,void *);void *RetailCall_081164e8(void *);

u32 RemainingBand43_00115CE4(void *parent,Event *event,Work *work) {
    s32 phase,next_phase;
    void *child;
    phase=event->phase;
    switch(phase) {
    case 0:
        work->object=event->object;
        work->completion=event->completion;
        *work->completion=phase;
        RetailCall_080d8c58(work->object,&work->x,&work->y);
        work->y=(u16)work->y-4;
        break;
    case 1:
        break;
    case 256:
        work->child=RetailCall_08116480(0,work->x,work->y,6,7,987,986,work->completion,parent);
        next_phase=event->phase+1;
        goto store_phase;
    case 257:
        child=RetailCall_081164e8(work->child);
        work->child=child;
        if(child==0) {
            next_phase=2;
store_phase:
            event->phase=next_phase;
        }
        break;
    }
    return 0;
}
asm(".global RetailCall_080d8c58\n.thumb_set RetailCall_080d8c58,0x080d8c59\n.global RetailCall_08116480\n.thumb_set RetailCall_08116480,0x08116481\n.global RetailCall_081164e8\n.thumb_set RetailCall_081164e8,0x081164e9\n");
