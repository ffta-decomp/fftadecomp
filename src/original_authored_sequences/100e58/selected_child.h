#ifndef FFTA_100E58_SELECTED_CHILD_H
#define FFTA_100E58_SELECTED_CHILD_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
typedef struct NestedRecord NestedRecord;
typedef struct SelectedChildEvent {
 u16 state,unknown02;
 void *source;
 NestedRecord *nested;
 u32 unknown0c,unknown10;
 u16 selector,mode;
 u32 unknown18;
} SelectedChildEvent;
typedef struct SelectedChildWork {
 u8 unknown00[6],mode,unknown07;
 u16 selector,unknown0a;
 NestedRecord *nested;
 TaskNode *child;
 void *source;
} SelectedChildWork;
typedef u32 (*TaskCallback)(TaskNode *,SelectedChildEvent *,void *);
typedef char Event28[sizeof(SelectedChildEvent)==28?1:-1];
typedef char Work24[sizeof(SelectedChildWork)==24?1:-1];
extern NestedRecord *GetRecordNestedPointer(void *);
extern void AdvanceCurrentSequenceState(void);
extern TaskNode *CreateOppositePhaseTask(TaskCallback,u16,const SelectedChildEvent *,TaskNode *);
extern TaskNode *PollAndReleaseChild(TaskNode *);
extern u32 SelectedRecordChildCallback(TaskNode *,SelectedChildEvent *,void *);
#endif
