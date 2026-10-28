typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TransitionCleanupAnchor {
    void *allocation;
    u8 unknown_04[122-4];
    u16 mode;
};
struct TransitionSaveFlags {
    u8 unknown_prefix[0x3c24];
    u32 pending_flags;
};
struct TransitionIwramControl {
    u8 unknown_prefix[7];
    u8 control;
};
struct TransitionTransientState {
    u8 unknown_prefix[150];
    u16 mode;
};
typedef char CleanupModeOffset[((u32)&((struct TransitionCleanupAnchor*)0)->mode==122)?1:-1];
typedef char PendingFlagOffset[((u32)&((struct TransitionSaveFlags*)0)->pending_flags==0x3c24)?1:-1];
typedef char TransientModeOffset[((u32)&((struct TransitionTransientState*)0)->mode==150)?1:-1];
extern struct TransitionCleanupAnchor gTransitionCleanup;
extern struct TransitionSaveFlags gTransitionSave;
extern struct TransitionIwramControl gTransitionIwram;
extern struct TransitionTransientState gTransitionTransient;
extern u16 gTransitionPaletteControl;
extern void ReleaseTransitionAllocation(void **);
extern void ReleaseTransitionResources(void);
extern void FinishTransitionCallbacks(void);
extern void ReleaseTransitionHeap(void);
/* Native mode3 writes reset markers then loops forever; preserve call CFG. */
extern void EnterTransitionResetLoop(void);
extern int IsTransitionDisplayActive(void);
extern void ClearTransitionDisplayWithFlag(u32);
extern u8 GetTransitionGameFlag(u16);
extern void SetTransitionDisplayValue(u16);
extern void SetTransitionDisplayValueHighBit(u16);
extern void CompactDeferredUnitRoster(void);
__asm__(".global gTransitionCleanup\n.set gTransitionCleanup,0x200f3ac");
__asm__(".global gTransitionSave\n.set gTransitionSave,0x2000000");
__asm__(".global gTransitionIwram\n.set gTransitionIwram,0x3000000");
__asm__(".global gTransitionTransient\n.set gTransitionTransient,0x200f390");
__asm__(".global gTransitionPaletteControl\n.set gTransitionPaletteControl,0x3003860");
__asm__(".global ReleaseTransitionAllocation\n.thumb_set ReleaseTransitionAllocation,0x80247fd");
__asm__(".global ReleaseTransitionResources\n.thumb_set ReleaseTransitionResources,0x8096cb9");
__asm__(".global FinishTransitionCallbacks\n.thumb_set FinishTransitionCallbacks,0x8022dd1");
__asm__(".global ReleaseTransitionHeap\n.thumb_set ReleaseTransitionHeap,0x802282d");
__asm__(".global EnterTransitionResetLoop\n.thumb_set EnterTransitionResetLoop,0x80231c1");
__asm__(".global IsTransitionDisplayActive\n.thumb_set IsTransitionDisplayActive,0x800395d");
__asm__(".global ClearTransitionDisplayWithFlag\n.thumb_set ClearTransitionDisplayWithFlag,0x8003935");
__asm__(".global GetTransitionGameFlag\n.thumb_set GetTransitionGameFlag,0x80c9541");
__asm__(".global SetTransitionDisplayValue\n.thumb_set SetTransitionDisplayValue,0x80038e9");
__asm__(".global SetTransitionDisplayValueHighBit\n.thumb_set SetTransitionDisplayValueHighBit,0x80038c9");
__asm__(".global CompactDeferredUnitRoster\n.thumb_set CompactDeferredUnitRoster,0x80891bd");
