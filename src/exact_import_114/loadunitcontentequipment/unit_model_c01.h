#ifndef FFTA_UNIT_MODEL_C01_H
#define FFTA_UNIT_MODEL_C01_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

u32 GetItemProperty(u16 item_id, u8 property);
u32 SumEquippedItemProperty(const u8 *unit, u32 property);
u32 GetUnitProperty(const u8 *unit, u8 property);
u32 UnitStateE9HasBit0(const u8 *unit);
u32 UnitField27HasBit15(const u8 *unit);
u32 UnitField27HasBit13(const u8 *unit);
u32 ReadUnitField(const u8 *unit, u32 field_id);
u32 UnitField01Equals(const u8 *unit, u32 expected);
void UnitModelCall_CA2E8(u8 *unit);
u32 UnitModelCall_CA394(const u8 *unit);
u32 UnitModelCall_CA624(const u8 *unit, u32 include_equipment_raw);
u32 UnitModelCall_CA66C(const u8 *unit, u32 include_equipment_raw);
u32 UnitModelCall_CA6B4(const u8 *unit, u32 include_equipment_raw);
u32 UnitModelCall_CA6FC(const u8 *unit, u32 include_equipment_raw);
u32 UnitModelCall_CA4F0(const u8 *unit, u32 property);
void UnitModelExternalCall_CA900(u16 item_id, u32 mode);
void UnitModelExternalCall_CCF44(u8 *unit, u16 item_id);

u32 GetUnitEquippedStat20(const u8 *unit, u32 include_equipment_raw);
u32 GetUnitEquippedStat24(const u8 *unit, u32 include_equipment_raw);
u32 GetUnitEquippedStat22(const u8 *unit, u32 include_equipment_raw);
u32 GetUnitEquippedStat26(const u8 *unit, u32 include_equipment_raw);
u32 SelectUnitEquippedStat20Or24(const u8 *unit, u32 selector_raw,
                                u32 include_equipment_raw);
u32 SelectUnitEquippedStat22Or26(const u8 *unit, u32 selector_raw,
                                u32 include_equipment_raw);
u32 SelectUnitEquippedStat20Or24Capped(const u8 *unit, u32 selector_raw);
u32 SelectUnitEquippedStat22Or26Capped(const u8 *unit, u32 selector_raw);
u32 ReadUnitEquipmentValue16(const u8 *unit);
u32 ReadUnitEquipmentValue16Scaled10(const u8 *unit);
void UpdateUnitDerivedBytes(u8 *unit);
void ApplyUnitContentProperty33(u8 *unit);
void LoadUnitContentEquipment(u8 *unit, const u8 *content);

#endif
