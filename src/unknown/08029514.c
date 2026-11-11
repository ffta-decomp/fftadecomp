typedef unsigned char u8;
typedef unsigned short u16;
struct ManagedRecordPrefix {
    u16 halfword_at_00;
    u8 unknown_before_0e[12];
    u16 halfword_at_0e;
};

/* Broader field roles are unresolved; retain these two widths and their order. */
void SetManagedRecordHalfwords(void) __asm__("CoreFrontier_00029514");
void SetManagedRecordHalfwords(void)
{
    struct ManagedRecordPrefix *record = *(struct ManagedRecordPrefix **)0x0200f438;
    record->halfword_at_0e = 0;
    record->halfword_at_00 = 1;
}
