typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,unknown2;void **external_cell;u32 opaque8[5];} Event;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u16 timer,delay;u8 unknown4[4];void **external_cell;void *center_sprite,*particles[28];Ramp center,x[28],y[28];void *stage;} Work;
typedef struct SpawnCue {u8 time,mode;s16 x,y;u16 unknown6;} SpawnCue;
void RetailCall_080e0608(Ramp*,s32,s32,u16);
u32 RetailCall_080e0690(const Ramp*);
void RetailCall_080e064c(Ramp*);
void RetailCall_080107d4(void*,s32,s32,u16);
void *RetailCall_080dfd8c(const void*,u8,u16,u16,void*);
void *RetailCall_080d5cc0(const void*,u32,s32,s32,u16,u8,u8,u8);
void RetailCall_08011428(void*);
void *RetailCall_08011484(void*);
u32 RetailCall_080d5f24(void**,u16);
s32 RemainingBand43_00111A5C(void*,Event*,Work*);

typedef char AuthoredConvergenceWorkMustBe816[sizeof(Work)==816?1:-1];
#define CUES ((const SpawnCue*)0x083a33f8)
/* Authored convergence: native guarded delays and two post-tested U8 loops. */
s32 RemainingBand43_00111A5C(void *parent,Event *event,Work *work)
{
    switch((s32)event->phase) {
    case 0:
        work->external_cell=event->external_cell;
        RetailCall_080e0608(&work->center,64,64,20);
        work->timer=30;
        break;
    case 1: break;
    case 256:
        if((u8)RetailCall_080e0690(&work->center)==0) {
            RetailCall_080e064c(&work->center);
            RetailCall_080107d4(*work->external_cell,120,(s16)work->center.value,0);
        } else {
            u32 remaining=work->timer-1;
            work->timer=remaining;
            if((u16)remaining!=0) break;
            work->stage=RetailCall_080dfd8c((const void*)0x083a33c4,1,4,0,parent);
            work->delay=30;
            event->phase++;
        }
        break;
    case 257: {
        u8 index;
        void **particles;
        const SpawnCue *cues;
        if(work->delay!=0) {
            u32 remaining=work->delay-1;
            work->delay=remaining;
            if((u16)remaining==0)
                work->center_sprite=RetailCall_080d5cc0((const void*)0x08504d8c,2,120,124,779,8,0,0);
        }
        index=0;
        particles=work->particles;
        do {
            void **slot=&particles[index];
            if(*slot!=0) {
                register Ramp *x asm("r5");
                u32 stride=(u32)index*sizeof(Ramp);
                /* Actual address definition, with R0 scratch and no memory access. */
                asm volatile("add r0,%1,#0\nadd r0,#140\nadd %0,%2,r0"
                    : "=l"(x) : "l"(stride),"l"(work) : "r0","cc");
                if((u8)RetailCall_080e0690(x)!=0) {
                    RetailCall_08011428(*slot);
                    *slot=0;
                } else {
                    RetailCall_080e064c(x);
                    RetailCall_080e064c(&work->y[index]);
                    RetailCall_080107d4(*slot,(s16)work->x[index].value,(s16)work->y[index].value,0);
                }
            }
            index++;
        } while(index<=27);
        index=0;
        do {
            const SpawnCue *cue;
            u32 cue_offset;
            cues=CUES;
            /* Actual ROM base is refreshed per iteration and survives its calls
               through the final completion threshold after the loop. */
            asm volatile("" : "+r"(cues));
            cue_offset=(u32)index*sizeof(SpawnCue);
            asm volatile("add %0,%1,%2"
                : "=l"(cue) : "l"(cue_offset),"l"(cues) : "cc");
            if(work->timer==cue->time) {
                particles[index]=RetailCall_080d5cc0((const void*)0x08504d8c,cue->mode,cue->x,cue->y,779,8,0,0);
                RetailCall_080e0608(&work->x[index],cue->x,120,24);
                RetailCall_080e0608(&work->y[index],cue->y,124,24);
            }
            index++;
        } while(index<=27);
        work->timer++;
        work->center_sprite=RetailCall_08011484(work->center_sprite);
        if(work->center_sprite!=0) break;
        if(work->timer<cues[27].time+24) break;
        if((u8)RetailCall_080d5f24(particles,28)!=0) event->phase=2;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080107d4\n.thumb_set RetailCall_080107d4,0x080107d5\n");
asm(".global RetailCall_08011428\n.thumb_set RetailCall_08011428,0x08011429\n");
asm(".global RetailCall_08011484\n.thumb_set RetailCall_08011484,0x08011485\n");
asm(".global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0,0x080d5cc1\n");
asm(".global RetailCall_080d5f24\n.thumb_set RetailCall_080d5f24,0x080d5f25\n");
asm(".global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d\n");
asm(".global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n");
asm(".global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n");
asm(".global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n");
