typedef unsigned char u8;
typedef unsigned int u32;

struct UnitTypePrefix {
    u8 reserved_00[4];
    u8 type_code;
};

/* Type-code names remain unknown; this predicate gates actor counting. */
u32 TestUnitSpecialTypeGroup(const struct UnitTypePrefix *unit)
{
    u32 matched = 0;
    if (unit != 0) {
        register u32 loaded_type __asm__("r0") = unit->type_code;
        register u32 unit_type __asm__("r1") = loaded_type;
        /* Compare the initialized copy while retaining the original range value. */
        asm("" : "+r"(unit_type) : "r"(loaded_type));
        if (unit_type == 82 || unit_type == 84 || unit_type == 83 ||
            unit_type == 30 || unit_type == 31 ||
            (u8)(loaded_type - 57) <= 13)
            matched = 1;
    }
    return matched;
}
