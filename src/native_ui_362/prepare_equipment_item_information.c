typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *volatile gEquipmentMenuOwner;
extern u8 gEquipmentBufferRoot[];
extern u8 gEquipmentInfoDisplay[];
extern void ConfigureEquipmentInfoGroup(u32,u32,u32,u32,void*,void*,void*,void*,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void SelectEquipmentInfoGroup(u32);
extern void ConfigureEquipmentInfoSurface(void*,u32,u32,u32,u32,u32,u32,u32);
extern u16 *ResolveEquipmentInfoTilemap(u32,u32,u32,u32);
extern void DrawEquipmentInfoText(u32,u16*,u32,u32,u32);
extern void DrawEquipmentInfoNumber(u32,u16*,u32,u32,u32);
__asm__(".global gEquipmentMenuOwner\n.set gEquipmentMenuOwner,0x03002818\n"
".global gEquipmentBufferRoot\n.set gEquipmentBufferRoot,0x03002740\n"
".global gEquipmentInfoDisplay\n.set gEquipmentInfoDisplay,0x030009e0\n"
".global ConfigureEquipmentInfoGroup\n.thumb_set ConfigureEquipmentInfoGroup,0x0808a269\n"
".global SelectEquipmentInfoGroup\n.thumb_set SelectEquipmentInfoGroup,0x0808aa19\n"
".global ConfigureEquipmentInfoSurface\n.thumb_set ConfigureEquipmentInfoSurface,0x08016801\n"
".global ResolveEquipmentInfoTilemap\n.thumb_set ResolveEquipmentInfoTilemap,0x0808b8e5\n"
".global DrawEquipmentInfoText\n.thumb_set DrawEquipmentInfoText,0x0808b7c1\n"
".global DrawEquipmentInfoNumber\n.thumb_set DrawEquipmentInfoNumber,0x0808b80d");
void PrepareEquipmentItemInformation(void) __asm__("CoreGlobal36_0008C354");
void PrepareEquipmentItemInformation(void)
{
 u8 *owner=gEquipmentMenuOwner;
 register u32 resource_a __asm__("r2");
 register u32 resource_b __asm__("r3");
 u32 one,width;
 register u32 height __asm__("r6");
 register u32 first_label __asm__("r8");
 register u32 text_base __asm__("r4");
 register u8 *display __asm__("r2");
 resource_a=*(u32*)(owner+12);
 resource_b=*(u32*)(owner+20);
 __asm__("" : "+r"(resource_a), "+r"(resource_b));
 {
  register const u8 *buffer_root __asm__("r0")=gEquipmentBufferRoot;
  register u8 *buffer_base __asm__("r0");
  __asm__("" : "+r"(buffer_root));
  buffer_base=*(u8**)(buffer_root+24);
  __asm__("" : "+r"(buffer_base));
  ConfigureEquipmentInfoGroup(6,12,resource_a,resource_b,
       buffer_base,buffer_base+468,buffer_base+936,buffer_base+1404,
       /* Both retained scalars are defined at their first actual consumers. */
       0,(one=1),(width=13),18,0,1,13,18,13,18);
 }
 SelectEquipmentInfoGroup(6);
 /* Constant one/width remain ordinary known values across the calls. */
 display=gEquipmentInfoDisplay;
 __asm__("" : "+r"(display));
 display[0x1fc]=244;
 display[0x1fd]=one;
 {
  register u16 *label_destination __asm__("r1")=(u16*)(display+0x1d6);
  register u32 zero __asm__("r0");
  register u32 label_working __asm__("r3");
  __asm__("" : "+r"(label_destination));
  zero=0;
  __asm__("" : "+r"(zero));
  label_working=0x30d;
  __asm__("" : "+r"(label_working));
  first_label=label_working;
  __asm__("" : "+r"(first_label));
  *label_destination=first_label;
  display[0x1c9]=zero;
 }
 display[0x210]=one;
 display[0x211]=one;
 {
  register u8 *height_destination __asm__("r0")=display+0x212;
  __asm__("" : "+r"(height_destination));
  height=11;
  __asm__("" : "+r"(height));
  *height_destination=height;
 }
 display[0x213]=8;
 {
  register void *surface __asm__("r0")=*(void**)(display+0x1e0);
  u32 shared_x,y;
  __asm__("" : "+r"(surface));
  shared_x=display[0x1f0];
  y=display[0x1f1];
  ConfigureEquipmentInfoSurface(surface,shared_x,y,0x800,shared_x,width,3,height);
 }
 {
  register u16 *destination __asm__("r1")=ResolveEquipmentInfoTilemap(6,1,1,1);
  __asm__("" : "+r"(destination));
  text_base=0xb000;
  __asm__("" : "+r"(text_base));
  DrawEquipmentInfoText(6,destination,first_label,11,text_base);
 }
 {
  register u16 *destination __asm__("r1")=ResolveEquipmentInfoTilemap(6,1,1,5);
  __asm__("" : "+r"(destination));
  DrawEquipmentInfoText(6,destination,0x323,11,text_base);
 }
 {
  register u16 *destination __asm__("r1")=ResolveEquipmentInfoTilemap(6,1,1,9);
  __asm__("" : "+r"(destination));
  DrawEquipmentInfoText(6,destination,0x339,11,text_base);
 }
 {
  register u16 *destination __asm__("r1")=ResolveEquipmentInfoTilemap(6,1,1,13);
  __asm__("" : "+r"(destination));
  DrawEquipmentInfoText(6,destination,0x34f,11,text_base);
 }
 {
  register u16 *destination __asm__("r1")=ResolveEquipmentInfoTilemap(6,1,1,7);
  register u32 number_label __asm__("r2");
  __asm__("" : "+r"(destination));
  number_label=0x365;
  __asm__("" : "+r"(number_label));
  text_base=0xc000;
  __asm__("" : "+r"(text_base));
  DrawEquipmentInfoNumber(6,destination,number_label,4,text_base);
 }
 {
  register u16 *destination __asm__("r1")=ResolveEquipmentInfoTilemap(6,1,1,11);
  __asm__("" : "+r"(destination));
  DrawEquipmentInfoNumber(6,destination,0x36d,4,text_base);
 }
 {
  register u16 *destination __asm__("r1")=ResolveEquipmentInfoTilemap(6,1,1,15);
  __asm__("" : "+r"(destination));
  DrawEquipmentInfoNumber(6,destination,0x375,4,text_base);
 }
 {
  register u16 *destination __asm__("r1")=ResolveEquipmentInfoTilemap(6,1,7,3);
  __asm__("" : "+r"(destination));
  DrawEquipmentInfoText(6,destination,0x37d,5,0xe000);
 }
}
