typedef unsigned char u8;
typedef unsigned int u32;
struct UnitRecord {
    u8 unknown00[4];
    u8 occupied;
    u8 unknown05[259];
};
typedef void (*ClearMemory)(void *, u32);
extern void *AllocateRecordGroup(u32);
extern void InitializeRecordGroup(void *, struct UnitRecord **, int, u32);
asm(".global AllocateRecordGroup\n.thumb_set AllocateRecordGroup,0x08022841\n.global InitializeRecordGroup\n.thumb_set InitializeRecordGroup,0x080c62cd");

/* Placement callers supply twelve records, matching the original local list. */
void *CreatePlacementUnitRecordGroup(struct UnitRecord *units, int count)
{
    struct UnitRecord *selected[12];
    register int selected_count asm("r5");
    void *group;
    if (*(u8 *)0x030028a0 & 8) {
        selected_count = 0;
        asm("" : "+r"(selected_count));
        if (selected_count < count) {
            register struct UnitRecord *cursor asm("r2") = units;
            register struct UnitRecord **write asm("r3") = selected;
            register u32 stride asm("r6") = sizeof(struct UnitRecord);
            int remaining;
            asm("" : "+r"(cursor), "+r"(write), "+r"(stride));
            remaining = count;
            do {
                if (cursor->occupied != 0) {
                    *write++ = cursor;
                    ++selected_count;
                }
                cursor = (struct UnitRecord *)((u8 *)cursor + stride);
                --remaining;
            } while (remaining != 0);
        }
    } else {
        (*(ClearMemory *)0x0836d4b8)(units, (u32)count * 264);
        if (count > 0) {
            register struct UnitRecord *cursor asm("r0") = units;
            register struct UnitRecord **write asm("r2") = selected;
            register u32 stride asm("r3") = sizeof(struct UnitRecord);
            int remaining;
            asm("" : "+r"(cursor), "+r"(write), "+r"(stride));
            remaining = count;
            do {
                *write++ = cursor;
                cursor = (struct UnitRecord *)((u8 *)cursor + stride);
                --remaining;
            } while (remaining != 0);
        }
        selected_count = count;
    }
    group = AllocateRecordGroup(180);
    InitializeRecordGroup(group, selected, selected_count,
                          (*(u8 *)0x030028a0 >> 3) & 1);
    return group;
}
