#include "interfaces.h"
#define GLOBAL_CONTEXT (*(u8 **)0x0200f438)
#define CONTENT_WORDS ((const u8 *)0x08527244)
#define CONTENT_POINTERS ((const u8 *const *)0x085567f0)

#define UPDATE_MAXIMUM(number) \
    { \
        register const u8 *const *bank asm("r2") = CONTENT_POINTERS; \
        register const u8 *row asm("r0"); \
        register u32 index asm("r0"); \
        u16 metric; \
        asm("" : "+r"(bank)); \
        row = CONTENT_WORDS + 4 * (number); \
        asm("" : "+r"(row)); \
        index = row[0] | ((u32)row[1] << 8); \
        asm("" : "+r"(index)); \
        metric = (u16)ContentMetric(bank[index]); \
        if (metric > maximum) maximum = metric; \
    }

/* Each of the three input bytes owns a separate original branch and write path. */
void Source52_00026580(u8 *context)
{
    u8 scratch[4];
    u8 *terminal = context + 128;
    u32 cursor = 0;
    u32 maximum;
    u8 selected_index;
    u8 *selected;

    selected = *(u8 **)(GLOBAL_CONTEXT + 24);
    selected_index = (u8)GetSelectedIndex(selected);
    maximum = 6;
    CollectStageBytes((u16)(202 + (u8)selected_index), scratch);

    if (scratch[0] == 0) {
        *(u16 *)(terminal + 4) -= 1;
    } else {
        {
            register u8 *destination asm("r0") = GLOBAL_CONTEXT;
            register u32 type_offset asm("r3") = 1152;
            asm("" : "+r"(destination), "+r"(type_offset));
            destination += type_offset;
            asm("" : "+r"(destination));
            *destination = 13;
        }
        {
            u32 job_word = GetJobProperty(scratch[0], scratch[0], 12);
            (*(u32 **)(context + 148))[0] = job_word;
        }
        selected = *(u8 **)(GLOBAL_CONTEXT + 24);
        if ((u8)SelectedPredicateOne(selected) != 0 ||
            (u8)SelectedPredicateTwo(*(u8 **)(GLOBAL_CONTEXT + 24)) != 0)
            (*(u8 **)(context + 152))[0] = 0;
        UPDATE_MAXIMUM(({
            register const u32 *entries asm("r1") = *(u32 **)(context + 148);
            register u32 first_slot asm("r3");
            register u32 scaled_offset asm("r0");
            register const u32 *entry asm("r0");
            asm("" : "+r"(entries));
            first_slot = cursor;
            asm("" : "+r"(first_slot));
            scaled_offset = 4 * first_slot;
            asm("" : "+r"(scaled_offset));
            entry = (const u32 *)(scaled_offset + (u32)entries);
            asm("" : "+r"(entry));
            *entry;
        }));
        cursor = (u8)(cursor + 1);
    }

    if (scratch[1] == 0) {
        *(u16 *)(terminal + 4) -= 1;
    } else {
        {
            register u8 *destination asm("r0") = GLOBAL_CONTEXT;
            register u32 type_offset asm("r1") = 1152;
            asm("" : "+r"(destination), "+r"(type_offset));
            destination += type_offset;
            asm("" : "+r"(destination));
            destination += cursor;
            asm("" : "+r"(destination));
            *destination = 14;
        }
        {
            u32 job_word = GetJobProperty(scratch[1], scratch[1], 12);
            (*(u32 **)(context + 148))[cursor] = job_word;
        }
        selected = *(u8 **)(GLOBAL_CONTEXT + 24);
        if ((u8)SelectedPredicateOne(selected) != 0 ||
            (u8)SelectedPredicateTwo(*(u8 **)(GLOBAL_CONTEXT + 24)) != 0)
            (*(u8 **)(context + 152))[cursor] = 0;
        UPDATE_MAXIMUM((*(u32 **)(context + 148))[cursor]);
        cursor = (u8)(cursor + 1);
    }

    if (scratch[2] == 0) {
        *(u16 *)(terminal + 4) -= 1;
    } else {
        {
            register u8 *destination asm("r0") = GLOBAL_CONTEXT;
            register u32 type_offset asm("r3") = 1152;
            asm("" : "+r"(destination), "+r"(type_offset));
            destination += type_offset;
            asm("" : "+r"(destination));
            destination += cursor;
            asm("" : "+r"(destination));
            *destination = 15;
        }
        {
            u32 job_word = GetJobProperty(scratch[2], scratch[2], 12);
            (*(u32 **)(context + 148))[cursor] = job_word;
        }
        selected = *(u8 **)(GLOBAL_CONTEXT + 24);
        if ((u8)SelectedPredicateOne(selected) != 0 ||
            (u8)SelectedPredicateTwo(*(u8 **)(GLOBAL_CONTEXT + 24)) != 0)
            (*(u8 **)(context + 152))[cursor] = 0;
        UPDATE_MAXIMUM((*(u32 **)(context + 148))[cursor]);
    }

    {
        register u32 raw_count asm("r0") = *(u16 *)(terminal + 4) - 3;
        register u32 snapshot asm("r1");
        register u32 working_count asm("r2");
        asm("" : "+r"(raw_count));
        snapshot = raw_count;
        asm("" : "+r"(raw_count) : "r"(snapshot));
        *(u16 *)(terminal + 4) = raw_count;
        working_count = snapshot;
        asm("" : "+r"(working_count));
        terminal[3] = (u8)snapshot;
        if ((u16)raw_count <= 5) {
            register u32 spacing_delta asm("r0") = 2 * (6 - working_count);
            register u32 old_spacing asm("r3");
            asm("" : "+r"(spacing_delta));
            old_spacing = terminal[1];
            asm("" : "+r"(old_spacing));
            terminal[1] = (u8)(spacing_delta + old_spacing);
        }
    }
    {
        register u32 maximum_byte asm("r0") = maximum;
        asm("" : "+r"(maximum_byte));
        terminal[2] = (u8)maximum_byte;
    }
    {
        register u32 top asm("r0") = 28;
        register u32 maximum_snapshot asm("r1") = maximum;
        register u32 maximum_gate asm("r0");
        asm("" : "+r"(top), "+r"(maximum_snapshot));
        terminal[0] = (u8)(top - maximum_snapshot);
        maximum_gate = (u8)maximum_snapshot;
        asm("" : "+r"(maximum_gate));
        if (maximum_gate > 10) {
            register u32 increment asm("r0") = maximum + 245;
            u32 updated_byte;
            register u32 old_byte asm("r2");
            register u8 *read_context asm("r2");
            register u8 *write_context asm("r3");
            asm("" : "+r"(increment));
            read_context = context;
            asm("" : "+r"(read_context));
            old_byte = read_context[11];
            asm("" : "+r"(old_byte));
            updated_byte = increment + old_byte;
            write_context = context;
            asm("" : "+r"(write_context) : "r"(updated_byte));
            write_context[11] = (u8)updated_byte;
        } else
            terminal[9] &= 239;
    }
}
