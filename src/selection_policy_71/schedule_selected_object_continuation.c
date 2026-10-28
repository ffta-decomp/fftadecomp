/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct TransactionRecord {u8 unknown00[4];void *selected;};
union ControllerState {
 struct {u16 current;u16 depth;u16 stack[1];} navigation;
 struct {u8 unknown00[78];u16 message;u8 unknown50;u8 pending;u8 unknown52[10];void *selected;u8 unknown60[4];u16 signature;u16 value;} dispatch;
};
extern struct TransactionRecord transaction;
extern union ControllerState *controller;
asm(".global transaction\n.set transaction,0x020020d0\n.global controller\n.set controller,0x0200f450");
typedef char ControllerLayout[sizeof(union ControllerState)==104?1:-1];

void ScheduleSelectedObjectContinuation(void)
{
    union ControllerState *state;
    {
        union ControllerState *selection_state=controller;
        selection_state->dispatch.selected=transaction.selected;
        selection_state->dispatch.pending=16;
    }
    state=controller;
    state->dispatch.message=197;
    state->dispatch.signature=0x9001;
    state->dispatch.value=0x1234;
    state->navigation.current=37;
    state->navigation.stack[state->navigation.depth++]=37;
    state->navigation.current=60;
    state->navigation.stack[state->navigation.depth++]=60;
    state->navigation.current=57;
    state->navigation.stack[state->navigation.depth++]=57;
    state->navigation.current=39;
    state->navigation.stack[state->navigation.depth++]=39;
    state->navigation.current=52;
    state->navigation.stack[state->navigation.depth++]=52;
    state->navigation.current=51;
    state->navigation.stack[state->navigation.depth++]=51;
    state->navigation.current=33;
    state->navigation.stack[state->navigation.depth++]=33;
    state->navigation.current=44;
    state->navigation.stack[state->navigation.depth++]=44;
    state->navigation.current=40;
    state->navigation.stack[state->navigation.depth++]=40;
    state->navigation.current=57;
}
