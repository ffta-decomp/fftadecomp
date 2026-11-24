#ifndef FFTA_10533C_TARGET_PALETTE_H
#define FFTA_10533C_TARGET_PALETTE_H
#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef signed int s32;
typedef struct TaskNode TaskNode;
typedef struct PaletteSequenceEvent {
 u16 state,unknown02;
 void *source;
 u32 unknown08[3];
 u8 selector_low,selector_high;
 u16 mode;
 u32 unknown18;
} PaletteSequenceEvent;
typedef struct TargetPaletteWork {
 u16 timer;
 u8 variant,mode,ready,unknown05;
 u16 x,y,unknown0a;
 void *actor_context,*target;
 TaskNode *ready_sequence;
 void *positioned_output;
 TaskNode *positioned;
 void *display_resource;
 TaskNode *authored;
 TaskNode *palettes[3];
 TaskNode *initial;
 void *source,*target_sequence;
 TaskNode *secondary;
} TargetPaletteWork;
typedef char Event28[sizeof(PaletteSequenceEvent)==28?1:-1];
typedef char Work68[sizeof(TargetPaletteWork)==68?1:-1];
typedef char ChildArrayAt40[(u32)&((TargetPaletteWork *)0)->palettes==40?1:-1];
extern void CopyBytes(void *,const void *,u32);
extern TaskNode *CreateInitialSequence(void *,const void *,u32,u32,u32,TaskNode *);
extern void CopyCountedPaletteGroupsToShadow(const u8 *,u32,u32,u32,u32);
extern void AdvanceCurrentSequenceState(void);
extern TaskNode *PollInitialSequence(TaskNode *);
extern u32 ReadSourceUnavailable(void *);
extern TaskNode *CreateActorReadySequence(void *,void **,u32,u32,u8 *,const void *,u32,u32,TaskNode *);
extern u32 QueryRecordPositionBoundary(void *);
extern u32 QueryDefinitionReadiness(void);
extern u32 CheckSourceStage(void *,u32);
extern void *ReadSequenceTarget(void *,u32);
extern void *ProjectActorWithDefaultTransition(void *,u16 *,u16 *,u16 *);
/* Site ABI retains full SIGN16 coordinates, including stack argument five. */
extern void ConfigureDefinitionCoordinates(u32,u32,u32,s32,s32);
extern void *CreateDefinitionResource(u32,const void *,u32,u32);
extern u32 ReadDisplayHighBitMask(u32);
extern TaskNode *CreateAuthoredSequence(const void *,TaskNode *);
extern TaskNode *CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode *CreateSecondarySequence(const void *,u32,u32,u32,TaskNode *);
extern TaskNode *PollAuthoredSequence(TaskNode *);
extern u32 PollStageHandleArray(TaskNode **,u32);
extern void *PollDefinitionResource(void *,u32);
extern u32 ReadRecordPropertyLowByte(void *,u8);
extern TaskNode *CreatePositionedDefinitionTask(s32,s32,s32,u32,u32,void *,const void *,TaskNode *);
extern void *CreateTargetSequence(void *,const void *,u32,u32,u32,TaskNode *,u32);
extern TaskNode *PollPositionedDefinition(TaskNode *);
extern void *PollTargetSequence(void *);
extern const u8 InitialGroupParameters[];
extern const u8 PropertySelectors[];
extern const u8 InitialSequenceData[];
extern const u8 *const VariantPaletteRecords[];
extern const u8 FixedObjectPaletteRecord[];
extern const u8 ReadySequenceData[];
extern const u8 DisplayResourceRecord[];
extern const u8 AuthoredSequenceData[];
extern const void *const VariantPaletteSequences[];
extern const u8 SecondaryStartData[];
extern const void *const PositionedSequences[];
extern const u8 SecondaryImpactData[];
extern const u8 TargetSequences[];
extern volatile u16 DisplayShadowControl;
#endif
