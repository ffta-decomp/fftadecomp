typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct MissionRecord {
    u32 mission_id : 10;
    u32 definition_value16 : 8;
    u32 record_type : 3;
    u32 unknown02 : 3;
    u8 remaining[13];
} __attribute__((packed));
typedef char RecordStride[(sizeof(struct MissionRecord)==16)?1:-1];
extern u8 ReadMissionProgressFlag(u16 flag);
__asm__(".global ReadMissionProgressFlag\n.thumb_set ReadMissionProgressFlag,0x080c9541");

u32 SelectEligibleMissionRecords(struct MissionRecord *base, s32 input_count,
                                struct MissionRecord **output, u32 remaining)
    __asm__("OriginalGameplayDependency_000D2AD0");
u32 SelectEligibleMissionRecords(struct MissionRecord *base, s32 input_count,
                                struct MissionRecord **output, u32 remaining)
{
    struct MissionRecord *current = base;
    register u32 accepted asm("r8") = 0;
    register s32 initial_ordinal asm("r1");
    s32 ordinal;
    s32 tested_count;
    /* Original defines accepted R8=0 separately from stack ordinal. */
    asm("" : "+r"(accepted));
    initial_ordinal = 0;
    asm("" : "+r"(initial_ordinal));
    for (ordinal = initial_ordinal, tested_count = (s32)accepted;
         tested_count < input_count; tested_count = ++ordinal, ++current) {
        u32 eligible = 0;
        if (current->mission_id == 0)
            goto ordinal_latch;
        switch (current->mission_id) {
        case 365:
        case 368:
            goto append_record;
        case 371:
            if (!ReadMissionProgressFlag(54))
                break;
            goto append_record;
        case 366:
        case 367:
        case 369:
        case 370:
        case 372:
        case 373:
            if ((u16)(current->mission_id - 372) <= 1 &&
                !ReadMissionProgressFlag(54))
                break;
            if (ReadMissionProgressFlag(current->mission_id + 766))
                eligible = 1;
            if (ReadMissionProgressFlag(current->mission_id + 767))
                eligible = 1;
            break;
        }
        if (!eligible)
            goto ordinal_latch;
append_record:
        *output++ = current;
        {
            /* The original uses this initialized word first as increment 1,
             * then destructively subtracts 30 to obtain the byte mask 0xE3. */
            register u32 mark_bits asm("r1") = 1;
            u32 previous_flags;
            register struct MissionRecord *mark_root asm("r5");
            asm("" : "+r"(mark_bits));
            accepted += mark_bits;
            mark_root = base;
            asm("" : "+r"(mark_root) : "r"(base));
            previous_flags = *((u8 *)mark_root + 2);
            mark_bits -= 30;
            mark_bits &= previous_flags;
            mark_bits |= 4;
            *((u8 *)mark_root + 2) = (u8)mark_bits;
        }
        if (--remaining == 0)
            break;
ordinal_latch:
        /* Original reloads the initialized ordinal stack word at this latch.
         * A read/write memory identity preserves that actual scalar lifetime. */
        asm("" : "+m"(output), "+m"(ordinal));
    }
    return accepted;
}
