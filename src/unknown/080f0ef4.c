#include "ffta/unsigned_types.h"
typedef signed short s16;
struct Task;
struct Event {u16 state;u8 unused2[2];void *action;u8 unused8[12];u16 mode;u8 unused22[6];};
struct Work {u8 mode,delay,count,index;void *action,*unit;struct Task *effects[4],*optional[4];u8 unknown44[4];};
struct Definition {u8 bytes[20];};
typedef char WorkSize[sizeof(struct Work)==48?1:-1];
extern u32 ReadActionCount(void*);
extern void *ReadActionUnit(void*,u8);
extern u32 RequestUnitVisibility(void*);
extern u32 ActionBusy(void);
extern struct Task *PollEffect(struct Task*);
extern void *ReadTargetRecord(void*,u8);
extern void *ResolveRecordPosition(void*,u16*,u16*,u16*);
extern u32 RecordSpecialFlag(void*);
extern u32 RecordValue(void*);
extern u32 RecordProperty(void*,u8);
extern u32 RecordOptionalFlag(void*,u8);
extern struct Task *CreateRecordEffect(void*,const void*,u8,u16,u16,struct Task*,u16);
extern struct Task *CreateOptionalEffect(void*,u16,struct Task*);
extern u32 RecordHasActor(void*);
extern void DispatchIndexedService(u8,u16);
extern const struct Definition gDefinitions[];
extern const u16 gServiceIds[];
u32 ProcessActionTargetEffects(struct Task*,struct Event*,struct Work*) __asm__("RemainingBand43_000F0EF4");
u32 ProcessActionTargetEffects(struct Task *task,struct Event *event,struct Work *work)
{
    /* Both polling phases assign these same real array-base quantities.
     * They are fresh addresses within the current work object each time. */
    u32 suppress;
    struct Task **effects;
    struct Task **optional;
    switch(event->state) {
    case 0:
        work->mode=event->mode;
        work->action=event->action;
        work->count=ReadActionCount(work->action);
        work->unit=ReadActionUnit(work->action,work->index);
        RequestUnitVisibility(work->unit);
        break;
    case 1:break;
    case 256: {
        u32 index;
        u16 x,y;
        void *record,*actor;
        u32 selected;
        u16 flags;
        const struct Definition *definition;
        u8 count;
        suppress=0;
        if((u8)ActionBusy())break;
        /* The actual fullword ordinal is defined after the busy gate but
         * before either retained array address. Its real updated value is
         * narrowed at the original low-byte wrap, not by a QI ASM output. */
        index=0;
        asm("" : "+r"(index));
        effects=work->effects;
        optional=work->optional;
        do {
            /* One native scaled offset, then the two true slot addresses. */
            u32 byte_offset=index*4;
            struct Task **effect_slot=(struct Task **)((u8*)effects+byte_offset);
            struct Task **optional_slot;
            *effect_slot=PollEffect(*effect_slot);
            optional_slot=(struct Task **)((u8*)optional+byte_offset);
            *optional_slot=PollEffect(*optional_slot);
            index=(u8)(index+1);
        } while(index<=3);
        record=ReadTargetRecord(work->action,work->index);
        actor=ResolveRecordPosition(record,&x,&y,0);
        selected=work->mode;
        {
            /* Original R0 is a short dispatch copy. The working selected
             * value survives in its own C quantity for the definition and
             * service consumers; this initialized view dies at its tests. */
            register u32 dispatch_mode asm("r0") = selected;
            asm("" : "+r"(dispatch_mode));
            if(dispatch_mode==0) {
                if(!(u8)RecordSpecialFlag(record)) {
                    selected=8;
                    if((u16)RecordValue(record)==0)suppress=1;
                } else {
                    if((u8)RecordProperty(record,5))selected=10;
                }
            } else if(dispatch_mode==6) {
                if(!(u8)RecordOptionalFlag(record,0)) {
                    selected=9;
                    if((u16)RecordValue(record)==0)suppress=1;
                }
            }
        }
        {
            /* Original zero-extended field value is consumed twice before
             * its R2 carrier becomes the count argument. No call crosses
             * this initialized fullword view. */
            register u32 position asm("r2")=work->index;
            asm("" : "+r"(position));
            flags=(position&1)?4:2;
            definition=&gDefinitions[selected];
            count=12-(position&6);
        }
        effects[work->index&3]=CreateRecordEffect(record,definition,count,10,flags,task,10);
        if(selected==6) {
            struct Task *created=CreateOptionalEffect(actor,0,task);
            u32 byte_offset=(work->index&3)*4;
            struct Task **slot=(struct Task **)((u8*)optional+byte_offset);
            *slot=created;
        }
        if((u8)RecordHasActor(record)) {
            u32 allowed=1;
            if(suppress==0) {
                int mode=work->mode;
                if(mode>=(int)allowed) {
                    if(mode<=3 || mode==7) {
                        s16 value=RecordValue(record);
                        if(value==32767 || value<=0)allowed=0;
                    }
                }
                if(allowed) {
                    u8 channel=(work->index&1)?2:1;
                    DispatchIndexedService(channel,gServiceIds[selected]);
                }
            }
        }
        work->index++;
        if(work->index==work->count)event->state=259;
        else {
            work->delay=48;
            event->state++;
        }
        break;
    }
    case 257:
        work->delay--;
        if(work->delay==0) {
            work->unit=ReadActionUnit(work->action,work->index);
            RequestUnitVisibility(work->unit);
            event->state=256;
        }
        break;
    case 258:event->state++;break;
    case 259: {
        u32 complete=1;
        u8 index=0;
        effects=work->effects;
        optional=work->optional;
        for(;index<=3;index++) {
            /* This actual scaled offset survives the first poll for the
             * second slot, matching the native R5 definition/last use. */
            register u32 byte_offset asm("r5")=index*4;
            struct Task **slot;
            asm("" : "+r"(byte_offset));
            slot=(struct Task **)((u8*)effects+byte_offset);
            *slot=PollEffect(*slot);
            if(*slot!=0)complete=0;
            slot=(struct Task **)((u8*)optional+byte_offset);
            *slot=PollEffect(*slot);
            if(*slot!=0)complete=0;
        }
        if(complete)event->state=2;
        break;
    }
    }
    return 0;
}
__asm__(".global gDefinitions\n.set gDefinitions,0x839a3f8\n.global gServiceIds\n.set gServiceIds,0x839a3e0\n.global ReadActionCount\n.thumb_set ReadActionCount,0x80dd495\n.global ReadActionUnit\n.thumb_set ReadActionUnit,0x80dd4b5\n.global RequestUnitVisibility\n.thumb_set RequestUnitVisibility,0x80db839\n.global ActionBusy\n.thumb_set ActionBusy,0x80d8b4d\n.global PollEffect\n.thumb_set PollEffect,0x80dba5d\n.global ReadTargetRecord\n.thumb_set ReadTargetRecord,0x80dd4a5\n.global ResolveRecordPosition\n.thumb_set ResolveRecordPosition,0x80dd749\n.global RecordSpecialFlag\n.thumb_set RecordSpecialFlag,0x80dd5ed\n.global RecordValue\n.thumb_set RecordValue,0x80dd4d5\n.global RecordProperty\n.thumb_set RecordProperty,0x80a8859\n.global RecordOptionalFlag\n.thumb_set RecordOptionalFlag,0x80dd685\n.global CreateRecordEffect\n.thumb_set CreateRecordEffect,0x80dcfe5\n.global CreateOptionalEffect\n.thumb_set CreateOptionalEffect,0x80df90d\n.global RecordHasActor\n.thumb_set RecordHasActor,0x80dd581\n.global DispatchIndexedService\n.thumb_set DispatchIndexedService,0x8141571\n");
