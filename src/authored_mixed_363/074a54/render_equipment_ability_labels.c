typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct PreviewRow { u8 label_low,label_high,value_low,value_high; };
struct AbilityEntry { u16 name,value;u8 other[4]; };
struct DisplayState { u8 prefix[328];void *first,*second;u8 gap[8];u8 x,y; };
extern u8 *volatile gEquipmentMenuOwner;
extern struct DisplayState gEquipmentDisplay;
extern const struct PreviewRow gPreviewRows[];
extern const void *const gPreviewNames[];
extern const struct AbilityEntry *const gAbilityEntryLists[];
extern void ClearPreviewArea(void*,u32,u32,u32,u32,u32,u32);
extern void FillPreviewArea(void*,u32,u32,u32,u32,u32,u32);
extern u16 *ResolvePreviewTilemap(u32,u32,u32,u32);
extern u32 DecodePreviewResource(void*,u32,u32);
extern void TransferPreviewResource(u32,u16*,u32,u32);
extern const volatile u8 *ReadPreviewProperty(const u8*,u32);
extern void DrawPreviewTiles(u32,u32,u32,u32,u32,u32,u32);
extern void DrawPreviewName(void*,const void*,u32,u32);
__asm__(".global gEquipmentMenuOwner\n.set gEquipmentMenuOwner,0x03002818\n"
".global gEquipmentDisplay\n.set gEquipmentDisplay,0x030009e0\n"
".global gPreviewRows\n.set gPreviewRows,0x08527244\n"
".global gPreviewNames\n.set gPreviewNames,0x085567f0\n"
".global gAbilityEntryLists\n.set gAbilityEntryLists,0x0851ba84\n"
".global ClearPreviewArea\n.thumb_set ClearPreviewArea,0x08016345\n"
".global FillPreviewArea\n.thumb_set FillPreviewArea,0x08016561\n"
".global ResolvePreviewTilemap\n.thumb_set ResolvePreviewTilemap,0x0808b8e5\n"
".global DecodePreviewResource\n.thumb_set DecodePreviewResource,0x08018525\n"
".global TransferPreviewResource\n.thumb_set TransferPreviewResource,0x08035679\n"
".global ReadPreviewProperty\n.thumb_set ReadPreviewProperty,0x080c7ea5\n"
".global DrawPreviewTiles\n.thumb_set DrawPreviewTiles,0x08089249\n"
".global DrawPreviewName\n.thumb_set DrawPreviewName,0x08089aad");
static __inline__ u32 PreviewValue(const struct PreviewRow *row)
{
 return row->value_low | ((u32)row->value_high << 8);
}
void RenderEquipmentAbilityLabels(const u8 *) __asm__("CoreScene34_00074A54");
void RenderEquipmentAbilityLabels(const u8 *record)
{
 u8 ids[5];
 register const volatile u8 *descriptor __asm__("r6");
 register const struct PreviewRow *preview_rows __asm__("r5");
 const struct PreviewRow *row;
 u16 *tilemap;
 u32 decoded,shared_x;
 register u8 *scratch __asm__("r6");
 register u8 *volatile *owner_slot __asm__("r9");
 register u32 clear_saved __asm__("r10");
 register u32 transfer_tag __asm__("r5");
 register s32 index __asm__("r4");
 register u8 *destination __asm__("r10");
 register const void *const *name_rows __asm__("r5");
 register const struct AbilityEntry *const *entry_lists __asm__("r8");
 register u8 *volatile *row_owner_slot __asm__("r6");
 register const void *text __asm__("r2");
 register const u8 *display __asm__("r5");
 scratch=(u8*)0x02003cb0;
 __asm__("" : "+r"(scratch));
 {
  register u8 *volatile *owner_work __asm__("r0")=&gEquipmentMenuOwner;
  register u8 *mode_address __asm__("r0");
  register u32 clear_work __asm__("r2");
  __asm__("" : "+r"(owner_work));
  owner_slot=owner_work;
  mode_address=(*owner_work)+0xbf5;
  __asm__("" : "+r"(mode_address));
  clear_work=0;
  __asm__("" : "+r"(clear_work));
  clear_saved=clear_work;
  *mode_address=3;
 }
 {
  register u32 surface_offset __asm__("r3");
  register void *surface __asm__("r0");
  register u32 x_offset __asm__("r2");
  register const u8 *x_address __asm__("r1");
  register const u8 *y_address __asm__("r2");
  display=(const u8*)&gEquipmentDisplay;
  __asm__("" : "+r"(display));
  surface_offset=332;
  __asm__("" : "+r"(surface_offset));
  surface=*(void *const *)(display+surface_offset);
  __asm__("" : "+r"(surface));
  x_offset=344;
  __asm__("" : "+r"(x_offset));
  x_address=display+x_offset;
  __asm__("" : "+r"(x_address));
  shared_x=*x_address;
  surface_offset+=13;
  __asm__("" : "+r"(surface_offset));
  y_address=display+surface_offset;
  __asm__("" : "+r"(y_address));
  ClearPreviewArea(surface,shared_x,*y_address,192,shared_x,5,12);
 }
 {
  register u32 fill_offset __asm__("r1")=328;
  register u32 fill_address __asm__("r0");
  register void *fill_surface __asm__("r0");
  __asm__("" : "+r"(fill_offset));
  fill_address=(u32)display+fill_offset;
  __asm__("" : "+r"(fill_address));
  fill_surface=*(void *const *)fill_address;
  __asm__("" : "+r"(fill_surface));
  FillPreviewArea(fill_surface,14,13,192,14,1,12);
 }
 transfer_tag=0xc03e;
 __asm__("" : "+r"(transfer_tag));
 tilemap=ResolvePreviewTilemap(4,1,1,1);
 decoded=DecodePreviewResource(scratch,62,4);
 TransferPreviewResource(transfer_tag,tilemap,decoded,1);
 descriptor=ReadPreviewProperty(record,34);
 {
  register u8 *first_id __asm__("r1")=ids;
  register u32 offset __asm__("r0");
  __asm__("" : "+r"(first_id));
  offset=(u32)descriptor[1]*4;
  __asm__("" : "+r"(offset));
  preview_rows=gPreviewRows;
  __asm__("" : "+r"(preview_rows));
  offset+=(u32)preview_rows;
  __asm__("" : "+r"(offset));
  *(volatile u8*)first_id=*(const u8*)offset;
 }
 {
  register u8 *volatile *slot_work __asm__("r2")=owner_slot;
  register u8 *field_owner __asm__("r1");
  register u32 row_address __asm__("r0");
  register u32 low_byte __asm__("r2");
  register u32 field_value __asm__("r0");
  register u32 field_offset __asm__("r3");
  __asm__("" : "+r"(slot_work));
  field_owner=*slot_work;
  __asm__("" : "+r"(field_owner));
  row_address=(u32)descriptor[1]*4;
  __asm__("" : "+r"(row_address));
  row_address+=(u32)preview_rows;
  __asm__("" : "+r"(row_address));
  low_byte=*(const u8*)(row_address+2);
  __asm__("" : "+r"(low_byte));
  field_value=*(const u8*)(row_address+3);
  field_value=(field_value<<8)|low_byte;
  __asm__("" : "+r"(field_value));
  field_offset=0x1234;
  __asm__("" : "+r"(field_offset));
  *(u16*)(field_owner+field_offset)=field_value;
 }
 DrawPreviewTiles(4,203,0xd000,1,2,2,2);
 {
  register u8 *second_id __asm__("r2")=ids;
  register u32 row_address __asm__("r0");
  register u32 low_byte __asm__("r1");
  register u32 label_word __asm__("r0");
  __asm__("" : "+r"(second_id));
  row_address=(u32)descriptor[2]*4;
  __asm__("" : "+r"(row_address));
  row_address+=(u32)preview_rows;
  __asm__("" : "+r"(row_address));
  low_byte=*(const u8*)row_address;
  __asm__("" : "+r"(low_byte));
  label_word=*(const u8*)(row_address+1);
  label_word=(label_word<<8)|low_byte;
  /* The full word is the destructive high-byte working before low-byte store. */
  __asm__("" : "+r"(label_word));
  *(volatile u8 *)(second_id+1)=label_word;
 }
 {
  register u8 *volatile *slot_work __asm__("r2")=owner_slot;
  register u8 *field_owner __asm__("r1");
  register u32 row_address __asm__("r0");
  register u32 low_byte __asm__("r2");
  register u32 field_value __asm__("r0");
  register u32 field_offset __asm__("r3");
  __asm__("" : "+r"(slot_work));
  field_owner=*slot_work;
  __asm__("" : "+r"(field_owner));
  row_address=(u32)descriptor[2]*4;
  __asm__("" : "+r"(row_address));
  row_address+=(u32)preview_rows;
  __asm__("" : "+r"(row_address));
  low_byte=*(const u8*)(row_address+2);
  __asm__("" : "+r"(low_byte));
  field_value=*(const u8*)(row_address+3);
  field_value=(field_value<<8)|low_byte;
  __asm__("" : "+r"(field_value));
  field_offset=0x1236;
  __asm__("" : "+r"(field_offset));
  *(u16*)(field_owner+field_offset)=field_value;
 }
 DrawPreviewTiles(4,203,0xd000,1,4,2,2);
 *(volatile u8 *)(ids+2)=record[58];
 DrawPreviewTiles(4,207,0xe000,1,6,2,2);
 *(volatile u8 *)(ids+3)=record[59];
 DrawPreviewTiles(4,211,0xd000,1,8,2,2);
 *(volatile u8 *)(ids+4)=record[60];
 DrawPreviewTiles(4,215,0xe000,1,10,2,2);
 {
  register u8 *volatile *clear_slot __asm__("r1")=owner_slot;
  register u8 *clear_owner __asm__("r0");
  register u32 offset __asm__("r2");
  register u8 *first_destination __asm__("r1");
  register u32 first_zero __asm__("r3");
  register u32 final_offset __asm__("r3");
  register u32 final_zero __asm__("r1");
  __asm__("" : "+r"(clear_slot));
  clear_owner=*clear_slot;
  __asm__("" : "+r"(clear_owner));
  offset=0x1238;
  __asm__("" : "+r"(offset));
  first_destination=clear_owner+offset;
  __asm__("" : "+r"(first_destination));
  first_zero=clear_saved;
  __asm__("" : "+r"(first_zero));
  *(u16*)first_destination=first_zero;
  offset+=2;
  __asm__("" : "+r"(offset));
  first_destination=clear_owner+offset;
  __asm__("" : "+r"(first_destination));
  *(u16*)first_destination=first_zero;
  final_offset=0x123c;
  __asm__("" : "+r"(final_offset));
  clear_owner+=final_offset;
  __asm__("" : "+r"(clear_owner));
  final_zero=clear_saved;
  __asm__("" : "+r"(final_zero));
  *(u16*)clear_owner=final_zero;
 }
 index=0;
 __asm__("" : "+r"(index));
 name_rows=gPreviewNames;
 __asm__("" : "+r"(name_rows));
 {
  register const struct AbilityEntry *const *entry_work __asm__("r2")=gAbilityEntryLists;
  register u8 *destination_work __asm__("r3");
  __asm__("" : "+r"(entry_work));
  entry_lists=entry_work;
  destination_work=(u8*)0x0600b560;
  __asm__("" : "+r"(destination_work));
  destination=destination_work;
 }
 row_owner_slot=owner_slot;
 __asm__("" : "+r"(row_owner_slot));
 do {
  register u8 *metadata_owner __asm__("r0");
  register u32 metadata_value __asm__("r1");
  register u32 metadata_offset __asm__("r3");
  if(index==0) {
   text=name_rows[ids[0]];
   goto draw_name;
  } else if(index==1) {
   text=name_rows[ids[1]];
   goto draw_name;
  } else if(index==2) {
   register u32 list_address __asm__("r0");
   register const struct AbilityEntry *table __asm__("r1");
   register u32 entry_address __asm__("r0");
   register const struct AbilityEntry *entry __asm__("r0");
   register u32 name __asm__("r2");
   register u8 *row_owner __asm__("r1");
   register u32 value __asm__("r0");
   register u32 offset __asm__("r3");
   /* Original list lookup: scale kind, add published root, then read table.
      Explicit6B avoids three empty-ASM instruction-length overestimates. */
   list_address=record[6];
   __asm__ volatile("lsl %0,%0,#2\n\tadd %0,%2\n\tldr %1,[%0]"
      : "+&l"(list_address), "=l"(table) : "h"(entry_lists) : "cc","memory");
   /* Fresh record-byte index is read only after table publication. */
   entry_address=record[58];
   __asm__("lsl %0,%0,#3\n\tadd %0,%0,%1"
      : "+&l"(entry_address) : "l"(table) : "cc");
   /* Ordered6B memory handoff: nameH0, fresh ownerW0, last entry H2.
      H2 destroys the now-dead pointer in the same full R0 carrier. */
   __asm__ volatile("ldrh %0,[%2]\n\tldr %1,[%3]\n\tldrh %2,[%2,#2]"
      : "=&l"(name), "=&l"(row_owner), "+l"(entry_address)
      : "l"(row_owner_slot) : "memory");
   value=entry_address;
   offset=0x1238;
   __asm__("" : "+r"(offset));
   *(u16*)(row_owner+offset)=value;
   text=name_rows[name];
   goto draw_name;
  } else if(index==3) {
   register u32 list_address __asm__("r0");
   register const struct AbilityEntry *table __asm__("r0");
   register u32 entry_address __asm__("r1");
   register const struct AbilityEntry *entry __asm__("r1");
   /* Original list lookup: scale kind, add published root, then read table.
      Explicit6B avoids three empty-ASM instruction-length overestimates. */
   list_address=record[6];
   __asm__ volatile("lsl %0,%0,#2\n\tadd %0,%1\n\tldr %0,[%0]"
      : "+&l"(list_address) : "h"(entry_lists) : "cc","memory");
   table=(const struct AbilityEntry*)list_address;
   /* Fresh record-byte index is read only after table publication. */
   entry_address=record[59];
   __asm__("lsl %0,%0,#3\n\tadd %0,%0,%1"
      : "+&l"(entry_address) : "l"(table) : "cc");
   entry=(const struct AbilityEntry*)entry_address;
   text=name_rows[entry->name];
   metadata_owner=*row_owner_slot;
   __asm__("" : "+r"(metadata_owner));
   metadata_value=entry->value;
   __asm__("" : "+r"(metadata_value));
   metadata_offset=0x123a;
   __asm__("" : "+r"(metadata_offset));
   goto publish_row_metadata;
  } else {
   register u32 list_address __asm__("r0");
   register const struct AbilityEntry *table __asm__("r2");
   register u32 entry_address __asm__("r1");
   register const struct AbilityEntry *entry __asm__("r1");
   /* Original list lookup: scale kind, add published root, then read table.
      Explicit6B avoids three empty-ASM instruction-length overestimates. */
   list_address=record[6];
   __asm__ volatile("lsl %0,%0,#2\n\tadd %0,%2\n\tldr %1,[%0]"
      : "+&l"(list_address), "=l"(table) : "h"(entry_lists) : "cc","memory");
   /* Fresh record-byte index is read only after table publication. */
   entry_address=record[60];
   __asm__("lsl %0,%0,#3\n\tadd %0,%0,%1"
      : "+&l"(entry_address) : "l"(table) : "cc");
   entry=(const struct AbilityEntry*)entry_address;
   text=name_rows[entry->name];
   metadata_owner=*row_owner_slot;
   __asm__("" : "+r"(metadata_owner));
   metadata_value=entry->value;
   __asm__("" : "+r"(metadata_value));
   metadata_offset=0x123c;
   __asm__("" : "+r"(metadata_offset));
  }
publish_row_metadata:
  *(u16*)(metadata_owner+metadata_offset)=metadata_value;
draw_name:
  /* Every row defines the actual full text pointer before call setup. */
  __asm__("" : "+r"(text));
  DrawPreviewName(destination,text,13,0);
  {
   /* Original full R0 stride working:208<<2, then update the high pointer. */
   register u32 stride __asm__("r0")=208;
   __asm__("lsl %1,%1,#2\n\tadd %0,%1"
      : "+h"(destination), "+l"(stride) : : "cc");
  }
  index++;
 } while(index<=4);
}
