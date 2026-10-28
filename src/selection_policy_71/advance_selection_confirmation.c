/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct TransactionRecord {u32 unknown00;u32 selected;};
struct SaveImage {u8 unknown00[0x1f64];u32 balance;u8 unknown1f68[0x20d0 - 0x1f68];struct TransactionRecord transaction;};
union ControllerState {
 struct {u16 current;u16 depth;u16 stack[1];} navigation;
 struct {u8 unknown00[78];u16 message;u8 mode;u8 pending;u8 unknown52[2];u32 flags;u32 selected88;u32 selected92;u32 unknown60;u16 signature;u16 value;} dispatch;
};
extern struct SaveImage live_save;
extern union ControllerState *controller;
extern u32 PollDisplayCompletion(void);
extern s8 GetConfirmation(void);
extern void ClearConfirmation(void);
typedef char ControllerLayout[sizeof(union ControllerState)==104?1:-1];
typedef char SaveLayout[sizeof(struct SaveImage)==0x20d8?1:-1];
asm(".global live_save\n.set live_save,0x02000000");
asm(".global controller\n.set controller,0x0200f450");
asm(".global PollDisplayCompletion\n.thumb_set PollDisplayCompletion,0x08011861");
asm(".global GetConfirmation\n.thumb_set GetConfirmation,0x08013381");
asm(".global ClearConfirmation\n.thumb_set ClearConfirmation,0x08013365");

void AdvanceSelectionConfirmation(void)
{
    if((u16)PollDisplayCompletion()!=0) {
        s32 confirmation=GetConfirmation();
        if(confirmation<0) {
            union ControllerState *state;
            controller->dispatch.flags&=~1;
            ClearConfirmation();
            state=controller;
            state->navigation.current=23;
            state->navigation.stack[state->navigation.depth++]=23;
            state->navigation.current=52;
            state->navigation.stack[state->navigation.depth++]=52;
            state->navigation.current=66;
        } else if(confirmation>0) {
            union ControllerState *state=controller;
            state->dispatch.flags&=~1;
            state->dispatch.message=187;
            state->navigation.current=28;
            state->navigation.stack[state->navigation.depth++]=28;
            state->navigation.current=52;
            state->navigation.stack[state->navigation.depth++]=52;
            state->navigation.current=53;
            state->navigation.stack[state->navigation.depth++]=53;
            state->navigation.current=66;
        } else if(live_save.balance<=4999) {
            union ControllerState *state=controller;
            state->dispatch.flags&=~1;
            state->dispatch.message=204;
            state->navigation.current=28;
            state->navigation.stack[state->navigation.depth++]=28;
            state->navigation.current=52;
            state->navigation.stack[state->navigation.depth++]=52;
            state->navigation.current=53;
            state->navigation.stack[state->navigation.depth++]=53;
            state->navigation.current=66;
        } else {
            union ControllerState *state;
            {
                union ControllerState *selection_state=controller;
                struct TransactionRecord *selected_transaction=&live_save.transaction;
                u32 selected=selected_transaction->selected;
                selection_state->dispatch.selected88=selected;
                selection_state->dispatch.selected92=selected;
                selection_state->dispatch.pending=16;
            }
            state=controller;
            state->dispatch.signature=0x9001;
            state->dispatch.value=0x1234;
            state->dispatch.message=186;
            state->navigation.current=26;
            state->navigation.stack[state->navigation.depth++]=26;
            state->navigation.current=21;
            state->navigation.stack[state->navigation.depth++]=21;
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
            state->navigation.current=52;
            state->navigation.stack[state->navigation.depth++]=52;
            state->navigation.current=53;
            state->navigation.stack[state->navigation.depth++]=53;
            state->navigation.current=67;
        }
    }
}
