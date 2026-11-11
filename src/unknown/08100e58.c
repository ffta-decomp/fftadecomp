#include "abi/interfaces/08100e58_selected_child.h"

u32 AdvanceSelectedRecordChildSequence(TaskNode *,SelectedChildEvent *,SelectedChildWork *)
 __asm__("OriginalRegisteredActionQuestion_00100E58");

u32 AdvanceSelectedRecordChildSequence(TaskNode *parent,SelectedChildEvent *event,
                                     SelectedChildWork *work)
{
 int state=event->state;
 switch(state) {
 case 0: {
  void *source;
  work->selector=event->selector;
  work->mode=event->mode;
  source=event->source;
  work->source=source;
  work->nested=GetRecordNestedPointer(source);
  break;
 }
 case 1:
  AdvanceCurrentSequenceState();
  break;
 case 256: {
  /* Original intentionally supplies only these four event fields. */
  SelectedChildEvent child_event;
  child_event.selector=work->selector;
  child_event.mode=0;
  child_event.source=work->source;
  child_event.nested=work->nested;
  work->child=CreateOppositePhaseTask(SelectedRecordChildCallback,52,&child_event,parent);
  event->state++;
  break;
 }
 case 257: {
  TaskNode *child=PollAndReleaseChild(work->child);
  work->child=child;
  if(child==0) event->state++;
  break;
 }
 case 258:
  event->state=2;
  break;
 }
 return 0;
}

__asm__(
 ".global GetRecordNestedPointer\n.thumb_set GetRecordNestedPointer,0x080DD47D\n"
 ".global AdvanceCurrentSequenceState\n.thumb_set AdvanceCurrentSequenceState,0x080D38B5\n"
 ".global CreateOppositePhaseTask\n.thumb_set CreateOppositePhaseTask,0x08005B6D\n"
 ".global PollAndReleaseChild\n.thumb_set PollAndReleaseChild,0x080E051D\n"
 ".global SelectedRecordChildCallback\n.thumb_set SelectedRecordChildCallback,0x080E3789\n"
);
