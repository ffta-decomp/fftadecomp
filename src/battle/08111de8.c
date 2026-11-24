typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,pad2;void **pair;u32 opaque8[5];} Event;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u16 delay;u8 pad2[6];Ramp y_a,y_b,size_a,size_b;void *child;void **pair;} Work;
void *RetailCall_080d3e9c(const void*,void*);void *RetailCall_080d3f08(void*);void RetailCall_080e0608(Ramp*,s32,s32,u16);void RetailCall_080e064c(Ramp*);u32 RetailCall_080e0690(const Ramp*);
void RetailCall_080dadfc(void*);void RetailCall_080dac80(void*,u32,s32,u32,u16);
extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
#define CONTROL (*(volatile u16*)display_shadow)
s32 RemainingBand43_00111DE8(void *parent,Event *event,Work *work)
{
    switch(event->phase) {
    case 0:
        work->pair=event->pair;
        display_shadow[66]=31;
        display_shadow[67]=63;
        display_shadow[68]=31;
        {
            register volatile u8 *base asm("r3")=display_shadow;
            asm volatile("ldrh r1,[%0]\nmov r2,#192\nlsl r2,r2,#7\nmov r0,r2\norr r0,r1\nstrh r0,[%0]"
                : : "r"(base) : "r0","r1","r2","cc","memory");
        }
        work->child=RetailCall_080d3e9c((const void*)0x0894dbb0,parent);
        RetailCall_080e0608(&work->y_a,124,124,39);
        RetailCall_080e0608(&work->size_a,4,120,39);
        work->delay=8;
        RetailCall_080e0608(&work->y_b,124,127,35);
        RetailCall_080e0608(&work->size_b,4,120,35);
        break;
    case 1:
        break;
    case 256: {
        Ramp *size_a;
        void *child;
        if(work->delay!=0) work->delay--;
        RetailCall_080dadfc(work->pair[0]);
        if(work->delay==0) RetailCall_080dadfc(work->pair[1]);
        {
            void *window=work->pair[0];
            register s32 y asm("r2")=(s16)work->y_a.value;
            u16 size;
            asm("" : "+r"(y));
            size=work->size_a.value;
            RetailCall_080dac80(window,120,y,size,(u16)((s16)size>>2));
        }
        if(work->delay==0) {
            void *window=work->pair[1];
            register s32 y asm("r2")=(s16)work->y_b.value;
            u16 size;
            asm("" : "+r"(y));
            size=work->size_b.value;
            RetailCall_080dac80(window,120,y,size,(u16)((s16)size>>2));
        }
        RetailCall_080e064c(&work->y_a);
        size_a=&work->size_a;
        RetailCall_080e064c(size_a);
        if(work->delay==0) {
            RetailCall_080e064c(&work->y_b);
            RetailCall_080e064c(&work->size_b);
        }
        child=RetailCall_080d3f08(work->child);
        work->child=child;
        if(child!=0) break;
        if((u8)RetailCall_080e0690(size_a)==0) break;
        if((u8)RetailCall_080e0690(&work->size_b)==0) break;
        display_shadow[74]=(u32)child;
        CONTROL=0x9fff&CONTROL;
        event->phase=2;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08,0x080d3f09\n.global RetailCall_080dac80\n.thumb_set RetailCall_080dac80,0x080dac81\n.global RetailCall_080dadfc\n.thumb_set RetailCall_080dadfc,0x080dadfd\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n.global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n");
