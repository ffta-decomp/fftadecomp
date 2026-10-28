/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct TransactionRecord {u32 unknown00;u32 selected;u32 amount;};
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

void AdvanceSelectionEventContinuation(void)
{
    s32 selection=GetEventRuntimePayloadField06(controller->dispatch.event);
    if(selection!=0) {
        if(selection==-1) {
            union ControllerState *state;
            ResetSelectionEvent(controller->dispatch.event);
            state=controller;
            state->dispatch.flags|=2;
            state->dispatch.flags|=4;
            state->dispatch.message=183;
            state->navigation.current=19;
            state->navigation.stack[state->navigation.depth++]=19;
            state->navigation.current=52;
            state->navigation.stack[state->navigation.depth++]=52;
            state->navigation.current=51;
            state->navigation.stack[state->navigation.depth++]=51;
            state->navigation.current=50;
        } else {
            union ControllerState *state;
            transaction.selected=GetSelectedValue(controller->dispatch.event);
            transaction.amount=5000;
            ResetSelectionEvent(controller->dispatch.event);
            state=controller;
            state->dispatch.flags|=2;
            state->dispatch.flags|=1;
            state->dispatch.flags&=~4;
            state->dispatch.message=185;
            state->navigation.current=25;
            state->navigation.stack[state->navigation.depth++]=25;
            state->navigation.current=51;
            state->navigation.stack[state->navigation.depth++]=51;
            state->navigation.current=66;
            state->navigation.stack[state->navigation.depth++]=66;
            state->navigation.current=50;
        }
    }
}
