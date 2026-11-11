typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *record;} Event;
typedef struct Work {s16 x,y;u8 counter,pad[3];u32 data8;void *window,*blend,*script,*raster,*record,*aux;} Work;
u32 RemainingBand43_000F2874(void *,Event *,Work *);
void *RetailCall_080d6098(s32,s32,u32,u32,u32,void *,const void *,void *);void RetailCall_080d7220(const void *,u32,u32,s32,s32,u32);
void *RetailCall_080d3e9c(const void *,void *);void RetailCall_080d3f84(void *,u32,u32);void *RetailCall_080d4704(const void *,void *);
void *RetailCall_080d98d4(u32,u32,u32,u32,const void *,void *);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void *RetailCall_080d3f08(void *);u32 RetailCall_080035a8(u32);void *RetailCall_080d6134(void *);void *RetailCall_080d4774(void *);void *RetailCall_080d9b64(void *);
u32 RemainingBand43_000F2874(void *parent,Event *event,Work *work)
{
    s32 phase=event->phase;
    s32 next_phase;
    switch(phase) {
    case 0:
        work->record=event->record;work->x=120;work->y=96;
        break;
    case 256: {
        register u32 counter_zero asm("r4");
        register s32 advanced_phase asm("r0");
        void *blend;
        work->window=RetailCall_080d6098(work->x,work->y,0,1,1,&work->data8,(void*)0x0839a81c,parent);
        RetailCall_080d7220((void*)0x088f5bb0,1,3,(s16)((u16)work->x-48),160,({counter_zero=0;asm("" : "+r"(counter_zero));counter_zero;}));
        blend=RetailCall_080d3e9c((void*)0x0894db38,parent);work->blend=blend;RetailCall_080d3f84(blend,8,255);
        work->script=RetailCall_080d4704((void*)0x0894b658,parent);
        work->raster=RetailCall_080d98d4(3,0,1,1,(void*)0x0839a834,parent);
        work->aux=RetailCall_080dfd8c((void*)0x0839a8d0,1,4,0,parent);
        work->counter=counter_zero;
        advanced_phase=event->phase+1;
        asm("" : "+r"(advanced_phase));
        next_phase=advanced_phase;
        goto store_phase;
    }
    case 257: {
        void *blend;
        ++work->counter;
        blend=RetailCall_080d3f08(work->blend);work->blend=blend;
        if(!blend) {
            void *window;
            *(u16*)0x03000940&=~RetailCall_080035a8(3);
            window=RetailCall_080d6134(work->window);work->window=window;
            if(!window) {
                void *script=RetailCall_080d4774(work->script);work->script=script;
                if(!script) {
                    void *raster=RetailCall_080d9b64(work->raster);work->raster=raster;
                    if(!raster) {next_phase=event->phase+1;goto store_phase;}
                }
            }
        }
        break;
    }
    case 258:
        next_phase=2;
store_phase:
        event->phase=next_phase;
        break;
    }
    return 0;
}

asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d3f84\n.thumb_set RetailCall_080d3f84, 0x080d3f85\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4774\n.thumb_set RetailCall_080d4774, 0x080d4775\n.global RetailCall_080d6098\n.thumb_set RetailCall_080d6098, 0x080d6099\n.global RetailCall_080d6134\n.thumb_set RetailCall_080d6134, 0x080d6135\n.global RetailCall_080d7220\n.thumb_set RetailCall_080d7220, 0x080d7221\n.global RetailCall_080d98d4\n.thumb_set RetailCall_080d98d4, 0x080d98d5\n.global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64, 0x080d9b65\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
