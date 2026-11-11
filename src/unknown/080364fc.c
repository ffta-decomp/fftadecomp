typedef unsigned char u8;
typedef unsigned int u32;

extern u32 SignedModulo(signed int dividend, signed int divisor);
extern u32 FindSceneSelectorFieldSlot(u32 selector_value);

/* Return a nonreserved selector value only when no field slot already uses it. */
u32 GetSceneSelectorValueIfUnused(u32 left_value, u32 right_value)
{
    u32 candidate = SignedModulo((signed int)(left_value + right_value), 31);
    u32 field_slot;

    if (candidate == 28 || candidate == 9) {
        return 0;
    }

    field_slot = FindSceneSelectorFieldSlot((u8)candidate);
    if (field_slot != 0xffffffff) {
        return 0;
    }
    return candidate;
}
