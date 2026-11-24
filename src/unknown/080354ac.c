typedef unsigned char u8;
typedef unsigned short u16;
struct PreviewRecord {u8 observed0[11];u8 value11;u8 observed12;u8 value13;} __attribute__((packed));
extern u8 *gMenuPreviewRoot;
extern struct PreviewRecord gPreviewRecords[];
extern u8 gPreviewUnitRecords[][264];
extern void CreateMenuPreview(void *,unsigned,unsigned,void *,void *,int,unsigned,unsigned,unsigned,unsigned);
extern unsigned QueryPreviewValue(unsigned,unsigned,unsigned);
extern void LoadPreviewPair(unsigned,unsigned,unsigned,unsigned);
extern void LoadPreviewRecord(void *,unsigned,unsigned);
__asm__(".global gMenuPreviewRoot\n.set gMenuPreviewRoot,0x03002810\n.global gPreviewRecords\n.set gPreviewRecords,0x08526cd8\n.global gPreviewUnitRecords\n.set gPreviewUnitRecords,0x02000080\n.global CreateMenuPreview\n.thumb_set CreateMenuPreview,0x0801174d\n.global QueryPreviewValue\n.thumb_set QueryPreviewValue,0x080c8571\n.global LoadPreviewPair\n.thumb_set LoadPreviewPair,0x08013109\n.global LoadPreviewRecord\n.thumb_set LoadPreviewRecord,0x08013211");
void ConfigureMenuPreviewContent(u8 selector0,u8 selector1,u16 encoded_id) {
 CreateMenuPreview(*(void **)(gMenuPreviewRoot+0xc08),selector0,selector1,(void *)0x03000990,(void *)0x030008b0,-1,0,22,6,203);
 if(encoded_id&0x8000) {
  u8 value0,value1;
  encoded_id &=0x7fff;
  if(encoded_id>127) {
   struct PreviewRecord *record=&gPreviewRecords[encoded_id];
   __asm__("" : "+r"(record));
   value0=record->value11;
   value1=record->value13;
  } else {
   u8 key=encoded_id;
   value0=(u8)QueryPreviewValue(key,key,9);
   value1=(u8)QueryPreviewValue(key,key,11);
  }
  LoadPreviewPair(value0,value1,0,9408);
 } else LoadPreviewRecord(gPreviewUnitRecords[encoded_id],0,9408);
}
