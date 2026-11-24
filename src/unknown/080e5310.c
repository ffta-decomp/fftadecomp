typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase;} Event;
typedef struct Work {u32 unknown0;u8 opaque4[16];void *window,*model,*blend,*script,*scan,*aux;} Work;
u32 RemainingBand43_000E5310(void *,Event *,Work *);
void RetailCall_080d49fc(u32,u32,u32,u32,u32);void *RetailCall_080d4b64(u32,const void *,u32,u32);u32 RetailCall_080035a8(u32);
void *RetailCall_080d4704(const void *,void *);void *RetailCall_080d3e9c(const void *,void *);void *RetailCall_080d6098(s32,s32,u32,u32,u32,void *,const void *,void *);
void *RetailCall_080d98d4(u32,u32,u32,u32,const void *,void *);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void *RetailCall_080d3f08(void *);void *RetailCall_080d4774(void *);void *RetailCall_080d4d2c(void *,u32);void *RetailCall_080d6134(void *);void *RetailCall_080d9b64(void *);

u32 RemainingBand43_000E5310(void *parent,Event *event,Work *work) {
    s32 phase=event->phase;
    switch(phase) {
    case 0:
        RetailCall_080d49fc(0,2,0,0,phase);
        work->model=RetailCall_080d4b64(0,(void*)0x088ED968,795,6);
        {
            u32 mask=RetailCall_080035a8(2);
            register u32 control asm("r1")=*(u16*)0x03000940;
            asm("" : "+r"(control));
            control |= mask;
            *(u16*)0x03000940=control;
        }
        work->script=RetailCall_080d4704((void*)0x08949498,parent);
        work->blend=RetailCall_080d3e9c((void*)0x0894D69C,parent);
        work->window=RetailCall_080d6098(120,96,0,1,4,work->opaque4,(void*)0x08396E18,parent);
        work->scan=RetailCall_080d98d4(2,0,0,0,(void*)0x08396F68,parent);
        work->aux=RetailCall_080dfd8c((void*)0x08396FAC,1,4,0,parent);
        break;
    case 1:break;
    case 256: {
        void *child=RetailCall_080d3f08(work->blend);work->blend=child;if(child)break;
        child=RetailCall_080d4774(work->script);work->script=child;if(child)break;
        child=RetailCall_080d4d2c(work->model,0);work->model=child;if(child)break;
        *(u16*)0x03000940 &= ~RetailCall_080035a8(2);
        child=RetailCall_080d6134(work->window);work->window=child;if(child)break;
        child=RetailCall_080d9b64(work->scan);work->scan=child;if(child)break;
        event->phase=2;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4774\n.thumb_set RetailCall_080d4774, 0x080d4775\n.global RetailCall_080d49fc\n.thumb_set RetailCall_080d49fc, 0x080d49fd\n.global RetailCall_080d4b64\n.thumb_set RetailCall_080d4b64, 0x080d4b65\n.global RetailCall_080d4d2c\n.thumb_set RetailCall_080d4d2c, 0x080d4d2d\n.global RetailCall_080d6098\n.thumb_set RetailCall_080d6098, 0x080d6099\n.global RetailCall_080d6134\n.thumb_set RetailCall_080d6134, 0x080d6135\n.global RetailCall_080d98d4\n.thumb_set RetailCall_080d98d4, 0x080d98d5\n.global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64, 0x080d9b65\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n");
