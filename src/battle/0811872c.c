typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;typedef signed short s16;
typedef void (*Callback)(void*,u16*,void*);
typedef struct Work {u16 unknown0,unknown2,unknown4;u8 count,timer,index,mode,unknown10,unknown11;u8 done[5];u8 unknown17[7];void *row_children[5],*second,*first,*record,*initial,*target_children[5],*sequence;} Work;
void *RetailCall_080e03f8(void*,const void*,u8,u8,const s16*,void*);
void RetailCall_080d38b4(void);
void *RetailCall_080e05dc(void*);
u32 RetailCall_080dd494(void*);
u32 RetailCall_080d8924(void*,u16,u16,void*);
void *RetailCall_08005b6c(Callback,u16,const u32*,void*);
void *RetailCall_080dfd8c(const void*,u8,u16,u16,void*);
void RetailCall_080e0540(void**,u16);
u8 RetailCall_080dbab8(void**,u32);
void *RetailCall_080dd4a4(void*,u8);
void *RetailCall_080dcfe4(void*,const void*,u8,u16,u16,void*,u16);
/* This alias is used only on the branch where its seventh stack word is zero. */
void *RetailCall_080dcfe4_zero_word(void*,const void*,u8,u16,u16,void*,u32);
void *RetailCall_080e051c(void*);

s32 OriginalActionCallback_0011872C(void *parent,u16 *event,Work *work)
{
    u32 row_event[7], paired_event[7];
    switch ((s32)event[0]) {
    case 0: {
        u8 mode;
        u16 incoming_mode=event[11];
        work->mode=incoming_mode;
        work->record=((void**)event)[1];
        mode=5;
        if ((u8)incoming_mode!=0) mode=0;
        work->initial=RetailCall_080e03f8(work->record,(const void*)0x083a6068,mode,1,0,parent);
        {
            register volatile u16 *palette_base asm("r0")=(volatile u16*)0x03003860;
            asm("" : "+r"(palette_base));
            palette_base+=113;
            asm("" : "+r"(palette_base));
            {
                register u32 palette_color asm("r1")=0x39ce;
                asm("" : "+r"(palette_color));
                *palette_base=palette_color;
            }
        }
        break;
    }
    case 1: RetailCall_080d38b4();break;
    case 256:
        work->initial=RetailCall_080e05dc(work->initial);
        if(work->initial!=0) break;
        work->count=RetailCall_080dd494(work->record);
        if(work->mode!=0) {
            work->timer=1;
            RetailCall_080d8924(work->record,0,20,parent);
            work->timer=1;
            if(work->count==0) {
                register u32 phase_value asm("r0")=261;
                asm("" : "+r"(phase_value));
                event[0]=phase_value;
            } else {
                register u32 phase_value asm("r0")=260;
                asm("" : "+r"(phase_value));
                event[0]=phase_value;
            }
        } else event[0]++;
        break;
    case 257: {
        register u32 index asm("r4");
        asm volatile("ldr r0, [%2, #52]\n\tstr r0, %1\n\tmov %0, #0"
                     : "=l"(index), "=m"(row_event[1])
                     : "l"(work), "m"(work->record) : "r0", "cc");
        if(index<work->count) {
            do {
                row_event[2]=(u32)&work->done[index];
                ((u16*)row_event)[10]=index;
                work->row_children[index]=RetailCall_08005b6c((Callback)0x0811836d,28,row_event,parent);
                asm volatile("add r0, %0, #1\n\tlsl r0, r0, #24\n\tlsr %0, r0, #24"
                             : "+l"(index) : : "r0", "cc");
            } while(index<work->count);
        }
        event[0]++;
        break;
    }
    case 258:
        if(work->done[work->count-1]==0) break;
        paired_event[1]=(u32)work->record;
        paired_event[2]=(u32)work->done;
        work->first=RetailCall_08005b6c((Callback)0x08118501,20,paired_event,parent);
        work->second=RetailCall_08005b6c((Callback)0x08118591,60,paired_event,parent);
        work->sequence=RetailCall_080dfd8c((const void*)0x083a60b8,2,4,0,parent);
        event[0]++;
        break;
    case 259:
        if(work->done[0]==0) break;
        RetailCall_080e0540(work->row_children,5);
        work->timer=30;
        event[0]++;
        break;
    case 260: {
        void *cell,*child;
        register void **targets asm("r8");
        register void **target_argument asm("r0");
        u32 variant;
        u32 index;
        asm volatile("mov %0, #60\n\tadd %0, %0, %2\n\tmov %1, %0"
                     : "=&l"(target_argument), "=r"(targets)
                     : "l"(work) : "cc");
        RetailCall_080dbab8(target_argument,5);
        {
        register u32 narrowed_remaining asm("r4");
        asm volatile("ldrb r0, [%2, #7]\n\tsub r0, #1\n\tstrb r0, [%2, #7]\n\tlsl r0, r0, #24\n\tlsr %0, r0, #24"
                     : "=l"(narrowed_remaining), "+m"(work->timer)
                     : "l"(work) : "r0", "cc");
        if(narrowed_remaining!=0) break;
        cell=RetailCall_080dd4a4(work->record,work->index);
        {
        register u32 actual_index asm("r1")=work->index;
        register u32 parity asm("r0")=1;
        asm("" : "+r"(actual_index), "+r"(parity));
        parity &= actual_index;
        asm("" : "+r"(parity));
        variant=2;
        if(parity) variant=4;
        }
        child=RetailCall_080dcfe4_zero_word(cell,(const void*)0x083a60a4,12,0,variant|8,parent,narrowed_remaining);
        targets[work->index]=child;
        index=(u32)work->index+1;
        work->index=index;
        if((u8)index<work->count) work->timer=40;
        else event[0]++;
        }
        break;
    }
    case 261:
        work->first=RetailCall_080e051c(work->first);
        if(work->first!=0) break;
        work->second=RetailCall_080e051c(work->second);
        if(work->second!=0) break;
        if((u8)RetailCall_080dbab8(work->target_children,5)!=0) event[0]=2;
        break;
    }
    return 0;
}
asm(".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n");
asm(".global RetailCall_080d38b4\n.thumb_set RetailCall_080d38b4,0x080d38b5\n");
asm(".global RetailCall_080d8924\n.thumb_set RetailCall_080d8924,0x080d8925\n");
asm(".global RetailCall_080dbab8\n.thumb_set RetailCall_080dbab8,0x080dbab9\n");
asm(".global RetailCall_080dcfe4\n.thumb_set RetailCall_080dcfe4,0x080dcfe5\n");
asm(".global RetailCall_080dd494\n.thumb_set RetailCall_080dd494,0x080dd495\n");
asm(".global RetailCall_080dd4a4\n.thumb_set RetailCall_080dd4a4,0x080dd4a5\n");
asm(".global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d\n");
asm(".global RetailCall_080e03f8\n.thumb_set RetailCall_080e03f8,0x080e03f9\n");
asm(".global RetailCall_080e051c\n.thumb_set RetailCall_080e051c,0x080e051d\n");
asm(".global RetailCall_080e0540\n.thumb_set RetailCall_080e0540,0x080e0541\n");
asm(".global RetailCall_080e05dc\n.thumb_set RetailCall_080e05dc,0x080e05dd\n");

asm(".global RetailCall_080dcfe4_zero_word\n.thumb_set RetailCall_080dcfe4_zero_word,0x080dcfe5\n");
