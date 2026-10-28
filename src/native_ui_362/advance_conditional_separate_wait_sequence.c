typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *record;u8 pad8[12];u16 mode;} Event;
typedef struct Work {u8 mode,pad1;s16 x,y;u16 unknown6;void *coordinate_child,*record;u32 opaque16;void *window,*secondary,*aux;} Work;
u32 RemainingBand43_000E8A30(void *,Event *,Work *);
void *RetailCall_080dd748(void *,s16 *,s16 *,s16 *);u32 RetailCall_080dd580(void *);void *RetailCall_080d6098(s32,s32,u32,u32,u32,void *,const void *,void *);
void *RetailCall_080dcfe4(void *,const void *,u32,u32,u32,void *,u32);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void *RetailCall_080d6134(void *);void *RetailCall_080dba5c(void *);

u32 RemainingBand43_000E8A30(void *parent,Event *event,Work *work) {
    s32 phase=event->phase;
    s32 next_phase;
    switch(phase) {
    case 0:
        work->mode=event->mode;work->record=event->record;
        work->coordinate_child=RetailCall_080dd748(work->record,&work->x,&work->y,0);
        break;
    case 256: {
        u32 flags;
        register s32 advanced_phase asm("r0");
        if((u8)RetailCall_080dd580(work->record)) {
            work->window=RetailCall_080d6098(work->x,work->y,0,1,1,&work->opaque16,(void*)0x08398288,parent);
            flags=(work->mode&1)?16:8;
            work->aux=RetailCall_080dfd8c((void*)0x083982BC,1,flags|4,0,parent);
        }
        flags=(work->mode&1)?4:2;
        work->secondary=RetailCall_080dcfe4(work->record,(void*)0x083982A0,12,20,flags,parent,0);
        advanced_phase=event->phase+1;
        asm("" : "+r"(advanced_phase));
        next_phase=advanced_phase;
        goto store_phase;
    }
    case 257: {
        void *child=RetailCall_080d6134(work->window);work->window=child;
        if(!child) {next_phase=event->phase+1;goto store_phase;}
        break;
    }
    case 258: {
        void *child=RetailCall_080dba5c(work->secondary);work->secondary=child;if(child)break;
        next_phase=2;
store_phase:
        event->phase=next_phase;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080d6098\n.thumb_set RetailCall_080d6098, 0x080d6099\n.global RetailCall_080d6134\n.thumb_set RetailCall_080d6134, 0x080d6135\n.global RetailCall_080dba5c\n.thumb_set RetailCall_080dba5c, 0x080dba5d\n.global RetailCall_080dcfe4\n.thumb_set RetailCall_080dcfe4, 0x080dcfe5\n.global RetailCall_080dd580\n.thumb_set RetailCall_080dd580, 0x080dd581\n.global RetailCall_080dd748\n.thumb_set RetailCall_080dd748, 0x080dd749\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
