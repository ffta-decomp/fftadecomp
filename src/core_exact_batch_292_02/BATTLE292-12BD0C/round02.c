typedef unsigned char u8;typedef unsigned int u32;
typedef struct {u32 event;u8 *owner;u32 untouched[5];} Template;
extern void *Create(void*,unsigned short,Template*,void*);extern u8 Callback[];
void Remaining38_0012BD0C(u8 *owner){Template data;owner[6]=0;data.owner=owner;Create(Callback,8,&data,0);}
asm(".global Create\n.thumb_set Create,0x8121b8d\n.global Callback\n.set Callback,0x812b981\n");
