typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
struct UnitState;struct Item {u8 prefix[26],rules[3],tail[3];};extern const struct Item gItems[];
extern u8 CheckActionRule(const struct UnitState*,u16,u16);
__asm__(".global gItems\n.set gItems,0x0851D180");
__asm__(".global CheckActionRule\n.thumb_set CheckActionRule,0x0812CB65");
