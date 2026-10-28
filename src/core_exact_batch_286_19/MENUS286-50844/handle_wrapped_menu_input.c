typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 gInputState[];
extern void ResetInputState(void *);
extern void PageMenu(void *,u32);
extern void ClearSelection(void *,u32);
extern void PlaySound(u32);
extern void SetCursor(void *,u32);
extern void UpdateSelectionStyle(void *,u32,u32);
void HandleWrappedMenuInput(u8 *menu,u32 directions,u32 modifiers)
{
 u16 direction=directions;
 u16 modifier=modifiers;
 u8 *cursor=menu+104;
 register u32 selected asm("r4")=0;
 u32 update=0;
 asm("" : "+r" (selected));
 if(direction&128){
  u32 next_shifted;
  register u32 first_row asm("r1");
  ResetInputState(gInputState);
  if(modifier&512){PageMenu(menu,128);return;}
  selected=(u32)cursor[17]<<24;
  asm("" : "+r" (selected));
  ClearSelection(menu,selected>>24);
  if(menu[10]>1)PlaySound(109);
  next_shifted=selected+0x01000000u;
  selected=next_shifted>>24;
  asm("" : "+r" (selected));
  if(((int)next_shifted>>24)>=menu[10])selected=0;
  first_row=selected;
  asm("" : "+r" (first_row));
  SetCursor(cursor,first_row);
  goto publish;
 }else if(direction&64){
  u32 next_shifted;
  ResetInputState(gInputState);
  if((modifier&512) && menu[8]!=1){PageMenu(menu,64);return;}
  selected=(u32)cursor[17]<<24;
  asm("" : "+r" (selected));
  ClearSelection(menu,selected>>24);
  if(menu[10]>1)PlaySound(109);
  next_shifted=selected+0xff000000u;
  selected=next_shifted>>24;
  asm("" : "+r" (selected));
  if((int)next_shifted<0){
   register u32 wrapped asm("r0")=menu[10]-1;
   asm("" : "+r" (wrapped));
   selected=(u8)wrapped;
  }
  update=1;
 }
 if(update!=0){
publish:
  SetCursor(cursor,selected);
  UpdateSelectionStyle(menu,selected,0);
 }
}
asm(".global gInputState\n.set gInputState,0x03000000\n.global ResetInputState\n.thumb_set ResetInputState,0x080023d1\n.global PageMenu\n.thumb_set PageMenu,0x08050af5\n.global ClearSelection\n.thumb_set ClearSelection,0x08050bf1\n.global PlaySound\n.thumb_set PlaySound,0x08141541\n.global SetCursor\n.thumb_set SetCursor,0x08017fb1\n.global UpdateSelectionStyle\n.thumb_set UpdateSelectionStyle,0x08050b9d");
