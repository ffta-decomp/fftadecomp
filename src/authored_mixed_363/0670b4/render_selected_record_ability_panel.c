typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef void (*PanelClearCallback)(void *,u32);
extern PanelClearCallback gPanelClearCallback;
extern struct PanelTileManager { u8 padding[16]; u8 *tiles; } gPanelTileManager;
extern const u8 *const gSelectedRecordLabels[];
extern const struct PanelRecordDescriptor { u8 prefix[29]; u8 pair_table; u8 suffix[2]; } gRecordPanelDescriptors[];
extern const u8 gRecordPanelPairs[];
extern const u8 *const gSelectedAbilityLabels[];
extern u8 gAbilityIconStaging[];
extern void InvokePanelClear(void *,u32,PanelClearCallback);
extern u32 GetPanelTextTile(u8 *,u32);
extern void ClearPanelText(void *,u32);
extern u32 ResolveSelectedRecordLabel(u32,u32);
extern void RenderPanelText(u8 *,void *,const u8 *,u32,u32);
extern void DrawPanelTextTiles(u8 *,u32,u32,u32,u32,u32,u32);
extern u32 CollectPanelAbilityRows(u32,u8 *);
extern u32 ResolvePanelAbilityKind(u32,u32,u32);
extern u8 *ResolvePanelAbilityValue(u32,u32);
extern void DrawPanelTileRun(u8 *,u32,u32,u32);
extern void DrawPanelDecimal(u8 *,u32,u32);
extern void CommitPanelTiles(u8 *,u8 *,u32,u32,u32);
extern void StagePanelAbilityIcon(u8 *,u32);
extern void CopyPanelAbilityIcon(u8 *,u8 *,u32);
extern u32 ResolvePanelAbilityVariant(u32);
__asm__(".global gPanelClearCallback\n.set gPanelClearCallback,0x0836d4b8\n"
".global gPanelTileManager\n.set gPanelTileManager,0x030008b0\n"
".global gSelectedRecordLabels\n.set gSelectedRecordLabels,0x08526680\n"
".global gRecordPanelDescriptors\n.set gRecordPanelDescriptors,0x0851d180\n"
".global gRecordPanelPairs\n.set gRecordPanelPairs,0x08520080\n"
".global gSelectedAbilityLabels\n.set gSelectedAbilityLabels,0x085567f0\n"
".global gAbilityIconStaging\n.set gAbilityIconStaging,0x02003cb0\n"
".global InvokePanelClear\n.thumb_set InvokePanelClear,0x0814224d\n"
".global GetPanelTextTile\n.thumb_set GetPanelTextTile,0x08017b9d\n"
".global ClearPanelText\n.thumb_set ClearPanelText,0x08013a89\n"
".global ResolveSelectedRecordLabel\n.thumb_set ResolveSelectedRecordLabel,0x080ca7a5\n"
".global RenderPanelText\n.thumb_set RenderPanelText,0x08015111\n"
".global DrawPanelTextTiles\n.thumb_set DrawPanelTextTiles,0x0802ab65\n"
".global CollectPanelAbilityRows\n.thumb_set CollectPanelAbilityRows,0x080c8d15\n"
".global ResolvePanelAbilityKind\n.thumb_set ResolvePanelAbilityKind,0x080c8571\n"
".global ResolvePanelAbilityValue\n.thumb_set ResolvePanelAbilityValue,0x080cd481\n"
".global DrawPanelTileRun\n.thumb_set DrawPanelTileRun,0x0802aca1\n"
".global DrawPanelDecimal\n.thumb_set DrawPanelDecimal,0x08029731\n"
".global CommitPanelTiles\n.thumb_set CommitPanelTiles,0x0802ac15\n"
".global StagePanelAbilityIcon\n.thumb_set StagePanelAbilityIcon,0x080cb9e1\n"
".global CopyPanelAbilityIcon\n.thumb_set CopyPanelAbilityIcon,0x0814186d\n"
".global ResolvePanelAbilityVariant\n.thumb_set ResolvePanelAbilityVariant,0x080cba15");
#define HALF(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define PTR(p,o) (*(u8 **)((u8 *)(p)+(o)))
void RenderSelectedRecordAbilityPanel(u8 *panel) __asm__("RemainingCore48_000670B4");
void RenderSelectedRecordAbilityPanel(u8 *panel)
{
 struct PanelSnapshots {
  /* Real manual sixth/seventh ABI words at SP4/SP8; not padding. */
  u32 outgoing_extra[2];
  u8 *text;
  u8 *widget;
  u8 *layout;
  s32 count;
  s32 tile_base;
  u8 *icon_text;
  u32 shifted_width;
  u8 **map_cell;
  s32 next_row;
  s32 double_width;
 } snapshots;
 {
 register u32 width_working __asm__("r4");
 register u32 width __asm__("r8");
 register u8 *text_cursor __asm__("r10");
 register u8 *selected __asm__("r5");
 register const u8 *pair_table __asm__("r9");
 s32 row;
 register u8 *first_run __asm__("r6");
 register u8 *second_run __asm__("r5");
 {
  register u8 *initial_text __asm__("r0")=panel+84;
  register u8 *widget_working __asm__("r1");
  register u8 *layout_working __asm__("r2");
  register PanelClearCallback *clear_slot __asm__("r2");
  snapshots.text=initial_text;
  __asm__("" : "+m"(snapshots.text));
  widget_working=panel+40;
  __asm__("" : "+r"(widget_working));
  snapshots.widget=widget_working;
  layout_working=panel;
  __asm__("" : "+r"(layout_working));
  layout_working+=24;
  __asm__("" : "+r"(layout_working));
  snapshots.layout=layout_working;
  __asm__("" : "+m"(snapshots.layout));
  width_working=widget_working[18];
  __asm__("" : "+r"(width_working));
  width=width_working;
  __asm__("" : "+r"(width));
  clear_slot=&gPanelClearCallback;
  __asm__("" : "+r"(clear_slot));
  initial_text+=104;
  __asm__("" : "+r"(initial_text));
  {
   register u8 *clear_destination __asm__("r0")=PTR(initial_text,0);
   __asm__("" : "+r"(clear_destination));
   InvokePanelClear(clear_destination,468,*clear_slot);
  }
 }
 text_cursor=gPanelTileManager.tiles+32*(u16)GetPanelTextTile(snapshots.text,0);
 __asm__("" : "+r"(text_cursor));
 {
 register u8 *header_text __asm__("r6")=snapshots.text;
 register u32 header_one __asm__("r4");
 __asm__("" : "+r"(header_text));
 ClearPanelText(text_cursor,2*header_text[21]);
 {
  register u8 *selection __asm__("r1")=PTR(panel,4);
  register u32 index_working __asm__("r0");
  register u8 *table __asm__("r1");
  register u32 table_offset __asm__("r2");
  __asm__("" : "+r"(selection));
  index_working=HALF(selection,106);
  __asm__("" : "+r"(index_working));
  index_working=(index_working+selection[129])<<16;
  __asm__("" : "+r"(index_working));
  table=PTR(panel,0);
  __asm__("" : "+r"(table));
  index_working>>=14;
  __asm__("" : "+r"(index_working));
  table_offset=0x424;
  __asm__("" : "+r"(table_offset));
  table+=table_offset;
  __asm__("" : "+r"(table));
  table+=index_working;
  __asm__("" : "+r"(table));
  selected=PTR(table,0);
 }
 PTR(panel,184)=selected;
 {
  register const u8 *label __asm__("r2")=gSelectedRecordLabels[ResolveSelectedRecordLabel(HALF(selected,0),0)];
  __asm__("" : "+r"(label));
  {
   register u8 *owner_text __asm__("r0")=PTR(panel,0)+20;
   __asm__("" : "+r"(owner_text));
   header_one=1;
   __asm__("" : "+r"(header_one));
   RenderPanelText(owner_text,text_cursor,label,5,header_one);
  }
 }
 {
  register u32 header_x __asm__("r1")=width+1;
  register u32 header_tile __asm__("r2")=HALF(header_text,28);
  register u32 header_width __asm__("r3")=width;
  __asm__("" : "+r"(header_x), "+r"(header_tile), "+r"(header_width));
  __asm__ volatile(
   "ldr r6,%5\n\t"
   "ldrb r0,[r6,#2]\n\t"
   "str r0,[sp,#0]\n\t"
   "mov r0,#0\n\t"
   "str r0,[sp,#4]\n\t"
   "str %4,[sp,#8]\n\t"
   "ldr r0,%6\n\t"
   "bl DrawPanelTextTiles"
   : "+r"(header_x), "+r"(header_tile), "+r"(header_width), "=m"(snapshots.outgoing_extra)
   : "r"(header_one), "m"(snapshots.layout), "m"(snapshots.text)
   : "r0", "r6", "r12", "lr", "cc", "memory");
 }
 }
 snapshots.count=(u8)CollectPanelAbilityRows(HALF(selected,0),panel+156);
 pair_table=({
  register u32 descriptor_offset __asm__("r0")=HALF(selected,0)<<5;
  register const u8 *descriptor_base __asm__("r1");
  register const struct PanelRecordDescriptor *descriptor __asm__("r0");
  register u32 table_id __asm__("r1");
  __asm__("" : "+r"(descriptor_offset));
  descriptor_base=(const u8*)gRecordPanelDescriptors;
  __asm__("" : "+r"(descriptor_base));
  descriptor=(const struct PanelRecordDescriptor*)(descriptor_offset+(u32)descriptor_base);
  __asm__("" : "+r"(descriptor));
  table_id=descriptor->pair_table;
  gRecordPanelPairs+20*table_id;
 });
 __asm__("" : "+r"(pair_table));
 snapshots.tile_base=({
  register u32 width_work __asm__("r1")=width;
  register u32 scaled __asm__("r0");
  register u8 *text_address __asm__("r2");
  register u32 base_tile __asm__("r2");
  __asm__("" : "+r"(width_work));
  scaled=width_work<<1;
  __asm__("" : "+r"(scaled));
  text_address=snapshots.text;
  __asm__("" : "+r"(text_address));
  base_tile=HALF(text_address,28);
  __asm__("" : "+r"(base_tile));
  scaled+=base_tile;
  scaled;
 });
 row=0;
 do {
  register s32 next_row_work __asm__("r1");
  register s32 row_count_work __asm__("r2");
  register u32 row_width __asm__("r4")=width;
  __asm__("" : "+r"(row_width));
  text_cursor+=row_width*64;
  {
   register u8 *row_text __asm__("r6")=snapshots.text;
   __asm__("" : "+r"(row_text));
   ClearPanelText(text_cursor,2*row_text[21]);
  }
  snapshots.map_cell=({ register u8 **map_working __asm__("r0")=(u8 **)(panel+188); __asm__("" : "+r"(map_working)); map_working; });
  snapshots.double_width=row_width*2;
  next_row_work=row+1;
  __asm__("" : "+r"(next_row_work));
  snapshots.next_row=next_row_work;
  row_count_work=snapshots.count;
  __asm__("" : "+r"(row_count_work));
  if(row<row_count_work){
   register u8 *record __asm__("r2");
   u8 *slot;
   __asm__("lsl r0,%1,#3\n\tadd %0,%2,r0"
    : "=r"(record) : "r"(row), "r"(panel) : "r0", "cc");
   slot=record+164;
   if(*slot!=255){
    s32 pair;
    {
     register const u8 *const *labels __asm__("r1")=gSelectedAbilityLabels;
     register u32 id __asm__("r0");
     register const u8 *label __asm__("r2");
     register u8 *owner __asm__("r0");
     register u32 row_one __asm__("r6");
     __asm__("mov %0,%1\n\tadd %0,#160\n\tldrh %0,[%0]"
      : "=&r"(id) : "r"(record) : "cc", "memory");
     label=labels[id];
     owner=PTR(panel,0)+20;
     __asm__("mov %0,#1" : "=r"(row_one) : "r"(owner) : "cc");
     RenderPanelText(owner,text_cursor,label,5,row_one);
    }
    {
     register u32 row_x __asm__("r1");
     register u32 row_tile __asm__("r2");
     register u32 width_argument __asm__("r0");
     register u32 shifted_argument __asm__("r3");
     register u32 base_tile_work __asm__("r6");
     row_x=({
     register u32 x_working __asm__("r1")=width;
     register u32 row_stride __asm__("r0");
     row_stride=x_working<<2;
     x_working=row_stride+x_working;
     x_working+=1;
     row_stride*=row;
     x_working+=row_stride;
     x_working=(u16)x_working;
     x_working;
    });
     row_tile=({
     register u32 y_working __asm__("r2")=width;
     y_working*=row;
     y_working<<=1;
     base_tile_work=snapshots.tile_base;
     y_working=base_tile_work+y_working;
     y_working=(u16)y_working;
     y_working;
    });
     width_argument=width;
     /* R6 still carries the real base tile until the following ABI island
        overwrites it with layout. One tuple boundary avoids phantom span. */
     __asm__("" : "+r"(width_argument) : "r"(base_tile_work));
     shifted_argument=width_argument<<24;
     {
      /* Ordinary five-word calls reserve SP0. The named outgoing_extra
         object owns SP4/SP8; + pointer snapshots form the observed 52B frame.
         Gate checks actual placement before accepting any result. */
      __asm__ volatile(
       "ldr r6,%4\n\t"
       "ldrb r0,[r6,#2]\n\t"
       "str r0,[sp,#0]\n\t"
       "mov r0,#0\n\t"
       "str r0,[sp,#4]\n\t"
       "mov r0,#1\n\t"
       "str r0,[sp,#8]\n\t"
       "ldr r0,%5\n\t"
       "lsr %2,%2,#24\n\t"
       "bl DrawPanelTextTiles"
       : "+r"(row_x), "+r"(row_tile), "+r"(shifted_argument), "=m"(snapshots.outgoing_extra)
       : "m"(snapshots.layout), "m"(snapshots.text)
       : "r0", "r6", "r12", "lr", "cc", "memory");
     }
    }
    pair=0;
    {
    register s32 pair_count __asm__("r1");
    __asm__ volatile("mov %0,%1\n\tldrb %0,[%0]"
     : "=&r"(pair_count) : "r"(pair_table) : "memory");
    if(pair<pair_count){
     register u8 *slot_working __asm__("r3")=slot;
pair_again:
     {
      s32 pair_offset=pair*2;
      register const u8 *pair_base __asm__("r0")=pair_table;
      register const u8 *candidate __asm__("r1");
      pair_base+=2;
      candidate=pair_base+pair_offset;
      if(*slot_working==*candidate){
       u32 kind=({
        register u32 ability_id __asm__("r1");
        __asm__("ldrb %0,%1" : "=r"(ability_id) : "m"(*candidate));
        (u8)ResolvePanelAbilityKind(ability_id,ability_id,1);
       });
       u8 *value=ResolvePanelAbilityValue(kind,({
        register const u8 *value_address __asm__("r1")=pair_table+3;
        value_address+=pair_offset;
        *value_address;
       }));
       register u8 *destination __asm__("r5")=({
        register u32 row_units __asm__("r0")=(row<<2)+8;
        register u32 product __asm__("r1");
        register u32 byte_count __asm__("r0");
        register u8 **map_address __asm__("r2");
        register u8 *map_base __asm__("r1");
        product=width;
        product*=row_units;
        byte_count=product;
        byte_count<<=1;
        map_address=snapshots.map_cell;
        map_base=*map_address;
        map_base+byte_count;
       });
       u32 displayed;
       {
        register u8 *run __asm__("r6")=destination+12;
        DrawPanelTileRun(run,0x24f,15,2);
       }
       displayed=10*value[7];
       if(displayed>999)displayed=999;
       DrawPanelDecimal(destination+16,3,displayed);
       goto row_complete;
      }
      {
       register s32 back_count __asm__("r4");
       ++pair;
       __asm__ volatile("mov %0,%1\n\tldrb %0,[%0]"
        : "=&r"(back_count) : "r"(pair_table) : "memory");
       if(pair<back_count)goto pair_again;
      }
     }
    }
    }
   }
  }
row_complete:
  row=snapshots.next_row;
 }while(row<=2);
 first_run=({
  register u32 byte_offset __asm__("r1")=snapshots.double_width+width;
  register u8 **map_address __asm__("r6");
  register u8 *base __asm__("r0");
  __asm__("" : "+r"(byte_offset));
  byte_offset<<=1;
  __asm__("" : "+r"(byte_offset));
  map_address=snapshots.map_cell;
  __asm__("" : "+r"(map_address));
  base=*map_address;
  __asm__("" : "+r"(base));
  base+=byte_offset;
  __asm__("" : "+r"(base));
  base+14;
 });
 __asm__("" : "+r"(first_run));
 InvokePanelClear(first_run,6,gPanelClearCallback);
 second_run=({
  register u32 copy_offset __asm__("r0")=snapshots.double_width;
  __asm__("" : "+r"(copy_offset));
  first_run+copy_offset;
 });
 __asm__("" : "+r"(second_run));
 InvokePanelClear(second_run,10,gPanelClearCallback);
 if(({
  register s32 live_count __asm__("r1")=snapshots.count;
  __asm__("" : "+r"(live_count));
  live_count;
 })!=0){
  register const u8 *id_pair __asm__("r2")=pair_table;
  register u32 id __asm__("r1");
  u32 kind;
  register const u8 *value_pair __asm__("r4");
  register u8 *value __asm__("r4");
  __asm__("" : "+r"(id_pair));
  id=id_pair[2];
  __asm__("" : "+r"(id));
  kind=(u8)ResolvePanelAbilityKind(id,id,1);
  value_pair=pair_table;
  __asm__("" : "+r"(value_pair));
  value=ResolvePanelAbilityValue(kind,value_pair[3]);
  __asm__("" : "+r"(value));
  {
  u32 second_tag;
  switch(value[6]){
  case 2:
   DrawPanelTileRun(first_run,0x238,13,2);
   second_tag=0x23a;
   goto draw_second_run;
  case 3:
   DrawPanelTileRun(first_run,0x23f,13,3);
   second_tag=0x242;
   goto draw_second_run;
  case 5:
   DrawPanelTileRun(first_run,0x247,13,3);
   second_tag=0x24a;
draw_second_run:
   DrawPanelTileRun(second_run,second_tag,13,5);
   break;
icon_sentinel:
   panel[15]=0;
   goto icons_complete;
  case 1:
   DrawPanelTileRun(first_run,0x230,13,3);
   DrawPanelTileRun(second_run,0x233,13,5);
   break;
  }
  }
 }
 {
  register u8 **map_address __asm__("r6")=snapshots.map_cell;
  register u8 *map __asm__("r1");
  register u8 *widget_read __asm__("r0");
  register u32 first __asm__("r2");
  register u32 second __asm__("r3");
  __asm__("" : "+r"(map_address));
  map=*map_address;
  __asm__("" : "+r"(map));
  widget_read=snapshots.widget;
  __asm__("" : "+r"(widget_read));
  first=widget_read[16];
  second=widget_read[17];
  /* Full five-word ABI tail: actual byte load, outgoing fifth word,
     fresh widget reload, Thumb call. All incoming values are captured. */
  __asm__ volatile(
   "ldrb %0,[%0,#19]\n\t"
   "str %0,[sp,#0]\n\t"
   "ldr %0,%4\n\t"
   "bl CommitPanelTiles"
   : "+r"(widget_read), "+r"(map), "+r"(first), "+r"(second)
   : "m"(snapshots.widget)
   : "r12", "lr", "cc", "memory");
 }
 }
 {
  register u32 byte_zero __asm__("r1")=0;
  register u32 half_zero __asm__("r0")=0;
  __asm__("" : "+r"(byte_zero), "+r"(half_zero));
  HALF(panel,10)=half_zero;
  panel[14]=byte_zero;
  panel[13]=byte_zero;
  panel[12]=byte_zero;
 }
 if(!(panel[9]&8)){
  register u8 *icon_text_working __asm__("r1");
  register u32 icon_widget_offset __asm__("r2");
  register u8 *icon_widget_working __asm__("r2");
  register u8 *icon_widget __asm__("r9");
  register u32 icon_width __asm__("r6");
  s32 icon_row;
  u32 raw_count;
  icon_text_working=panel+84;
  __asm__("" : "+r"(icon_text_working));
  snapshots.icon_text=icon_text_working;
  icon_widget_offset=40;
  __asm__("" : "+r"(icon_widget_offset));
  icon_widget_working=(u8 *)(icon_widget_offset+(u32)panel);
  __asm__("" : "+r"(icon_widget_working));
  icon_widget=icon_widget_working;
  __asm__("" : "+r"(icon_widget));
  icon_width=icon_widget_working[18];
  __asm__("" : "+r"(icon_width));
  HALF(panel,10)=1;
  {
   register u32 selected_id __asm__("r0")=HALF(PTR(panel,184),0);
   __asm__("" : "+r"(selected_id));
   icon_text_working+=72;
   __asm__("" : "+r"(icon_text_working));
   raw_count=CollectPanelAbilityRows(selected_id,icon_text_working);
  }
  panel[15]=raw_count;
  icon_row=0;
  if(icon_row<(s32)raw_count){
   register u8 *staging_working __asm__("r4")=gAbilityIconStaging;
   register u8 *staging __asm__("r10");
   __asm__("" : "+r"(staging_working));
   staging=staging_working;
   __asm__("" : "+r"(staging));
   snapshots.shifted_width=icon_width<<24;
icon_again:
   {
    register s32 row_offset __asm__("r1")=8*icon_row;
    register u32 tile __asm__("r8");
    register u8 *slot __asm__("r4");
    register u32 variant __asm__("r0");
    __asm__("" : "+r"(row_offset));
    tile=(u16)(row_offset+0x251);
    __asm__("" : "+r"(tile));
    slot=({
     register u8 *selection_address __asm__("r0")=panel;
     register u32 selected_offset __asm__("r0");
     register u8 *slot_base __asm__("r1");
     __asm__("" : "+r"(selection_address));
     selection_address+=12;
     __asm__("" : "+r"(selection_address));
     selection_address+=icon_row;
     __asm__("" : "+r"(selection_address));
     selected_offset=*selection_address;
     __asm__("" : "+r"(selected_offset));
     selected_offset+=row_offset;
     __asm__("" : "+r"(selected_offset));
     slot_base=panel;
     __asm__("" : "+r"(slot_base));
     slot_base+=164;
     __asm__("" : "+r"(slot_base));
     slot_base+selected_offset;
    });
    __asm__("" : "+r"(slot));
    if(*slot!=255){
    StagePanelAbilityIcon(staging,*slot);
    CopyPanelAbilityIcon(staging,gPanelTileManager.tiles+32*tile,128);
    variant=(u8)ResolvePanelAbilityVariant(*slot);
    {
     register u32 icon_x __asm__("r1")=icon_width<<3;
     register u32 row_stride __asm__("r2");
     __asm__("" : "+r"(variant), "+r"(icon_x));
     icon_x-=icon_width;
     __asm__("" : "+r"(icon_x));
     icon_x+=1;
     __asm__("" : "+r"(icon_x));
     row_stride=icon_width<<2;
     __asm__("" : "+r"(row_stride));
     row_stride*=icon_row;
     __asm__("" : "+r"(row_stride));
     icon_x+=row_stride;
     __asm__("" : "+r"(icon_x));
     icon_x=(u16)icon_x;
     __asm__("" : "+r"(icon_x));
     __asm__ volatile(
      "mov r2,#4\n\t"
      "str r2,[sp,#0]\n\t"
      "str %0,[sp,#4]\n\t"
      "mov %0,#0\n\t"
      "str %0,[sp,#8]\n\t"
      "ldr %0,%4\n\t"
      "mov r2,%3\n\t"
      "ldr r4,%5\n\t"
      "lsr r3,r4,#24\n\t"
      "bl DrawPanelTextTiles"
      : "+r"(variant), "+r"(icon_x), "=m"(snapshots.outgoing_extra)
      : "r"(tile), "m"(snapshots.icon_text), "m"(snapshots.shifted_width)
      : "r2", "r3", "r4", "r12", "lr", "cc", "memory");
    }
    {
     register u32 live_count __asm__("r0");
     ++icon_row;
     live_count=panel[15];
     __asm__("" : "+r"(live_count));
     if(icon_row<(s32)live_count)goto icon_again;
    }
    }else goto icon_sentinel;
   }
  }
icons_complete:
  if(panel[15]!=0){
   register u8 **map_address __asm__("r2")=snapshots.map_cell;
   register u8 *map __asm__("r1");
   register u8 *widget_read __asm__("r4");
   __asm__("" : "+r"(map_address));
   map=*map_address;
   __asm__("" : "+r"(map));
   widget_read=icon_widget;
   __asm__("" : "+r"(widget_read));
   CommitPanelTiles(icon_widget,map,widget_read[16],widget_read[17],widget_read[19]);
  }
 }
}
