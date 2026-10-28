/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct UnitTail { u8 mode; u8 category; u8 unknown; s8 amount; };
extern u8 UnitPredicate_000CDA4C(const void *unit);
extern u32 ReadUnitField(const void *unit, u8 selector);

asm(".global UnitPredicate_000CDA4C\n.thumb_set UnitPredicate_000CDA4C,0x080cda4d");
s32 CalculateUnitTailThresholdValue(const void *unit, u16 threshold)
{
    struct UnitTail *tail;
    int initial_magnitude;
    int current_magnitude;
    s16 signed_threshold;
    u32 factor;
    if (UnitPredicate_000CDA4C(unit))
        return 0;
    tail = (struct UnitTail *)ReadUnitField(unit, 68);
    initial_magnitude = tail->amount;
    if (initial_magnitude < 0)
        initial_magnitude = -initial_magnitude;
    signed_threshold = threshold;
    if (initial_magnitude >= signed_threshold || tail->mode == 2 || tail->category == 4)
        return 0;
    factor = ReadUnitField(unit, 20);
    current_magnitude = tail->amount;
    if (current_magnitude < 0)
        current_magnitude = -current_magnitude;
    /* The original wraps the product to signed19 bits before division by8. */
    return (s32)((u32)(signed_threshold - current_magnitude) * factor << 13) >> 16;
}
