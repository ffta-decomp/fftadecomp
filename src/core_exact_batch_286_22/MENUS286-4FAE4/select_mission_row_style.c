typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SelectedMission {u16 mission_id:10;u16 other_bits:6;} __attribute__((packed));
struct MissionListOwner {u8 prefix[0x424];struct SelectedMission *entries[0];};
struct MissionListContext {struct MissionListOwner *owner;};
extern u32 GetMissionProperty(u32,u32);
extern u32 MapMissionRowStyle(u32);
u8 SelectMissionRowStyle(struct MissionListContext *menu,u32 row)
{
 struct SelectedMission *selected=menu->owner->entries[row];
 register u32 category_bits asm("r0")=GetMissionProperty(selected->mission_id,2)<<24;
 u32 style;
 category_bits+=0x0f000000;
 asm("" : "+r" (category_bits));
 style=category_bits>>24;
 if(GetMissionProperty(selected->mission_id,1)==1)style=6;
 return MapMissionRowStyle(style);
}
asm(".global GetMissionProperty\n.thumb_set GetMissionProperty,0x080ce4dd\n.global MapMissionRowStyle\n.thumb_set MapMissionRowStyle,0x080cb9cd");
