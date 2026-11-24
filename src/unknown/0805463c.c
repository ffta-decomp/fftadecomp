typedef unsigned char u8;typedef unsigned int u32;
struct KeyContinuation {u8 *state;u32 nextState;u32 returnState;};
extern u8 *gUI asm("RootPtr");extern void PlaySound(u32) asm("PlaySound");
void CoreClosure31_0005463C(struct KeyContinuation *record){
 u8 *root;u32 value;
 *record->state=record->nextState;
 root=gUI;value=record->returnState;
 root[0x2d38]=value;PlaySound(105);
}
asm(".global RootPtr\n.set RootPtr,0x0200f428\n.global PlaySound\n.thumb_set PlaySound,0x08141541\n");
