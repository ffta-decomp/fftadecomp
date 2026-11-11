typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase;} Event;
typedef struct Work {u16 timer,pad;u32 unknown4;void *child;} Work;
void *RetailCall_080d3e9c(const void *,void *);void *RetailCall_080d3f08(void *);

u32 RemainingBand43_00113C68(void *parent,Event *event,Work *work) {
    s32 phase,remaining,next_phase;
    void *child;
    phase=event->phase;
    switch(phase) {
    case 0:
        work->timer=30;
        break;
    case 256: {
        register s32 advanced_phase asm("r0");
        remaining=work->timer-1;
        work->timer=remaining;
        if((u16)remaining!=0) break;
        work->child=RetailCall_080d3e9c((void *)0x0894DC00,parent);
        advanced_phase=event->phase+1;
        asm("" : "+r"(advanced_phase));
        next_phase=advanced_phase;
        goto store_phase;
    }
    case 257:
        child=RetailCall_080d3f08(work->child);
        work->child=child;
        if(child==0) {
            next_phase=event->phase+1;
            goto store_phase;
        }
        break;
    case 258:
        next_phase=2;
store_phase:
        event->phase=next_phase;
        break;
    }
    return 0;
}
asm(".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08,0x080d3f09\n");
