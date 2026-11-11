typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 value,pad[5];} Curve;
typedef struct {u32 unused;u16 counter;s8 side;u8 ordinal;void *first,*second;Curve x,y;} Work;
typedef struct {u16 phase;u8 pad[18];u16 ordinal,side;} Event;
typedef struct {s16 x,y;} Pair;
extern const u8 Delays[] __asm__("0x0839F75C");
extern const Pair Starts[] __asm__("0x0839F764");
extern const Pair Ends[] __asm__("0x0839F78C");
extern const u8 Values[] __asm__("0x0839F7B4");
extern void InitCurve(Curve *,s32,s32,u32) __asm__("0x080E0608");
extern void TickCurve(Curve *) __asm__("0x080E064C");
extern u32 CurveDone(Curve *) __asm__("0x080E0690");
extern void *Create(const void *,u32,s32,s32,u32,u32,u32,u32) __asm__("0x080D5CC0");
extern void SetFlag(void *,u32) __asm__("0x08011118");
extern void SetDepth(void *,s32) __asm__("0x0801121C");
extern void SetValue(void *,u32) __asm__("0x08011058");
extern void SetPosition(void *,s32,s32,u32) __asm__("0x080107D4");
extern void Release(void **,u32) __asm__("0x080D5F74");
u32 RemainingBand43_0010493C(void *ignored,Event *event,Work *work)
{
 switch(event->phase) {
 case 0:
  work->ordinal=event->ordinal;work->side=event->side;
  work->counter=Delays[work->ordinal]+1;break;
 case 256: {
  u32 remaining=(u16)--work->counter;
  if(remaining)break;
  InitCurve(&work->x,Starts[work->side*5+work->ordinal].x,Ends[work->side*5+work->ordinal].x,90);
  InitCurve(&work->y,Starts[work->side*5+work->ordinal].y,Ends[work->side*5+work->ordinal].y,90);
  work->first=Create((void *)0x08506E80,0,(s16)work->x.value,(s16)work->y.value,928,6,remaining,remaining);
  work->second=Create((void *)0x08506E80,1,(s16)work->x.value,(s16)work->y.value,928,6,remaining,remaining);
  if(work->side){SetFlag(work->first,1);SetFlag(work->second,1);}
  SetDepth(work->first,-1);SetDepth(work->second,-1);
  SetValue(work->first,Values[work->ordinal]);SetValue(work->second,Values[work->ordinal]);
  ++event->phase;break;
 }
 case 257:
  TickCurve(&work->x);TickCurve(&work->y);
  SetPosition(work->first,(s16)work->x.value,(s16)work->y.value,0);
  SetPosition(work->second,(s16)work->x.value,(s16)work->y.value,0);
  if((u8)CurveDone(&work->x)){Release(&work->first,2);++event->phase;}
  break;
 case 258:event->phase=2;break;
 }
 return 0;
}
