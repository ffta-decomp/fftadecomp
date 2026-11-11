typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,unknown2;void *word4;u32 opaque8[5];} Event;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u32 unknown0[2];void *opaque,*sprite,*auxiliary,*first_palette,*second_palette;Ramp ramp;void *stage;} Work;
void *RetailCall_080d5cc0(const void*,u16,u16,u16,u16,u8,u8,u32);
void RetailCall_08011100(void*,u16);
u32 RetailCall_080035d0(u8);
u32 RetailCall_080035a8(u8);
void RetailCall_0814186c(const void*,void*,u32);
void RetailCall_080d7220(const void*,u8,u8,u8,u16,u16);
void *RetailCall_080d3e9c(const void*,void*);
void *RetailCall_080d4704(const void*,void*);
void RetailCall_080e0608(Ramp*,s32,s32,u16);
void *RetailCall_080dfd8c(const void*,u8,u16,u16,void*);
void RetailCall_080e064c(Ramp*);
void RetailCall_080d7468(const void*,u8,u16,s32);
u32 RetailCall_080e0690(const Ramp*);
void *RetailCall_080d4774(void*);
void *RetailCall_080d3f08(void*);
void RetailCall_08011428(void*);
s32 RemainingBand43_0011360C(void*,Event*,Work*);

extern volatile u8 AuthoredRampDisplay[];
#define CONTROL (*(volatile u16*)AuthoredRampDisplay)
/* Authored resource ramp; keep actual phase and returned cleanup snapshots. */
s32 RemainingBand43_0011360C(void *parent,Event *event,Work *work)
{
    u16 palette_fill;
    register u32 phase asm("r4")=event->phase;
    /* Actual captured phase remains live through phase0 calls and fill storage. */
    asm("" : "+r"(phase));
    switch((s32)phase) {
    case 0:
        work->opaque=event->word4;
        work->sprite=RetailCall_080d5cc0((const void*)0x085055d0,1,120,112,664,6,1,phase);
        RetailCall_08011100(work->sprite,2);
        AuthoredRampDisplay[68]=63&~RetailCall_080035d0(2);
        AuthoredRampDisplay[69]=63;
        /* Mixed island,12 instruction bytes: exactly one volatile H0 |= 0x8000.
           Base is unchanged; scratch R0/R1/R2, flags and H0 memory are modified. */
        asm volatile("ldrh r1,[%0]\n"
                     "mov r2,#128\n"
                     "lsl r2,r2,#8\n"
                     "add r0,r2,#0\n"
                     "orr r0,r1\n"
                     "strh r0,[%0]\n"
                     : : "r"(AuthoredRampDisplay) : "r0","r1","r2","cc","memory");
        palette_fill=phase;
        RetailCall_0814186c(&palette_fill,(void*)0x03003920,0x01000010);
        break;
    case 1: break;
    case 256:
        RetailCall_080d7220((const void*)0x088f5f08,0,2,0,0,0);
        work->auxiliary=RetailCall_080d3e9c((const void*)0x0894d69c,parent);
        work->first_palette=RetailCall_080d4704((const void*)0x0894bdd8,parent);
        work->second_palette=RetailCall_080d4704((const void*)0x0894bdb4,parent);
        RetailCall_080e0608(&work->ramp,0,-1,5);
        work->stage=RetailCall_080dfd8c((const void*)0x083a37d0,1,4,0,parent);
        event->phase++;
        break;
    case 257:
        RetailCall_080e064c(&work->ramp);
        RetailCall_080d7468((const void*)0x088f5f08,2,0,(s16)work->ramp.value);
        if((u8)RetailCall_080e0690(&work->ramp)!=0) {
            register s32 ramp_start asm("r1");
            /* Mixed island,4 instruction bytes: signed H28 read, original R2 index.
               Read exactly work->ramp.value; output is genuinely instruction-defined. */
            asm volatile("mov r2,#28\nldrsh %0,[%1,r2]"
                         : "=r"(ramp_start) : "r"(work),"m"(work->ramp.value) : "r2","cc");
            RetailCall_080e0608(&work->ramp,ramp_start,(s16)(work->ramp.value-1),5);
        }
        work->first_palette=RetailCall_080d4774(work->first_palette);
        if(work->first_palette!=0) break;
        work->second_palette=RetailCall_080d4774(work->second_palette);
        if(work->second_palette!=0) break;
        event->phase++;
        break;
    case 258: {
        void *completed=RetailCall_080d3f08(work->auxiliary);
        work->auxiliary=completed;
        if(completed!=0) break;
        RetailCall_08011428(work->sprite);
        work->sprite=completed;
        {
            u32 mask=RetailCall_080035a8(2);
            u32 retained_control=CONTROL&~mask;
            register u32 final_zero asm("r3");
            /* Mixed island,2 instruction bytes: define actual zero after BIC,
               preserving the initialized control working value through this phase. */
            asm volatile("mov %0,#0" : "=r"(final_zero) : "r"(retained_control) : "cc");
            {
                register u32 final_mask asm("r0")=0x7fff;
                /* Actual full-word mask working value, consumed once after zero. */
                asm("" : "+r"(final_mask));
                CONTROL=retained_control&final_mask;
            }
            AuthoredRampDisplay[74]=final_zero;
        }
        event->phase=2;
        break;
    }
    }
    return 0;
}
asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8,0x080035a9\n");
asm(".global RetailCall_080035d0\n.thumb_set RetailCall_080035d0,0x080035d1\n");
asm(".global RetailCall_08011100\n.thumb_set RetailCall_08011100,0x08011101\n");
asm(".global RetailCall_08011428\n.thumb_set RetailCall_08011428,0x08011429\n");
asm(".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d\n");
asm(".global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08,0x080d3f09\n");
asm(".global RetailCall_080d4704\n.thumb_set RetailCall_080d4704,0x080d4705\n");
asm(".global RetailCall_080d4774\n.thumb_set RetailCall_080d4774,0x080d4775\n");
asm(".global RetailCall_080d5cc0\n.thumb_set RetailCall_080d5cc0,0x080d5cc1\n");
asm(".global RetailCall_080d7220\n.thumb_set RetailCall_080d7220,0x080d7221\n");
asm(".global RetailCall_080d7468\n.thumb_set RetailCall_080d7468,0x080d7469\n");
asm(".global RetailCall_080dfd8c\n.thumb_set RetailCall_080dfd8c,0x080dfd8d\n");
asm(".global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n");
asm(".global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n");
asm(".global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n");
asm(".global RetailCall_0814186c\n.thumb_set RetailCall_0814186c,0x0814186d\n");
asm(".global AuthoredRampDisplay\n.set AuthoredRampDisplay,0x03000940\n");
