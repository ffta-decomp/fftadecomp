#include "abi/interfaces/080fdab0_continuation_sequence.h"

u32 AdvanceRecordContinuationSequence(TaskNode *, EventRecord *, ContinuationWork *)
    __asm__("OriginalRegisteredActionQuestion_000FDAB0");

u32 AdvanceRecordContinuationSequence(TaskNode *parent, EventRecord *event,
                                      ContinuationWork *work)
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
        parameter = 5;
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
        work->initial = child;
        if (child != 0)
            break;
        child = CreateRecordEffectContinuation(work->source, 5, 0,
                                               (u32)&work->status, parent);
        work->continuation = child;
        if (child != 0)
            event->state++;
        else
            event->state = 2;
        break;
    }
    case 257: {
        u8 status = work->status;
        if (status != 0) {
            if (status == 2) {
                event->state = 258;
            } else {
                /* Original supplies only these three fields of the genuine
                 * 28-byte event; do not invent zeros for the other fields. */
                EventRecord followup;
                followup.selector = 158;
                followup.mode = 1;
                followup.source = work->source;
                work->followup = CreateOppositePhaseTask(FollowupCallback, 64,
                                                          &followup, parent);
                event->state++;
            }
        }
        break;
    }
    case 258: {
        TaskNode *child = PollContinuation(work->continuation);
        work->continuation = child;
        if (child != 0)
            break;
        child = PollFollowup(work->followup);
        work->followup = child;
        if (child == 0)
            event->state = 2;
        break;
    }
    }
    return 0;
}

__asm__(
 ".global CreateInitialSequence\n.thumb_set CreateInitialSequence,0x080E03F9\n"
 ".global AdvanceCurrentSequenceState\n.thumb_set AdvanceCurrentSequenceState,0x080D38B5\n"
 ".global PollInitialSequence\n.thumb_set PollInitialSequence,0x080E05DD\n"
 ".global CreateRecordEffectContinuation\n.thumb_set CreateRecordEffectContinuation,0x080FDE59\n"
 ".global CreateOppositePhaseTask\n.thumb_set CreateOppositePhaseTask,0x08005B6D\n"
 ".global PollContinuation\n.thumb_set PollContinuation,0x080FDEBD\n"
 ".global PollFollowup\n.thumb_set PollFollowup,0x080E051D\n"
 ".global FollowupCallback\n.thumb_set FollowupCallback,0x080E5F51\n"
 ".global InitialSequenceData\n.set InitialSequenceData,0x0839D798\n"
);
