typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
extern u8 *gMenuContext;
extern void ResetSelectionPlaceholder(void *,u32);
extern void SetSelection(void *,u32);
extern int ResolveMenuSelection(void *,int);
extern void ApplyPanelDirection(void *,u32,u32);
extern void SetMenuRowStyle(void *,int,u32,u32);
extern void RefreshSlotContent(u32,int,void *);
void UpdateSlotMenuSelection(u32 slot,u32 direction,u32 selection,u32 refresh)
{
 u8 input_direction=direction;
 u8 next_selection=selection;
 u8 refresh_content=refresh;
 u8 **cell=&gMenuContext;
 u32 stride=204*slot;
 u32 block=stride+0x2c88;
 ResetSelectionPlaceholder(*cell+block+172,input_direction);
 if(refresh_content==0) {
  register u8 *row_panel asm("r0")=*cell+block+120;
  u32 shifted_selection;
  int signed_selection;
  asm("" : "+r" (row_panel));
  shifted_selection=(u32)next_selection<<24;
  signed_selection=(int)shifted_selection>>24;
  SetMenuRowStyle(row_panel,signed_selection,11,11);
  SetSelection(*cell+block+152,shifted_selection>>24);
  *(u8 *)((u32)*cell+stride+0x2cbe)=ResolveMenuSelection(*cell+stride+0x2d00,signed_selection);
 } else {
  RefreshSlotContent(slot,(s8)next_selection,*cell+block+120);
  *(u8 *)((u32)*cell+stride+0x2cbe)=ResolveMenuSelection(*cell+stride+0x2d00,(s8)next_selection);
  ApplyPanelDirection(*cell+block+120,input_direction,1);
  SetMenuRowStyle(*cell+block+120,(s8)(*cell)[stride+0x2d31],11,11);
 }
}
asm(".global gMenuContext\n.set gMenuContext,0x03002818\n.global ResetSelectionPlaceholder\n.thumb_set ResetSelectionPlaceholder,0x08017fbd\n.global SetSelection\n.thumb_set SetSelection,0x08017fb1\n.global ResolveMenuSelection\n.thumb_set ResolveMenuSelection,0x08017b69\n.global ApplyPanelDirection\n.thumb_set ApplyPanelDirection,0x08017885\n.global SetMenuRowStyle\n.thumb_set SetMenuRowStyle,0x08080f69\n.global RefreshSlotContent\n.thumb_set RefreshSlotContent,0x080835a5");
