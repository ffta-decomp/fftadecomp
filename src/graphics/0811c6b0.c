#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef struct Event {u16 phase,h2;void *record;u8 rest[20];} Event;
typedef struct Slot {void *object;u8 phase,pad[3];} Slot;
typedef struct Ramp {u8 value,rest[11];} Ramp;
typedef struct Work {u16 timer;u8 pad[6];Slot slots[8];Ramp ramp;void *record;u32 tail;} Work;
extern void *CreateRingObject(u32,u32,int,int,u32,u32,u32,u32);
extern void SetRingObjectMode(void *,int);
extern void InitializeRingRamp(Ramp *,u32,u32,u32);
extern void UpdateRingRamp(Ramp *);
extern u32 RingRampComplete(Ramp *);
extern void PositionRing(Slot *,u32);
extern void StartRingTransition(int,int,int);
extern void GetRecordCoordinates(void *,s16 *,s16 *);
extern void ProjectRecordCoordinates(void *,int,int,s16 *,s16 *);
extern void PositionLayerX(int,u32);
extern void PositionLayerY(int,u32);
extern u32 RingTransitionBusy(void);
extern void DestroyRingObject(void *);
u32 AdvanceAuthoredEightObjectRing(void *unused,Event *event_arg,Work *work_arg)
{
    s16 x,y;
    register Event *event __asm__("r9") = event_arg;
    Work *work=work_arg;
    int state;
    state=event_arg->phase;
    __asm__("" : "+r"(event), "+r"(work));
    switch(state) {
    case 0: {
        register Event *read_context __asm__("r1")=event;
        __asm__("" : "+r"(read_context));
        work->record=read_context->record;
        work->timer=25;
        break;
    }
    case 1: break;
    case 256:
        work->timer--;
        if (!work->timer) {
            register u32 phase_low __asm__("r2")=0;
            register u32 angle __asm__("r8");
            register Ramp *ramp_low __asm__("r3");
            u8 index;
            Slot *slots;
            Ramp *ramp;
            __asm__("" : "+r"(phase_low));
            angle=phase_low;
            index=0;
            slots=work->slots;
            /* Actual ramp address = byte Work base + 72. */
            __asm__ volatile (".L_authored_11c6b0_ramp_address:\nmov %0,#72\nadd %0,%0,%1"
                : "=&r"(ramp_low) : "r"(work) : "cc");
            ramp=ramp_low;
            __asm__("" : "+r"(angle));
            do {
                void *object=CreateRingObject(0x08507ee8,0,120,64,992,6,0,0);
                {
                    register Slot *destination __asm__("r1");
                    /* Actual base-first Slot8 address, then ordinary object store. */
                    __asm__ volatile (".L_authored_11c6b0_create_slot_address:\nadd %0,%1,%2"
                        : "=r"(destination) : "r"(slots), "r"((u32)index*8) : "cc");
                    destination->object=object;
                }
                SetRingObjectMode(object,-1);
                {
                    u8 *phase_record=(u8 *)work+(u32)index*8;
                    __asm__("" : "+r"(phase_record));
                    {
                        register u32 phase_value __asm__("r0")=angle;
                        __asm__("" : "+r"(phase_value));
                        phase_record[12]=phase_value;
                    }
                }
                angle=(u8)(angle+32);
                index++;
            } while(index<=7);
            InitializeRingRamp(ramp,0,64,44);
            {
                Event *phase_context=event;
                u32 next=phase_context->phase+1;
                __asm__ volatile ("" : "+r"(phase_context), "+r"(next));
                phase_context->phase=next;
            }
        }
        break;
    case 257: {
        Ramp *ramp=&work->ramp;
        UpdateRingRamp(ramp);
        PositionRing(work->slots,ramp->value);
        if ((u8)RingRampComplete(ramp)) {
            StartRingTransition(56,208,40);
            {
                register Event *phase_context __asm__("r2")=event;
                u32 next=phase_context->phase+1;
                __asm__ volatile ("" : "+r"(phase_context), "+r"(next));
                /* Native phase-local H0 publication; jump.c must not merge it. */
                __asm__ volatile (".L_authored_11c6b0_phase257_store:\nstrh %1,[%2]"
                    : "=m"(phase_context->phase) : "r"(next), "r"(phase_context));
            }
        }
        break;
    }
    case 258: {
        register Slot *ring_arg __asm__("r0")=work->slots;
        Ramp *ramp;
        __asm__("" : "+r"(ring_arg));
        ramp=&work->ramp;
        PositionRing(ring_arg,ramp->value);
        GetRecordCoordinates(work->record,&x,&y);
        {
            register void *record_arg __asm__("r0")=work->record;
            register int signed_x __asm__("r1");
            __asm__("" : "+r"(record_arg));
            /* Actual SP16 signed halfword load for the second ABI argument. */
            signed_x=(int)&x;
            __asm__ volatile (".L_authored_11c6b0_signed_x_argument:\nmov r3,#0\nldrsh %0,[%0,r3]"
                : "+r"(signed_x) : "m"(*(const s16 *)signed_x) : "r3", "cc");
            ProjectRecordCoordinates(record_arg,signed_x,y,&x,&y);
        }
        PositionLayerX(x,3);
        {
            register const s16 *y_source __asm__("r4")=&y;
            register int signed_y __asm__("r0");
            /* Actual full signed Y argument; MOV writes the declared R2/cc. */
            __asm__ volatile (".L_authored_11c6b0_signed_y_argument:\nmov r2,#0\nldrsh %0,[%2,r2]"
                : "=r"(signed_y) : "m"(*y_source), "r"(y_source) : "r2", "cc");
            PositionLayerY(signed_y,3);
        }
        if (!(u8)RingTransitionBusy()) {
            InitializeRingRamp(ramp,64,0,44);
            {
                register Event *phase_context __asm__("r3")=event;
                u32 next=phase_context->phase+1;
                __asm__ volatile ("" : "+r"(phase_context), "+r"(next));
                /* Native phase-local H0 publication; jump.c must not merge it. */
                __asm__ volatile (".L_authored_11c6b0_phase258_store:\nstrh %1,[%2]"
                    : "=m"(phase_context->phase) : "r"(next), "r"(phase_context));
            }
        }
        break;
    }
    case 259: {
        Ramp *ramp=&work->ramp;
        Slot *slots;
        u32 complete;
        UpdateRingRamp(ramp);
        work=(Work *)((u8 *)work+8);
        PositionRing((Slot *)work,ramp->value);
        complete=(u8)RingRampComplete(ramp);
        slots=(Slot *)work;
        if (complete) {
            u8 index=0;
            register u32 zero __asm__("r6")=0;
            __asm__("" : "+r"(zero));
            do {
                register Slot *destination __asm__("r4");
                /* The native ADD consumes its real stride input destructively. */
                __asm__ volatile (".L_authored_11c6b0_destroy_slot_address:\nadd %0,%1,%2"
                    : "=r"(destination) : "r"(slots), "0"((u32)index*8) : "cc");
                DestroyRingObject(destination->object);
                destination->object=(void *)zero;
                index++;
            } while(index<=7);
            {
                register u32 terminal_value __asm__("r0")=2;
                __asm__("" : "+r"(terminal_value));
                event->phase=terminal_value;
            }
        }
        break;
    }
    default: break;
    }
    return 0;
}
__asm__(".global CreateRingObject\n.thumb_set CreateRingObject,0x80d5cc1");
__asm__(".global SetRingObjectMode\n.thumb_set SetRingObjectMode,0x801121d");
__asm__(".global InitializeRingRamp\n.thumb_set InitializeRingRamp,0x80e0609");
__asm__(".global UpdateRingRamp\n.thumb_set UpdateRingRamp,0x80e064d");
__asm__(".global RingRampComplete\n.thumb_set RingRampComplete,0x80e0691");
__asm__(".global PositionRing\n.thumb_set PositionRing,0x811c645");
__asm__(".global StartRingTransition\n.thumb_set StartRingTransition,0x801bb0d");
__asm__(".global GetRecordCoordinates\n.thumb_set GetRecordCoordinates,0x80dbdc9");
__asm__(".global ProjectRecordCoordinates\n.thumb_set ProjectRecordCoordinates,0x80dc225");
__asm__(".global PositionLayerX\n.thumb_set PositionLayerX,0x8003509");
__asm__(".global PositionLayerY\n.thumb_set PositionLayerY,0x8003559");
__asm__(".global RingTransitionBusy\n.thumb_set RingTransitionBusy,0x801bdb1");
__asm__(".global DestroyRingObject\n.thumb_set DestroyRingObject,0x8011429");
__asm__(".global RemainingBand43_0011C6B0\n.thumb_set RemainingBand43_0011C6B0,AdvanceAuthoredEightObjectRing");
