typedef unsigned char u8;
struct Root {unsigned words[4];};
extern struct Root root;
asm(".global root\n.set root,0x03002710");
void sub_0804E014(u8 request){u8 *state=(u8 *)root.words[3];if(request==0)*state=7;else *state=0;}
