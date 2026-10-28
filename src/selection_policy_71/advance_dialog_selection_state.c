/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Root {u8 gap[16];void *selected;};
struct State {struct Root *root;u16 flags;u16 current;u8 index;u8 continuation;u16 choice;u8 opaque[32];void *frame;void *dialog;};
struct Event {u16 state;u8 gap[18];u16 argument;};
struct View {void *selected;u8 gap[12];u8 mode;u8 kind;};
extern struct Root *gRoot;
extern struct View gView;
extern void * AllocateTaskBytes(u32);
extern void FreeTaskBytes(void *);
extern u32 PollDialog(void);
extern int ReadDialogResult(void);
extern void SetDialogFrame(void *);
extern void OpenDialog(void *,u8);
extern u8 ProcessInput(struct State *);
extern void AdvanceContinuation(struct State *);
extern void PrepareState(struct State *);

asm(".global gRoot\n.set gRoot,0x0200f454\n.global gView\n.set gView,0x020020d0\n.global AllocateTaskBytes\n.thumb_set AllocateTaskBytes,0x8005b29\n.global FreeTaskBytes\n.thumb_set FreeTaskBytes,0x8005b41\n.global PollDialog\n.thumb_set PollDialog,0x8011861\n.global ReadDialogResult\n.thumb_set ReadDialogResult,0x8013381\n.global SetDialogFrame\n.thumb_set SetDialogFrame,0x8013391\n.global OpenDialog\n.thumb_set OpenDialog,0x8061565\n.global ProcessInput\n.thumb_set ProcessInput,0x8066ad1\n.global AdvanceContinuation\n.thumb_set AdvanceContinuation,0x8066bc5\n.global PrepareState\n.thumb_set PrepareState,0x80688d1\n");
int AdvanceDialogSelectionState(void *unused,struct Event *event,struct State *state)
{
    u8 result;
    u16 event_state = event->state;
    u16 active_state = 260;
    switch (event_state) {
    case 1:
        if (state->frame) {
            FreeTaskBytes(state->frame);
            state->frame = 0;
        }
        if (state->dialog) {
            FreeTaskBytes(state->dialog);
            state->dialog = 0;
        }
        break;
    case 0:
        state->index = event->argument;
        state->root = gRoot;
        gView.selected = state->root->selected;
        gView.mode = 0;
        gView.kind = 3;
        break;
    case 256:
        state->frame = AllocateTaskBytes(0x794);
        PrepareState(state);
        goto active;
    case 260:
        if ((u16)PollDialog()) {
            if (state->flags & 64) {
                state->continuation = 0;
                event->state = 259;
            } else {
                goto resume;
            }
        }
        break;
    case 262:
        if (state->flags & 128) {
            state->flags &= 0xff7f;
            event->state = 3;
        }
        break;
    case 261:
        if (ProcessInput(state)) {
            if (state->flags & 256) {
                state->flags &= 0xfeff;
                event->state = 265;
            } else goto active;
        }
        break;
    case 259:
        FreeTaskBytes(state->frame);
        state->frame = 0;
        state->current = state->choice;
        event->state = 262;
        break;
    case 265:
        state->dialog = AllocateTaskBytes(0xa04);
        OpenDialog(state->dialog,2);
        event->state = 266;
        break;
    case 266:
        if ((u16)PollDialog()) {
            result = ReadDialogResult();
            SetDialogFrame(state->frame);
            FreeTaskBytes(state->dialog);
            state->dialog = 0;
            if ((s8)result < 0) {
resume:
                state->continuation = 1;
                event->state = 261;
            } else {
                if ((s8)result > 0) {
                    state->choice = 0xffff;
                    state->flags = 64;
                } else {
                    state->choice = 0xfffe;
                    state->flags |= 64;
                }
active:
                event->state = active_state;
            }
        }
        break;
    }
    AdvanceContinuation(state);
    return 0;
}
