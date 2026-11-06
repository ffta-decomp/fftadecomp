typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct Event {u16 phase,pad;void *record;} Event;
typedef struct Tween {u32 current;u8 opaque4[40];} Tween;
typedef struct Work {u8 active,pad1;u16 timer,seed,rows[160];u8 step_a,step_b;u16 phase,unknown330;void *record;Tween motion,fade_a,fade_b;void *scan_a,*scan_b,*aux_a,*aux_b;} Work;
typedef struct Template {u8 opaque0[16];const u16 *seed;u8 opaque20[12];} Template;
extern const Template InitialTemplate __asm__("0x08149CE8");
typedef struct Shadow {u16 control;u8 pad2[72];volatile u8 b74,b75,b76,b77;} Shadow;
#define SHADOW ((Shadow*)0x03000940)
u32 RemainingBand43_000ED4E8(void *,Event *,Work *);
void *RetailCall_080d9914(u32,u32,void *);void RetailCall_080d9ba8(void *,u32);void *RetailCall_080d9a24(u32,u32,u32,u32,void *);
void RetailCall_0801e610(u8 *,u8 *);u32 RetailCall_080035f8(u32);u32 RetailCall_080035a8(u32);
void RetailCall_080075cc(Tween *,s32,s32,s32,s32);void RetailCall_080076a0(Tween *);u32 RetailCall_08007880(Tween *);
void *RetailCall_080dfd8c(const void *,u32,u32,u32,void *);void RetailCall_080d9b38(void *);
void RetailCall_080ed308(Work *);void RetailCall_080ed3b8(Work *);

u32 RemainingBand43_000ED4E8(void *parent_in,Event *event_in,Work *work_in) {
    register void *parent asm("r9") = parent_in;
    register Event *event asm("r6") = event_in;
    Work *work = work_in;
    s32 phase,next_phase;
    asm("" : "+r"(parent), "+r"(event));
    phase=event->phase;
    switch(phase) {
    case 0: {
        Template initial=InitialTemplate;
        volatile u8 layer_a,layer_b;
        u32 seed_value,mask,initial_layer;
        register u32 shadow_zero asm("r10");
        void *scan_a,*scan_b;
        u16 row,value;
        register Shadow *shadow asm("r8");
        register Shadow *first_shadow asm("r3");
        seed_value=*initial.seed;
        shadow_zero=0;
        asm("" : "+r"(shadow_zero));
        work->seed=seed_value;
        scan_a=RetailCall_080d9914(2,0,parent);
        RetailCall_080d9ba8(scan_a,1);
        work->scan_a=scan_a;
        scan_b=RetailCall_080d9a24(0,16,0,0,parent);
        asm volatile("add r0, sp, #36\n\tmov r1, sp\n\tadd r1, #37\n\tbl RetailCall_0801e610" : : : "r0", "r1", "r2", "r3", "lr", "cc", "memory");
        initial_layer=RetailCall_080035f8(2);
        first_shadow=SHADOW;
        shadow=first_shadow;
        asm("" : "+r"(first_shadow), "+r"(shadow));
        first_shadow->b74=initial_layer|64;
        mask=RetailCall_080035f8(layer_a);
        mask|=RetailCall_080035f8(layer_b);
        { register u32 actual_mask asm("r4") = mask;
          asm volatile("mov r0, #48\n\tmov r2, r8\n\tadd r2, #75\n\tldrb r1, [r2]\n\torr r4, r0\n\tstrb r4, [r2]\n\tmov r0, r8\n\tadd r0, #76\n\tldrb r1, [r0]\n\tmov r4, r10\n\tstrb r4, [r0]" : "+r"(actual_mask) : "r"(shadow), "r"(shadow_zero) : "r0", "r1", "r2", "cc", "memory"); }
        asm volatile("mov r1, r8\n\tadd r1, #77\n\tldrb r0, [r1]\n\tmov r0, #16\n\tstrb r0, [r1]" : : "r"(shadow) : "r0", "r1", "cc", "memory");
        asm volatile("mov r1, #236\n\tlsl r1, r1, #1\n\tadd r0, %0, r1\n\tstr %1, [r0]" : : "r"(work), "r"(scan_b) : "r0", "r1", "cc", "memory");
        { register Tween *actual_motion asm("r0");
          asm volatile("mov r2, #168\n\tlsl r2, r2, #1\n\tadd %0, %1, r2" : "=r"(actual_motion) : "r"(work) : "r2", "cc");
          RetailCall_080075cc(actual_motion,160,0,-31,30); }
        work->active=1;
        value=0;row=0;
        do {
            work->rows[row]=value;
            if(row&1)value=(u16)(value-1);
            row=(u16)(row+1);
        }while(row<=159);
        work->record=event->record;
        work->aux_a=RetailCall_080dfd8c((void*)0x083993AC,1,4,0,parent);
        break;
    }
    case 1:break;
    case 256: {
        Tween *motion=&work->motion;
        RetailCall_080076a0(motion);
        RetailCall_080ed308(work);
        if(RetailCall_08007880(motion)) {
            register s32 advanced_phase asm("r0");
            work->timer=210;
            RetailCall_080d9b38(work->scan_b);
            advanced_phase=event->phase+1;
            asm("" : "+r"(advanced_phase));
            next_phase=advanced_phase;goto store_phase;
        }
        break;
    }
    case 257: {
        register s32 advanced_phase asm("r0");
        SHADOW->b76=16;SHADOW->b77=16;
        advanced_phase=event->phase+1;
        asm("" : "+r"(advanced_phase));
        next_phase=advanced_phase;goto store_phase;
    }
    case 258: {
        u32 remaining=work->timer-1;
        work->timer=remaining;
        if(!(u16)remaining) {
            register s32 advanced_phase asm("r0");
            work->timer=10;
            RetailCall_080075cc(&work->fade_a,16,0,0,15);
            RetailCall_080075cc(&work->fade_b,16,0,16,15);
            work->aux_b=RetailCall_080dfd8c((void*)0x083993B4,3,4,0,parent);
            advanced_phase=event->phase+1;
            asm("" : "+r"(advanced_phase));
            next_phase=advanced_phase;goto store_phase;
        }
        break;
    }
    case 259: {
        u16 row=0;
        u32 remaining;
        Tween *fade_a;
        register Shadow *fade_shadow asm("r4");
        do {
            work->rows[row]+=4;
            row=(u16)(row+1);
        }while(row<=159);
        remaining=work->timer;
        if(!remaining) goto fade_now;
        --remaining;work->timer=remaining;
        if(!(u16)remaining) {
fade_now:
            RetailCall_080076a0(&work->fade_a);
            RetailCall_080076a0(&work->fade_b);
        }
        fade_shadow=SHADOW;
        asm("" : "+r"(fade_shadow));
        fade_a=&work->fade_a;
        fade_shadow->b76=fade_a->current;
        { register u32 fade_b_value asm("r1") = work->fade_b.current;
          register volatile u8 *fade_byte asm("r3") = &fade_shadow->b77;
          asm("" : "+r"(fade_b_value), "+r"(fade_byte));
          (void)*fade_byte;
          *fade_byte=fade_b_value; }
        if(RetailCall_08007880(fade_a)) {
            register s32 advanced_phase asm("r0");
            fade_shadow->control&=~RetailCall_080035a8(2);
            advanced_phase=event->phase+1;
            asm("" : "+r"(advanced_phase));
            next_phase=advanced_phase;goto store_phase;
        }
        break;
    }
    case 260:
        work->active=0;
        RetailCall_080d9b38(work->scan_a);
        next_phase=2;
store_phase:
        event->phase=next_phase;
        break;
    }
    if(work->active)RetailCall_080ed3b8(work);
    return 0;
}
asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_080035f8\n.thumb_set RetailCall_080035f8, 0x080035f9\n.global RetailCall_080075cc\n.thumb_set RetailCall_080075cc, 0x080075cd\n.global RetailCall_080076a0\n.thumb_set RetailCall_080076a0, 0x080076a1\n.global RetailCall_08007880\n.thumb_set RetailCall_08007880, 0x08007881\n.global RetailCall_0801e610\n.thumb_set RetailCall_0801e610, 0x0801e611\n.global RetailCall_080d9914\n.thumb_set RetailCall_080d9914, 0x080d9915\n.global RetailCall_080d9a24\n.thumb_set RetailCall_080d9a24, 0x080d9a25\n.global RetailCall_080d9b38\n.thumb_set RetailCall_080d9b38, 0x080d9b39\n.global RetailCall_080d9ba8\n.thumb_set RetailCall_080d9ba8, 0x080d9ba9\n.global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c, 0x080dfd8d\n.global RetailCall_080ed308\n.thumb_set RetailCall_080ed308, 0x080ed309\n.global RetailCall_080ed3b8\n.thumb_set RetailCall_080ed3b8, 0x080ed3b9\n");
