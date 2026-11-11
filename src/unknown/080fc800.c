#include "abi/interfaces/080fc800_approach_sequence.h"

u32 AdvanceActorTargetApproachSequence(TaskNode *, EventRecord *, ApproachWork *)
    __asm__("OriginalRegisteredActionQuestion_000FC800");

/* Preserve source and target actor identities, real countdown fallthrough,
 * three independent resource cells, and their callback-visible reloads. */
u32 AdvanceActorTargetApproachSequence(TaskNode *parent, EventRecord *event,
                                     ApproachWork *work)
{
    u16 state = event->state;
    switch (state) {
    case 0: {
        u16 mode = event->mode;
        void *source;
        u32 parameter;
        work->mode = mode;
        source = event->source;
        work->source = source;
        parameter = 4;
        if ((u8)mode != 0)
            parameter = 0;
        work->initial = CreateInitialSequence(source, InitialSequenceData,
                                               parameter, 0, state, parent);
        break;
    }
    case 1:
        AdvanceCurrentSequenceState();
        break;
    case 256: {
        TaskNode *child = PollInitialSequence(work->initial);
        u8 unavailable;
        work->initial = child;
        if (child != 0)
            break;
        unavailable = ReadSourceUnavailable(work->source);
        if (unavailable != 0) {
            event->state = 2;
            break;
        }
        work->ready_sequence = CreateActorReadySequence(work->source,
            &work->source_actor, 0x8007, 1, &work->ready, ReadySequenceData,
            5, unavailable, parent);
        event->state++;
        break;
    }
    case 257:
        if (work->ready == 0)
            break;
        ApplySourceTransition(work->source, 0);
        work->timer = 30;
        event->state++;
        /* Original FALLTHROUGH: the new timer reaches 29 on this invocation. */
    case 258: {
        u8 busy;
        void *target;
        u32 direction;
        u16 original_x, start_x, start_y;
        void *resource;
        if (work->timer != 0) {
            u32 remaining = work->timer - 1;
            work->timer = remaining;
            if ((u16)remaining != 0)
                break;
        }
        busy = QueryDefinitionReadiness();
        if (busy != 0)
            break;
        if ((u8)CheckSourceStage(work->source, 0) == 0) {
            event->state = 2;
            break;
        }
        target = ReadSequenceTarget(work->source, 0);
        work->projected_actor = ProjectActorWithDefaultTransition(target,
                                                    &work->x, &work->y, 0);
        /* This is the SOURCE actor output from the ready sequence, distinct
         * from the target projection return just published in work. */
        if ((u8)ReadActorFlag15(work->source_actor) != 0)
            work->y = work->y - 8;
        direction = ReadActorSignedDirection(work->source_actor);
        work->direction = direction;
        original_x = work->x;
        start_x = original_x + 96;
        start_y = work->y - 96;
        if ((u8)direction > 1)
            start_x = original_x - 96;
        resource = CreatePositionedResource(PrimaryResourceData, 0,
            (s16)start_x, (s16)start_y, 0x3F6, 6, busy, busy);
        work->primary_resource = resource;
        ConfigureResourceOptionA(resource, 1);
        if (work->direction > 1)
            ConfigureResourceOptionB(work->primary_resource, 1);
        InitializeDefinitionRamp(&work->x_ramp, (s16)start_x, (s16)work->x, 25);
        InitializeDefinitionRamp(&work->y_ramp, (s16)start_y, (s16)work->y, 25);
        work->target_sequence = CreateTargetSequence(target, TargetSequenceData,
                                                       12, 25, 20, parent, 25);
        work->secondary = CreateSecondarySequence(SecondarySequenceData, 1, 4, 0, parent);
        event->state++;
        break;
    }
    case 259: {
        u8 thresholds[3];
        DefinitionRamp *x_ramp, *y_ramp;
        register DefinitionRamp *prepared_x __asm__("r5");
        register DefinitionRamp *prepared_y __asm__("r4");
        void **children;
        u8 index;
        u32 zero;
        void *resource;
        CopyBytes(thresholds, ThresholdSource, 3);
        prepared_x = &work->x_ramp;
        __asm__("" : "+r"(prepared_x));
        AdvanceDefinitionRamp(prepared_x);
        prepared_y = &work->y_ramp;
        __asm__("" : "+r"(prepared_y));
        AdvanceDefinitionRamp(prepared_y);
        SetResourceCoordinates(work->primary_resource, (s16)prepared_x->value,
                               (s16)prepared_y->value, 0);
        index = 0;
        /* Actual preparation pointers survive the three calls in R5/R4;
         * their separate snapshots remain live across the following loop. */
        __asm__("" : "+r"(prepared_x), "+r"(prepared_y));
        x_ramp = prepared_x;
        y_ramp = prepared_y;
        children = work->children;
        do {
            void **cell = &children[index];
            void *child = *cell;
            if (child == 0 && (s16)y_ramp->value >= thresholds[index]) {
                u16 base_x = x_ramp->value;
                u16 x = base_x + 3;
                u16 y = y_ramp->value + 6;
                if (work->direction > 1)
                    x = base_x - 3;
                resource = CreatePositionedResource(BurstResourceData, 1,
                    (s16)x, (s16)y, 0x3D5, 7, (u32)child, (u32)child);
                *cell = resource;
                if (work->direction > 1)
                    ConfigureResourceOptionB(resource, 1);
                CommitResource(*cell);
            }
            index++;
        } while (index < 3);
        if ((u8)IsDefinitionRampComplete(x_ramp) == 0)
            break;
        RemoveDefinitionResource(work->primary_resource);
        zero = 0;
        work->primary_resource = (void *)zero;
        resource = CreatePositionedResource(FinalResourceData, 0,
            (s16)work->x, (s16)work->y, 0x368, 7, zero, zero);
        work->final_resource = resource;
        if (work->direction > 1)
            ConfigureResourceOptionB(resource, 1);
        CommitResource(work->final_resource);
        work->palette_sequence = CreateDefinitionPaletteTask(PaletteSequenceData, parent);
        event->state++;
        break;
    }
    case 260:
        if ((u8)IsActorSequenceFinished(work->source_actor) != 0) {
            TaskNode *palette;
            void *target;
            PollAndReleaseDefinitionWorkset(work->children, 3);
            work->final_resource = PollFinalResource(work->final_resource);
            palette = PollPaletteSequence(work->palette_sequence);
            work->palette_sequence = palette;
            if (palette != 0)
                break;
            target = PollTargetSequence(work->target_sequence);
            work->target_sequence = target;
            if (target != 0)
                break;
            event->state = 2;
        }
        break;
    }
    return 0;
}

__asm__(
    ".global CreateInitialSequence\n.thumb_set CreateInitialSequence,0x080E03F9\n"
    ".global AdvanceCurrentSequenceState\n.thumb_set AdvanceCurrentSequenceState,0x080D38B5\n"
    ".global PollInitialSequence\n.thumb_set PollInitialSequence,0x080E05DD\n"
    ".global ReadSourceUnavailable\n.thumb_set ReadSourceUnavailable,0x080D3B55\n"
    ".global CreateActorReadySequence\n.thumb_set CreateActorReadySequence,0x080DDF69\n"
    ".global ApplySourceTransition\n.thumb_set ApplySourceTransition,0x080DC059\n"
    ".global QueryDefinitionReadiness\n.thumb_set QueryDefinitionReadiness,0x080D8B4D\n"
    ".global CheckSourceStage\n.thumb_set CheckSourceStage,0x080D8859\n"
    ".global ReadSequenceTarget\n.thumb_set ReadSequenceTarget,0x080DD4A5\n"
    ".global ProjectActorWithDefaultTransition\n.thumb_set ProjectActorWithDefaultTransition,0x080DD749\n"
    ".global ReadActorFlag15\n.thumb_set ReadActorFlag15,0x080DD73D\n"
    ".global ReadActorSignedDirection\n.thumb_set ReadActorSignedDirection,0x080DBC89\n"
    ".global CreatePositionedResource\n.thumb_set CreatePositionedResource,0x080D5CC1\n"
    ".global ConfigureResourceOptionA\n.thumb_set ConfigureResourceOptionA,0x08011059\n"
    ".global ConfigureResourceOptionB\n.thumb_set ConfigureResourceOptionB,0x08011119\n"
    ".global InitializeDefinitionRamp\n.thumb_set InitializeDefinitionRamp,0x080E0609\n"
    ".global CreateTargetSequence\n.thumb_set CreateTargetSequence,0x080DCFE5\n"
    ".global CreateSecondarySequence\n.thumb_set CreateSecondarySequence,0x080DFD8D\n"
    ".global CopyBytes\n.thumb_set CopyBytes,0x081443FD\n"
    ".global AdvanceDefinitionRamp\n.thumb_set AdvanceDefinitionRamp,0x080E064D\n"
    ".global SetResourceCoordinates\n.thumb_set SetResourceCoordinates,0x080107D5\n"
    ".global CommitResource\n.thumb_set CommitResource,0x08011199\n"
    ".global IsDefinitionRampComplete\n.thumb_set IsDefinitionRampComplete,0x080E0691\n"
    ".global RemoveDefinitionResource\n.thumb_set RemoveDefinitionResource,0x08011429\n"
    ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x080D4705\n"
    ".global IsActorSequenceFinished\n.thumb_set IsActorSequenceFinished,0x080DE1F1\n"
    ".global PollAndReleaseDefinitionWorkset\n.thumb_set PollAndReleaseDefinitionWorkset,0x080D5F25\n"
    ".global PollFinalResource\n.thumb_set PollFinalResource,0x08011485\n"
    ".global PollPaletteSequence\n.thumb_set PollPaletteSequence,0x080D4775\n"
    ".global PollTargetSequence\n.thumb_set PollTargetSequence,0x080DBA5D\n"
    ".global InitialSequenceData\n.set InitialSequenceData,0x0839D420\n"
    ".global ReadySequenceData\n.set ReadySequenceData,0x0839D464\n"
    ".global TargetSequenceData\n.set TargetSequenceData,0x0839D450\n"
    ".global SecondarySequenceData\n.set SecondarySequenceData,0x0839D468\n"
    ".global ThresholdSource\n.set ThresholdSource,0x08149D88\n"
    ".global PrimaryResourceData\n.set PrimaryResourceData,0x08502DA4\n"
    ".global BurstResourceData\n.set BurstResourceData,0x084F6BC8\n"
    ".global FinalResourceData\n.set FinalResourceData,0x085000D8\n"
    ".global PaletteSequenceData\n.set PaletteSequenceData,0x089492DC\n"
);
