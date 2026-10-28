typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef int s32;
struct ActionSelection { void *actor; void *target; void *affected; u8 unknown_0c[26]; u16 flags; };
typedef char FlagsOffset[((u32)&((struct ActionSelection *)0)->flags == 38) ? 1 : -1];
extern struct ActionSelection gActionSelection __asm__("0x0200f3f0");
extern s32 CollectEquipment(void *unit, u16 *equipment) __asm__("RetailCall_0812f0d8");
extern int UnitField19IsZero(const void *unit) __asm__("RetailCall_080c8280");
extern u32 GetAbilityProperty(u16 ability, u8 selector) __asm__("RetailCall_080ccd50");
extern void PrepareAction(u16 ability, u16 equipment, u8 mode) __asm__("RetailCall_0812f2a4");
extern void SelectSlot(u8 slot) __asm__("RetailCall_0812f328");
extern void SetAffected(void *unit) __asm__("RetailCall_0812f34c");
extern void SetSlotFlag(u32 slot) __asm__("RetailCall_0812f39c");
extern u8 CheckSlotPredicate(void) __asm__("RetailCall_08130fbc");
extern u8 CheckTargetPredicate(void) __asm__("RetailCall_08131378");

/* Check target eligibility and retain the first passing action slot. */
static inline u32 CalculateTargetEligibility(void *actor, void *target, u16 ability)
{
    u16 equipment[2];
    u16 first_equipment;
    struct ActionSelection *selection;
    s32 slot;

    if ((s16)CollectEquipment(actor, equipment) == 0)
        equipment[0] = 0;
    first_equipment = equipment[0];
    selection = &gActionSelection;
    if (ability == 0) {
        if (actor == target)
            return 0;
        return (u8)UnitField19IsZero(target) == 0;
    }
    if (GetAbilityProperty(ability, 11) == 0 && actor == target)
        return 0;
    PrepareAction(ability, first_equipment, 0);
    selection->actor = actor;
    selection->target = target;
    selection->flags |= 16;
    for (slot = 0; slot < 3; slot++) {
        SelectSlot(slot);
        SetAffected(0);
        if (CheckSlotPredicate() && CheckTargetPredicate()) {
            SetSlotFlag(slot);
            SetAffected(target);
            return 1;
        }
    }
    return 0;
}

u8 CoreRegion30_000C48A4(void *actor, void *target, u16 ability)
{
    register u32 result __asm__("r0") = CalculateTargetEligibility(actor, target, ability);

    /* Original shared tail normalizes the completed value in R0. The input is
     * fully defined by C; the instruction-free read/write constraint retains
     * the late fullword definition before the original low-byte conversion. */
    __asm__ volatile("" : "+r"(result));
    return (u8)result;
}
