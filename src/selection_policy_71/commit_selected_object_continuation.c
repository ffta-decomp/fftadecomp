/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SelectedObject {u32 key;};
struct TransactionRecord {u8 unknown00[4];struct SelectedObject *selected;};
union ControllerState {
 struct {u16 current;u16 depth;u16 stack[1];} navigation;
 struct {u8 unknown00[68];void *event;u8 unknown48[8];u8 mode;u8 pending;u8 unknown52[2];u32 flags;s32 selection88;s32 selection92;u32 original;u16 signature;u16 value;} dispatch;
};
extern struct TransactionRecord transaction;
extern union ControllerState *controller;
extern s16 GetEventRuntimePayloadField06(void *);
extern u32 GetSelectedValue(void *);
extern u32 FindSelectedObjectKey(struct SelectedObject *);
extern u32 GetOriginalSelectedValue(void *);
extern void ResetSelectionEvent(void *);
typedef char ControllerLayout[sizeof(union ControllerState)==104?1:-1];
asm(".global transaction\n.set transaction,0x020020d0");
asm(".global controller\n.set controller,0x0200f450");
asm(".global GetSelectedValue\n.thumb_set GetSelectedValue,0x08065061");
asm(".global FindSelectedObjectKey\n.thumb_set FindSelectedObjectKey,0x080ca0f9");
asm(".global GetOriginalSelectedValue\n.thumb_set GetOriginalSelectedValue,0x0806514d");
asm(".global ResetSelectionEvent\n.thumb_set ResetSelectionEvent,0x08066029");
asm(".global GetEventRuntimePayloadField06\n.thumb_set GetEventRuntimePayloadField06,0x08065051");

void CommitSelectedObjectContinuation(void)
{
    s32 selection=GetEventRuntimePayloadField06(controller->dispatch.event);
    if(selection!=0) {
        union ControllerState *state;
        {
            union ControllerState *selection_state=controller;
            selection_state->dispatch.selection92=selection;
            selection_state->dispatch.selection88=selection;
            selection_state->dispatch.flags|=2;
            selection_state->dispatch.pending=16;
        }
        controller->dispatch.mode=3;
        if(selection!=-1) {
            struct SelectedObject *selected=(struct SelectedObject *)GetSelectedValue(controller->dispatch.event);
            transaction.selected=selected;
            selected->key=FindSelectedObjectKey(selected);
            controller->dispatch.original=GetOriginalSelectedValue(controller->dispatch.event);
        }
        ResetSelectionEvent(controller->dispatch.event);
        state=controller;
        if(state->dispatch.flags&4) {
            if(selection==-1) {
                state->dispatch.signature=0x9001;
                state->dispatch.value=0x1234;
                state->navigation.current=34;
                state->navigation.stack[state->navigation.depth++]=34;
                state->navigation.current=33;
                state->navigation.stack[state->navigation.depth++]=33;
                state->navigation.current=55;
                state->navigation.stack[state->navigation.depth++]=55;
                state->navigation.current=43;
                state->navigation.stack[state->navigation.depth++]=43;
                state->navigation.current=40;
                state->navigation.stack[state->navigation.depth++]=40;
                state->navigation.current=57;
                state->navigation.stack[state->navigation.depth++]=57;
                state->navigation.current=50;
                state->navigation.stack[state->navigation.depth++]=50;
                state->navigation.current=56;
            } else {
                state->navigation.current=34;
                state->navigation.stack[state->navigation.depth++]=34;
                state->navigation.current=50;
                state->navigation.stack[state->navigation.depth++]=50;
                state->navigation.current=56;
            }
        } else {
            state->dispatch.signature=0x9001;
            state->dispatch.value=0x1234;
            state->navigation.current=34;
            state->navigation.stack[state->navigation.depth++]=34;
            state->navigation.current=33;
            state->navigation.stack[state->navigation.depth++]=33;
            state->navigation.current=55;
            state->navigation.stack[state->navigation.depth++]=55;
            state->navigation.current=43;
            state->navigation.stack[state->navigation.depth++]=43;
            state->navigation.current=40;
            state->navigation.stack[state->navigation.depth++]=40;
            state->navigation.current=57;
            state->navigation.stack[state->navigation.depth++]=57;
            state->navigation.current=59;
            state->navigation.stack[state->navigation.depth++]=59;
            state->navigation.current=50;
            state->navigation.stack[state->navigation.depth++]=50;
            state->navigation.current=56;
        }
    }
}
