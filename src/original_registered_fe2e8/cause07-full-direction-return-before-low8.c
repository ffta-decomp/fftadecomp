#include "driver_sequence_arrays.h"

u32 AdvanceSourceTargetDriverSequence(TaskNode *, EventRecord *, SequenceWork *)
    __asm__("OriginalRegisteredActionQuestion_000FE2E8");

/* Both templates are genuine seven-word objects, with only the original
 * supplied fields initialized. The constructor synchronously invokes a child;
 * later observations therefore reload the parent's callback-visible fields. */
u32 AdvanceSourceTargetDriverSequence(TaskNode *parent, EventRecord *event,
                                     SequenceWork *work)
{
    u16 state = event->state;
    switch (state) {
    case 0: {
        u32 parameter;
        u16 mode = event->mode;
        void *source;
        work->mode = mode;
        source = event->source;
        work->source = source;
        parameter = 4;
        if ((u8)mode != 0)
            parameter = 0;
        work->initial_child = CreateInitialSequence(source, InitialSequenceData,
                                                   parameter, 0, state, parent);
        break;
    }
    case 1:
        AdvanceCurrentSequenceState();
        break;
    case 256: {
        TaskNode *child = PollInitialSequence(work->initial_child);
        u8 unavailable;
        ActorModel *model;
        WorldPosition3 *from;
        register WorldPosition3 *position __asm__("r4");
        WorldPosition3 *to;
        u8 has_targets;
        register u32 direction __asm__("r4");
        DriverEvent child_event;
        work->initial_child = child;
        if (child != 0)
            break;
        unavailable = ReadSourceUnavailable(work->source);
        if (unavailable != 0) {
            event->state = 2;
            break;
        }
        model = ResolveSourceModel(work->source);
        work->model = model;
        work->ready_child = CreateReadySequence(model, &work->ready, 0, 2,
            unavailable, unavailable, unavailable, parent);
        ReadModelPosition(work->model,
            ({ position = &work->from;
               __asm__("" : "+r"(position));
               &(*position)[0]; }), &work->from[1], &work->from[2]);
        has_targets = CountSequenceTargets(work->source);
        from = position;
        if (has_targets != 0) {
            void *target = ReadTargetModel(work->source, 0);
            work->target = target;
            position = (WorldPosition3 *)((u8 *)position + 8);
            ReadTargetPosition(target, &(*position)[0], &work->to[1],
                               &work->to[2]);
        } else {
            ReadFallbackPosition(work->source,
                &(*(position = &work->to))[0], &work->to[1], &work->to[2]);
        }
        /* Actual initialized cursor remains R4 through both OUT arms; the
         * final destination snapshot survives the two following helpers. */
        __asm__("" : "+r"(position));
        to = position;
        direction = ReadActorSignedDirection(work->model);
        /* Capture the helper's full physical return before LOW8 normalization.
         * Native R4 first holds that result, then its truncated byte value. */
        __asm__("" : "+r"(direction));
        direction = (u8)direction;
        child_event.selector = ReadSourceSelector(work->source);
        child_event.direction = (s8)direction;
        child_event.from = from;
        child_event.to = to;
        work->driver = CreateOppositePhaseTask(DriverSequenceCallback, 536,
                                               &child_event, parent);
        event->state++;
        break;
    }
    case 257: {
        TargetRecord *target;
        TilePosition3 current;
        if ((ReadTaskState(work->driver) << 16) != (259u << 16))
            break;
        target = ReadSequenceTarget(work->source, 0);
        if (target->kind == 6)
            work->special = 1;
        if (work->special != 0) {
            DriverWork *driver = ReadDriverWork(work->driver);
            u16 adjusted_parameter = driver->parameter20 + 18;
            ReadModelPhysicalPosition(work->model, &current[0], &current[1],
                                        &current[2]);
            /* The helper writes halfwords; this caller observes only the low
             * physical bytes of X and Z, exactly as the original LDRBs. */
            work->special_child = CreateSpecialTargetSequence(target, 0x3D1, 6,
                *(u8 *)&current[0], *(u8 *)&current[2], adjusted_parameter, parent);
        }
        SetActorSequenceState(work->model, 152);
        event->state++;
        break;
    }
    case 258:
        if (work->ready != 0) {
            DriverWork *driver;
            SetTaskState(work->driver, 260);
            driver = ReadDriverWork(work->driver);
            StopDriverChannel(driver->channel);
            ConfigureDriverActor(driver->actor, 1);
            ApplySourceTargetStage(work->source, work->target);
            work->secondary_child = CreateSecondarySequence(SecondarySequenceData,
                                                             1, 4, 0, parent);
            event->state++;
        }
        break;
    case 259: {
        TaskNode *child = PollSequenceTask(work->driver);
        EventRecord child_event;
        work->driver = child;
        if (child != 0)
            break;
        child_event.source = ReadSequenceTarget(work->source, 0);
        if (work->target != 0) {
            if (work->special == 0)
                work->followup = CreateOppositePhaseTask(TargetFollowupCallback,
                                                          36, &child_event, parent);
        } else {
            ApplySourceStage(work->source, 0);
        }
        event->state++;
        break;
    }
    case 260:
        if ((u8)IsActorSequenceFinished(work->model) != 0) {
            TaskNode *followup = PollSequenceTask(work->followup);
            work->followup = followup;
            if (followup == 0) {
                void *special = PollSpecialTargetSequence(work->special_child);
                work->special_child = special;
                if (special == 0)
                    event->state = 2;
            }
        }
        break;
    }
    return 0;
}

__asm__(".global CreateInitialSequence\n.thumb_set CreateInitialSequence,0x080E03F9\n"
        ".global AdvanceCurrentSequenceState\n.thumb_set AdvanceCurrentSequenceState,0x080D38B5\n"
        ".global PollInitialSequence\n.thumb_set PollInitialSequence,0x080E05DD\n"
        ".global ReadSourceUnavailable\n.thumb_set ReadSourceUnavailable,0x080D3B55\n"
        ".global ResolveSourceModel\n.thumb_set ResolveSourceModel,0x080DD47D\n"
        ".global CreateReadySequence\n.thumb_set CreateReadySequence,0x080DE4B1\n"
        ".global ReadModelPosition\n.thumb_set ReadModelPosition,0x080DBD5D\n"
        ".global CountSequenceTargets\n.thumb_set CountSequenceTargets,0x080DD495\n"
        ".global ReadTargetModel\n.thumb_set ReadTargetModel,0x080DD4B5\n"
        ".global ReadTargetPosition\n.thumb_set ReadTargetPosition,0x080DBD5D\n"
        ".global ReadFallbackPosition\n.thumb_set ReadFallbackPosition,0x080D8B7D\n"
        ".global ReadActorSignedDirection\n.thumb_set ReadActorSignedDirection,0x080DBC89\n"
        ".global ReadSourceSelector\n.thumb_set ReadSourceSelector,0x080DD489\n"
        ".global CreateOppositePhaseTask\n.thumb_set CreateOppositePhaseTask,0x08005B6D\n"
        ".global DriverSequenceCallback\n.thumb_set DriverSequenceCallback,0x080FDF91\n"
        ".global ReadTaskState\n.thumb_set ReadTaskState,0x08005BAD\n"
        ".global ReadSequenceTarget\n.thumb_set ReadSequenceTarget,0x080DD4A5\n"
        ".global ReadDriverWork\n.thumb_set ReadDriverWork,0x08005BFD\n"
        ".global ReadModelPhysicalPosition\n.thumb_set ReadModelPhysicalPosition,0x080DBD79\n"
        ".global CreateSpecialTargetSequence\n.thumb_set CreateSpecialTargetSequence,0x080DFA31\n"
        ".global SetActorSequenceState\n.thumb_set SetActorSequenceState,0x080DE10D\n"
        ".global SetTaskState\n.thumb_set SetTaskState,0x08005BA9\n"
        ".global StopDriverChannel\n.thumb_set StopDriverChannel,0x080D5C21\n"
        ".global ConfigureDriverActor\n.thumb_set ConfigureDriverActor,0x0801115D\n"
        ".global ApplySourceTargetStage\n.thumb_set ApplySourceTargetStage,0x080FDEE9\n"
        ".global CreateSecondarySequence\n.thumb_set CreateSecondarySequence,0x080DFD8D\n"
        ".global PollSequenceTask\n.thumb_set PollSequenceTask,0x080E051D\n"
        ".global TargetFollowupCallback\n.thumb_set TargetFollowupCallback,0x080FE235\n"
        ".global ApplySourceStage\n.thumb_set ApplySourceStage,0x080D8859\n"
        ".global IsActorSequenceFinished\n.thumb_set IsActorSequenceFinished,0x080DE1F1\n"
        ".global PollSpecialTargetSequence\n.thumb_set PollSpecialTargetSequence,0x080DBA5D\n"
        ".global InitialSequenceData\n.set InitialSequenceData,0x0839D844\n"
        ".global SecondarySequenceData\n.set SecondarySequenceData,0x0839D8B8");
