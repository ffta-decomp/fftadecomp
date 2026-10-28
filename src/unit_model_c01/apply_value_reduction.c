/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct UnitValues {
    u8 prefix[24];
    u16 current_first;
    u16 maximum_first;
    u16 current_second;
    u16 maximum_second;
    u16 value_32;
    u16 value_34;
    u16 value_36;
    u16 value_38;
    u8 remaining[170];
    s16 value_210;
} UnitValues;
typedef struct RuleDescriptor {
    u8 prefix[2];
    u8 divisor_selector : 3;
    u8 remaining_bits : 5;
} __attribute__((packed)) RuleDescriptor;
typedef char DescriptorByteSize[sizeof(RuleDescriptor) == 3 ? 1 : -1];
typedef struct ReductionContext {
    u8 prefix[8];
    UnitValues *unit;
    const RuleDescriptor *descriptor;
} ReductionContext;
#define OFFSET(T, M) ((u32)&(((T *)0)->M))
typedef char UnitMaximumOffset[OFFSET(UnitValues, maximum_first) == 26 ? 1 : -1];
typedef char UnitSecondOffset[OFFSET(UnitValues, maximum_second) == 30 ? 1 : -1];
typedef char UnitLastStatOffset[OFFSET(UnitValues, value_38) == 38 ? 1 : -1];
typedef char UnitSignedOffset[OFFSET(UnitValues, value_210) == 210 ? 1 : -1];
typedef char ContextUnitOffset[OFFSET(ReductionContext, unit) == 8 ? 1 : -1];
typedef char ContextDescriptorOffset[OFFSET(ReductionContext, descriptor) == 12 ? 1 : -1];
extern const u8 UnitReductionDivisors[8];
extern u32 GetUnitProperty(const void *, u8);
extern u32 DivideUnsigned(u32, u32);
extern s32 DivideSigned(s32, s32);
__asm__(".global UnitReductionDivisors\n.set UnitReductionDivisors, 0x083a8260");
__asm__(".global GetUnitProperty\n.thumb_set GetUnitProperty, 0x080c92f1");
__asm__(".global DivideUnsigned\n.thumb_set DivideUnsigned, 0x08142ab1");
__asm__(".global DivideSigned\n.thumb_set DivideSigned, 0x081426b9");


/* Apply one source-selected unit reduction; the return is only its low byte.
 * Quotients wrap to 16 bits before signed zero/upper-limit comparisons.
 * Unit field roles beyond the paired current/maximum relation are provisional. */
u8 ApplyUnitValueReduction(ReductionContext *context, u8 selection)
{
    UnitValues *unit = context->unit;
    s16 amount = 0;
    u8 divisor = UnitReductionDivisors[context->descriptor->divisor_selector];

    switch (selection) {
    case 0:
        amount = DivideUnsigned(GetUnitProperty(unit, 23), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->maximum_first <= amount)
            amount = unit->maximum_first - 1;
        unit->maximum_first -= amount;
        if (unit->current_first > unit->maximum_first)
            unit->current_first = unit->maximum_first;
        break;
    case 1:
        amount = DivideUnsigned(GetUnitProperty(unit, 24), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->maximum_second <= amount)
            amount = unit->maximum_second - 1;
        unit->maximum_second -= amount;
        if (unit->current_second > unit->maximum_second)
            unit->current_second = unit->maximum_second;
        break;
    case 2:
        amount = DivideUnsigned(GetUnitProperty(unit, 26), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->value_32 <= amount)
            amount = unit->value_32 - 1;
        unit->value_32 -= amount;
        break;
    case 3:
        amount = DivideUnsigned(GetUnitProperty(unit, 27), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->value_34 <= amount)
            amount = unit->value_34 - 1;
        unit->value_34 -= amount;
        break;
    case 4:
        amount = DivideUnsigned(GetUnitProperty(unit, 28), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->value_36 <= amount)
            amount = unit->value_36 - 1;
        unit->value_36 -= amount;
        break;
    case 5:
        amount = DivideUnsigned(GetUnitProperty(unit, 29), divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 99)
            amount = 99;
        if (unit->value_38 <= amount)
            amount = unit->value_38 - 1;
        unit->value_38 -= amount;
        break;
    case 6:
        amount = DivideSigned(10, divisor);
        if (amount == 0)
            amount = 1;
        else if (amount > 10)
            amount = 10;
        if (unit->value_210 - amount <= 10)
            amount = unit->value_210 - 10;
        unit->value_210 -= amount;
        break;
    }
    return amount;
}
