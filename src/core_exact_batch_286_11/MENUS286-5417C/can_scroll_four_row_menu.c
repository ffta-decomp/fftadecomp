typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
u32 CanScrollFourRowMenu(u8 *menu,u32 direction)
{
 u16 key=direction;
 u32 result;
 if(key==64) {
  if(*(s16 *)(menu+26)==0) goto cannot_scroll;
 } else {
  if(key!=128) goto cannot_scroll;
  if(*(s16 *)(menu+26)+4>=*(s16 *)(menu+24)) goto cannot_scroll;
 }
 result=1;
 goto finished;
 cannot_scroll:
 result=0;
 finished:
 return result;
}
