typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u8 *PairContext;
extern u16 InputState[];
struct WorkRam { u8 prefix[0x3c34]; u16 pairs[0]; };
extern struct WorkRam WorkRam;
extern u8 EligibilityRecords[];
extern u8 PaletteWork[];
extern u8 ResourceBankA[];
extern u8 ResourceBankB[];
extern u32 CopyRoutineCell;
extern void Call_0802E160(void);
extern void Call_0802F4F4(void);
extern u32 Call_0802E3E0(void);
extern u32 Call_0802E520(void);
extern void Call_0802A2C0(u32,u32,u32,u32);
extern void Call_0802E070(void);
extern void Call_080A9478(u32);
extern void Call_08141540(u32);
extern void Call_08141570(u32,u32);
extern void Call_080023D0(void *);
extern void Call_0802F35C(u32);
extern u8 *Call_080CBA84(u32);
extern void Call_08142250(void *,const void *,u32,u32);
extern void Call_08019A8C(void *,u32,void *,void *);
extern void Call_08013404(u32,u32);
extern void Call_08017FE8(void *);
extern u32 Call_08011860(void);
__asm__(".global PairContext\n.set PairContext,0x200f444\n.global InputState\n.set InputState,0x3000000\n.global WorkRam\n.set WorkRam,0x2000000\n.global EligibilityRecords\n.set EligibilityRecords,0x8528f34\n.global PaletteWork\n.set PaletteWork,0x30039c8\n.global ResourceBankA\n.set ResourceBankA,0x30008b0\n.global ResourceBankB\n.set ResourceBankB,0x3000990\n.global CopyRoutineCell\n.set CopyRoutineCell,0x836d4bc\n.global Call_0802E160\n.thumb_set Call_0802E160,0x802e161\n.global Call_0802F4F4\n.thumb_set Call_0802F4F4,0x802f4f5\n.global Call_0802E3E0\n.thumb_set Call_0802E3E0,0x802e3e1\n.global Call_0802E520\n.thumb_set Call_0802E520,0x802e521\n.global Call_0802A2C0\n.thumb_set Call_0802A2C0,0x802a2c1\n.global Call_0802E070\n.thumb_set Call_0802E070,0x802e071\n.global Call_080A9478\n.thumb_set Call_080A9478,0x80a9479\n.global Call_08141540\n.thumb_set Call_08141540,0x8141541\n.global Call_08141570\n.thumb_set Call_08141570,0x8141571\n.global Call_080023D0\n.thumb_set Call_080023D0,0x80023d1\n.global Call_0802F35C\n.thumb_set Call_0802F35C,0x802f35d\n.global Call_080CBA84\n.thumb_set Call_080CBA84,0x80cba85\n.global Call_08142250\n.thumb_set Call_08142250,0x8142251\n.global Call_08019A8C\n.thumb_set Call_08019A8C,0x8019a8d\n.global Call_08013404\n.thumb_set Call_08013404,0x8013405\n.global Call_08017FE8\n.thumb_set Call_08017FE8,0x8017fe9\n.global Call_08011860\n.thumb_set Call_08011860,0x8011861\n");
u32 Source52_0002FC74(void)
{
 register u8 *context __asm__("r2")=PairContext;
 if(!context) return 1;
 switch(context[4]) {
 case 0:
   Call_0802E160();
   context=PairContext;
   Call_0802A2C0(context[0],context[2],26,(u8)(context[8]*2+3));
   PairContext[4]=3;
   break;
 case 1:
   Call_0802F4F4();
   PairContext=0;
   return 1;
 case 3:
   if((u8)Call_0802E3E0()) PairContext[4]=10;
   break;
 case 4:
   if((u8)Call_0802E520()) {
     Call_0802A2C0(0,0,0,0);
     PairContext[4]=1;
   }
   break;
 case 10: {
   u32 pressed=InputState[1];
   register u32 repeated __asm__("r5")=InputState[2];
   __asm__("" : "+r"(repeated));
   if(pressed&3) {
     if(pressed&1) Call_08141540(100);
     else Call_08141570(1,105);
     Call_0802E070();
     PairContext[4]=4;
     break;
   }
   if(pressed&4) {
     register u32 pair __asm__("r0");
     u8 *record;
     register struct WorkRam *pair_base __asm__("r1")=&WorkRam;
     __asm__("" : "+r"(pair_base) : : "memory");
     context=PairContext;
     pair=(int)*(s16 *)(context+12)*2;
     pair_base=(struct WorkRam *)((u8 *)pair_base+0x3c34);
     __asm__("" : "+r"(pair), "+r"(pair_base));
     pair+=(u32)pair_base;
     __asm__("" : "+r"(pair));
     pair=*(u16 *)pair;
     if(pair==0) goto invalid_pair;
     record=EligibilityRecords+pair*16;
     if(context[15]==0 || record[1]!=0) goto accept_pair;
invalid_pair:
     Call_08141570(1,107);
     goto movement;
accept_pair:
     Call_080A9478(2);
     PairContext[4]=17;
     Call_08017FE8(PairContext+0x1248);
     break;
   }
movement:

   if(repeated&48) {
     register u32 position __asm__("r0");
     register u16 *field __asm__("r1");
     u8 *toggle_context;
     PairContext[15]^=1;
     toggle_context=PairContext;
     if(toggle_context[15]==0) {
       position=(*(u16 *)toggle_context-1)*8+2;
       field=(u16 *)(toggle_context+0x124c);
       __asm__("" : "+r"(position), "+r"(field));
     } else {
       position=(*(u16 *)toggle_context+11)*8+6;
       field=(u16 *)(toggle_context+0x124c);
       __asm__("" : "+r"(position), "+r"(field));
     }
     *field=position;
     Call_08141540(109);
   }
   if(PairContext[8]>1) {
     if(repeated&128) {
       Call_080023D0(InputState);
       Call_08141540(109);
       context=PairContext;
       if(*(s16 *)(context+12)<context[8]-1) *(u16 *)(context+12)+=1;
       else *(u16 *)(context+12)=0;
     } else {
      repeated &= 64;
      __asm__("" : "+r"(repeated));
      if(repeated) {
       register u32 selected __asm__("r2");
       register u32 new_selected __asm__("r0");
       register u8 *down_context __asm__("r1");
       Call_080023D0(InputState);
       Call_08141540(109);
       down_context=PairContext;
       selected=*(u16 *)(down_context+12);
       if(*(s16 *)(down_context+12)>0) new_selected=selected-1;
       else new_selected=down_context[8]-1;
       *(u16 *)(down_context+12)=new_selected;
      }
     }
   }
   Call_0802F35C(1);
   break;
 }
 case 17: {
   u32 record;
   register u32 entry __asm__("r1");
   register u32 base_value __asm__("r3");
   register u32 sum __asm__("r0");
   register struct WorkRam *pair_base __asm__("r0")=&WorkRam;
   __asm__("" : "+r"(pair_base) : : "memory");
   context=PairContext;
   entry=(int)*(s16 *)(context+12)*2;
   pair_base=(struct WorkRam *)((u8 *)pair_base+0x3c34);
   __asm__("" : "+r"(entry), "+r"(pair_base));
   entry+=(u32)pair_base;
   base_value=1208;
   __asm__("" : "+r"(entry), "+r"(pair_base), "+r"(base_value));
   sum=base_value;
   __asm__("" : "+r"(sum), "+r"(entry));
   entry=*(u16 *)entry;
   sum+=entry;
   record=(u16)sum;
   if(context[15]!=0) record=(u16)(record+262);
   Call_08019A8C(context+0x844,record,ResourceBankA,ResourceBankB);
   Call_08013404(0x0802f255,0x0802f269);
   PairContext[4]=18;
   Call_08017FE8(PairContext+0x1248);
   break;
 }
 case 18: {
   u8 **cell=&PairContext;
   context=*cell;
   if(*(s16 *)(context+0x124e)+*(s16 *)(context+0x1252)>63)
     Call_08017FE8(context+0x1248);
   if((u16)Call_08011860()) {
     Call_080A9478(0);
     (*cell)[4]=10;
   }
   break;
 }
 }
 return 0;
}
