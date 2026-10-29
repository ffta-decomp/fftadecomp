#include "interfaces.h"
extern u8 gInitialSaveImage[0x3ca8];
asm(".global gInitialSaveImage\n.set gInitialSaveImage,0x02000000\n");

#define GLOBAL_CONTEXT (*(u8 **)0x0200f438)
#define ABILITY_ROWS ((const u8 *)0x0855187c)
#define CONTENT_POINTERS ((const u8 *const *)0x085567f0)

/* Preserve the separate decisions and callback-visible loads for each row. */
void Source52_00026D44(StageContext *context, StageState *state)
{
    u8 *terminal = context->terminal_bytes;
    register int ordinal asm("r10");
    register u32 cursor asm("r9");
    register u8 *record asm("r5");
    const u8 *definition;
    u16 record_id;
    u8 measured;
    u16 content_index;
    u8 metric;
    u8 *selected;

    state->status = 0;
    ordinal = state->first_ordinal;
    asm("" : "+r"(ordinal));
    cursor = 0;
    asm("" : "+r"(cursor));
    while (ordinal <= state->last_ordinal) {
        {
            register int row_ordinal asm("r0") = ordinal;
            register u32 row_offset asm("r1");
            register u8 *row_base asm("r0");
            asm("" : "+r"(row_ordinal));
            row_offset = 8 * row_ordinal;
            asm("" : "+r"(row_offset));
            row_base = state->record_base;
            asm("" : "+r"(row_base) : "r"(row_offset));
            record = row_base + row_offset;
            asm("" : "+r"(record));
        }
        if (record[6] != 1 && record[6] != 4)
            goto next_record;
        selected = *(u8 **)(GLOBAL_CONTEXT + 24);
        if ((u8)QualifiesRecord(selected, (u8)ordinal) == 0)
            goto next_record;

        record_id = *(u16 *)(record + 4);
        {
            register const u8 *definition_work asm("r0") =
                (const u8 *)(28 * record_id + (u32)ABILITY_ROWS);
            asm("" : "+r"(definition_work));
            definition = definition_work;
        }
        context->stage_words[cursor] = ordinal;
        if ((u8)ReadSaveByte(13) == 1)
            goto save_mode_gate;

after_save_mode_gate:
        selected = *(u8 **)(GLOBAL_CONTEXT + 24);
        if ((u8)IsSelectedContextActive(selected) != 0 &&
            GetAbilityProperty(*(u16 *)(record + 4), 20) == 0) {
            if (definition[4] != 0) {
                measured = (u8)MeasureDefinitionValue(
                    *(u8 **)(GLOBAL_CONTEXT + 24), definition[4]);
                if (state->status <= 2)
                    state->status = 3;
                if (measured > 99)
                    state->status = 4;
            }
            context->stage_bytes[cursor] = 0;
            goto processed;
        }

        if (definition[4] != 0) {
            measured = (u8)MeasureDefinitionValue(
                *(u8 **)(GLOBAL_CONTEXT + 24), definition[4]);
            if (state->status <= 2)
                state->status = 3;
            if (measured > 99)
                state->status = 4;
            selected = *(u8 **)(GLOBAL_CONTEXT + 24);
            if (*(u16 *)(selected + 28) < measured)
                context->stage_bytes[cursor] = 0;
            goto processed;
        }

        selected = *(u8 **)(GLOBAL_CONTEXT + 24);
        if ((u8)SelectedContextCondition(selected) != 0 &&
            state->mode_marker == 21 && ordinal != 26) {
            context->stage_bytes[cursor] = 0;
            goto processed;
        }

        {
        register u32 raw_id asm("r0") = *(u16 *)(record + 4);
        register u32 gate_id asm("r1") = raw_id;
        register u32 normalized_id asm("r0");
        asm("" : "+r"(gate_id) : "r"(raw_id));
        if (gate_id == 217) {
            register u32 image_base asm("r0") = (u32)gInitialSaveImage;
            asm("" : "+r"(image_base));
            if (*(u32 *)(image_base + 0x1f64) <= 99) {
                context->stage_bytes[cursor] = 0;
                goto processed;
            }
        }
        normalized_id = (u16)gate_id;
        asm("" : "+r"(normalized_id));
        if ((normalized_id == 148 || normalized_id == 211) &&
            (u8)TestDefinitionClass() == 0) {
            context->stage_bytes[cursor] = 0;
            goto processed;
        }
        }
        {
        register u32 value_gate asm("r0") = *(u16 *)(record + 4);
        asm("" : "+r"(value_gate));
        if ((value_gate == 222 || value_gate == 124) &&
            (u8)TestDefinitionValue(
                *(u8 **)(GLOBAL_CONTEXT + 24), definition[5]) == 0) {
            context->stage_bytes[cursor] = 0;
            goto processed;
        }
        }
        {
        register u32 range_work asm("r0") = *(u16 *)(record + 4);
        asm("" : "+r"(range_work));
        if (range_work == 88) {
            if ((u8)TestDefinitionCode(*(u8 **)(GLOBAL_CONTEXT + 24)) != 0)
                context->stage_bytes[cursor] = 0;
            goto processed;
        }
        range_work -= 202;
        asm("" : "+r"(range_work));
        if ((u16)range_work <= 8 &&
            (u8)TestDefinitionRange(*(volatile u16 *)(record + 4)) == 0) {
            context->stage_bytes[cursor] = 0;
            goto processed;
        }
        }
        {
        register u32 context_gate asm("r0") = *(u16 *)(record + 4);
        asm("" : "+r"(context_gate));
        if (context_gate == 33 && (u8)TestSpecialContext(context) == 0) {
            /* Caller explicitly normalizes R0 into R1 before the shared store. */
            context->stage_bytes[cursor] = 0;
        }
        }

        goto processed;
save_mode_gate:
        if (GetAbilityProperty(*(u16 *)(record + 4), 31) != 0)
            goto after_save_mode_gate;
        context->stage_bytes[cursor] = 0;
processed:
        cursor++;
        {
            register const u8 *const *metric_bank asm("r1") = CONTENT_POINTERS;
            asm("" : "+r"(metric_bank));
            content_index = *(u16 *)definition;
            metric = (u8)MetricFromContent(metric_bank[content_index]);
        }
        if (metric > state->maximum_metric)
            state->maximum_metric = metric;
next_record:
        ordinal++;
    }
    if (state->status != 0)
        terminal[13] = 9;
    state->stage_count = (u8)cursor;
}
