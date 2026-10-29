typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *volatile gEquipmentMenuOwner;
extern u8 gEquipmentSurfaceRoot[];
extern const u8 gEquipmentSelectionTableA[];
extern const u8 gEquipmentSelectionTableB[];
extern u32 ReadEquipmentDisplayProperty(u32);
extern u16 *ResolvePreviewTilemap(u32,u32,u32,u32);
extern void TransferPreviewResource(u32,u16*,u32,u32);
extern void FillPreviewHeader(u16*,u32,u32,u32);
extern void DrawEquipmentSelectionMarker(void*,u32,u32,u32,u32,u32,u32,const void*,const void*,u32);
__asm__(".global gEquipmentMenuOwner\n.set gEquipmentMenuOwner,0x03002818\n"
".global gEquipmentSurfaceRoot\n.set gEquipmentSurfaceRoot,0x03000e30\n"
".global gEquipmentSelectionTableA\n.set gEquipmentSelectionTableA,0x0894eb14\n"
".global gEquipmentSelectionTableB\n.set gEquipmentSelectionTableB,0x0894eb94\n"
".global ReadEquipmentDisplayProperty\n.thumb_set ReadEquipmentDisplayProperty,0x080c95a9\n"
".global ResolvePreviewTilemap\n.thumb_set ResolvePreviewTilemap,0x0808b8e5\n"
".global TransferPreviewResource\n.thumb_set TransferPreviewResource,0x08035679\n"
".global FillPreviewHeader\n.thumb_set FillPreviewHeader,0x08035a69\n"
".global DrawEquipmentSelectionMarker\n.thumb_set DrawEquipmentSelectionMarker,0x0804c4d5");
void RenderEquipmentRowSelection(u32) __asm__("CoreScene34_00076420");
void RenderEquipmentRowSelection(u32 selected_row)
{
 register u32 original_selection __asm__("r5");
 register u8 *volatile *owner_slot __asm__("r4");
 register u32 header_selection __asm__("r6");
 register u32 header_tag __asm__("r4");
 register u32 loop_selection __asm__("r6");
 register int index __asm__("r4");
 /* Ordinary cross-call root: allocator must account for its callee-saved home. */
 const u8 *surface_root;
 register u32 zero __asm__("r5");
 original_selection=selected_row;
 __asm__("" : "+r"(original_selection));
 owner_slot=&gEquipmentMenuOwner;
 __asm__("" : "+r"(owner_slot));
 if((*owner_slot)[0x44d]==4)
  return;
 if((u8)ReadEquipmentDisplayProperty(51)!=6) {
  header_selection=original_selection;
 } else {
  register u8 *mapping __asm__("r0")=*owner_slot;
  mapping+=0x9ba;
  __asm__("" : "+r"(mapping));
  mapping+=original_selection;
  __asm__("" : "+r"(mapping));
  header_selection=*mapping;
 }
 __asm__("" : "+r"(header_selection));
 header_tag=0xd0bf;
 __asm__("" : "+r"(header_tag));
 {
  register u16 *resource_tilemap __asm__("r1")=ResolvePreviewTilemap(0,1,26,19);
  __asm__("" : "+r"(resource_tilemap));
  TransferPreviewResource(header_tag,resource_tilemap,2,1);
 }
 {
  register u16 *header_tilemap __asm__("r0")=ResolvePreviewTilemap(0,1,28,19);
  __asm__("" : "+r"(header_tilemap));
  FillPreviewHeader(header_tilemap,2,header_selection+1,0xf000);
 }
 /* Mapping affects only the header, not the original full-row comparison. */
 loop_selection=original_selection;
 index=0;
 __asm__("" : "+r"(index));
 if(index>=(int)gEquipmentMenuOwner[0x95c])
  return;
 /* Constant real root only: no nullable R7 predicate or SP-derived address. */
 surface_root=gEquipmentSurfaceRoot;
 __asm__("" : "+r"(surface_root));
 zero=0;
 __asm__("" : "+r"(zero));
 do {
  if((u32)index!=loop_selection) {
   register u16 *row_tilemap __asm__("r0");
   register u32 tile_word __asm__("r2");
   register u32 stored_word __asm__("r1");
   row_tilemap=ResolvePreviewTilemap(0,1,index+2,19);
   __asm__("" : "+r"(row_tilemap));
   tile_word=0xd0be;
   __asm__("" : "+r"(tile_word));
   stored_word=tile_word;
   __asm__("" : "+r"(stored_word));
   *row_tilemap=stored_word;
  } else {
   const volatile u8 *count_address=gEquipmentMenuOwner+0x95c;
   register u32 style __asm__("r2");
   register u8 *workspace __asm__("r0");
   if(*count_address==1) {
    style=3;
   } else if(index>0) {
    int last=(int)*count_address-1;
    style=2;
    if(index<last)
     style=0;
   } else {
    style=1;
   }
   __asm__("" : "+r"(style));
   workspace=*(u8 *volatile *)(surface_root+4);
   workspace+=728;
   __asm__("" : "+r"(workspace));
   *(u16*)(workspace+20)=1;
   DrawEquipmentSelectionMarker(*(u8 *volatile *)(surface_root+4),26,style,
        (((u32)index<<27)+0x10000000u)>>24,160,zero,zero,
        gEquipmentSelectionTableA,gEquipmentSelectionTableB,444);
  }
  index++;
 } while(index<(int)gEquipmentMenuOwner[0x95c]);
}
