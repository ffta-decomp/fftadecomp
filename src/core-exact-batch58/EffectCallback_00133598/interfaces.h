#ifndef FFTA_BATTLE_EFFECT_APPLICATION_11_H
#define FFTA_BATTLE_EFFECT_APPLICATION_11_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

/* Source-proven shared fields; these do not define the complete battle model.
 * Volatile accesses retain reloads after callbacks and opaque helper calls. */
typedef struct {
    void *actor;
    void *previous;
    void *affected;
    u16 action;
    u16 item;
    u8 reserved10[8];
    u16 result;
    u8 reserved1a[12];
    u16 flags;
    u8 amount_index;
    u8 reserved29[7];
    u8 *descriptor;
} ApplicationContext;
typedef struct {
    void (*apply)(volatile ApplicationContext *context);
    u32 field04;
    s8 metadata;
    u8 reserved09[3];
} ApplicationDescriptor;
#define ApplicationByte(object, offset) (*(volatile u8 *)((u8 *)(object) + (offset)))
#define ApplicationHalf(object, offset) (*(volatile u16 *)((u8 *)(object) + (offset)))
#define ApplicationWord(object, offset) (*(volatile u32 *)((u8 *)(object) + (offset)))
#define ApplicationAmount(context) (*(volatile s16 *)((u8 *)(context) + 32 + 2 * (context)->amount_index))
/* Runtime IWRAM copy/clear pointers are loaded on every call. */
#define ApplicationCopy(destination, source, count) \
    (*(void (**)(void *, const void *, u32))0x0836d4bc)((destination), (source), (count))
#define ApplicationClear(destination, count) \
    (*(void (**)(void *, u32))0x0836d4b8)((destination), (count))

u32 IP03_RandomWord(void);
void * RetailCall_08022840(u32 bytes);
void RetailCall_08022854(void *allocation);
void EffectApplicationCall_0802DA00(u32 choice);
void EffectApplicationCall_0802DC60(u32 owner, u32 value, u32 mode);
void * RetailCall_08096d7c(void);
void ResetBattleUnitTransientState(void *unit);
u32 EffectApplicationCall_08098E7C(void *state, void *actor, void *previous, void *reference, u8 *x, u8 *y);
void * RetailCall_08099560(void *state, void *unit);
u32 IP03_GetUnitName(void *unit, u32 property);
u32 RetailCall_080c8240(void *unit);
u32 EffectApplicationCall_080C832C(void *unit);
void SceneHelper_080C9574(u32 flag, u32 value);
u32 IP03_ReadProgressionField(u32 flag);
void UnitModelCall_CA2E8(void *unit);
u32 RetailCall_080ca900(u32 reference, u32 quantity);
u32 IT03_RemoveItem(u32 item, u32 quantity);
void ReplaceEquipmentSlotForScan(void *unit, u32 item, u32 slot);
void EquipmentScanMask81(void *unit, u32 mode);
u32 EquipmentProvidesAbility(void *unit, u32 slot);
void EffectApplicationCall_080CD364(void *unit, u32 slot);
void EffectApplicationCall_080CD544(void *unit, u32 slot);
void IP03_RefreshUnitAbility(void *unit, u32 slot);
u32 RetailCall_080cd8cc(void *unit);
u32 EffectResolutionCall_080CD8FC(void *unit);
u32 UnitStateEAHasBit5(void *unit);
void SetUnitStateE8Bit1(void *unit, u32 value);
void SetUnitStateE8Bit2(void *unit, u32 value);
void SetUnitStateE8Bit3(void *unit, u32 value);
void SetUnitStateE8Bit4(void *unit, u32 value);
void SetUnitStateE8Bit5(void *unit, u32 value);
void SetUnitStateE8Bit6(void *unit, u32 value);
void SetUnitStateE8Bit7(void *unit, u32 value);
void SetUnitStateE9Bit0(void *unit, u32 value);
void SetUnitStateE9Bit1(void *unit, u32 value);
void SetUnitStateE9Bit2(void *unit, u32 value);
void EffectApplicationCall_080CDE80(void *unit, u32 value);
void SetUnitStateE9Bit4(void *unit, u32 value);
void SetUnitStateE9Bit5(void *unit, u32 value);
void SetUnitStateE9Bit6(void *unit, u32 value);
void SetUnitStateE9Bit7(void *unit, u32 value);
void SetUnitStateEABit0(void *unit, u32 value);
void SetUnitStateECBit2(void *unit, u32 value);
void SetUnitStateECBit1(void *unit, u32 value);
void SetUnitStateEABit1(void *unit, u32 value);
void SetUnitStateEABit2(void *unit, u32 value);
void SetUnitStateEABit4(void *unit, u32 value);
void SetUnitStateEABit5(void *unit, u32 value);
void SetUnitStateEABit6(void *unit, u32 value);
void SetUnitStateEABit7(void *unit, u32 value);
void SetUnitStateEBBit0(void *unit, u32 value);
void SetUnitStateEBBit1(void *unit, u32 value);
void SetUnitStateEBBit2(void *unit, u32 value);
void SetUnitStateEBBit3(void *unit, u32 value);
void SetUnitStateEBBit4(void *unit, u32 value);
void SetUnitStateEBBit5(void *unit, u32 value);
void SetUnitStateEBBit6(void *unit, u32 value);
void SetUnitStateEBBit7(void *unit, u32 value);
void SetUnitStateECBit0(void *unit, u32 value);
void SetUnitStateEABit3(void *unit, u32 value);
void SetUnitStateECBit3(void *unit, u32 value);
void SetUnitStateECBit4(void *unit, u32 value);
void SetUnitStateECBit5(void *unit, u32 value);
void SetUnitStateECBit6(void *unit, u32 value);
void SetUnitStateECBit7(void *unit, u32 value);
void SetUnitStateEDBit0(void *unit, u32 value);
void SetUnitStateEDBit1(void *unit, u32 value);
void SetUnitStateEDBit2(void *unit, u32 value);
void SetUnitStateEDBit3(void *unit, u32 value);
void EffectApplicationCall_080CE314(void *unit, u32 value);
u32 ReadUnitCounterDA(void *unit);
u32 ReadUnitCounterDB(void *unit);
void WriteUnitCounterD9(void *unit, u32 value);
void WriteUnitCounterDA(void *unit, u32 value);
void WriteUnitCounterDB(void *unit, u32 value);
void WriteUnitCounterDC(void *unit, u32 value);
void WriteUnitCounterDD(void *unit, u32 value);
void WriteUnitCounterDE(void *unit, u32 value);
void WriteUnitCounterDF(void *unit, u32 value);
void WriteUnitCounterE0(void *unit, u32 value);
void WriteUnitCounterE1(void *unit, u32 value);
void WriteUnitCounterE2(void *unit, u32 value);
void WriteUnitCounterE3(void *unit, u32 value);
void WriteUnitCounterE4(void *unit, u32 value);
void WriteUnitCounterE5(void *unit, u32 value);
void WriteUnitCounterE6(void *unit, u32 value);
u32 EffectApplicationCall_0812D660(void *actor, void *affected, u32 mode, s16 *effect);
u32 EffectApplicationCall_0812D7FC(void *actor, void *affected, u32 mode, s16 *effect);
void EffectApplicationCall_0812EBD0(u32 reference, void *unit);
u32 EffectApplicationCall_0812EDF0(void *unit);
u32 EffectResolutionCall_0812F008(void *actor, void *affected, u32 code);
u32 RetailCall_0812f0cc(void *unit, u16 *equipment);
u32 EffectResolutionCall_0812F124(void *unit);
u32 RetailCall_0812f358(void);
void RetailCall_08130688(u32 item, u32 action, void *unit);
u32 RetailCall_08131b20(void);
u32 EffectApplicationCall_08131BB8(void *unit);
void EffectApplicationCall_08131C28(u32 effect, void *unit);
void RetailCall_08131c58(void *unit);
void EffectApplicationCall_08131DD4(volatile ApplicationContext *context, u32 effect);
void EffectApplicationCall_081320E8(volatile ApplicationContext *context);
void EffectApplicationCall_08132160(volatile ApplicationContext *context);
void EffectApplicationCall_081321B4(volatile ApplicationContext *context);
void EffectApplicationCall_0813255C(volatile ApplicationContext *context);
u32 RetailCall_081329ec(void *unit);
u32 EffectApplicationCall_08132CB8(volatile ApplicationContext *context, u32 property);
void EffectApplicationCall_08132D84(void *records, u32 count, u32 stride);
u32 EffectApplicationCall_08132DDC(void *unit, void *ability);
u32 EffectApplicationCall_08132E2C(void *unit, void *abilities, u32 count, u32 *index);
void EffectApplicationCall_0813325C(volatile ApplicationContext *context);
u32 EffectResolutionCall_08133A58(void *unit, u32 effect);
u32 EffectApplicationCall_08133CC8(void *output, void *unit);
s32 IT03_SignedRemainder(s32 numerator, s32 denominator);

#endif
