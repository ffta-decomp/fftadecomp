typedef unsigned char u8;
struct MissionRow {u8 id_low;u8 id_high;};
struct MissionRows {u8 prefix[32];struct MissionRow *rows[0];};
extern struct MissionRows *gMissionRows;
extern unsigned GetMenuMissionProperty(unsigned,unsigned);
extern unsigned GetMenuCategoryNibble(unsigned);
__asm__(".global gMissionRows\n.set gMissionRows,0x0200f44c\n.global GetMenuMissionProperty\n.thumb_set GetMenuMissionProperty,0x080ce4dd\n.global GetMenuCategoryNibble\n.thumb_set GetMenuCategoryNibble,0x080cb9cd");
unsigned QueryMissionRowCategory(void *ignored,unsigned index) {
 register struct MissionRow *row __asm__("r4")=gMissionRows->rows[index];
 __asm__("" : "+r"(row));
 {
 unsigned low=row->id_low;
 unsigned high=row->id_high;
 unsigned mask=3;
 unsigned id,category;
 register unsigned shifted __asm__("r0");
 __asm__("" : "+r"(low), "+r"(high), "+r"(mask));
 id=((high&mask)<<8)|low;
 shifted=GetMenuMissionProperty(id,2)<<24;
 __asm__("" : "+r"(shifted));
 category=(shifted+0x0f000000)>>24;
 low=row->id_low;high=row->id_high;
 __asm__("" : "+r"(low), "+r"(high));
 id=((high&mask)<<8)|low;
 __asm__("" : : "r"(mask));
 if(GetMenuMissionProperty(id,1)==1) category=6;
 return (u8)GetMenuCategoryNibble(category);
}
}
