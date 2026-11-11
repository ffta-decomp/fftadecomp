typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
extern u32 record_flag(void*,u8);
int RemainingBand43_000DC4E0(void *record,u8 *descriptor)
{
 u8 i;
 if((u8)(descriptor[8]+1)<=1)return 1;
 for(i=0;i<(s8)descriptor[8];i++) {
  register u32 value __asm__("r2")=0;
  register u8 *cursor __asm__("r0");u32 selector;
  __asm__("" : "+r"(value));
  cursor=descriptor+9;__asm__("" : "+r"(cursor));
  cursor+=i;__asm__("" : "+r"(cursor));selector=*cursor;
  {
   u32 flags;
   if(selector==0) {
    flags=*(u16*)((char*)record+12);
    if(flags&1) {value=*(u16*)((char*)record+30);goto value_ready;}
   } else if(selector==1)flags=*(u16*)((char*)record+12);
   else goto next_item;
   {register u32 bit __asm__("r0")=2;
    __asm__("" : "+r"(bit) : "r"(flags));bit &= flags;
    __asm__("" : "+r"(bit));
    if(bit)value=*(u16*)((char*)record+32);
   }
  }
 value_ready: {
  register int signed_value __asm__("r0")=(s16)value;
  __asm__("" : "+r"(signed_value));
  if(signed_value>0)return 1;
  if(signed_value<0) {if((u8)record_flag(record,5))return -1;}
  else return 0;
 }
 next_item:;
 }
 return 1;
}
__asm__(".global record_flag\n.thumb_set record_flag,0x080a8859");
