typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct Event { u32 w0; void *record; void *w8; void *w12; u32 w16; u16 h20,h22;u32 w24; } Event;
typedef struct Work { s16 x,y;u16 outx,outy;u8 mode,signal;u16 pad;void *palette;void *cell;void *child1,*child2,*child3,*child4,*child5,*child6,*child7;void *initial,*record,*last,*fade; } Work;
extern u32 GetDisplayShadowHighBitMask(u32) __asm__("0x080035a8");
extern void *Remaining38_00005B6C(u32,u32,Event *,void *) __asm__("0x08005b6c");
extern void *CoreGlobal36_0000A654(u32) __asm__("0x0800a654");
extern void ReleaseCurrentSceneResource(void *) __asm__("0x0800a668");
extern void CoreGlobal36_0001B878(void) __asm__("0x0801b878");
extern void CoreGlobal36_0001E2A4(void) __asm__("0x0801e2a4");
extern void BattleDependency_0001E5E0(int,int) __asm__("0x0801e5e0");
extern void CoreGlobal36_0001E610(u8 *,u8 *) __asm__("0x0801e610");
extern void BattleDependency_0001E6F0(s16 *,s16 *) __asm__("0x0801e6f0");
extern void RemainingBand43_000D38B4(void) __asm__("0x080d38b4");
extern const void *RemainingBand43_000D3904(void) __asm__("0x080d3904");
extern void *RemainingBand43_000DFD68(u32,u32,void *) __asm__("0x080dfd68");
extern void *RemainingBand43_000DFED8(void *) __asm__("0x080dfed8");
extern void *CreateDefinitionEffectTask(void *,const void *,u32,u32,void *,void *) __asm__("0x080e03f8");
extern void *PollAndReleaseDefinitionChild(void *) __asm__("0x080e051c");
extern void *RemainingBand43_000E05DC(void *) __asm__("0x080e05dc");
extern void RemainingBand43_00115ACC(void *) __asm__("0x08115acc");
extern void *RemainingBand43_00115AE4(void *,u32,void *) __asm__("0x08115ae4");
extern void *RemainingBand43_00115B40(void *) __asm__("0x08115b40");
extern void BiosCpuSet(const void *,void *,u32) __asm__("0x0814186c");
u32 AdvanceAuthoredTargetSequence(void *parent,Event *event_input,Work *work)
{
 Event *event=event_input;
 Event a,b,c,d,e,f,g;
 u8 outa,outb;
 u16 *pair[2];
 u32 next;
 __asm__("" : "+r"(event));
 switch (*(u16 *)event) {
 case 0: {
  u16 mode=event->h22;
  void *record;
  u32 index;
  work->mode=mode;
  record=event->record;
  work->record=record;
  index=11;
  if ((u8)mode!=0) index=0;
  work->initial=CreateDefinitionEffectTask(record,(const void *)0x083a31e0,index,7,0,parent);
  BattleDependency_0001E6F0(&work->x,&work->y);
  break;
 }
 case 1:
  RemainingBand43_000D38B4();break;
 case 256:
  if (work->mode!=0) {
   work->initial=RemainingBand43_000E05DC(work->initial);
   if (work->initial!=0) break;
   next=265;__asm__ volatile("" : "+r"(next));goto set_phase;
  }
  work->initial=RemainingBand43_000E05DC(work->initial);
  if (work->initial!=0) break;
  work->fade=RemainingBand43_000DFD68(1,30,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 case 257:
  work->fade=RemainingBand43_000DFED8(work->fade);
  if (work->fade!=0) break;
  a.record=&work->signal;
  a.w8=&work->cell;
  pair[0]=&work->outx;pair[1]=&work->outy;
  a.w12=pair;
  work->child1=Remaining38_00005B6C(0x081112a1,44,&a,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 case 258:
  if (work->signal==0) break;
  b.record=&work->cell;
  work->child2=Remaining38_00005B6C(0x0811166d,1024,&b,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 case 259:
  work->child1=PollAndReleaseDefinitionChild(work->child1);
  if (work->child1!=0) break;
  work->child2=PollAndReleaseDefinitionChild(work->child2);
  if (work->child2!=0) break;
  c.record=&work->cell;
  work->child3=Remaining38_00005B6C(0x08111a5d,816,&c,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 case 260:
  work->child3=PollAndReleaseDefinitionChild(work->child3);
  if (work->child3!=0) break;
  d.record=&work->cell;
  work->child4=Remaining38_00005B6C(0x081120cd,80,&d,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 case 261: {
  void *palette;
  work->child4=PollAndReleaseDefinitionChild(work->child4);
  if (work->child4!=0) break;
  palette=CoreGlobal36_0000A654(192);
  work->palette=palette;
  BiosCpuSet((const void *)0x03003862,palette,95);
  BiosCpuSet(RemainingBand43_000D3904(),(void *)0x03003862,95);
  work->child5=Remaining38_00005B6C(0x08112361,48,&e,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 }
 case 262:
  work->child5=PollAndReleaseDefinitionChild(work->child5);
  if (work->child5!=0) break;
  f.h20=work->outx;f.h22=work->outy;
  work->child6=Remaining38_00005B6C(0x08112595,44,&f,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 case 263:
  work->child6=PollAndReleaseDefinitionChild(work->child6);
  if (work->child6!=0) break;
  g.record=&work->signal;
  work->child7=Remaining38_00005B6C(0x08112a61,20,&g,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 case 264: {
  u32 mask;
  register u32 control __asm__("r1");
  volatile u16 *shadow;
  if (work->signal==0) break;
  CoreGlobal36_0001E2A4();
  CoreGlobal36_0001E610(&outa,&outb);
  mask=GetDisplayShadowHighBitMask(outa);
  shadow=(volatile u16 *)0x03000940;
  control=*shadow;
  __asm__("" : "+r"(control));
  control|=mask;
  *shadow=(u16)control;
  mask=GetDisplayShadowHighBitMask(outb);
  control=*shadow;
  __asm__("" : "+r"(control));
  control|=mask;
  *shadow=(u16)control;
  BattleDependency_0001E5E0(work->x,work->y);
  CoreGlobal36_0001B878();
  RemainingBand43_00115ACC(work->record);
  work->fade=RemainingBand43_000DFD68(0,30,parent);
  BiosCpuSet(work->palette,(void *)0x03003862,95);
  ReleaseCurrentSceneResource(work->palette);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 }
 case 265:
  work->fade=RemainingBand43_000DFED8(work->fade);
  if (work->fade!=0) break;
  work->child7=PollAndReleaseDefinitionChild(work->child7);
  if (work->child7!=0) break;
  work->last=RemainingBand43_00115AE4(work->record,2,parent);
  next=*(u16 *)event+1;__asm__ volatile("" : "+r"(next));goto set_phase;
 case 266:
  work->last=RemainingBand43_00115B40(work->last);
  if (work->last!=0) break;
  next=2;__asm__ volatile("" : "+r"(next));goto set_phase;
 }
 return 0;
set_phase:
 *(u16 *)event=next;
 return 0;
}
