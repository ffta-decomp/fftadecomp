#ifndef WORKER3_EFFECT_DIRECT_00132CB8_INTERFACES_H
#define WORKER3_EFFECT_DIRECT_00132CB8_INTERFACES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

u32 ReadUnitField(const u8 *unit, u32 selector);
u32 GetItemProperty(u16 item, u8 property);
u32 NextRandom15(void);
s32 SignedModulo(s32 dividend, s32 divisor);
void ReplaceEquipmentSlotForScan(u8 *unit, u32 item, u32 slot);
u32 ScanEquipmentMask81(u8 *unit, u32 mode);
u32 EffectDirect_00131BB8(const u8 *unit);
int RemoveInventoryItem(u16 item, u8 quantity);
int AddInventoryItem(u16 item, u8 quantity);
void UpdateUnitDerivedBytes(u8 *unit);

/* Link only to already recovered Thumb helpers; these emit no instructions. */
__asm__(".global ScanEquipmentMask81\n.thumb_set ScanEquipmentMask81, 0x080cb54d");
__asm__(".global EffectDirect_00131BB8\n.thumb_set EffectDirect_00131BB8, 0x08131bb9");
__asm__(".global RemoveInventoryItem\n.thumb_set RemoveInventoryItem, 0x080ca9e9");
__asm__(".global UpdateUnitDerivedBytes\n.thumb_set UpdateUnitDerivedBytes, 0x080ca2e9");

#endif
