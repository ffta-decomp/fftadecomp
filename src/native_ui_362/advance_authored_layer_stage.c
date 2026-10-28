typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed short s16;typedef signed int s32;
typedef struct Event {u16 phase,unknown2;u32 opaque4[4];u16 x,y;u32 opaque24;} Event;
typedef struct Ramp {u16 value;s16 remaining,error;u16 step,period,magnitude;} Ramp;
typedef struct Work {u16 timer,x,y,unknown6;void *child;Ramp ramp;u32 unknown24;} Work;
typedef s32(*Callback)(void*,Event*,void*);
void *RetailCall_08005b6c(Callback,u16,const Event*,void*);
void RetailCall_080d74e0(u8,u8,u8,s32,s32,void*,void*);
/* Actual selected mask getter returns a full zero-extended halfword in R0. */
u32 RetailCall_080035a8(u8);
void RetailCall_080e0608(Ramp*,u16,u16,u16);
u32 RetailCall_080e0690(const Ramp*);
void RetailCall_080e064c(Ramp*);
void RetailCall_08003558(s32,u8);
void *RetailCall_080e051c(void*);
s32 RemainingBand43_00112E88(void*,Event*,Work*);

#define CONTROL (*(volatile u16*)0x03000940)
/* Authored captured-coordinate layer sequence; opaque child event is untouched. */
s32 RemainingBand43_00112E88(void *parent,Event *event,Work *work)
{
    Event child_event;
    switch((s32)event->phase) {
    case 0:
        work->x=event->x;
        work->y=event->y;
        break;
    case 1: break;
    case 256:
        work->child=RetailCall_08005b6c((Callback)0x08112ccd,32,&child_event,parent);
        work->timer=30;
        event->phase++;
        break;
    case 257: {
        u32 remaining=work->timer-1;
        work->timer=remaining;
        if((u16)remaining!=0) break;
        RetailCall_080d74e0(1,2,1,(s16)(work->x-120),(s16)(work->y-248),(void*)0x06008000,(void*)0x06007000);
        {
            u32 mask=RetailCall_080035a8(1);
            {
                register u32 previous_control asm("r1")=CONTROL;
                /* Actual old-control snapshot is the destructive OR destination. */
                asm("" : "+r"(previous_control));
                {
                    register u32 merged_control asm("r1")=previous_control|mask;
                    /* Actual merged result overwrites the old-control carrier. */
                    asm("" : "+r"(merged_control));
                    CONTROL=merged_control;
                }
            }
            /* Native returned mask remains unchanged in R0 through this store. */
            asm("" : : "r"(mask));
        }
        RetailCall_080e0608(&work->ramp,248,112,40);
        event->phase++;
        break;
    }
    case 258:
        if((u8)RetailCall_080e0690(&work->ramp)==0) {
            RetailCall_080e064c(&work->ramp);
            RetailCall_08003558((s16)(work->y-work->ramp.value),1);
        } else {
            work->child=RetailCall_080e051c(work->child);
            if(work->child==0) event->phase=2;
        }
        break;
    }
    return 0;
}
asm(".global RetailCall_08003558\n.thumb_set RetailCall_08003558,0x08003559\n");
asm(".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8,0x080035a9\n");
asm(".global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c,0x08005b6d\n");
asm(".global RetailCall_080d74e0\n.thumb_set RetailCall_080d74e0,0x080d74e1\n");
asm(".global RetailCall_080e051c\n.thumb_set RetailCall_080e051c,0x080e051d\n");
asm(".global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n");
asm(".global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n");
asm(".global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n");
