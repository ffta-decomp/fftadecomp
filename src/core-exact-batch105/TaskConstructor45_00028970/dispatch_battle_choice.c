typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u16 InputState[];
extern u8 *ContextCell;
extern u8 *ChoiceTables[];
extern u32 Call_08017B68(u8 *,int);
extern u32 Call_08028824(u8 *,int);
extern u32 Call_080287F0(u8 *);
extern u32 Call_080287C4(u8 *);
extern void Call_08016D64(u8 *);
extern void Call_08017D18(u8 *,u32);
extern u32 Call_08028708(u8 *,u32);
extern u32 Call_08028584(u8 *,u32,u32);
extern void Call_08141540(u32);
extern void Call_08141570(u32,u32);
__asm__(".global InputState\n.set InputState,0x03000000\n.global ContextCell\n.set ContextCell,0x0200F438\n.global ChoiceTables\n.set ChoiceTables,0x0851BA84\n.global Call_08017B68\n.thumb_set Call_08017B68,0x8017b69\n.global Call_08028824\n.thumb_set Call_08028824,0x8028825\n.global Call_080287F0\n.thumb_set Call_080287F0,0x80287f1\n.global Call_080287C4\n.thumb_set Call_080287C4,0x80287c5\n.global Call_08016D64\n.thumb_set Call_08016D64,0x8016d65\n.global Call_08017D18\n.thumb_set Call_08017D18,0x8017d19\n.global Call_08028708\n.thumb_set Call_08028708,0x8028709\n.global Call_08028584\n.thumb_set Call_08028584,0x8028585\n.global Call_08141540\n.thumb_set Call_08141540,0x8141541\n.global Call_08141570\n.thumb_set Call_08141570,0x8141571");
u32 TaskConstructor45_00028970(u8 *input_request)
{
 register u8 *request __asm__("r4")=input_request;
 u8 *widget=request+12;
 u8 *row_control=request+88;
 register u32 pressed __asm__("r5")=InputState[1];
 u32 repeated=InputState[2];
 u32 held=InputState[0];
 __asm__("" : "+r"(request), "+r"(pressed));
 if(pressed&4) {
   u32 index=Call_08017B68(request+56,*(s8 *)(row_control+17));
   u32 value=Call_08028824(request,(s16)index);
   u8 *context=ContextCell;
   *(u16 *)(context+8)=value;
   if((u16)value) {
     *(u16 *)(context+8)=value-1;
     { register u32 sentinel __asm__("r0")=0xfffe;
       __asm__("" : "+r"(sentinel));
       *(u16 *)context=sentinel; }
     return 1;
   }
 }
 if(pressed&2) {
   if((u8)Call_080287F0(request)) goto reject;
   Call_08141570(1,105);
   Call_08016D64(widget);
   Call_08017D18(row_control,0);
   {
     u8 *context=ContextCell;
     register u32 sentinel __asm__("r0")=0xffff;
     __asm__("" : "+r"(sentinel));
     *(u16 *)context=sentinel;
   }
   return 1;
 }
 pressed &= 1;
 __asm__("" : "+r"(pressed));
 if(pressed) {
   u32 queried=Call_08017B68(request+56,*(s8 *)(row_control+17));
   u8 *context=ContextCell;
   u16 index;
   register u32 mode __asm__("r5");
   register u32 loaded_mode __asm__("r1");
   { register u8 *initial_context __asm__("r2")=context;
     __asm__("" : "+r"(initial_context));
     *(u16 *)initial_context=queried+1; }
   index=queried;
   if((u8)Call_080287C4(request)) {
reject:
     Call_08141570(1,107);
     return 0;
   }
   {
     register u8 *mode_context __asm__("r3")=ContextCell;
     loaded_mode=mode_context[4];
     __asm__("" : "+r"(mode_context), "+r"(loaded_mode));
     context=mode_context;
     mode=loaded_mode;
   }
   if(mode==5) {
     *(u16 *)(context+16)=index;
     *(u32 *)(context+28)=*(u32 *)(context+24);
   } else if((u8)(loaded_mode-6)<=2 || mode==15) {
     register u8 *table __asm__("r2")=ChoiceTables[request[10]];
     register u32 shifted __asm__("r0")=(u32)index<<16;
     register u32 *entries __asm__("r1");
     u32 id;
     u32 value;
     __asm__("" : "+r"(shifted));
     entries=*(u32 **)(request+148);
     __asm__("" : "+r"(entries), "+r"(shifted), "+r"(request));
     shifted=(int)shifted>>14;
     shifted+=(u32)entries;
     id=*(u32 *)shifted;
     table += id*8;
     __asm__("" : "+r"(table));
     value=*(u16 *)(table+4);
     *(u32 *)(context+20)=value;
     if(mode==15) *(u16 *)(context+16)=value;
   } else if(mode==2) {
     register u32 shifted __asm__("r0")=(u32)index<<16;
     register u32 *entries __asm__("r1");
     u32 value;
     __asm__("" : "+r"(shifted));
     entries=*(u32 **)(request+148);
     __asm__("" : "+r"(entries), "+r"(shifted), "+r"(request));
     shifted=(int)shifted>>14;
     shifted+=(u32)entries;
     value=*(u32 *)shifted;
     *(u32 *)(context+20)=value;
     *(u32 *)(context+24)=value;
   } else {
     register u32 mode_delta __asm__("r0")=loaded_mode;
     __asm__("" : "+r"(mode_delta));
     if((u8)(mode_delta-13)<=1) {
     register u32 shifted __asm__("r0")=(u32)index<<16;
     register u32 *entries __asm__("r1");
     __asm__("" : "+r"(shifted));
     entries=*(u32 **)(request+148);
     __asm__("" : "+r"(entries), "+r"(shifted), "+r"(request));
     shifted=(int)shifted>>14;
     shifted+=(u32)entries;
     *(u16 *)(context+16)=*(u32 *)shifted;
   }
   }
   __asm__("" : "+r"(request));
   Call_08141540(100);
   Call_08016D64(widget);
   Call_08017D18(row_control,0);
   return 1;
 }
 {
   register u32 result __asm__("r0");
   if(ContextCell[5]!=0) {
     result=(u8)Call_08028708(request,repeated);
     __asm__("" : "+r"(result));
   } else {
     result=(u8)Call_08028584(request,repeated,held);
     __asm__("" : "+r"(result));
   }
   return result;
 }
}
