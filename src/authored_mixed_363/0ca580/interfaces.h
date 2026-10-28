typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u32 GetItemProperty(u16 item_id, u8 property);
struct UnitEquipmentValueView { u8 unknown_00[42]; u16 equipment[5]; u8 unknown_34[158]; u16 value_d2; };
typedef char EquipmentOffsetCheck[(unsigned int)&((struct UnitEquipmentValueView *)0)->equipment==42?1:-1];
typedef char ValueOffsetCheck[(unsigned int)&((struct UnitEquipmentValueView *)0)->value_d2==210?1:-1];
