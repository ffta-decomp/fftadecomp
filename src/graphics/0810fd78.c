typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,pad2;u8 *handshake;u32 opaque8[5];} Event;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u16 timer;s16 x,y;u16 pad6;u32 q16,velocity;u8 *handshake;void *sprite,*background,*sequence,*sequence2;Ramp width,y_path;void *extra,*extra2;} Work;
void *RetailCall_080d3e9c(const void*,void*);void *RetailCall_080d3f08(void*);void *RetailCall_080d4704(const void*,void*);void *RetailCall_080d4774(void*);
void *RetailCall_080d5cc0(const void*,u32,s32,s32,u16,u8,u8,u8);void RetailCall_0801121c(void*,s32);void RetailCall_08011428(void*);void RetailCall_080107d4(void*,s32,s32,u16);
void RetailCall_080d7220(const void*,u32,u32,u32,u32,u32);void *RetailCall_080dfd8c(const void*,u8,u16,u16,void*);
void RetailCall_080e0608(Ramp*,s32,s32,u16);void RetailCall_080e064c(Ramp*);u32 RetailCall_080e0690(const Ramp*);
void RetailCall_0814186c(const void*,void*,u32);u32 RetailCall_080035a8(u32);u32 RetailCall_080035d0(u32);
extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
#define CONTROL (*(volatile u16*)display_shadow)
typedef char WorkMustBe68[sizeof(Work)==68?1:-1];
s32 RemainingBand43_0010FD78(void *parent,Event *event,Work *work)
{
    volatile u16 palette_a,palette_b,palette_clear;
    u16 phase=event->phase;
    switch(phase) {
    case 0:
        work->handshake=event->handshake;
        *work->handshake=(u8)phase;
        work->background=RetailCall_080d3e9c((const void*)0x083a2ed2,parent);
        display_shadow[59]=68;
        display_shadow[58]=172;
        palette_a=0x7fff;
        RetailCall_0814186c((const void*)&palette_a,(void*)0x03003920,0x01000010);
        display_shadow[66]=63;
        display_shadow[68]=63&~RetailCall_080035d0(2);
        display_shadow[63]=(u8)phase;
        display_shadow[62]=255;
        {register u32 control __asm__("r1")=CONTROL;
         register u32 mask __asm__("r3")=0x2000;
         register u32 combined __asm__("r0");
         asm("" : "+r"(control), "+r"(mask));
         combined=mask; asm("" : "+r"(combined));
         combined|=control; CONTROL=combined;}
        RetailCall_080d7220((const void*)0x088f46cc,0,2,0,phase,phase);
        work->extra=RetailCall_080dfd8c((const void*)0x083a2ee8,1,4,0,
            ({register void *parent_arg __asm__("r1"); asm("mov %0, %1" : "=l"(parent_arg) : "h"(parent)); parent_arg;}));
        break;
    case 1:
        break;
    case 256:
        work->background=RetailCall_080d3f08(work->background);
        if(work->background!=0) break;
        palette_b=({register u32 value __asm__("r2")=0x7fff;
                    register u32 stored __asm__("r1");
                    asm("" : "+r"(value)); stored=value;
                    asm("" : "+r"(stored)); stored;});
        RetailCall_0814186c((const void*)&palette_b,(void*)0x03003b20,0x01000010);
        work->x=120;
        work->y=-8;
        work->q16=(u32)(s32)work->y<<16;
        work->velocity=0x2e666;
        work->sprite=RetailCall_080d5cc0((const void*)0x08501d1c,0,120,work->y,920,6,0,0);
        RetailCall_0801121c(work->sprite,-1);
        work->timer=20;
        event->phase++;
        break;
    case 257:
        if(work->timer!=0) {
            work->timer--;
            if(work->timer==0) {
                work->sequence=RetailCall_080d4704((const void*)0x0894a8a4,parent);
                RetailCall_080e0608(&work->width,52,0,60);
                work->extra2=RetailCall_080dfd8c((const void*)0x083a2ef0,1,4,0,parent);
            }
        } else {
            Ramp *width=&work->width;
            u32 done=(u8)RetailCall_080e0690(width);
            if(done==0) {
                RetailCall_080e064c(width);
                display_shadow[59]=120-work->width.value;
                display_shadow[58]=120+work->width.value;
                if((u8)RetailCall_080e0690(width)!=0) {
                    palette_clear=done;
                    RetailCall_0814186c((const void*)&palette_clear,(void*)0x03003920,0x01000010);
                    display_shadow[74]=0;
                    CONTROL=0xdfff&CONTROL;
                    CONTROL&=~RetailCall_080035a8(2);
                    work->sequence2=RetailCall_080d4704((const void*)0x0894a8e4,parent);
                }
            }
        }
        {
            register u32 position __asm__("r0")=work->q16;
            register u32 velocity __asm__("r1")=work->velocity;
            s32 y;
            asm("" : "+r"(position), "+r"(velocity));
            position+=velocity;
            work->q16=position;
            velocity+=0xfffff852;
            work->velocity=velocity;
            if(velocity<=0x1998) work->velocity=0x1999;
            y=*((s16*)&work->q16+1);
            work->y=y;
            if(y>135) {
                work->y=136;
                *work->handshake=1;
                event->phase++;
            }
        }
        RetailCall_080107d4(work->sprite,work->x,work->y,0);
        work->sequence=RetailCall_080d4774(work->sequence);
        break;
    case 258: {
        register u32 i __asm__("r2")=0;
        u16 timer=work->timer;
        register void *sprite __asm__("r4")=work->sprite;
        register const u8 *thresholds __asm__("r6")=(const u8*)0x083a2ecb;
        register const s8 *steps __asm__("r3")=(const s8*)0x083a2ec4;
        asm("" : "+r"(sprite), "+r"(thresholds), "+r"(steps));
    search_258:
        if(timer==({register const u8 *address __asm__("r0");
                    asm("add %0, %1, %2" : "=l"(address) : "l"(i), "l"(thresholds)); *address;})) {
            if(({register const s8 *address __asm__("r0");
                 asm("add %0, %1, %2" : "=l"(address) : "l"(i), "l"(steps)); *address;})==0) {work->timer=0;i=0;}
            {register u32 raw_step __asm__("r0");
             asm("add %0, %1, %2" : "=l"(raw_step) : "l"(i), "l"(steps));
             raw_step=*(const u8*)raw_step;
             asm("" : "+r"(raw_step));
             work->y=(u16)work->y+(s8)raw_step;}
            timer=work->timer;
        } else {
            {register u32 raw_next __asm__("r0")=i+1;
             asm("" : "+r"(raw_next)); i=(u8)raw_next;}
            if(i<=6) goto search_258;
        }
        work->timer=timer+1;
        RetailCall_080107d4(sprite,work->x,work->y,0);
        if(*work->handshake!=2) break;
        work->sequence2=RetailCall_080d4774(work->sequence2);
        if(work->sequence2!=0) break;
        event->phase++;
        break;
    }
    case 259: {
        register u32 i __asm__("r2")=0;
        u16 timer=work->timer;
        register void *sprite __asm__("r4")=work->sprite;
        register const u8 *thresholds __asm__("r6")=(const u8*)0x083a2ecb;
        register const s8 *steps __asm__("r3")=(const s8*)0x083a2ec4;
        asm("" : "+r"(sprite), "+r"(thresholds), "+r"(steps));
    search_259:
        if(timer==({register const u8 *address __asm__("r0");
                    asm("add %0, %1, %2" : "=l"(address) : "l"(i), "l"(thresholds)); *address;})) {
            if(({register const s8 *address __asm__("r0");
                 asm("add %0, %1, %2" : "=l"(address) : "l"(i), "l"(steps)); *address;})==0) {work->timer=0;i=0;}
            {register u32 raw_step __asm__("r0");
             asm("add %0, %1, %2" : "=l"(raw_step) : "l"(i), "l"(steps));
             raw_step=*(const u8*)raw_step;
             asm("" : "+r"(raw_step));
             work->y=(u16)work->y+(s8)raw_step;}
            timer=work->timer;
        } else {
            {register u32 raw_next __asm__("r0")=i+1;
             asm("" : "+r"(raw_next)); i=(u8)raw_next;}
            if(i<=6) goto search_259;
        }
        work->timer=timer+1;
        RetailCall_080107d4(sprite,work->x,work->y,0);
        if(*work->handshake!=3) break;
        RetailCall_080e0608(&work->y_path,work->y,256,180);
        work->timer=0;
        event->phase++;
        break;
    }
    case 260: {
        Ramp *path=&work->y_path;
        RetailCall_080e064c(path);
        work->y=work->y_path.value;
        RetailCall_080107d4(work->sprite,work->x,work->y,0);
        if(++work->timer==170) *work->handshake=4;
        if((u8)RetailCall_080e0690(path)==0) break;
        RetailCall_080e0608(path,work->y,-8,20);
        event->phase++;
        break;
    }
    case 261: {
        Ramp *path=&work->y_path;
        RetailCall_080e064c(path);
        work->y=work->y_path.value;
        RetailCall_080107d4(work->sprite,work->x,work->y,0);
        if(++work->timer==184) *work->handshake=5;
        if((u8)RetailCall_080e0690(path)==0) break;
        RetailCall_08011428(work->sprite);
        work->sprite=0;
        event->phase=2;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080035d0\n.thumb_set RetailCall_080035d0, 0x080035d1\n.global RetailCall_080107d4\n.thumb_set RetailCall_080107d4, 0x080107d5\n.global RetailCall_0801121c\n.thumb_set RetailCall_0801121c, 0x0801121d\n.global RetailCall_08011428\n.thumb_set RetailCall_08011428, 0x08011429\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c, 0x080d3e9d\n.global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08, 0x080d3f09\n.global RetailCall_080d4704\n.thumb_set RetailCall_080d4704, 0x080d4705\n.global RetailCall_080d4774\n.thumb_set RetailCall_080d4774, 0x080d4775\n.global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0, 0x080d5cc1\n.global RetailCall_080d7220\n.thumb_set RetailCall_080d7220, 0x080d7221\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608, 0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c, 0x080e064d\n.global RetailCall_080e0690\n.thumb_set RetailCall_080e0690, 0x080e0691\n.global RetailCall_0814186c\n.thumb_set RetailCall_0814186c, 0x0814186d\n");
