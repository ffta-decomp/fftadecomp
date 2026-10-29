typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u16 *ResolveEquipmentRowTilemap(u32,u32,u32,u32);
extern void DrawEquipmentRowText(u32,u16*,u32,u32,u32);
__asm__(".global ResolveEquipmentRowTilemap\n.thumb_set ResolveEquipmentRowTilemap,0x0808b8e5\n"
".global DrawEquipmentRowText\n.thumb_set DrawEquipmentRowText,0x0808b7c1");
void RenderEquipmentRowLabels(u8 *context,u32 alternate_layout) __asm__("CoreScene34_000774B4");
void RenderEquipmentRowLabels(u8 *context,u32 alternate_layout)
{
 u8 *row;
 if(alternate_layout==0){
  row=context+0x106;
  if(*row!=255){
   register u16 *destination __asm__("r1")=ResolveEquipmentRowTilemap(4,1,3,*row*2+2);
   __asm__("" : "+r"(destination));
   DrawEquipmentRowText(4,destination,*row*26+0x1ab,11,0xc000);
  }
  row=context+0x105;
  {
   register u16 *destination __asm__("r1")=ResolveEquipmentRowTilemap(4,1,3,*row*2+2);
   __asm__("" : "+r"(destination));
   DrawEquipmentRowText(4,destination,*row*26+0x1ab,11,0xb000);
  }
 }else{
  row=context+0x106;
  if(*row!=255){
   register u16 *destination __asm__("r1")=ResolveEquipmentRowTilemap(4,1,3,*row*2+4);
   __asm__("" : "+r"(destination));
   DrawEquipmentRowText(4,destination,13*(*row*2+2)+0x1ab,11,0xc000);
  }
  row=context+0x105;
  {
   register u16 *destination __asm__("r1")=ResolveEquipmentRowTilemap(4,1,3,*row*2+4);
   __asm__("" : "+r"(destination));
   DrawEquipmentRowText(4,destination,13*(*row*2+2)+0x1ab,11,0xb000);
  }
 }
}
