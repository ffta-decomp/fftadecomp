typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
extern int ResolveMenuSelection(void *,int);
extern void SetMenuRowStyle(void *,int,u32);
void UpdateSelectedMenuRowStyle(u8 *menu,u32 selection,u32 skip_empty)
{
 u8 row=selection;
 u8 skip=skip_empty;
 u32 style=11;
 if(menu[8]==4) {
  u16 index=ResolveMenuSelection(menu+72,(s8)row);
  register unsigned address asm("r1")=(u32)*(u8 **)menu;
  register unsigned scaled_index asm("r0")=4*(u32)index;
  u8 *item;
  asm("" : "+r" (address), "+r" (scaled_index));
  address+=0x424;
  address+=scaled_index;
  asm("" : "+r" (address));
  item=*(u8 **)address;
  if(*(u16 *)(item+2)!=0) style=10;
  else if(skip!=0) return;
 }
 SetMenuRowStyle(menu+72,(s8)row,style);
}
asm(".global ResolveMenuSelection\n.thumb_set ResolveMenuSelection,0x08017b69\n.global SetMenuRowStyle\n.thumb_set SetMenuRowStyle,0x08017af5");
