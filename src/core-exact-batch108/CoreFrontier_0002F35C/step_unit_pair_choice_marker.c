typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u8 *PairContext;
extern u8 IndicatorAsset[];
extern void Call_08017FE8(void *);
extern void Call_08001CF0(const void *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
__asm__(".global PairContext\n.set PairContext,0x0200F444\n.global IndicatorAsset\n.set IndicatorAsset,0x0839177A\n.global Call_08017FE8\n.thumb_set Call_08017FE8,0x08017FE9\n.global Call_08001CF0\n.thumb_set Call_08001CF0,0x08001CF1");
void CoreFrontier_0002F35C(u32 advance)
{
 u8 *context;
 if((u8)advance) {
   u32 next;
   register u32 zero __asm__("r3");
   context=PairContext;
   next=*(u16 *)(context+4694)+1;
   zero=0;
   __asm__("" : "+r"(next), "+r"(zero));
   *(u16 *)(context+4694)=next;
   if((s16)next>5) {
     *(u16 *)(context+4694)=zero;
     next=*(u16 *)(context+4688)+1;
     *(u16 *)(context+4688)=next;
     if((s16)next>2) *(u16 *)(context+4688)=zero;
   }
   {
     register u8 *row_context __asm__("r1")=PairContext;
     register u32 position __asm__("r0")=*(s16 *)(row_context+12)*16;
     __asm__("" : "+r"(row_context), "+r"(position));
     *(u16 *)(row_context+4690)=position;
   }
 }
 Call_08017FE8(PairContext+4680);
 {
   register u8 *indicator_context __asm__("r2")=PairContext;
   register u32 flag_offset __asm__("r1")=1127;
   register u8 *flag_field __asm__("r0");
   __asm__("" : "+r"(indicator_context), "+r"(flag_offset));
   flag_field=indicator_context+flag_offset;
   __asm__("" : "+r"(flag_field), "+r"(indicator_context));
   if(*flag_field)
     Call_08001CF0(IndicatorAsset,(*(u16 *)indicator_context+1)*8,*(u16 *)(indicator_context+2)*8-4,0,0,0,0,0,0,0,0);
 }
}
