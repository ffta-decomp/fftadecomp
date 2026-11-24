typedef unsigned char u8;
extern u8 *gMenuCommitContext;
extern void PlayMenuCommit(unsigned);
__asm__(".global gMenuCommitContext\n.set gMenuCommitContext,0x0200f428\n.global PlayMenuCommit\n.thumb_set PlayMenuCommit,0x08141541");
void CommitMenuInput(u8 *state) {PlayMenuCommit(100); *state=200; gMenuCommitContext[0x1d44]=254;}
