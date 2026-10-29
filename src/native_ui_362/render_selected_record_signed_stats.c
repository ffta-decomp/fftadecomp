typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern const s8 gSelectedRecordStatTable[];
extern u32 ResolveSelectedRecordOrdinal(void*,s32);
extern const u8 *ResolveSelectedRecordControl(u32);
extern void DrawSelectedRecordStat(u32,u32,u32,u32);
__asm__(".global gSelectedRecordStatTable\n.set gSelectedRecordStatTable,0x0851d180\n"
".global ResolveSelectedRecordOrdinal\n.thumb_set ResolveSelectedRecordOrdinal,0x08017b69\n"
".global ResolveSelectedRecordControl\n.thumb_set ResolveSelectedRecordControl,0x08005bfd\n"
".global DrawSelectedRecordStat\n.thumb_set DrawSelectedRecordStat,0x080684b5");
void RenderSelectedRecordSignedStats(u8 *panel) __asm__("RemainingCore48_00068548");
void RenderSelectedRecordSignedStats(u8 *panel)
{
 register u8 *list_root __asm__("r4")=*(u8**)panel;
 register void *cursor __asm__("r0");
 register const u8 *row_address __asm__("r1");
 u32 ordinal;
 const u8 *selected;
 const s8 *stats;
 __asm__("" : "+r"(list_root));
 cursor=panel+80;
 __asm__("" : "+r"(cursor));
 row_address=panel+129;
 __asm__("" : "+r"(row_address));
 ordinal=ResolveSelectedRecordOrdinal(cursor,(s8)*row_address);
 {
  register u32 selected_offset __asm__("r0")=(u32)(u16)ordinal<<2;
  __asm__("" : "+r"(selected_offset));
  list_root+=0x424;
  __asm__("" : "+r"(list_root));
  list_root+=selected_offset;
  __asm__("" : "+r"(list_root));
  selected=*(u8**)list_root;
 }
 {
  register u32 record_offset __asm__("r0")=(u32)*(u16*)selected<<5;
  register const s8 *table __asm__("r1");
  __asm__("" : "+r"(record_offset));
  table=gSelectedRecordStatTable;
  __asm__("" : "+r"(table));
  stats=(const s8*)(record_offset+(u32)table);
 }
 DrawSelectedRecordStat(88,92,3,(u16)stats[16]);
 DrawSelectedRecordStat(88,104,3,(u16)stats[17]);
 DrawSelectedRecordStat(88,116,3,(u16)stats[18]);
 DrawSelectedRecordStat(88,128,3,(u16)stats[19]);
 DrawSelectedRecordStat(88,140,3,(u16)stats[20]);
 {
  register u32 flags __asm__("r1")=ResolveSelectedRecordControl(*(u32*)(panel+16))[9];
  __asm__("" : "+r"(flags));
  if((flags&1)==0){
   DrawSelectedRecordStat(168,88,1,(u16)stats[22]);
   DrawSelectedRecordStat(168,100,1,(u16)stats[23]);
   DrawSelectedRecordStat(216,100,2,(u16)stats[21]);
  }
 }
}
