typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 DisplayShadow[];
extern void Call_0802A2C0(u32,u32,u32,u32);
extern void Call_0802A370(u32,u32,u32,u32);
__asm__(".global DisplayShadow\n.set DisplayShadow,0x03000940\n.global Call_0802A2C0\n.thumb_set Call_0802A2C0,0x0802A2C1\n.global Call_0802A370\n.thumb_set Call_0802A370,0x0802A371");
void IsolatedCore57_00028BDC(void)
{
 register u8 *shadow __asm__("r2");
 register volatile u8 *field __asm__("r1");
 Call_0802A370(0,0,0,0);
 shadow=DisplayShadow;
 __asm__("" : "+r"(shadow));
 field=shadow+68;
 __asm__("" : "+r"(shadow), "+r"(field));
 (void)*field;
 *field=31;
 field -= 2;
 (void)*field;
 *field=63;
 field -= 7;
 (void)*field;
 *field=136;
 field += 4;
 (void)*field;
 *field=48;
 field -= 5;
 (void)*field;
 *field=248;
 field += 4;
 (void)*field;
 *field=144;
 {
  register u32 control __asm__("r1")=*(volatile u16 *)shadow;
  register u32 mask __asm__("r3")=8192;
  register u32 updated __asm__("r0");
  __asm__("" : "+r"(control), "+r"(mask), "+r"(shadow));
  updated=mask;
  __asm__("" : "+r"(updated), "+r"(control), "+r"(shadow));
  *(volatile u16 *)shadow=updated|control;
 }
}
