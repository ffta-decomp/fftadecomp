/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ProgressChoiceRecord {
    u8 tag;
    u8 flags;
    u16 value;
};
struct ProgressChoiceContext {
    u8 prefix[0x11aa];
    u8 selected;
    u8 reserved[157];
    struct ProgressChoiceRecord *records[0];
};
extern struct ProgressChoiceContext *gProgressChoiceContext;
extern u8 GetGameFlag(u16 flag);
__asm__(".global gProgressChoiceContext\n.set gProgressChoiceContext, 0x0200f448");


/* Resolve the policy code from two selected records, the mode and flag0x202. */
u32 ResolveProgressChoiceCode(u8 mode)
{
    s32 index = 0;
    struct ProgressChoiceContext *context = gProgressChoiceContext;
    u32 selection_offset = context->selected * sizeof(struct ProgressChoiceRecord *);
    struct ProgressChoiceRecord **table = context->records;
    struct ProgressChoiceRecord **cursor;
    /* Preserve the retail Thumb ADD operand encoding at 0805D1D8. Both
     * pointer inputs are read before the output; only condition codes change.
     * The surrounding selection and policy remain ordinary C. */
    __asm__("add %0, %1, %2" : "=l" (cursor)
            : "l" (selection_offset), "l" (table) : "cc");

    do {
        struct ProgressChoiceRecord *record = *cursor;
        if (record != 0 && record->value != 0 && (record->flags & 1))
            return 84;
        ++cursor;
        ++index;
    } while (index <= 1);
    if (!GetGameFlag(0x202) && mode != 0)
        return 88;
    if (GetGameFlag(0x202) == 0)
        return 89;
    return 77;
}
