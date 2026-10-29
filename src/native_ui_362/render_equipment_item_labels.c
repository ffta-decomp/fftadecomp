typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ItemTextRow { u16 name;u8 other[30]; };
struct DisplayState { u8 prefix[328];void *first,*second;u8 gap[8];u8 x,y; };
extern u8 *volatile gEquipmentMenuOwner;
extern struct DisplayState gEquipmentDisplay;
extern const struct ItemTextRow gItemTextRows[];
extern const void *const gItemNames[];
extern void ClearPreviewArea(void*,u32,u32,u32,u32,u32,u32);
extern void FillPreviewArea(void*,u32,u32,u32,u32,u32,u32);
extern u16 *ResolvePreviewTilemap(u32,u32,u32,u32);
extern u32 DecodePreviewResource(void*,u32,u32);
extern void TransferPreviewResource(u32,u16*,u32,u32);
extern u32 ReadItemPreviewVariant(u32);
extern void DecodeItemPreview(void*,u32);
extern void CopyItemPreview(const void*,void*,u32);
extern void DrawPreviewTiles(u32,u32,u32,u32,u32,u32,u32);
extern void DrawPreviewName(void*,const void*,u32,u32);
__asm__(".global gEquipmentMenuOwner\n.set gEquipmentMenuOwner,0x03002818\n"
".global gEquipmentDisplay\n.set gEquipmentDisplay,0x030009e0\n"
".global gItemTextRows\n.set gItemTextRows,0x0851d180\n"
".global gItemNames\n.set gItemNames,0x08526680\n"
".global ClearPreviewArea\n.thumb_set ClearPreviewArea,0x08016345\n"
".global FillPreviewArea\n.thumb_set FillPreviewArea,0x08016561\n"
".global ResolvePreviewTilemap\n.thumb_set ResolvePreviewTilemap,0x0808b8e5\n"
".global DecodePreviewResource\n.thumb_set DecodePreviewResource,0x08018525\n"
".global TransferPreviewResource\n.thumb_set TransferPreviewResource,0x08035679\n"
".global ReadItemPreviewVariant\n.thumb_set ReadItemPreviewVariant,0x080cb99d\n"
".global DecodeItemPreview\n.thumb_set DecodeItemPreview,0x080cb981\n"
".global CopyItemPreview\n.thumb_set CopyItemPreview,0x0814186d\n"
".global DrawPreviewTiles\n.thumb_set DrawPreviewTiles,0x08089249\n"
".global DrawPreviewName\n.thumb_set DrawPreviewName,0x08089aad");
void RenderEquipmentItemLabels(const u8 *) __asm__("CoreScene34_00074908");
void RenderEquipmentItemLabels(const u8 *record)
{
 u32 shared_x,decoded;
 u16 *tilemap;
 register u32 transfer_tag __asm__("r5");
 register s32 index __asm__("r8");
 register s32 test_index __asm__("r2");
 register u32 texture_offset __asm__("r9");
 register u8 *name_destination __asm__("r10");
 /* The original incoming full pointer has an addressable SP12 snapshot. */
 __asm__("" : "+m"(record));
 *(u8*)(gEquipmentMenuOwner+0xbf5)=2;
 {
  register void *surface __asm__("r0")=gEquipmentDisplay.second;
  __asm__("" : "+r"(surface));
  shared_x=gEquipmentDisplay.x;
  ClearPreviewArea(surface,shared_x,gEquipmentDisplay.y,192,shared_x,5,12);
 }
 FillPreviewArea(gEquipmentDisplay.first,14,13,192,14,1,12);
 transfer_tag=0xc03e;
 __asm__("" : "+r"(transfer_tag));
 tilemap=ResolvePreviewTilemap(4,1,1,1);
 decoded=DecodePreviewResource((void*)0x02003cb0,62,28);
 TransferPreviewResource(transfer_tag,tilemap,decoded,1);
 {
  register u32 zero __asm__("r2")=0;
  register u8 *name_work __asm__("r3");
  __asm__("" : "+r"(zero));
  index=zero;
  name_work=(u8*)0x0600b560;
  __asm__("" : "+r"(name_work));
  name_destination=name_work;
  texture_offset=zero;
 }
 do {
  register u32 low_index __asm__("r0")=index;
  register u32 row_offset __asm__("r4");
  register u32 item __asm__("r5");
  register u32 name_index __asm__("r6");
  u8 *texture_destination;
  u32 variant;
  /* Only final full text capture; no R7 arithmetic, guard or stack carrier. */
  register const void *text __asm__("r7");
  __asm__("" : "+r"(low_index));
  row_offset=low_index*2;
  __asm__("" : "+r"(row_offset));
  {
   register const u8 *row_record __asm__("r0")=record;
   row_record+=42;
   __asm__("" : "+r"(row_record));
   row_record+=row_offset;
   __asm__("" : "+r"(row_record));
   item=*(const u16*)row_record;
  }
  __asm__("" : "+r"(item));
  name_index=gItemTextRows[item].name;
  __asm__("" : "+r"(name_index));
  texture_destination=(u8*)0x0600b4e0+texture_offset;
  __asm__("" : "+r"(texture_destination));
  {
   register u32 tile_flags __asm__("r2");
   register u32 variant_base __asm__("r1");
   tile_flags=ReadItemPreviewVariant(item);
   __asm__("" : "+r"(tile_flags));
   tile_flags<<=28;
   __asm__("" : "+r"(tile_flags));
   variant_base=0xd0000000u;
   __asm__("" : "+r"(variant_base));
   tile_flags+=variant_base;
   __asm__("" : "+r"(tile_flags));
   tile_flags>>=16;
   __asm__("" : "+r"(tile_flags));
   DrawPreviewTiles(4,(u16)((u32)index*26+0x1a7),
       tile_flags,1,(u8)(row_offset+2),2,2);
  }
  {
   register void *decode_scratch __asm__("r0")=(void*)0x02003cb0;
   __asm__("" : "+r"(decode_scratch));
   DecodeItemPreview(decode_scratch,item);
  }
  {
   register const void *copy_scratch __asm__("r0")=(const void*)0x02003cb0;
   __asm__("" : "+r"(copy_scratch));
   CopyItemPreview(copy_scratch,texture_destination,64);
  }
  text=gItemNames[name_index];
  __asm__("" : "+r"(text));
  DrawPreviewName(name_destination,text,13,0);
  name_destination+=832;
  texture_offset+=832;
  {
   register s32 step __asm__("r1")=1;
   __asm__("" : "+r"(step));
   index+=step;
   test_index=index;
   __asm__("" : "+r"(test_index));
  }
 } while(test_index<=4);
}
