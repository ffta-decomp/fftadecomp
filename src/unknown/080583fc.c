typedef unsigned char u8;
typedef signed short s16;
void UpdateThreeRowScrollFlags(u8 *request,u8 *view)
{
 u8 *scroll=*(u8 **)(view+4);
 if(scroll[26]!=0) {
  unsigned flags=request[16];
  register unsigned updated asm("r0")=4;
  asm("" : "+r" (updated) : "r" (flags));
  updated|=flags;
  asm("" : "+r" (updated));
  request[16]=updated;
 }
 else request[16]&=251;
 scroll=*(u8 **)(view+4);
 if(scroll[26]==*(s16 *)(scroll+24)-3) request[16]&=247;
 else {
  unsigned flags=request[16];
  register unsigned updated asm("r0")=8;
  asm("" : "+r" (updated) : "r" (flags));
  updated|=flags;
  asm("" : "+r" (updated));
  request[16]=updated;
 }
}
