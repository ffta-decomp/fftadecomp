typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct EffectContext {
 void *actor; void *previous; void *affected;
 u16 action; u16 item; u8 unknown10[22];
 u16 flags; u8 amount_index; u8 unknown29[7]; u8 *descriptor;
} EffectContext;
typedef struct EffectDescriptor {
 void (*apply)(EffectContext *); u32 field04; s8 metadata; u8 unknown09[3];
} EffectDescriptor;
u32 Compatible(void *,u32) __asm__("EffectResolutionCall_08133A58");
u32 GetKind(void) __asm__("RetailCall_0812f358");
void ApplyEffect(u32,void *) __asm__("EffectApplicationCall_08131C28");
void NotifyItem(u32,u32,void *) __asm__("RetailCall_08130688");
void Normalize(void *) __asm__("RetailCall_08131c58");
void Refresh(void *) __asm__("UnitModelCall_CA2E8");

/* Shared fixed-address battle transaction object, not an entry ABI. */
extern EffectContext BattleEffectContext __asm__("0x0200f3f0");

/* GNU trailing-array view: base32 and signed halfword stride are proven;
 * no total slot capacity is asserted or used in sizeof/allocation. */
typedef struct { u8 prefix[32]; s16 selected_amount[0]; } AmountView;
