typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *record;} Event;
typedef struct Work {s16 x,y;u32 unknown4;void *blend,*scripts[4],*record,*aux;} Work;
u32 RemainingBand43_000F1858(void *,Event *,Work *);
void RetailCall_080d7220(const void *,u32,u32,s32,s32,u32);void *RetailCall_080d3e9c(const void *,void *);void *RetailCall_080d4704(const void *,void *);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void *RetailCall_080d3f08(void *);u32 RetailCall_080035a8(u32);u32 RetailCall_080d48dc(void **,u32);

u32 RemainingBand43_000F1858(void *parent, Event *event, Work *work) {
    s32 phase, next_phase;
    void *blend;
    phase=event->phase;
    switch(phase) {
    case 0:
        work->record=event->record;work->x=120;work->y=48;
        break;
    case 256: {
        register s32 advanced_phase asm("r0");
        RetailCall_080d7220((void *)0x088F4E9C,0,2,work->x,work->y,0);
        work->blend=RetailCall_080d3e9c((void *)0x0894DBE8,parent);
        work->scripts[0]=RetailCall_080d4704((void *)0x0894B8E8,parent);
        work->scripts[2]=RetailCall_080d4704((void *)0x0894B268,parent);
        work->scripts[3]=RetailCall_080d4704((void *)0x08949DD8,parent);
        work->aux=RetailCall_080dfd8c((void *)0x0839A57C,1,4,0,parent);
        advanced_phase=event->phase+1;
        asm("" : "+r"(advanced_phase));
        next_phase=advanced_phase;
        goto store_phase;
    }
    case 257:
        blend=RetailCall_080d3f08(work->blend);
        work->blend=blend;
        if(blend==0 && (RetailCall_080d48dc(work->scripts,4)<<24)!=0) {
            *(u16 *)0x03000940 &= ~RetailCall_080035a8(2);
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
asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d48dc\n.thumb_set RetailCall_080d48dc, 0x080d48dd\n.global RetailCall_080d7220\n.thumb_set RetailCall_080d7220, 0x080d7221\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
