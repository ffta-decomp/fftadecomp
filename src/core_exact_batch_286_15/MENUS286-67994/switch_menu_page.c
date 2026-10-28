typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;
#define H(p,n) (*(u16 *)((p)+(n)))
extern void sound(unsigned);
unsigned RemainingCore48_00067994(u8 *panel,u16 keys){u8 *list=panel+80;u8 *cursor=panel+112;if(keys&16){u8 *save=*(u8 **)panel+0xA24+4*(s8)panel[11];H(save,0)=H(list,26);H(save,2)=cursor[17];sound(101);{register unsigned state __asm__("r0")=0xFFFB;__asm__("" : "+r"(state));H(panel,6)=state;}if((s8)panel[11]<panel[12]-1)panel[11]++;else panel[11]=0;return 1;}else if(keys&32){u8 *save=*(u8 **)panel+0xA24+4*(s8)panel[11];H(save,0)=H(list,26);H(save,2)=cursor[17];sound(101);{register unsigned state __asm__("r0")=0xFFFB;__asm__("" : "+r"(state));H(panel,6)=state;}if((s8)panel[11]>0)panel[11]--;else panel[11]=panel[12]-1;return 1;}return 0;}
__asm__(".thumb_set sound,0x08141541");
