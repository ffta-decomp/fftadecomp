typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *record;} Event;
typedef struct Ramp {s16 value;u16 a,b,c,d,e;} Ramp;
typedef struct Work {s16 x,y;u8 delay,pad[3];u32 helper_word;void *window,*blend,*script_a,*script_b;Ramp ramp;void *scan,*record,*aux;} Work;
u32 RemainingBand43_000F1BE8(void *,Event *,Work *);
void *RetailCall_080d6098(s32,s32,u32,u32,u32,void *,const void *,void *);void *RetailCall_080d3e9c(const void *,void *);void *RetailCall_080dab84(u32,u32,u32,void *);void RetailCall_080d9ba8(void *,u32);void *RetailCall_080d4704(const void *,void *);void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);
void RetailCall_080e0608(Ramp *,s32,s32,s32);void RetailCall_080e064c(Ramp *);u32 RetailCall_080e0690(Ramp *);void RetailCall_080dadfc(void *);void RetailCall_080dac40(void *,s32,s32,u32);void RetailCall_080d3f84(void *,u32,u32);
void *RetailCall_080d9b64(void *);void *RetailCall_080d3f08(void *);void *RetailCall_080d4774(void *);void *RetailCall_080d6134(void *);
typedef struct Shadow {u16 control;u8 pad2[56];u8 b58;volatile u8 b59,b60,b61;volatile s8 b62;volatile u8 b63,b64,b65,b66,b67,b68;u8 pad69[5];volatile u8 b74;u8 pad75[3];volatile u8 b78;} Shadow;
#define SHADOW ((Shadow*)0x03000940)
u32 RemainingBand43_000F1BE8(void *parent,Event *event,Work *work)
{
    s32 phase=event->phase;
    s32 next_phase;
    switch(phase) {
    case 0:
        work->record=event->record;work->x=120;work->y=56;
        break;
    case 1:break;
    case 256: {
        register s32 advanced_phase asm("r0");
        void *scan;
        work->window=RetailCall_080d6098(work->x,work->y,0,1,1,&work->helper_word,(void*)0x0839a544,parent);
        work->blend=RetailCall_080d3e9c((void*)0x0894db7c,parent);
        scan=RetailCall_080dab84(0,0,255,parent);work->scan=scan;RetailCall_080d9ba8(scan,1);
        SHADOW->b78=0;SHADOW->b66=63;SHADOW->b68=31;SHADOW->b59=0;SHADOW->b58=255;SHADOW->b63=0;SHADOW->b62=-1;
        SHADOW->control|=0x2000;
        work->script_a=RetailCall_080d4704((void*)0x0894b268,parent);
        work->script_b=RetailCall_080d4704((void*)0x089492dc,parent);
        work->aux=RetailCall_080dfd8c((void*)0x0839a594,1,4,0,parent);
        work->delay=20;
        advanced_phase=event->phase+1;
        asm volatile("" : "+r"(advanced_phase));
        next_phase=advanced_phase;goto store_phase;
    }
    case 257: {
        u32 timer=work->delay-1;
        work->delay=timer;
        if(!(u8)timer) {
            register s32 advanced_phase asm("r0");
            RetailCall_080e0608(&work->ramp,188,11,40);
            advanced_phase=event->phase+1;
            asm volatile("" : "+r"(advanced_phase));
            next_phase=advanced_phase;goto store_phase;
        }
        break;
    }
    case 258: {
        Ramp *ramp=&work->ramp;
        RetailCall_080e064c(ramp);RetailCall_080dadfc(work->scan);
        RetailCall_080dac40(work->scan,120,16,(u16)work->ramp.value);
        if((u8)RetailCall_080e0690(ramp)) {
            register s32 advanced_phase asm("r0");
            RetailCall_080d3f84(work->blend,47,255);work->delay=40;
            advanced_phase=event->phase+1;
            asm volatile("" : "+r"(advanced_phase));
            next_phase=advanced_phase;goto store_phase;
        }
        break;
    }
    case 259: {
        u32 timer=work->delay-1;
        u32 remaining;
        work->delay=timer;remaining=(u8)timer;
        if(!remaining) {
            register s32 advanced_phase asm("r0");
            SHADOW->b74=remaining;SHADOW->control&=0xdfff;
            advanced_phase=event->phase+1;
            asm volatile("" : "+r"(advanced_phase));
            next_phase=advanced_phase;goto store_phase;
        }
        break;
    }
    case 260: {
        void *scan=RetailCall_080d9b64(work->scan);work->scan=scan;
        if(!scan) {
            void *blend=RetailCall_080d3f08(work->blend);work->blend=blend;
            if(!blend) {
                void *script_a=RetailCall_080d4774(work->script_a);work->script_a=script_a;
                if(!script_a) {
                    void *script_b=RetailCall_080d4774(work->script_b);work->script_b=script_b;
                    if(!script_b) {
                        void *window=RetailCall_080d6134(work->window);work->window=window;
                        if(!window) {
                            next_phase=2;
store_phase:
                            event->phase=next_phase;
                        }
                    }
                }
            }
        }
        break;
    }
    }
    return 0;
}

asm(".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d3f84\n.thumb_set RetailCall_080d3f84, 0x080d3f85\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4774\n.thumb_set RetailCall_080d4774, 0x080d4775\n.global RetailCall_080d6098\n.thumb_set RetailCall_080d6098, 0x080d6099\n.global RetailCall_080d6134\n.thumb_set RetailCall_080d6134, 0x080d6135\n.global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64, 0x080d9b65\n.global RetailCall_080d9ba8\n.thumb_set RetailCall_080d9ba8, 0x080d9ba9\n.global RetailCall_080dab84\n.thumb_set RetailCall_080dab84, 0x080dab85\n.global RetailCall_080dac40\n.thumb_set RetailCall_080dac40, 0x080dac41\n.global RetailCall_080dadfc\n.thumb_set RetailCall_080dadfc, 0x080dadfd\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608, 0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c, 0x080e064d\n.global RetailCall_080e0690\n.thumb_set RetailCall_080e0690, 0x080e0691\n");
