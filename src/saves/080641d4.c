/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Selection {u16 state,depth;u16 stack[38];u8 mode;u8 gap[27];u8 operation_start;};
extern struct Selection *gSelection;
extern u8 PollPersistenceOperation(void *);
extern void RequestSaveGatedPolicyMode(u16);

asm(".global gSelection\n.set gSelection,0x0200f450\n.global PollPersistenceOperation\n.thumb_set PollPersistenceOperation,0x80c73d9\n.global RequestSaveGatedPolicyMode\n.thumb_set RequestSaveGatedPolicyMode,0x80c71b5");
void AdvanceSelectionPersistenceOperation(void)
{
    u8 result = PollPersistenceOperation(&gSelection->operation_start);
    switch (result) {
    case 2: {
        struct Selection *next = gSelection;
        next->state = 68;
        next->stack[next->depth++] = 68;
        next->state = 52;
        next->stack[next->depth++] = 52;
        next->state = 54;
        break;
    }
    case 0: {
        struct Selection *next;
        RequestSaveGatedPolicyMode(gSelection->mode);
        next = gSelection;
        next->state = next->stack[--next->depth];
        break;
    }
    }
}
