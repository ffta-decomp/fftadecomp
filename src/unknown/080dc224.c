typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
extern u32 object_id(void*);
void RemainingBand43_000DC224(void *object,u32 x,u32 y,s16 *out_x,s16 *out_y)
{
 register u32 raw_x __asm__("r0")=(u16)x;
 register u32 raw_y __asm__("r2");
 __asm__("" : "+r"(raw_x));
 raw_y=(u16)y;__asm__("" : "+r"(raw_y));
 if(out_x) {
  register int center __asm__("r1")=16;
  register int signed_x __asm__("r0")=(s16)raw_x;
  __asm__("" : "+r"(center), "+r"(signed_x));
  center-=signed_x;__asm__("" : "+r"(center));
  *out_x=center;
 }
 if(out_y) {
  register int center __asm__("r0")=48;
  register int signed_y __asm__("r1")=(s16)raw_y;
  __asm__("" : "+r"(center), "+r"(signed_y));
  *out_y=center-signed_y;
  if((u16)object_id(object)==81)*out_y-=4;
 }
}
__asm__(".global object_id\n.thumb_set object_id,0x080dd6e1");
