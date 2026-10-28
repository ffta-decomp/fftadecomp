/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct TransactionRecord {u8 unknown00[18];u8 field12;};
union ControllerState {
 struct {u16 current;u16 depth;u16 stack[1];} navigation;
 struct {u8 unknown00[68];void *event;u8 unknown48[5];u8 mode77;u16 message;u8 mode80;u8 pending;u8 unknown52[2];u32 flags;s32 selection88;s32 selection92;u32 original;u16 signature;u16 value;} dispatch;
};
extern struct TransactionRecord transaction;
extern union ControllerState *controller;
extern s16 GetEventRuntimePayloadField06(void *);
extern u32 GetSelectedValue(void *);
extern void StoreSelectedValue(u32);
extern void ResetSelectionEvent(void *);
typedef char ControllerLayout[sizeof(union ControllerState)==104?1:-1];
asm(".global transaction\n.set transaction,0x020020d0");
asm(".global controller\n.set controller,0x0200f450");
asm(".global GetEventRuntimePayloadField06\n.thumb_set GetEventRuntimePayloadField06,0x08065051");
asm(".global GetSelectedValue\n.thumb_set GetSelectedValue,0x08065061");
asm(".global StoreSelectedValue\n.thumb_set StoreSelectedValue,0x0806603d");
asm(".global ResetSelectionEvent\n.thumb_set ResetSelectionEvent,0x08066029");

void AdvanceSelectionModeEvent(void)
{
    s32 selection=GetEventRuntimePayloadField06(controller->dispatch.event);
    if(selection!=0) {
        if(selection==-1) {
            union ControllerState *state;
            {
                union ControllerState *cancel_state=controller;
                cancel_state->dispatch.selection92=selection;
                cancel_state->dispatch.message=173;
                cancel_state->dispatch.flags|=2;
                cancel_state->dispatch.mode80=3;
            }
            {
                union ControllerState *message_state=controller;
                message_state->dispatch.signature=0x9001;
                message_state->dispatch.value=0x1234;
                ResetSelectionEvent(message_state->dispatch.event);
            }
            state=controller;
            state->navigation.current=48;
            state->navigation.stack[state->navigation.depth++]=48;
            state->navigation.current=57;
            state->navigation.stack[state->navigation.depth++]=57;
            state->navigation.current=59;
            state->navigation.stack[state->navigation.depth++]=59;
            state->navigation.current=52;
            state->navigation.stack[state->navigation.depth++]=52;
            state->navigation.current=51;
            state->navigation.stack[state->navigation.depth++]=51;
            state->navigation.current=41;
            state->navigation.stack[state->navigation.depth++]=41;
            state->navigation.current=40;
            state->navigation.stack[state->navigation.depth++]=40;
            state->navigation.current=57;
            state->navigation.stack[state->navigation.depth++]=57;
            state->navigation.current=50;
        } else {
            union ControllerState *state;
            StoreSelectedValue(GetSelectedValue(controller->dispatch.event));
            controller->dispatch.mode77=9;
            transaction.field12=0;
            ResetSelectionEvent(controller->dispatch.event);
            state=controller;
            state->navigation.current=10;
            state->navigation.stack[state->navigation.depth++]=10;
            state->navigation.current=49;
            state->navigation.stack[state->navigation.depth++]=49;
            state->navigation.current=50;
        }
    }
}
