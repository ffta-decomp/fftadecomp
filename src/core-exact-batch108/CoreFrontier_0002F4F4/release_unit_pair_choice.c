typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *PairContext;
extern u8 DisplayShadow[];
extern void Call_08022854(void *);
__asm__(".global PairContext\n.set PairContext,0x0200F444\n.global DisplayShadow\n.set DisplayShadow,0x03000940\n.global Call_08022854\n.thumb_set Call_08022854,0x08022855");
void CoreFrontier_0002F4F4(void)
{
 if(PairContext) {
   register volatile u8 *shadow __asm__("r3");
   register u32 zero __asm__("r1");
   register volatile u8 *first_field __asm__("r0");
   register volatile u8 *field __asm__("r2");
   Call_08022854(*(void **)(PairContext+672));
   zero=0;
   __asm__("" : "+r"(zero));
   PairContext=(u8 *)zero;
   shadow=DisplayShadow;
   __asm__("" : "+r"(shadow), "+r"(zero));
   first_field=shadow+68;
   __asm__("" : "+r"(first_field), "+r"(shadow), "+r"(zero));
   (void)*first_field; *first_field=zero;
   field=shadow+66;
   __asm__("" : "+r"(field), "+r"(shadow), "+r"(zero));
   (void)*field; *field=zero;
   field-=3;
   (void)*field; *field=zero;
   {
     register u32 value __asm__("r0")=*field;
     register u32 offset __asm__("r2")=59;
     register volatile u8 *saved __asm__("ip");
     register u32 discarded __asm__("r2");
     register volatile u8 *store_field __asm__("r4");
     __asm__("" : "+r"(value), "+r"(offset), "+r"(shadow), "+r"(zero));
     field=(volatile u8 *)(offset+(u32)shadow);
     saved=field;
     __asm__("" : "+r"(saved), "+r"(field), "+r"(value), "+r"(zero), "+r"(shadow));
     discarded=*field;
     __asm__("" : "+r"(discarded), "+r"(saved), "+r"(value), "+r"(zero), "+r"(shadow));
     store_field=saved;
     __asm__("" : "+r"(store_field), "+r"(discarded), "+r"(value), "+r"(zero), "+r"(shadow));
     *store_field=value;
   }
   field=shadow+62;
   __asm__("" : "+r"(field), "+r"(zero), "+r"(shadow));
   (void)*field; *field=zero;
   {
     register u32 value __asm__("r0")=*field;
     field-=4;
     (void)*field; *field=value;
   }
   *(volatile u16 *)shadow &= 0xdfff;
 }
}
