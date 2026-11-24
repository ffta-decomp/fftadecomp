typedef unsigned char u8;typedef unsigned short u16;typedef short s16;
#define H(p,n) (*(u16 *)((p)+(n)))
extern u8 state[];
extern void update(void*);
void RemainingCore48_00066BC4(u8 *p){if(p[9] && state[18]!=3){unsigned value=H(p,26)+1;unsigned zero=0;H(p,26)=value;if((s16)value>5){H(p,26)=zero;value=H(p,20)+1;H(p,20)=value;if((s16)value>2)H(p,20)=zero;value=H(p,36)-1;H(p,36)=value;if((s16)value<=-3)H(p,36)=zero;}update(p+12);update(p+28);}}
__asm__(".set state,0x020020D0\n.thumb_set update,0x08017fe9");
