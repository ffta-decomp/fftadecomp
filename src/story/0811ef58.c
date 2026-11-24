typedef unsigned char u8; typedef signed short s16; typedef unsigned short u16; typedef unsigned int u32;
typedef struct { u16 phase; } Event;
typedef struct { u8 opaque[20]; s16 x,y,ordinal; u8 tail[2]; } ChildEvent;
typedef struct { u16 value; u8 rest[10]; } Interp;
typedef struct { u16 flags,tick; u8 reserved4[4],ordinal,ordinal2,delay,pad11; void *ring1[8],*ring2[8]; void *raster,*background,*sequence,*sequence2; Interp x,y; void *prelude; } Work;
typedef struct { u16 control; u8 reserved2[56]; volatile u8 b58,b59; u8 reserved60[2]; volatile u8 b62,b63; u8 reserved64[2]; volatile u8 b66; u8 reserved67; volatile u8 b68; } Shadow;
extern Shadow shadow __asm__("0x03000940");
extern const u16 timeline[] __asm__("0x083A7504");
extern void *BeginPrelude(const void*,int,void*) __asm__("0x080D7A70");
extern void *PollPrelude(void*) __asm__("0x080D7ABC");
extern void Setup(int,int,int,int,int) __asm__("0x080D49FC");
extern void SetupBg(int,int) __asm__("0x0800BD24");
extern void *StartRaster(int,const void*,int,int) __asm__("0x080D4B64");
extern u32 PlaneMask(int) __asm__("0x080035A8");
extern void SetRaster(void*,int) __asm__("0x0800BDA4");
extern void *StartSeq(const void*,void*) __asm__("0x080D4704");
extern void *StartBg(const void*,void*) __asm__("0x080D3E9C");
extern void InterpInit(Interp*,int,int,int) __asm__("0x080E0608");
extern void InterpStep(Interp*) __asm__("0x080E064C");
extern u32 InterpDone(Interp*) __asm__("0x080E0690");
extern u32 PollRing(void**,int) __asm__("0x080E0570");
extern void Scroll(int,int,int) __asm__("0x0800BC08");
extern void *CreateChild(const void*,int,ChildEvent*,void*) __asm__("0x08005B6C");
extern void *PollSeq(void*) __asm__("0x080D4774");
extern void *PollBg(void*) __asm__("0x080D3F08");
extern void StopRaster(void*,int) __asm__("0x080D4D14");
extern void EndScene(void) __asm__("0x080D4020");
extern u32 PlaneDisable(int) __asm__("0x080035D0");
u32 RemainingBand43_0011EF58(void *parent,Event *event,Work *w)
{
 register u32 flags __asm__("r1")=w->flags;
 register u32 pause __asm__("r4");
 register u32 tested __asm__("r0");
 __asm__("" : "+r"(flags));
 pause=0x8000;
 __asm__("" : "+r"(pause));
 tested=pause;
 __asm__("" : "+r"(tested));
 if(tested & flags) return 0;
 switch(event->phase){
 case 1:break;
 case 0:w->prelude=BeginPrelude((void*)0x083A7394,3,parent);break;
 case 256:
  w->prelude=PollPrelude(w->prelude);
  if(!w->prelude){register u32 prior __asm__("r0")=w->flags;register u32 enabled __asm__("r1")=1;__asm__("orr %0, %1\n\torr %0, %2" : "+l"(enabled) : "l"(prior), "l"(pause) : "cc");w->flags=enabled;++event->phase;}break;
 case 257:
  Setup(1,3,0,171,15);SetupBg(1,0);
  w->raster=StartRaster(1,(void*)0x088F3A38,757,6);
  {register u32 mask __asm__("r0")=PlaneMask(3);register u32 current __asm__("r1")=shadow.control;__asm__("orr %0, %1" : "+l"(current) : "l"(mask) : "cc");shadow.control=current;}SetRaster(w->raster,1);
  w->sequence=StartSeq((void*)0x0894CF90,parent);
  w->background=StartBg((void*)0x0894DED0,parent);
  InterpInit(&w->x,171,48,375);InterpInit(&w->y,15,110,375);
  shadow.b59=171;shadow.b58=240;shadow.b63=15;shadow.b62=160;shadow.b66=63;
  shadow.b68=63&~PlaneDisable(3);shadow.control|=0x2000;
  w->delay=8;++event->phase;break;
 case 258:{u8 ord;ChildEvent child;
  PollRing(w->ring1,8);PollRing(w->ring2,8);InterpStep(&w->x);InterpStep(&w->y);
  shadow.b59=(u8)w->x.value;shadow.b63=(u8)w->y.value;
  Scroll(1,(s16)w->x.value,(s16)w->y.value);
  ord=w->ordinal;
  while(ord<=21 && timeline[ord]<=w->tick){
   if(w->tick==timeline[ord]){register u32 slot __asm__("r4");register u32 ordinal __asm__("r2");child.x=w->x.value+32;child.y=w->y.value+24;child.ordinal=ord;
    ordinal=ord;slot=7;__asm__("and %0, %1" : "+l"(slot) : "l"(ordinal) : "cc");w->ring1[slot]=CreateChild((void*)0x0811ED41,44,&child,parent);++w->ordinal;break;}
   ++ord;
  }
  if(!--w->delay){u8 slot;w->delay=8;child.x=w->x.value+40;child.y=w->y.value+24;child.ordinal=w->ordinal2;
   slot=w->ordinal2&7;w->ring2[slot]=CreateChild((void*)0x0811EE49,44,&child,parent);++w->ordinal2;}
  ++w->tick;w->sequence=PollSeq(w->sequence);
  if(!w->sequence){if(w->tick==345)w->sequence2=StartSeq((void*)0x0894CFBC,parent);
   if((u8)InterpDone(&w->x) && (u8)InterpDone(&w->y))++event->phase;}
  break;}
 case 259:
  w->background=PollBg(w->background);
  if(!w->background){if(w->sequence2){w->sequence2=PollSeq(w->sequence2);if(w->sequence2)break;
   StopRaster(w->raster,1);w->raster=0;{register u32 mask __asm__("r0")=PlaneMask(3);register u16 *control __asm__("r2")=&shadow.control;register u32 value __asm__("r1");__asm__("" : "+r"(mask), "+r"(control));value=*control;__asm__("bic %0, %1" : "+l"(value) : "l"(mask) : "cc");{register u32 keep __asm__("r0")=0xdfff;__asm__("and %0, %1" : "+l"(value) : "l"(keep) : "cc");*control=value;}}w->flags|=2;}
   if((u8)PollRing(w->ring1,8) && (u8)PollRing(w->ring2,8)){EndScene();event->phase=2;}}
  break;
 }
 return 0;
}
