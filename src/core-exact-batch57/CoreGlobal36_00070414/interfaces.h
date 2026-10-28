typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct RosterSceneRoot {
    u8 unknown_0000[0x43a];
    u8 field_043a; /* Meaning tentative; native entry stores 3. */
    u8 unknown_043b[0x44c - 0x43b];
    u8 pending_state;
    u8 unknown_044d[2];
    u8 dispatch_state;
    u8 unknown_0450[0x95e - 0x450];
    s8 field_095e; /* Native entry clears bit 0. */
    u8 unknown_095f[0xc1e - 0x95f];
    u8 field_0c1e; /* Native entry sets all eight bits. */
    u8 unknown_0c1f[0x2c38 - 0xc1f];
    u8 saved_working_region[80];
};
#define CHECK_OFFSET(name, field, offset) typedef char name[((u32)&((struct RosterSceneRoot *)0)->field == offset) ? 1 : -1]
CHECK_OFFSET(RosterPendingOffset, pending_state, 0x44c);
CHECK_OFFSET(RosterDispatchOffset, dispatch_state, 0x44f);
CHECK_OFFSET(RosterBackupOffset, saved_working_region, 0x2c38);
struct RosterTaskGroup;
typedef void (*RosterContinuation)(void); /* Stored addresses only; not an invocation ABI. */
extern struct RosterSceneRoot *gRosterSceneRoot;
extern u8 gRosterWorkingRegion[80];
extern u8 gRosterInterruptState;
extern void *gRosterObjectHandles[2];
extern struct RosterTaskGroup gRosterPrimaryGroup;
extern struct RosterTaskGroup gRosterSecondaryGroup;
extern u8 gRosterTaskMemory[];
extern u8 gRosterTaskStates[];
extern void *CopyRosterBytes(void *, const void *, u32);
extern void SetupRosterMode(u32);
extern void TeardownRosterMode(u32);
extern void ResetRosterInterruptState(void);
extern void InitializeRosterDisplay(void);
extern void InitializeRosterDisplayLists(void);
extern void ResetRosterObjectRange(void *, u32);
extern void ConfigureRosterLayout(void);
extern void WriteRosterSceneSaveByte(u16, u8);
extern void InitializeRosterTaskGroup(struct RosterTaskGroup *, void *, void *, u32);
extern void AttachRosterContinuation(struct RosterTaskGroup *, u32, RosterContinuation);
extern void AdvanceRosterTaskGroup(struct RosterTaskGroup *, u32);
extern void ClearRosterTaskGroup(struct RosterTaskGroup *);
extern void RemoveRosterContinuation(struct RosterTaskGroup *, u32);
extern void EnableRosterInterruptState(void);
extern void CompactPersistentRoster(void);
extern void RequestRosterReturnScene(u32);
extern void RosterMainContinuation(void);
extern void RosterEmptyContinuation(void);
extern void RosterDetailContinuation(void);
extern void RosterAuxiliaryContinuation(void);
extern void RosterInputContinuation(void);
extern void RosterSecondaryFirst(void);
extern void RosterSecondarySecond(void);
__asm__(
    ".global gRosterSceneRoot\n.set gRosterSceneRoot,0x03002818\n"
    ".global gRosterWorkingRegion\n.set gRosterWorkingRegion,0x03000940\n"
    ".global gRosterInterruptState\n.set gRosterInterruptState,0x030027a4\n"
    ".global gRosterObjectHandles\n.set gRosterObjectHandles,0x03000e30\n"
    ".global gRosterPrimaryGroup\n.set gRosterPrimaryGroup,0x03002730\n"
    ".global gRosterSecondaryGroup\n.set gRosterSecondaryGroup,0x03000880\n"
    ".global gRosterTaskMemory\n.set gRosterTaskMemory,0x03000910\n"
    ".global gRosterTaskStates\n.set gRosterTaskStates,0x03000ec0\n"
    ".global CopyRosterBytes\n.thumb_set CopyRosterBytes,0x081443fd\n"
    ".global SetupRosterMode\n.thumb_set SetupRosterMode,0x0807109d\n"
    ".global TeardownRosterMode\n.thumb_set TeardownRosterMode,0x08071235\n"
    ".global ResetRosterInterruptState\n.thumb_set ResetRosterInterruptState,0x08089c4d\n"
    ".global InitializeRosterDisplay\n.thumb_set InitializeRosterDisplay,0x08087161\n"
    ".global InitializeRosterDisplayLists\n.thumb_set InitializeRosterDisplayLists,0x08087301\n"
    ".global ResetRosterObjectRange\n.thumb_set ResetRosterObjectRange,0x0804c835\n"
    ".global ConfigureRosterLayout\n.thumb_set ConfigureRosterLayout,0x080712d1\n"
    ".global WriteRosterSceneSaveByte\n.thumb_set WriteRosterSceneSaveByte,0x080c95c1\n"
    ".global InitializeRosterTaskGroup\n.thumb_set InitializeRosterTaskGroup,0x08006a7d\n"
    ".global AttachRosterContinuation\n.thumb_set AttachRosterContinuation,0x08006add\n"
    ".global AdvanceRosterTaskGroup\n.thumb_set AdvanceRosterTaskGroup,0x080069f5\n"
    ".global ClearRosterTaskGroup\n.thumb_set ClearRosterTaskGroup,0x08006b5d\n"
    ".global RemoveRosterContinuation\n.thumb_set RemoveRosterContinuation,0x08006b8d\n"
    ".global EnableRosterInterruptState\n.thumb_set EnableRosterInterruptState,0x08089c85\n"
    ".global CompactPersistentRoster\n.thumb_set CompactPersistentRoster,0x080891bd\n"
    ".global RequestRosterReturnScene\n.thumb_set RequestRosterReturnScene,0x08003935\n"
    ".global RosterMainContinuation\n.thumb_set RosterMainContinuation,0x08073705\n"
    ".global RosterEmptyContinuation\n.thumb_set RosterEmptyContinuation,0x08071375\n"
    ".global RosterDetailContinuation\n.thumb_set RosterDetailContinuation,0x0807411d\n"
    ".global RosterAuxiliaryContinuation\n.thumb_set RosterAuxiliaryContinuation,0x080888b5\n"
    ".global RosterInputContinuation\n.thumb_set RosterInputContinuation,0x08087fb9\n"
    ".global RosterSecondaryFirst\n.thumb_set RosterSecondaryFirst,0x08087f0d\n"
    ".global RosterSecondarySecond\n.thumb_set RosterSecondarySecond,0x0808b289\n"
);
