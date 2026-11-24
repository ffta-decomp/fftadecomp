typedef unsigned char u8;
typedef unsigned int u32;
struct MenuSelectionContinuation {u8 *state;u32 next_state;u32 selection;};
struct MenuSelectionContext {u8 unknown0[0x1d44];u8 selection;};
extern struct MenuSelectionContext *gMenuSelectionContext;
extern void PlayMenuSound(u32);
void CommitMenuSelection(struct MenuSelectionContinuation *request)
{
 PlayMenuSound(105);
 *request->state=request->next_state;
 gMenuSelectionContext->selection=request->selection;
}
__asm__(".global CoreClosure31_00051084\n.thumb_set CoreClosure31_00051084, CommitMenuSelection\n.global PlayMenuSound\n.thumb_set PlayMenuSound,0x08141541\n.global gMenuSelectionContext\n.set gMenuSelectionContext,0x0200f428\n");
