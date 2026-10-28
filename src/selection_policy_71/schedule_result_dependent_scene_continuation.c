/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TransactionRecord {u8 unknown00[12];u16 selector;};
struct SceneStatus {u8 unknown00[5];u8 active;};
union ControllerState {
 struct {u16 current;u16 depth;u16 stack[1];} navigation;
 struct {u8 unknown00[77];u8 mode;u8 unknown4e[3];u8 pending;u8 result;u8 unknown53;u32 flags;u8 unknown58[12];u16 signature;u16 value;} dispatch;
};
extern struct TransactionRecord transaction;
extern struct SceneStatus scene_status;
extern union ControllerState *controller;
extern void StopCurrentAudioSequence(void);
asm(".global transaction\n.set transaction,0x020020d0\n.global controller\n.set controller,0x0200f450\n.global scene_status\n.set scene_status,0x03000ed0\n.global StopCurrentAudioSequence\n.thumb_set StopCurrentAudioSequence,0x08141709");
typedef char ControllerLayout[sizeof(union ControllerState)==104?1:-1];

void ScheduleResultDependentSceneContinuation(void)
{
    union ControllerState *state;
    scene_status.active=1;
    if(controller->dispatch.result==0)
        transaction.selector=28;
    else
        transaction.selector=27;
    controller->dispatch.mode=11;
    controller->dispatch.pending=90;
    state=controller;
    state->navigation.current=63;
    state->navigation.stack[state->navigation.depth++]=63;
    state->navigation.current=55;
    state->navigation.stack[state->navigation.depth++]=55;
    state->navigation.current=49;
}
