typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct {u16 phase,unused2;void *record;} SceneEvent;
typedef struct {s16 x,y;u32 unused4;void *blend;void *scripts[3];void *record;void *auxiliary;} SceneWork;
extern void CreateModel(const void *,u32,u32,int,int,u32) __asm__("0x080d7220");
extern void *CreateBlend(const void *,void *) __asm__("0x080d3e9c");
extern void ConfigureBlend(void *,u32,u32) __asm__("0x080d3f84");
extern void *CreateScript(const void *,void *) __asm__("0x080d4704");
extern void *CreateAuxiliary(const void *,u32,u32,u32,void *) __asm__("0x080dfd8c");
extern u32 PollScripts(void **,u32) __asm__("0x080d48dc");
extern void *PollBlend(void *) __asm__("0x080d3f08");
extern u32 LayerControlMask(u32) __asm__("0x080035a8");
u32 RemainingBand43_000F1AEC(void *parent,SceneEvent *event,SceneWork *work)
{
 switch(event->phase) {
 case 0:
  work->record=event->record;
  work->x=120;
  work->y=56;
  break;
 case 256: {
  void *created;
  CreateModel((const void *)0x088f5b78,1,3,work->x,(s16)((u16)work->y-2),0);
  created=CreateBlend((const void *)0x0894d69c,parent);
  work->blend=created;
  ConfigureBlend(created,8,255);
  work->scripts[0]=CreateScript((const void *)0x0894b554,parent);
  work->scripts[1]=CreateScript((const void *)0x0894848c,parent);
  work->scripts[2]=CreateScript((const void *)0x0894b268,parent);
  work->auxiliary=CreateAuxiliary((const void *)0x0839a58c,1,4,0,parent);
  ++event->phase;
  break;
 }
 case 257:
  if((u8)PollScripts(work->scripts,3)!=0) {
   work->blend=PollBlend(work->blend);
   if(work->blend==0) {
    *(u16 *)0x03000940&=~LayerControlMask(3);
    ++event->phase;
   }
  }
  break;
 case 258:
  event->phase=2;
  break;
 }
 return 0;
}
