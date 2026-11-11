typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
int RemainingBand43_000DD4D4(void *record)
{
 register u32 flags __asm__("r4")=*(u16*)((char*)record+12);
 register u32 value __asm__("r1");
 register u32 bit __asm__("r0")=1;
 register int signed_value __asm__("r3");
 bit &= flags;__asm__("" : "+r"(bit));
 value=32767;
 if(bit)value=*(u16*)((char*)record+30);
 {register u32 shifted __asm__("r0")=value<<16;
  __asm__("" : "+r"(shifted));signed_value=(int)shifted>>16;
  __asm__("" : "+r"(signed_value));}
 if(signed_value==32767) {
  bit=2;bit &= flags;value=signed_value;
  __asm__("" : "+r"(bit), "+r"(value));
  if(bit)value=*(u16*)((char*)record+32);
 }
 return (s16)value;
}
