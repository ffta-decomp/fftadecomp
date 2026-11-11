typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,pad2;u32 opaque4[4];u16 x,y;u32 opaque24;} Event;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u16 opaque0,x,y,pad6;Ramp x_path,y_path;u32 opaque32;} Work;
void RetailCall_080d74e0(u32,u32,u32,s32,s32,void*,void*);
void RetailCall_080e0608(Ramp*,s32,s32,u16);void RetailCall_080e064c(Ramp*);u32 RetailCall_080e0690(const Ramp*);
u32 RetailCall_080035d0(u32);u32 RetailCall_080035a8(u32);void RetailCall_08003508(s32,u32);void RetailCall_08003558(s32,u32);

extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
#define CONTROL (*(volatile u16*)display_shadow)
s32 RemainingBand43_00114DBC(void *parent,Event *event,Work *work)
{
    register u32 next_phase asm("r0");
    switch(event->phase) {
    case 0:
        work->x=event->x;
        work->y=event->y;
        break;
    case 256:
        RetailCall_080d74e0(1,2,1,(s16)(work->x+88),(s16)(work->y-232),(void*)0x06008000,(void*)0x06007000);
        RetailCall_080e0608(&work->x_path,-88,120,30);
        RetailCall_080e0608(&work->y_path,232,112,30);
        display_shadow[59]=0;
        display_shadow[58]=0;
        display_shadow[63]=0;
        display_shadow[62]=160;
        display_shadow[66]=63;
        display_shadow[68]=63&~RetailCall_080035d0(1);
        {
            register volatile u8 *base asm("r5")=display_shadow;
            asm volatile("ldrh r1,[%0]\nmov r2,#128\nlsl r2,r2,#6\nmov r0,r2\norr r0,r1\nstrh r0,[%0]" : : "r"(base) : "r0","r1","r2","cc","memory");
        }
        next_phase=event->phase+1;
        asm("" : "+r"(next_phase));
        goto store_phase;
    case 257: {
        Ramp *x_path;
        u16 x_value;
        register volatile u8 *stage_base asm("r5");
        {
            register u32 mask asm("r0")=RetailCall_080035a8(1);
            stage_base=display_shadow;
            asm volatile("ldrh r1,[%0]\norr r1,%1\nstrh r1,[%0]" : : "r"(stage_base),"r"(mask) : "r1","cc","memory");
        }
        x_path=&work->x_path;
        RetailCall_080e064c(x_path);
        RetailCall_080e064c(&work->y_path);
        x_value=work->x_path.value;
        if(*(s16*)&work->x_path.value>0) {
            register u32 consumed_x asm("r1")=x_value;
            asm volatile("ldrb r2,[%1,#2]\nadd r0,%0,r2\nmov r2,%2\nadd r2,#58\nldrb %0,[r2]\nstrb r0,[r2]"
                : "+r"(consumed_x) : "l"(work),"r"(stage_base) : "r0","r2","cc","memory");
        }
        RetailCall_08003508((s16)(work->x-work->x_path.value),1);
        RetailCall_08003558((s16)(work->y-work->y_path.value),1);
        if((u8)RetailCall_080e0690(x_path)==0) break;
        *(volatile u16*)stage_base=0xdfff&*(volatile u16*)stage_base;
        next_phase=event->phase+1;
        asm("" : "+r"(next_phase));
        goto store_phase;
    }
    case 258:
        next_phase=2;
    store_phase:
        event->phase=next_phase;
        break;
    }
    return 0;
}
asm(".global RetailCall_08003508\n.thumb_set RetailCall_08003508, 0x08003509\n.global RetailCall_08003558\n.thumb_set RetailCall_08003558, 0x08003559\n.global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080035d0\n.thumb_set RetailCall_080035d0, 0x080035d1\n.global RetailCall_080d74e0\n.thumb_set RetailCall_080d74e0, 0x080d74e1\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608, 0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c, 0x080e064d\n.global RetailCall_080e0690\n.thumb_set RetailCall_080e0690, 0x080e0691\n");
