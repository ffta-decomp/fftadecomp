typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,pad2;void *payload;u32 opaque8[5];} Event;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u16 timer;u8 opaque2[6];void *holder,*child_a,*child_b,*child_c,*child_d;Ramp ramp_a,ramp_b,ramp_c;void *background,*window_a,*window_b,*extra;} Work;
void *RetailCall_080dab84(u32,u32,u32,void*);void RetailCall_080d9ba8(void*,u32);void *RetailCall_080d9b64(void*);
void *RetailCall_080d3e9c(const void*,void*);void RetailCall_080d3efc(void*);
void RetailCall_080e0608(Ramp*,s32,s32,u16);void RetailCall_080e064c(Ramp*);
void RetailCall_080dabc4(void*,s32,u32,s32,u32,u32);void RetailCall_080dadfc(void*);void RetailCall_080dac40(void*,u32,u32,u32);
void *RetailCall_08005b6c(void*,u32,Event*,void*);void *RetailCall_080dfd8c(const void*,u32,u32,u32,void*);void *RetailCall_080e051c(void*);
extern volatile u8 display_shadow[];
asm(".global display_shadow\n.set display_shadow,0x03000940");
#define CONTROL (*(volatile u16*)display_shadow)
typedef char EventMustBe28[(sizeof(Event)==28)?1:-1];
typedef char WorkMustBe80[(sizeof(Work)==80)?1:-1];
s32 RemainingBand43_001120CC(void *parent,Event *event,Work *work)
{
    Event event_a,event_b;
    u16 phase=event->phase;
    switch(phase) {
    case 0:
        work->holder=event->payload;
        work->window_a=RetailCall_080dab84(1,0,240,parent);
        work->window_b=RetailCall_080dab84(0,0,0,parent);
        RetailCall_080d9ba8(work->window_a,1);
        RetailCall_080d9ba8(work->window_b,1);
        display_shadow[59]=phase;
        display_shadow[58]=phase;
        display_shadow[63]=phase;
        display_shadow[62]=160;
        display_shadow[61]=phase;
        display_shadow[60]=phase;
        display_shadow[65]=phase;
        display_shadow[64]=160;
        display_shadow[66]=63;
        display_shadow[67]=63;
        display_shadow[68]=31;
        {
            register volatile u8 *shadow asm("r3")=display_shadow;
            asm volatile("ldrh r1, [%0]\n\tmov r2, #192\n\tlsl r2, r2, #7\n\tadd r0, r2, #0\n\torr r0, r1\n\tstrh r0, [%0]"
                         : : "l"(shadow) : "r0", "r1", "r2", "cc", "memory");
        }
        work->background=RetailCall_080d3e9c((const void*)0x0894dbdc,parent);
        RetailCall_080e0608(&work->ramp_a,12,0,4);
        RetailCall_080e0608(&work->ramp_c,40,12,4);
        break;
    case 1:
        break;
    case 256: {
        u32 timer;
        register s32 origin asm("r4");
        register u32 shared_zero asm("r9");
        register u32 later_zero asm("r5");
        register u32 limit asm("r5");
        {
            register void *window asm("r0")=work->window_a;
            register u32 actual_value asm("r2")=work->ramp_a.value;
            register s32 left asm("r1");
            register s32 negative asm("r5");
            register u32 origin_input asm("r5")=308;
            asm("" : "+r"(window), "+r"(actual_value));
            asm("" : "+r"(origin_input));
            origin=origin_input;
            asm("" : "+r"(origin));
            left=(s16)(origin-actual_value);
            asm volatile("mov %0, #68\n\tneg %0, %0"
                         : "=l"(negative) : "l"(window), "l"(actual_value), "l"(left) : "cc");
            {
                register s32 right asm("r3")=negative;
                asm("" : "+r"(right) : "l"(window), "l"(left), "l"(actual_value));
                right-=actual_value;
                asm("" : "+r"(right) : "l"(window), "l"(left));
                right=(s16)right;
                asm("" : "+r"(right) : "l"(window), "l"(left));
                asm volatile("mov %3, #248\n\tstr %3, [sp]\n\tmov r2, #0\n\tmov %4, r2\n\tstr r2, [sp, #4]\n\tbl RetailCall_080dabc4"
                             : "+l"(window), "+l"(left), "+l"(right), "=l"(limit), "=r"(shared_zero)
                             : : "r2", "r12", "lr", "cc", "memory");
            }
        }
        {
            register void *window asm("r0")=work->window_a;
            register u32 actual_value asm("r3")=work->ramp_a.value;
            asm("" : "+r"(window), "+r"(actual_value), "+r"(origin));
            origin=(s16)(actual_value+origin);
            asm("" : "+r"(origin));
            RetailCall_080dabc4(window,origin,0,(s16)(actual_value-68),limit,1);
        }
        RetailCall_080dadfc(work->window_b);
        RetailCall_080dac40(work->window_b,120,124,work->ramp_c.value);
        RetailCall_080e064c(&work->ramp_a);
        RetailCall_080e064c(&work->ramp_c);
        timer=work->timer+1;
        work->timer=timer;
        if((u16)timer<=5) break;
        RetailCall_080d3efc(work->background);
        later_zero=shared_zero;
        asm("" : "+r"(later_zero));
        work->background=(void *)later_zero;
        work->child_a=RetailCall_08005b6c((void*)0x08111c7d,28,&event_a,parent);
        event_a.payload=work->holder;
        work->child_b=RetailCall_08005b6c((void*)0x08111d51,16,&event_a,parent);
        event_a.payload=&work->window_a;
        work->child_c=RetailCall_08005b6c((void*)0x08111de9,68,&event_a,parent);
        work->extra=RetailCall_080dfd8c((const void*)0x083a33cc,1,4,0,parent);
        work->timer=later_zero;
        event->phase++;
        break;
    }
    case 257:
        RetailCall_080e064c(&work->ramp_b);
        RetailCall_080e064c(&work->ramp_c);
        if(work->timer<=7) {
            work->timer++;
            break;
        }
        work->child_a=RetailCall_080e051c(work->child_a);
        if(work->child_a!=0) break;
        work->child_b=RetailCall_080e051c(work->child_b);
        if(work->child_b!=0) break;
        work->child_c=RetailCall_080e051c(work->child_c);
        if(work->child_c!=0) break;
        work->timer=1;
        event->phase++;
        break;
    case 258: {
        u32 timer=work->timer-1;
        work->timer=timer;
        if((u16)timer!=0) break;
        event_b.payload=work->holder;
        work->child_d=RetailCall_08005b6c((void*)0x08111f61,40,&event_b,parent);
        event->phase++;
        break;
    }
    case 259:
        work->window_a=RetailCall_080d9b64(work->window_a);
        if(work->window_a!=0) break;
        work->window_b=RetailCall_080d9b64(work->window_b);
        if(work->window_b!=0) break;
        work->child_d=RetailCall_080e051c(work->child_d);
        if(work->child_d!=0) break;
        event->phase=2;
        break;
    }
    return 0;
}
asm(".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n.global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d\n.global RetailCall_080d3efc\n.thumb_set RetailCall_080d3efc,0x080d3efd\n.global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64,0x080d9b65\n.global RetailCall_080d9ba8\n.thumb_set RetailCall_080d9ba8,0x080d9ba9\n.global RetailCall_080dab84\n.thumb_set RetailCall_080dab84,0x080dab85\n.global RetailCall_080dabc4\n.thumb_set RetailCall_080dabc4,0x080dabc5\n.global RetailCall_080dac40\n.thumb_set RetailCall_080dac40,0x080dac41\n.global RetailCall_080dadfc\n.thumb_set RetailCall_080dadfc,0x080dadfd\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d\n.global RetailCall_080e051c\n.thumb_set RetailCall_080e051c,0x080e051d\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n");
