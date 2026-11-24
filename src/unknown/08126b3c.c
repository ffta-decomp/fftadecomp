typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct {u32 untouched[5];u16 a,b,c,reserved;} Template;
extern void *Create(void*,u16,Template*,void*);extern u8 Callback[];
void Remaining38_00126B3C(u8 a,u8 b,u8 c){Template data;data.a=a;data.b=b;data.c=c;Create(Callback,72,&data,0);}
asm(".global Create\n.thumb_set Create,0x8121b8d\n.global Callback\n.set Callback,0x8126911\n");
