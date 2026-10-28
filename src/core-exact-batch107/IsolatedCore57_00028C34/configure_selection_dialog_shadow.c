typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 DisplayShadow[];
extern void Call_0802A2C0(u32,u32,u32,u32);
extern void Call_0802A370(u32,u32,u32,u32);
__asm__(".global DisplayShadow\n.set DisplayShadow,0x03000940\n.global Call_0802A2C0\n.thumb_set Call_0802A2C0,0x0802A2C1\n.global Call_0802A370\n.thumb_set Call_0802A370,0x0802A371");
void IsolatedCore57_00028C34(void)
{
 register u8 *shadow __asm__("r2");
 register volatile u8 *field __asm__("r1");
 shadow=DisplayShadow;
 __asm__("" : "+r"(shadow));
 field=shadow+67;
 __asm__("" : "+r"(shadow), "+r"(field));
 (void)*field;
 *field=19;
 field -= 6;
 (void)*field;
 *field=16;
 field += 4;
 (void)*field;
 *field=8;
 field -= 5;
 (void)*field;
 *field=224;
 field += 4;
 (void)*field;
 *field=32;
 {
  register u32 control __asm__("r1")=*(volatile u16 *)shadow;
  register u32 mask __asm__("r3")=16384;
  register u32 updated __asm__("r0");
  __asm__("" : "+r"(control), "+r"(mask), "+r"(shadow));
  updated=mask;
  __asm__("" : "+r"(updated), "+r"(control), "+r"(shadow));
  *(volatile u16 *)shadow=updated|control;
 }
 Call_0802A2C0(2,2,26,6);
}
