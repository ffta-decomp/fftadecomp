typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {u16 value,opaque[5];} Curve;
typedef struct {u16 phase,pad;void **output;u8 rest[12];u16 mode;} Event;
typedef struct {u8 mode,pad[3];void **output;void *objects[4];Curve firstCurve,secondCurve;void *aux;} Work;
extern const void * const ObjectResources[] __asm__("0x0839A3C0");
extern void *CreateObject(const void *,u32,s32,s32,u32,u32,u32,u32) __asm__("0x080D5CC0");
extern void SetObjectFlag(void *,u32) __asm__("0x080111A8");
extern void SetObjectDepth(void *,s32) __asm__("0x0801121C");
extern void SetOutputVisible(void *,u32) __asm__("0x0801115C");
extern void InitCurve(Curve *,s32,s32,u32) __asm__("0x080E0608");
extern u32 UpdateOrbit(Work *) __asm__("0x080F0AC0");
extern void *CreateAux(const void *,u32,u32,u32,void *) __asm__("0x080DFD8C");
extern void CloseObjects(void **,u32) __asm__("0x080D5F74");
u32 RemainingBand43_000F0BFC(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 0:
  work->mode=event->mode;
  work->output=event->output;
  break;
 case 256: {
  u8 i;
  for(i=0;i<4;i++) {
   work->objects[i]=CreateObject(ObjectResources[work->mode],0,0,0,640,6,0,0);
   SetObjectFlag(work->objects[i],1);
   SetObjectDepth(work->objects[i],-1);
  }
  *work->output=CreateObject(ObjectResources[work->mode],0,120,56,640,6,0,0);
  SetObjectDepth(*work->output,-1);
  SetOutputVisible(*work->output,0);
  InitCurve(&work->firstCurve,60,0,40);
  InitCurve(&work->secondCurve,224,384,40);
  UpdateOrbit(work);
  work->aux=CreateAux((const void *)0x0839A4D4,1,4,0,parent);
  ++event->phase;
  break;
 }
 case 257:
  if((u8)UpdateOrbit(work)) ++event->phase;
  break;
 case 258:
  SetOutputVisible(*work->output,1);
  CloseObjects(work->objects,4);
  event->phase=2;
  break;
 }
 return 0;
}
