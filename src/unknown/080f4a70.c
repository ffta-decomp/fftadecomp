typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct Timed {u16 value;u8 unknown2[10];} Timed;
typedef struct Event {u16 phase,pad2;void *record;u8 unknown8[20];} Event;
typedef struct Work {u16 countdown;s16 x,y;u16 pad6;void *record,*script;Timed first,second;void *first_window,*second_window;} Work;
s32 RemainingBand43_000F4A70(void*,Event*,Work*);
void RetailCall_080dbdc8(void*,s16*,s16*);void RetailCall_080e0608(Timed*,s32,s32,u32);void RetailCall_080e064c(Timed*);u32 RetailCall_080e0690(Timed*);
void *RetailCall_080dab84(u32,u32,u32,void*);void RetailCall_080d9ba8(void*,u32);void *RetailCall_080d3ec0(const void*,u32,void*);
void RetailCall_080dac80(void*,s32,s32,u32,u16);void *RetailCall_080d9b64(void*);void *RetailCall_080d3f08(void*);
extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
typedef char WorkSize48[sizeof(Work)==48?1:-1];
s32 RemainingBand43_000F4A70(void *parent,Event *event,Work *work)
{
    register u32 next_phase asm("r0");
    switch(event->phase) {
    case 0:
        work->record=event->record;
        RetailCall_080dbdc8(work->record,&work->x,&work->y);
        work->y-=8;
        break;
    case 256:
        display_shadow[74]=191;
        display_shadow[78]=12;
        display_shadow[66]=31;
        display_shadow[67]=63;
        display_shadow[68]=31;
        {volatile u8 *cursor=&display_shadow[59]; u8 observed;
         observed=*cursor; asm("" : : "l"(observed)); *cursor=0;
         --cursor; observed=*cursor; asm("" : : "l"(observed)); *cursor=0;
         cursor+=5; observed=*cursor; asm("" : : "l"(observed)); *cursor=0;
         --cursor; {register u32 ff __asm__("r0")=255; asm("" : "+r"(ff)); *(u8*)cursor=ff;}
         --cursor; observed=*cursor; asm("" : : "l"(observed)); *cursor=0;}
        display_shadow[60]=0;
        display_shadow[65]=0;
        {volatile u8 *end=&display_shadow[64]; u8 old_byte; register s32 minus_one __asm__("r0");
         old_byte=*end; asm("" : : "l"(old_byte));
         minus_one=-1; asm("" : "+r"(minus_one)); *end=minus_one;}
        {register u32 control __asm__("r1")=*(volatile u16*)display_shadow;
         register u32 mask __asm__("r2")=0x6000;
         register u32 combined __asm__("r0");
         asm("" : "+r"(control), "+r"(mask));
         combined=mask; asm("" : "+r"(combined));
         combined|=control; *(volatile u16*)display_shadow=combined;}
        RetailCall_080e0608(&work->first,4,64,26);
        RetailCall_080e0608(&work->second,4,64,20);
        work->countdown=8;
        work->first_window=RetailCall_080dab84(1,0,0,parent);
        work->second_window=RetailCall_080dab84(0,0,0,parent);
        RetailCall_080d9ba8(work->first_window,1);
        RetailCall_080d9ba8(work->second_window,1);
        work->script=RetailCall_080d3ec0((const void*)0x0839b278,16,parent);
        next_phase=event->phase+1;
        asm("" : "+r"(next_phase));
        goto store_phase;
    case 257: {
        register u32 first_address __asm__("r3")=16;
        register Timed *first __asm__("r9");
        Timed *second;
        register u32 raw_wait __asm__("r0");
        register u32 wait __asm__("r8");
        asm("" : "+r"(first_address));
        first_address+=(u32)work;
        asm("" : "+r"(first_address));
        first=(Timed*)first_address; asm("" : "+r"(first));
        RetailCall_080e064c(first);
        RetailCall_080dac80(work->first_window,work->x,(s16)(work->y+2),work->first.value,(u16)((s16)work->first.value>>1));
        raw_wait=work->countdown;
        wait=raw_wait;
        asm("" : "+r"(raw_wait), "+r"(wait));
        if(raw_wait) {work->countdown=raw_wait-1;break;}
        second=&work->second;
        RetailCall_080e064c(second);
        RetailCall_080dac80(work->second_window,work->x,work->y,work->second.value,(u16)((s16)work->second.value>>1));
        if(!(u8)RetailCall_080e0690(first))break;
        if(!(u8)RetailCall_080e0690(second))break;
        display_shadow[74]=wait;
        *(volatile u16*)display_shadow&=0x9fff;
        next_phase=event->phase+1;
        asm("" : "+r"(next_phase));
        goto store_phase;
    }
    case 258:
        work->first_window=RetailCall_080d9b64(work->first_window);
        if(work->first_window)break;
        work->second_window=RetailCall_080d9b64(work->second_window);
        if(work->second_window)break;
        work->script=RetailCall_080d3f08(work->script);
        if(work->script)break;
        next_phase=2;
    store_phase:
        event->phase=next_phase;
        break;
    }
    return 0;
}
asm(".global RetailCall_080d3ec0\n.thumb_set RetailCall_080d3ec0, 0x080d3ec1\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64, 0x080d9b65\n.global RetailCall_080d9ba8\n.thumb_set RetailCall_080d9ba8, 0x080d9ba9\n.global RetailCall_080dab84\n.thumb_set RetailCall_080dab84, 0x080dab85\n.global RetailCall_080dac80\n.thumb_set RetailCall_080dac80, 0x080dac81\n.global RetailCall_080dbdc8\n.thumb_set RetailCall_080dbdc8, 0x080dbdc9\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608, 0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c, 0x080e064d\n.global RetailCall_080e0690\n.thumb_set RetailCall_080e0690, 0x080e0691\n");
