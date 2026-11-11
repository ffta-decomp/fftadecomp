typedef signed int s32;typedef unsigned int u32;typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;
typedef struct Event {u16 phase,pad;void *record;} Event;
typedef struct Work {s16 x,y;u8 counter,pad[3];void *layer,*blend,*script,*raster,*record,*child;} Work;
u32 RemainingBand43_000F244C(void *,Event *,Work *);
void RetailCall_080d49fc(u32,u32,u32,s32,s32);void *RetailCall_080d4b64(u32,const void *,u32,u32);
u32 RetailCall_080035a8(u32);void *RetailCall_080d3e9c(const void *,void *);void *RetailCall_080d4704(const void *,void *);
void *RetailCall_080d98d4(u32,u32,u32,u32,const void *,void *);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void *RetailCall_080d3f08(void *);void *RetailCall_080d4d2c(void *,u32);void *RetailCall_080d9b64(void *);void *RetailCall_080d4774(void *);

u32 RemainingBand43_000F244C(void *parent, Event *event, Work *work) {
    s32 phase;
    s32 next_phase;
    void *blend;
    void *layer;
    void *raster;
    void *script;
    register Event *event_carrier asm("r6")=event;

    asm("" : "+r"(event_carrier));
    event=event_carrier;
    phase = event->phase;
    switch (phase) {                              /* irregular */
    case 0x0:
        work->record = event->record;
        work->x = (s16) phase;
        work->y = (s16) phase;
        break;
    case 0x100: {
        register u32 counter_zero asm("r4");
        register s32 advanced_phase asm("r0");
        u32 control;
        RetailCall_080d49fc(0U, 2U, 0U, (s32) work->x, (s32) work->y);
        work->layer = RetailCall_080d4b64(0U, (void *)0x088F0D08, 0x29BU, 6U);
        control=RetailCall_080035a8(2U);
        control=*(u16 *)0x03000940 | control;
        counter_zero=0;
        asm("" : "+r"(counter_zero));
        *(u16 *)0x03000940=control;
        work->blend = RetailCall_080d3e9c((void *)0x0894DAF8, parent);
        work->script = RetailCall_080d4704((void *)0x0894B3E8, parent);
        work->raster = RetailCall_080d98d4(2U, 0U, 0U, 0U, (void *)0x0839A74C, parent);
        work->child = RetailCall_080dfd8c((void *)0x0839A8A8, 2U, 4U, 0U, parent);
        work->counter = counter_zero;
        advanced_phase = event->phase + 1;
        asm("" : "+r"(advanced_phase));
        next_phase = advanced_phase;
        goto store_phase;
    }
    case 0x101:
        work->counter += 1;
        blend = RetailCall_080d3f08(work->blend);
        work->blend = blend;
        if (blend == 0) {
            layer = RetailCall_080d4d2c(work->layer, 0U);
            work->layer = layer;
            if (layer == 0) {
                *(u16 *)0x03000940 &= ~RetailCall_080035a8(2U);
                raster = RetailCall_080d9b64(work->raster);
                work->raster = raster;
                if (raster == 0) {
                    script = RetailCall_080d4774(work->script);
                    work->script = script;
                    if (script == 0) {
                        next_phase = event->phase + 1;
                        goto store_phase;
                    }
                }
            }
        }
        break;
    case 0x102:
        next_phase = 2;
store_phase:
        event->phase = next_phase;
        break;
    }
    return 0U;
}

asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4774\n.thumb_set RetailCall_080d4774, 0x080d4775\n.global RetailCall_080d49fc\n.thumb_set RetailCall_080d49fc, 0x080d49fd\n.global RetailCall_080d4b64\n.thumb_set RetailCall_080d4b64, 0x080d4b65\n.global RetailCall_080d4d2c\n.thumb_set RetailCall_080d4d2c, 0x080d4d2d\n.global RetailCall_080d98d4\n.thumb_set RetailCall_080d98d4, 0x080d98d5\n.global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64, 0x080d9b65\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
