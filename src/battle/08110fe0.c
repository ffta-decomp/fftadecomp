typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,unknown2;void *record;u32 word8,word12,word16;u16 id,mode;u32 word24;} Event;
typedef struct BoundsView {u16 first; s16 y; u16 remaining[4];} BoundsView;
typedef u32(*Callback)(void*,Event*,void*);
typedef struct Work {u8 unknown0[4];u8 timer,variant,signal,mode;u8 unknown8[512];void *first,*second,*third,*request,*initial,*record,*record_effect,*fade;} Work;
void *RetailCall_080e03f8(void*,const void*,u8,u8,const void*,void*);
void RetailCall_080d38b4(void);
void *RetailCall_080e05dc(void*);
void *RetailCall_080dfd68(u8,u16,void*);
void *RetailCall_080dfed8(void*);
void *RetailCall_08005b6c(Callback,u16,const Event*,void*);
void RetailCall_0801cae0(u16*);
void *RetailCall_080d89d0(u32,u32,u32,u32,u32,u32,void*,void*,u32,u32,u32,u32,u32,void*);
void *RetailCall_080d8aec(void*);
void *RetailCall_080e051c(void*);
void *RetailCall_08115ae4(void*,u32,void*);
void *RetailCall_08115b40(void*);

s32 OriginalAuthoredSequence_00110FE0(void *parent,Event *event,Work *work)
{
    Event first_event;
    u16 bounds[6];
    Event second_event,third_event;
    switch((s32)event->phase) {
    case 0: {
        u8 count;
        register void *record asm("r4");
        work->mode=event->mode;
        asm volatile("mov r1, #135\n\tlsl r1, r1, #2\n\tadd r0, %2, r1\n\tldr %0, [%1, #4]\n\tstr %0, [r0]"
                     : "=&l"(record) : "l"(event), "l"(work) : "r0", "r1", "cc", "memory");
        count=7;
        if(work->mode!=0) count=0;
        work->initial=RetailCall_080e03f8(record,(const void*)0x083a2e70,count,4,0,parent);
        break;
    }
    case 1: RetailCall_080d38b4();break;
    case 256:
        if(work->mode!=0) {
            work->initial=RetailCall_080e05dc(work->initial);
            if(work->initial==0) event->phase=261;
        } else {
            if(work->fade==0) work->fade=RetailCall_080dfd68(1,30,parent);
            work->initial=RetailCall_080e05dc(work->initial);
            if(work->initial==0) {
                first_event.record=&work->signal;
                work->first=RetailCall_08005b6c((Callback)0x0810fd79,68,&first_event,parent);
                event->phase++;
            }
        }
        break;
    case 257: {
        u32 height,parameter,extent;
        s32 grid_y;
        register u8 *variant_ptr asm("r4");
        register BoundsView *bounds_ip asm("r12");
        register u32 signal asm("r0");
        work->fade=RetailCall_080dfed8(work->fade);
        if(work->fade!=0) break;
        signal=work->signal;
        asm("" : "+r"(signal));
        if(signal!=1) break;
        variant_ptr=&work->variant;
        asm("" : "+r"(variant_ptr));
        RetailCall_0801cae0(bounds);
        {
            register u32 height_word asm("r0");
            asm volatile("add %0, sp, #68\n\tmov r2, #156\n\tlsl r2, r2, #1\n\tldrh r1, [%0, #10]\n\tmov %1, %0\n\tmov r1, %1\n\tldrh %0, [r1, #10]\n\tlsr %0, %0, #3"
                         : "=&l"(height_word), "=r"(bounds_ip) : : "r1", "r2", "cc", "memory");
            height=height_word;
        }
        if(height>47) {
            parameter=0;extent=64;*variant_ptr=0;
        } else if(height>31) {
            parameter=4;extent=48;*variant_ptr=1;
        } else {
            parameter=3;extent=32;*variant_ptr=2;
        }
        grid_y=bounds_ip->y>>3;
        work->request=RetailCall_080d89d0(3,parameter,1,16,48,190,
            (void*)0x0600cc00,(void*)0x06005000,255,20,(u8)grid_y,24,extent,parent);
        work->timer=30;
        event->phase++;
        break;
    }
    case 258:
        if(work->timer!=0) {
            work->timer--;
            if(work->timer!=0) break;
        }
        work->request=RetailCall_080d8aec(work->request);
        if(work->request!=0) break;
        work->signal=2;
        work->second=RetailCall_08005b6c((Callback)0x081101dd,16,&second_event,parent);
        event->phase++;
        break;
    case 259:
        work->second=RetailCall_080e051c(work->second);
        if(work->second==0) event->phase++;
        break;
    case 260:
        third_event.id=work->variant;
        third_event.record=&work->signal;
        third_event.word8=(u32)work->record;
        work->third=RetailCall_08005b6c((Callback)0x08110889,800,&third_event,parent);
        event->phase++;
        break;
    case 261:
        work->first=RetailCall_080e051c(work->first);
        if(work->first!=0) break;
        work->signal=6;
        event->phase++;
        break;
    case 262:
        work->third=RetailCall_080e051c(work->third);
        if(work->third!=0) break;
        work->record_effect=RetailCall_08115ae4(work->record,1,parent);
        event->phase++;
        break;
    case 263:
        work->record_effect=RetailCall_08115b40(work->record_effect);
        if(work->record_effect==0) event->phase=2;
        break;
    }
    return 0;
}
asm(".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n");
asm(".global RetailCall_0801cae0\n.thumb_set RetailCall_0801cae0,0x0801cae1\n");
asm(".global RetailCall_080d38b4\n.thumb_set RetailCall_080d38b4,0x080d38b5\n");
asm(".global RetailCall_080d89d0\n.thumb_set RetailCall_080d89d0,0x080d89d1\n");
asm(".global RetailCall_080d8aec\n.thumb_set RetailCall_080d8aec,0x080d8aed\n");
asm(".global RetailCall_080dfd68\n.thumb_set RetailCall_080dfd68,0x080dfd69\n");
asm(".global RetailCall_080dfed8\n.thumb_set RetailCall_080dfed8,0x080dfed9\n");
asm(".global RetailCall_080e03f8\n.thumb_set RetailCall_080e03f8,0x080e03f9\n");
asm(".global RetailCall_080e051c\n.thumb_set RetailCall_080e051c,0x080e051d\n");
asm(".global RetailCall_080e05dc\n.thumb_set RetailCall_080e05dc,0x080e05dd\n");
asm(".global RetailCall_08115ae4\n.thumb_set RetailCall_08115ae4,0x08115ae5\n");
asm(".global RetailCall_08115b40\n.thumb_set RetailCall_08115b40,0x08115b41\n");
