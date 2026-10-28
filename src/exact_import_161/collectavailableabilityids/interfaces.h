#ifndef AVAILABLE_ABILITY_INTERFACES_H
#define AVAILABLE_ABILITY_INTERFACES_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u8 before_list_modes[53]; u8 list_modes[3]; } AbilityUnit;
typedef struct { u32 unknown; u16 ability; u8 kind; u8 tail; } AbilityListRecord;
extern u32 UnitAbilityCollectionBlocked(AbilityUnit *unit);
extern AbilityListRecord *ReadUnitAbilityList(AbilityUnit *unit, u8 selector, u8 *first, u8 *last);
extern u32 UnitUsesInventoryAbilityMapping(AbilityUnit *unit);
extern u32 ReadAbilityInventoryItem(u8 index);
extern u32 HasAbilityInventoryItem(u16 item);
extern u32 IsUnitAbilityListEntryAvailable(AbilityUnit *unit, u8 index);
extern u32 AbilityOutputContains(u16 ability, u16 *output, u32 count);
extern u32 CanUseAbilityInCollectionMode(AbilityUnit *unit, u16 ability, s8 mode);
typedef char list_record_stride_is_eight[(sizeof(AbilityListRecord)==8)?1:-1];
asm(
    ".global UnitAbilityCollectionBlocked\n.thumb_set UnitAbilityCollectionBlocked,0x080c8299\n"
    ".global ReadUnitAbilityList\n.thumb_set ReadUnitAbilityList,0x080cce61\n"
    ".global UnitUsesInventoryAbilityMapping\n.thumb_set UnitUsesInventoryAbilityMapping,0x08133bc5\n"
    ".global ReadAbilityInventoryItem\n.thumb_set ReadAbilityInventoryItem,0x080cb389\n"
    ".global HasAbilityInventoryItem\n.thumb_set HasAbilityInventoryItem,0x080cb2b5\n"
    ".global IsUnitAbilityListEntryAvailable\n.thumb_set IsUnitAbilityListEntryAvailable,0x080cd561\n"
    ".global AbilityOutputContains\n.thumb_set AbilityOutputContains,0x08133f49\n"
    ".global CanUseAbilityInCollectionMode\n.thumb_set CanUseAbilityInCollectionMode,0x08133e19\n"
);
#endif
