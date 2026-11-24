#include "ffta/types.h"
typedef struct TaskNode TaskNode;
typedef void (*TaskCallback)(TaskNode *,u16 *,void *);
struct DirectionOffset { u16 x,y; };
struct DirectionOffsetSet { struct DirectionOffset row[4]; };
struct PackedCoordinates { u32 x:16,y:16; };
struct DirectionalSequenceEvent {
    u16 phase,unknown02;
    void *actor;
    u8 unknown08[12];
    s16 definition_id;
    u16 variant;
    u8 unknown18[4];
};
struct TargetChildEvent {
    u32 unknown00;
    void *target;
    u8 unknown08[12];
    u16 direction,ordinal,special,unknown1a;
};
struct DirectionalSequenceWork {
    u32 unknown00;
    u8 special,variant,completion[2];
    s8 direction;
    u8 count,unknown0a,byte_delay;
    u16 ordinal,unknown0e;
    TaskNode *children[4];
    void *record,*actor;
    TaskNode *initial_effect,*record_child,*motion,*sequence;
};
typedef char OffsetSetSize[sizeof(struct DirectionOffsetSet)==16?1:-1];
typedef char EventSize[sizeof(struct DirectionalSequenceEvent)==28?1:-1];
typedef char ChildEventSize[sizeof(struct TargetChildEvent)==28?1:-1];
typedef char PackedCoordinateSize[sizeof(struct PackedCoordinates)==4?1:-1];
typedef char WorkSize[sizeof(struct DirectionalSequenceWork)==56?1:-1];
extern const struct DirectionOffsetSet gDirectionOffsets;
extern const u8 gDirectionalOpeningStage[],gDirectionalPalette[],gDirectionalRecordStage[],gDirectionalStage[];
extern void *GetActorNestedRecord(void *);
extern s32 ReadRecordDirection(void *);
extern void ProjectNestedRecord(const void *,u16 *,u16 *,u16 *);
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDefinitionInputs(void);
extern TaskNode *PollDefinitionEffect(TaskNode *);
extern void CopyPaletteGroups(const void *,u32,u32,u32,u32);
extern u32 ReadDefinitionTargetCount(void *);
extern TaskNode *CreateRecordSequence(void *,void **,u16,u8,u8 *,const void *,u16,u16,TaskNode *);
extern TaskNode *CreateRecordMotion(void *,u8,u8,u16,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern u32 QueryDefinitionTargets(void *,u16,u16,TaskNode *);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTarget(void *,u8);
extern TaskNode *CreateOppositePhaseChild(TaskCallback,u16,const u32 *,TaskNode *);
extern TaskNode *PollAndReleaseMotion(TaskNode *);
extern u32 IsRecordFinished(void *);
extern s32 RunDirectionalTargetChild(TaskNode *,u16 *,void *);
__asm__(".global gDirectionOffsets\n.set gDirectionOffsets,0x08149d3c\n"
 ".global gDirectionalOpeningStage\n.set gDirectionalOpeningStage,0x0839ba10\n"
 ".global gDirectionalPalette\n.set gDirectionalPalette,0x088eaa30\n"
 ".global gDirectionalRecordStage\n.set gDirectionalRecordStage,0x0839ba50\n"
 ".global gDirectionalStage\n.set gDirectionalStage,0x0839ba58\n"
 ".global GetActorNestedRecord\n.thumb_set GetActorNestedRecord,0x080dd47d\n"
 ".global ReadRecordDirection\n.thumb_set ReadRecordDirection,0x080dbc89\n"
 ".global ProjectNestedRecord\n.thumb_set ProjectNestedRecord,0x080dbda1\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080e03f9\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x080d38b5\n"
 ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x080e05dd\n"
 ".global CopyPaletteGroups\n.thumb_set CopyPaletteGroups,0x080d45d1\n"
 ".global ReadDefinitionTargetCount\n.thumb_set ReadDefinitionTargetCount,0x080dd495\n"
 ".global CreateRecordSequence\n.thumb_set CreateRecordSequence,0x080ddf69\n"
 ".global CreateRecordMotion\n.thumb_set CreateRecordMotion,0x080dbb15\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x080dfd8d\n"
 ".global QueryDefinitionTargets\n.thumb_set QueryDefinitionTargets,0x080d8925\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x080e0571\n"
 ".global GetDefinitionTarget\n.thumb_set GetDefinitionTarget,0x080dd4a5\n"
 ".global CreateOppositePhaseChild\n.thumb_set CreateOppositePhaseChild,0x08005b6d\n"
 ".global PollAndReleaseMotion\n.thumb_set PollAndReleaseMotion,0x080dba5d\n"
 ".global IsRecordFinished\n.thumb_set IsRecordFinished,0x080de245\n"
 ".global RunDirectionalTargetChild\n.thumb_set RunDirectionalTargetChild,0x080f6c49");
/* This scalar expression is expanded while storing its own stack argument,
 * after earlier slots and before hard register arguments are filled. */
#define STACK_PARENT_VALUE(reg_name, node_value) \
    __extension__ ({ \
        register TaskNode *stack_parent __asm__(reg_name)=(node_value); \
        __asm__("" : "+r" (stack_parent)); \
        stack_parent; \
    })

s32 AdvanceAuthoredDirectionalTargetSequence(TaskNode *,struct DirectionalSequenceEvent *,struct DirectionalSequenceWork *)
    __asm__("OriginalActionCallback_000F6E74");
s32 AdvanceAuthoredDirectionalTargetSequence(TaskNode *parent,struct DirectionalSequenceEvent *event_input,
                                            struct DirectionalSequenceWork *work_input)
{
    register s32 phase __asm__("r2");
    u32 next_phase;
    register struct DirectionalSequenceEvent *incoming_event __asm__("r1")=event_input;
    register struct DirectionalSequenceWork *incoming_work __asm__("r2")=work_input;
    register struct DirectionalSequenceEvent *event __asm__("r8")=incoming_event;
    struct DirectionalSequenceWork *work;
    struct DirectionOffsetSet offsets;
    u16 projected_x,projected_y,projected_depth;
    struct PackedCoordinates position;
    /* Preserve the raw ABI pointers until their actual capture/load points.
     * Work is an ordinary saved pointer: it has no explicit R7 binding. */
    __asm__("" : "+r" (event) : "r" (incoming_event), "r" (incoming_work));
    work=incoming_work;
    __asm__("" : "+r" (work) : "r" (incoming_event));
    phase=incoming_event->phase;
    /* The halfword storage feeds this real full-word signed switch value. */
    __asm__("" : "+r" (phase));
    switch(phase) {
    case 0: {
        register u32 variant __asm__("r0");
        register u32 opening_count __asm__("r8");
        void *actor,*record;
        register struct DirectionalSequenceEvent *opening_event __asm__("r3");
        offsets=gDirectionOffsets;
        work->special=(u8)phase;
        if(event->definition_id==0x149) work->special=1;
        opening_event=event;
        /* Actual short root survives the variant value until the actor load. */
        __asm__("" : "+r" (opening_event));
        variant=opening_event->variant;
        work->variant=(u8)variant;
        __asm__("" : "+r"(variant));
        actor=opening_event->actor;
        work->actor=actor;
        /* Actual SI count is 2 or 0. These transparent native producers
         * define every bit; the LOW8 ABI consumer is kept in the call bridge
         * below, rather than changing its u8 prototype or inventing a range. */
        __asm__ volatile("mov r4, #2\n\tmov %0, r4"
                         : "=h" (opening_count) : : "r4", "cc");
        if((u8)variant!=0)
            __asm__ volatile("mov r5, #0\n\tmov %0, r5"
                             : "=h" (opening_count) : : "r5", "cc");
        record=GetActorNestedRecord(actor);
        work->direction=(s8)ReadRecordDirection(record);
        ProjectNestedRecord(record,&projected_x,&projected_y,&projected_depth);
        /* Preserve the two physical low/high halfword assignments. The
         * other half remains unwritten until its original assignment. */
        position.x=(u16)(projected_x-offsets.row[work->direction].x);
        position.y=(u16)(projected_y-offsets.row[work->direction].y);
        {
            register void *actor_result __asm__("r0")=work->actor;
            register const u8 *stage_argument __asm__("r1")=gDirectionalOpeningStage;
            register const s16 *coordinates_argument __asm__("r2")=(const s16 *)&position;
            /* Original six-argument Thumb call: R0 actor, R1 stage,
             * LOW8(R2) count, LOW8(R3)=6, SP0 coordinates, SP4 parent.
             * Other retained C calls reserve the outgoing 20-byte area;
             * these two original outgoing writes never change SP or locals.
             * R0 returns the task. R1/R2 are initialized call-clobbered inputs;
             * the C declaration above remains u8 and is not widened. */
            __asm__ volatile("str %2, [sp]\n\t"
                             "mov %2, %4\n\t"
                             "str %2, [sp, #4]\n\t"
                             "mov %2, %5\n\t"
                             "mov r3, #6\n\t"
                             "bl CreateDefinitionEffectTask"
                             : "+r" (actor_result), "+r" (stage_argument),
                               "+r" (coordinates_argument)
                             : "m" (position), "r" (parent), "h" (opening_count)
                             : "r3", "r12", "lr", "cc", "memory");
            work->initial_effect=(TaskNode *)actor_result;
        }
        break;
    }
    case 1:
        CleanupDefinitionInputs();
        break;
    case 256: {
        u8 special,variant;
        u16 value;
        work->initial_effect=PollDefinitionEffect(work->initial_effect);
        if(work->initial_effect!=0) break;
        special=work->special;
        if(special==1) CopyPaletteGroups(gDirectionalPalette,6,1,2,special);
        variant=work->variant;
        if(variant!=0) {
            work->count=(u8)ReadDefinitionTargetCount(work->actor);
            work->byte_delay=1;
            {
                u32 variant_phase;
                register struct DirectionalSequenceEvent *variant_event __asm__("r3");
                variant_phase=259;
                __asm__("" : "+r" (variant_phase));
                variant_event=event;
                /* Real numeric value precedes this actual publication address. */
                __asm__("" : "+r" (variant_event) : "r" (variant_phase));
                variant_event->phase=(u16)variant_phase;
            }
            break;
        }
        value=52;
        if(work->special==1) value=84;
        work->record_child=CreateRecordSequence(work->actor,&work->record,value,2,
                     work->completion,gDirectionalRecordStage,variant,variant,STACK_PARENT_VALUE("r5",parent));
        goto advance_phase;
        break;
    }
    case 257: {
        u32 count;
        if(work->completion[0]==0) break;
        if(work->special==0)
            work->motion=CreateRecordMotion(work->record,2,12,0,STACK_PARENT_VALUE("r2",parent));
        else
            work->motion=CreateRecordMotion(work->record,1,12,0,STACK_PARENT_VALUE("r3",parent));
        work->sequence=CreateSequenceStage(gDirectionalStage,1,4,0,STACK_PARENT_VALUE("r4",parent));
        count=QueryDefinitionTargets(work->actor,0,30,parent);
        work->count=(u8)count;
        if((u8)count==0) {
            next_phase=90;
            /* Real ordinal producer is also the following phase arithmetic input. */
            __asm__("" : "+r" (next_phase));
            work->ordinal=(u16)next_phase;
            next_phase+=170;
            goto publish_phase;
        } else {
            work->ordinal=30;
advance_phase:
            { register u16 *phase_ptr __asm__("r1") = &event->phase;
          register u32 phase_value __asm__("r0") = (u32)*phase_ptr + 1;
          /* One real H0 store owns precisely this output; no post-store USE. */
          __asm__ volatile("strh %1, [%2]"
                           : "=m" (*phase_ptr)
                           : "l" (phase_value), "l" (phase_ptr)); }
        }
        break;
    }
    case 258: {
        u32 remaining=work->ordinal;
        if(remaining!=0) {
            --remaining;
            work->ordinal=(u16)remaining;
            if((u16)remaining!=0) break;
        }
        work->byte_delay=1;
        { register u16 *phase_ptr __asm__("r2") = &event->phase;
          register u32 phase_value __asm__("r0") = (u32)*phase_ptr + 1;
          /* One real H0 store owns precisely this output; no post-store USE. */
          __asm__ volatile("strh %1, [%2]"
                           : "=m" (*phase_ptr)
                           : "l" (phase_value), "l" (phase_ptr)); }
        break;
    }
    case 259: {
        struct TargetChildEvent child_event;
        TaskNode **polled_children=work->children;
        register TaskNode **children __asm__("r10");
        u32 remaining,countdown_test;
        u8 slot,special;
        TaskNode *first;
        register s32 direction __asm__("r4");
        register void *actor_source __asm__("r3");
        register void *actor __asm__("r12");
        u32 ordinal;
        struct TargetChildEvent *child;
        PollDefinitionTaskArray(polled_children,4);
        remaining=work->byte_delay-1;
        work->byte_delay=(u8)remaining;
        countdown_test=remaining<<24;
        children=polled_children;
        __asm__("" : "+r"(children) : "r"(countdown_test));
        if(countdown_test!=0) break;
        slot=0;
        first=work->children[0];
        direction=work->direction;
        /* Real signed direction overlaps both still-unbound child and slot. */
        __asm__("" : "+r" (direction));
        actor_source=work->actor;
        actor=actor_source;
        /* Both real stages exist before the ordinal and special-byte reads. */
        __asm__("" : "+r" (actor) : "r" (actor_source));
        ordinal=work->ordinal;
        child=&child_event;
        special=work->special;
        if(first!=0) {
            TaskNode **scan_children=children;
            __asm__("" : "+r"(scan_children));
            do {
                ++slot;
                if(slot>3) break;
            } while(__extension__ ({
                register u32 slot_address __asm__("r0")=(u32)slot<<2;
                /* Native address add writes R0 from real base plus offset;
                 * the following ordinary pointer read owns the memory effect. */
                __asm__("add %0, %1, %0"
                        : "+l" (slot_address) : "l" (scan_children) : "cc");
                *(TaskNode **)slot_address;
            })!=0);
        }
        child->direction=(u16)direction;
        child->ordinal=(u16)ordinal;
        child->special=special;
        child->target=GetDefinitionTarget(actor,(u8)ordinal);
        /* Preserve the original scan result even when all four handles are
         * non-NULL; no invented clamp or early-return behavior. */
        children[slot]=CreateOppositePhaseChild((TaskCallback)RunDirectionalTargetChild,
                                                40,(const u32 *)child,parent);
        work->byte_delay=40;
        ++work->ordinal;
        if(work->ordinal==work->count) { register u16 *phase_ptr __asm__("r4") = &event->phase;
          register u32 phase_value __asm__("r0") = (u32)*phase_ptr + 1;
          /* One real H0 store owns precisely this output; no post-store USE. */
          __asm__ volatile("strh %1, [%2]"
                           : "=m" (*phase_ptr)
                           : "l" (phase_value), "l" (phase_ptr)); }
        break;
    }
    case 260:
        work->motion=PollAndReleaseMotion(work->motion);
        if(work->motion!=0) break;
        if((u8)IsRecordFinished(work->record)==0) break;
        if((u8)PollDefinitionTaskArray(work->children,4)!=0) {
            next_phase=2;
publish_phase:
            {
                register struct DirectionalSequenceEvent *numeric_event __asm__("r5")=event;
                /* Real common H0 address; the actual number remains unbound. */
                __asm__("" : "+r" (numeric_event));
                numeric_event->phase=(u16)next_phase;
            }
        }
        break;
    }
    return 0;
}
