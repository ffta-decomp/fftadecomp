/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Selection {u16 state,depth;u16 stack[32];void *window;u8 gap[8];u8 mode,pending;u8 gap82[2];u32 flags;int choice,result;u8 gap96[4];u16 signature_a,signature_b;};
extern struct Selection *gSelection;
extern s16 GetEventRuntimePayloadField06(void *);
extern void ResetSelectionWindow(void *);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global GetEventRuntimePayloadField06\n.thumb_set GetEventRuntimePayloadField06,0x8065051\n.global ResetSelectionWindow\n.thumb_set ResetSelectionWindow,0x8066029");
void AdvanceSelectionRuntimeEvent(void)
{
    int result = GetEventRuntimePayloadField06(gSelection->window);
    if (result) {
        struct Selection *selection = gSelection;
        selection->result = result;
        selection->choice = result;
        selection->flags |= 2;
        selection->pending = 16;
        gSelection->mode = 3;
        { struct Selection *signature = gSelection;
        signature->signature_a = 0x9001;
        signature->signature_b = 0x1234;
        ResetSelectionWindow(signature->window);
        }
        { struct Selection *checked = gSelection;
        if ((checked->flags & 4) && result != -1) {
            checked->state = 22;
        } else {
            struct Selection *queued = gSelection;
            queued->state = 22;
            queued->stack[queued->depth++] = 22;
            queued->state = 21;
            queued->stack[queued->depth++] = 21;
            queued->state = 55;
            queued->stack[queued->depth++] = 55;
            queued->state = 43;
            queued->stack[queued->depth++] = 43;
            queued->state = 40;
            queued->stack[queued->depth++] = 40;
            queued->state = 57;
            queued->stack[queued->depth++] = 57;
            queued->state = 59;
        }
        }
        { struct Selection *continuation = gSelection;
        continuation->stack[continuation->depth++] = continuation->state;
        continuation->state = 50;
        continuation->stack[continuation->depth++] = 50;
        continuation->state = 56;
        }
    }
}
