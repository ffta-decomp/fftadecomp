#ifndef FFTA_BATTLE_RECORD_C03B_H
#define FFTA_BATTLE_RECORD_C03B_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern u32 RetailCall_0809d6bc(s32 coordinate_delta_x, s32 coordinate_delta_y);
extern u32 RetailCall_080b7dc8(u32 unit_address, u32 action_id,
                               u32 equipment_id, u32 zero);
extern u32 RetailCall_080a12fc(u32 scratch_address, u32 source_context,
                               u32 lookup_context, s32 source_x,
                               s32 source_y, s32 radius, u32 range,
                               u32 *context_output, u32 *value_output,
                               u32 record_payload_address, u32 mode_a,
                               u32 mode_b);
extern u32 RetailCall_0812ee98(u32 unit_address, u32 equipment_id);
extern u32 RetailCall_080a05c4(u32 source_context, const void *source_point,
                               const void *target_point,
                               u32 record_payload_address);
extern u32 RetailCall_08099c1c(u32 context_address, s32 coordinate_x,
                               s32 coordinate_y);
extern u32 RetailCall_08099d08(u32 lookup_context, u32 *context_list);
extern u32 RetailCall_08099d34(u32 lookup_context, u32 *context_list);
extern u32 RetailCall_080b7c50(u32 unit_address, u32 action_id,
                               u32 equipment_id, u32 zero);
extern u32 RetailCall_080c8280(u32 unit_address);
extern u32 RetailCall_080cdcec(u32 unit_address);
extern u32 RetailCall_08002804(void);
extern s32 RetailCall_08142950(s32 dividend, s32 divisor);
extern s32 RetailCall_080b4a1c(const void *coordinate_query,
                               s32 radius, s32 include_origin,
                               u32 coordinate_list);
extern u32 RetailCall_080b4c90(u32 source_unit, u32 target_unit,
                               u32 zero, u32 equipment_id);
extern u32 RetailCall_080c8298(u32 unit_address);
extern u32 RetailCall_0812e470(u32 unit_address);
extern void RetailCall_080a3778(u32 record_block, u32 lookup_context,
                                u32 flag);
extern void RetailCall_080a3848(u32 record_block, u32 lookup_context,
                                u32 flag);
extern u32 RetailCall_0801cc18(u32 coordinate_x, u32 coordinate_y);
extern u32 RetailCall_08099644(u32 lookup_context, s32 coordinate_x,
                               s32 coordinate_y);
extern void (* volatile gCopyRecordMemory)(void *destination,
                                            const void *source,
                                            u32 byte_count);

asm(".global RetailCall_0809d6bc\n.thumb_set RetailCall_0809d6bc, 0x809d6bd\n.global RetailCall_080b7dc8\n.thumb_set RetailCall_080b7dc8, 0x80b7dc9\n.global RetailCall_080a12fc\n.thumb_set RetailCall_080a12fc, 0x80a12fd\n.global RetailCall_0812ee98\n.thumb_set RetailCall_0812ee98, 0x812ee99\n.global RetailCall_080a05c4\n.thumb_set RetailCall_080a05c4, 0x80a05c5\n.global RetailCall_08099c1c\n.thumb_set RetailCall_08099c1c, 0x8099c1d\n.global RetailCall_08099d08\n.thumb_set RetailCall_08099d08, 0x8099d09\n.global RetailCall_08099d34\n.thumb_set RetailCall_08099d34, 0x8099d35\n.global RetailCall_080b7c50\n.thumb_set RetailCall_080b7c50, 0x80b7c51\n.global RetailCall_080c8280\n.thumb_set RetailCall_080c8280, 0x80c8281\n.global RetailCall_080cdcec\n.thumb_set RetailCall_080cdcec, 0x80cdced\n.global RetailCall_08002804\n.thumb_set RetailCall_08002804, 0x8002805\n.global RetailCall_08142950\n.thumb_set RetailCall_08142950, 0x8142951\n.global RetailCall_080b4a1c\n.thumb_set RetailCall_080b4a1c, 0x80b4a1d\n.global RetailCall_080b4c90\n.thumb_set RetailCall_080b4c90, 0x80b4c91\n.global RetailCall_080c8298\n.thumb_set RetailCall_080c8298, 0x80c8299\n.global RetailCall_0812e470\n.thumb_set RetailCall_0812e470, 0x812e471\n.global RetailCall_080a3778\n.thumb_set RetailCall_080a3778, 0x80a3779\n.global RetailCall_080a3848\n.thumb_set RetailCall_080a3848, 0x80a3849\n.global RetailCall_0801cc18\n.thumb_set RetailCall_0801cc18, 0x801cc19\n.global RetailCall_08099644\n.thumb_set RetailCall_08099644, 0x8099645\n.global _call_via_r3\n.thumb_set _call_via_r3, 0x08142251\n.global gCopyRecordMemory\n.set gCopyRecordMemory, 0x0836d4bc");

#endif


typedef struct UnitCoordinates {
    u8 unknown_0[246];
    u8 x, y, facing;
} UnitCoordinates;

typedef struct UnitContext {
    UnitCoordinates *unit;
} UnitContext;

typedef struct TargetRow {
    UnitContext *context;
    u8 unknown_4[40];
} TargetRow;

typedef struct TargetRecord {
    UnitContext *source;
    u16 flags;
    u8 unknown_6[2];
    s8 classification;
    u8 mode, x, y, result, unknown_13;
    u16 value, action, equipment;
    u16 point_x, point_height, point_y;
    u8 unknown_26[2];
    u8 marker;
    u8 unknown_29[675];
    u8 row_count;
} TargetRecord;

typedef struct CoordinateQuery {
    UnitCoordinates *unit;
    u8 unit_x, unit_y, requested_x, requested_y;
    u16 action, equipment;
} CoordinateQuery;

/* The consumer reads six bytes. The native producer preserves the unused
 * upper halfword of the second word while updating these packed fields. */
typedef struct TargetPoint {
    unsigned int x : 16;
    unsigned int height : 16;
    unsigned int y : 16;
    unsigned int unknown_6 : 16;
} TargetPoint;

typedef struct CandidateCoordinate {
    s8 x, y;
    u8 unknown_2[2];
} CandidateCoordinate;

typedef char TargetRowStride[(sizeof(TargetRow) == 44) ? 1 : -1];
typedef char TargetCountOffset[((u32)&((TargetRecord *)0)->row_count == 704) ? 1 : -1];
typedef char QuerySize[(sizeof(CoordinateQuery) == 12) ? 1 : -1];
typedef char PointSize[(sizeof(TargetPoint) == 8) ? 1 : -1];

#define READ_ROW_COUNT(record) ((record)->row_count)
#define RECORD_ROWS(record) ((TargetRow *)((u8 *)(record) + 32))
#define APPEND_ROW(record, target) do { \
    register u32 row_offset asm("r1") = READ_ROW_COUNT(record) * 44; \
    u8 *row_base; \
    asm("" : "+r"(row_offset)); \
    row_base = (u8 *)(record) + 32; \
    asm volatile ("" : "+r"(row_base)); \
    ((TargetRow *)(row_base + row_offset))->context = (target); \
    (record)->row_count = READ_ROW_COUNT(record) + 1; \
} while (0)

u32 ResolveActionTargets(TargetRecord *record,
    UnitContext *required_context, u32 lookup_context, UnitContext *source,
    u32 requested_x_word, u32 requested_y_word, u32 action_word,
    u32 equipment_word, u32 mode_word,
    UnitContext *override_context, const CandidateCoordinate *coordinates,
    u32 flag_word) asm("ActionDependency_000A39F8");

u32 ResolveActionTargets(TargetRecord *record,
    UnitContext *required_context, u32 lookup_context, UnitContext *source,
    u32 requested_x_word, u32 requested_y_word, u32 action_word,
    u32 equipment_word, u32 mode_word,
    UnitContext *override_context, const CandidateCoordinate *coordinates,
    u32 flag_word)
{
    CoordinateQuery query;
    u32 scratch[192];
    u32 mode3_context, mode3_value, selected_context_output, selected_value;
    TargetPoint source_point, target_point;
    u32 requested_x = (u8)requested_x_word;
    u32 requested_y = (u8)requested_y_word;
    register u32 action asm("r9") = (u16)action_word;
    u32 equipment = (u16)equipment_word;
    u32 mode = (u8)mode_word;
    u32 flag = (u8)flag_word;
    u32 original_action;
    u32 enable_second_processor = 1;
    s32 signed_requested_x, signed_requested_y;
    s32 requested_x_shift, requested_y_shift;
    s32 lookup_x_shift, lookup_y_shift;
    u16 flags;
    s32 index;

    asm("" : "+r"(action));
    original_action = action;
    if (action == 223)
        action = 0;
    requested_x_shift = (u32)requested_x << 24;
    signed_requested_x = requested_x_shift >> 24;
    requested_y_shift = (u32)requested_y << 24;
    signed_requested_y = requested_y_shift >> 24;
    record->source = source;
    record->action = action;
    record->equipment = equipment;
    record->x = signed_requested_x;
    record->y = signed_requested_y;
    record->mode = mode;
    record->marker = 255;

    lookup_y_shift = requested_y_shift;
    {
        register s32 phase_x_input asm("r8") = requested_x_shift;
        asm("" : "=r"(lookup_x_shift), "+g"(lookup_y_shift)
                : "0"(phase_x_input));
    }
    if (source) {
        UnitCoordinates *unit = source->unit;
        u32 unit_x = unit->x;
        register UnitCoordinates *facing_unit asm("r2") = unit;
        /* Separate actual facing root survives the coordinate comparisons. */
        asm("" : "+r"(facing_unit));
        if ((signed_requested_x == unit_x && signed_requested_y == unit->y)
            || mode == 12) {
            register UnitCoordinates *facing_read asm("r0") = facing_unit;
            /* Native facing load begins by copying the surviving R2 root to R0. */
            asm("" : "+r"(facing_read));
            record->classification = facing_read->facing;
        } else {
            record->classification = RetailCall_0809d6bc(
                (s8)(signed_requested_x - unit_x),
                (s8)(signed_requested_y - unit->y));
        }
    }
    flags = record->flags;
    if (flag)
        flags |= 16;
    record->flags = flags;

    if (mode == 12) {
        /* This branch deliberately appends a null source as well. */
        {
            register u32 row_offset asm("r1") = READ_ROW_COUNT(record) * 44;
            u8 *row_base;
            /* Native multiply is complete before materializing the +32 base. */
            asm("" : "+r"(row_offset));
            row_base = (u8 *)record + 32;
            asm volatile ("" : "+r"(row_base));
            ((TargetRow *)(row_base + row_offset))->context = source;
            record->row_count = READ_ROW_COUNT(record) + 1;
        }
        record->action = original_action;
        return 1;
    }
    if (mode == 3) {
        UnitContext *mode3_target;
        u32 radius = (u8)RetailCall_080b7dc8((u32)record->source->unit,
            action, equipment, 0);
        u32 found_context = RetailCall_08099644(lookup_context,
            lookup_x_shift >> 24, lookup_y_shift >> 24);
        u32 result;
        mode3_context = found_context;
        result = RetailCall_080a12fc((u32)scratch, (u32)source,
            found_context, (s8)source->unit->x, (s8)source->unit->y,
            (s8)radius, 1024, &mode3_context, &mode3_value,
            (u32)&record->point_x, 1, 0);
        record->value = mode3_value;
        record->result = result;
        mode3_target = (UnitContext *)mode3_context;
        if (mode3_target)
            APPEND_ROW(record, mode3_target);
        record->action = original_action;
        return 1;
    }

    {
        u32 tag = (u8)RetailCall_0812ee98((u32)source->unit, equipment);
        if (action == 0) {
            if (tag >= 13 && tag <= 14) {
                u32 radius = (u8)RetailCall_080b7dc8((u32)source->unit,
                    0, equipment, 0);
                UnitContext *found = (UnitContext *)RetailCall_08099644(
                    lookup_context, lookup_x_shift >> 24, lookup_y_shift >> 24);
                u32 result = RetailCall_080a12fc((u32)(scratch + 96),
                    (u32)source, (u32)found,
                    (s8)source->unit->x, (s8)source->unit->y,
                    (s8)radius, mode == 2 ? 2304 : 1024,
                    &selected_context_output, &selected_value,
                    (u32)&record->point_x, 0, mode == 2 ? 1 : 0);
                record->value = selected_value;
                record->result = result;
                if (mode != 2)
                    found = (UnitContext *)selected_context_output;
                if (override_context)
                    found = override_context;
                if (found)
                    APPEND_ROW(record, found);
                goto common_processors;
            }
            if (tag == 19) {
                UnitContext *projected_target;
                projected_target = (UnitContext *)RetailCall_08099644(lookup_context,
                    lookup_x_shift >> 24, lookup_y_shift >> 24);
                if (mode != 2) {
                    u8 *source_x_address = &source->unit->x;
                    s32 source_y = (s8)source->unit->y;
                    u32 projected_output = (u32)&record->point_x;
                    s32 source_x;
                    asm("" : "+r"(projected_output));
                    source_x = (s8)*source_x_address;
                    source_point.x = source_x * 32 + 16;
                    source_point.y = source_y * 32 + 16;
                    source_point.height =
                        (RetailCall_08099c1c((u32)source, source_x, source_y)
                            << 4) + 24;
                    target_point.x = projected_target->unit->x * 32 + 16;
                    target_point.y = projected_target->unit->y * 32 + 16;
                    target_point.height =
                        ((u8)RetailCall_0801cc18(projected_target->unit->x,
                                               projected_target->unit->y) << 4) + 24;
                    projected_target = (UnitContext *)RetailCall_080a05c4((u32)source,
                        &source_point, &target_point, projected_output);
                } else {
                    record->point_x = projected_target->unit->x * 32 + 16;
                    record->point_height =
                        ((u8)RetailCall_0801cc18(projected_target->unit->x,
                                               projected_target->unit->y) << 4) + 16;
                    record->point_y = projected_target->unit->y * 32 + 16;
                }
                if (projected_target)
                    APPEND_ROW(record, projected_target);
                goto common_processors;
            }
        }
    }

    if ((RetailCall_080b7c50((u32)source->unit, action, equipment, 0) & 15) == 4) {
        {
            UnitContext **first_cursor = (UnitContext **)(scratch + 96);
            s32 first_count;
            register s32 saved_first_count asm("r8");
            first_count = RetailCall_08099d08(lookup_context, (u32 *)first_cursor);
            saved_first_count = first_count;
            if (first_count > 0) {
                register u32 first_special_action asm("r10") = 301;
                register u8 *first_count_address asm("r6") = &record->row_count;
                register s32 remaining asm("r5") = saved_first_count;
                do {
                    if (action == first_special_action &&
                        (u8)RetailCall_080c8280((u32)(*first_cursor)->unit))
                        goto next_first_context;
                    if ((u8)RetailCall_080cdcec((u32)(*first_cursor)->unit))
                        goto next_first_context;
                    {
                        register u32 row_offset asm("r1") = *first_count_address * 44;
                        register u8 *row_base asm("r0") = (u8 *)record + 32;
                        ((TargetRow *)(row_base + row_offset))->context = *first_cursor;
                        *first_count_address = *first_count_address + 1;
                    }
next_first_context:
                    first_cursor++;
                } while (--remaining != 0);
            }
        }
        {
            UnitContext **second_cursor = (UnitContext **)(scratch + 96);
            register s32 second_count asm("r8") =
                RetailCall_08099d34(lookup_context, (u32 *)second_cursor);
            register s32 second_index asm("r5") = 0;
            if (second_index < second_count) {
                register u32 second_special_action asm("r10") = 301;
                register u8 *second_count_address asm("r6") = &record->row_count;
                do {
                    if (action == second_special_action &&
                        (u8)RetailCall_080c8280((u32)(*second_cursor)->unit))
                        goto next_second_context;
                    if ((u8)RetailCall_080cdcec((u32)(*second_cursor)->unit))
                        goto next_second_context;
                    {
                        register u32 row_offset asm("r1") = *second_count_address * 44;
                        register u8 *row_base asm("r0") = (u8 *)record + 32;
                        ((TargetRow *)(row_base + row_offset))->context = *second_cursor;
                        *second_count_address = *second_count_address + 1;
                    }
next_second_context:
                    second_cursor++;
                    second_index++;
                } while (second_index < second_count);
            }
        }
        if (action == 301) {
            s32 selected_row = RetailCall_08142950(
                (s16)RetailCall_08002804(), READ_ROW_COUNT(record));
            if (selected_row != 0)
                gCopyRecordMemory(RECORD_ROWS(record),
                    RECORD_ROWS(record) + selected_row, 44);
            record->row_count = 1;
        }
        goto common_processors;
    }

    {
        s32 query_count;
        UnitCoordinates *query_unit = source->unit;
        query.unit = query_unit;
        query.unit_x = query_unit->x;
        query.unit_y = query_unit->y;
        query.requested_x = requested_x;
        query.requested_y = requested_y;
        query.action = action;
        query.equipment = equipment;
        query_count = RetailCall_080b4a1c(&query, record->classification, 1,
                                        (u32)coordinates);
        if (query_count == 1)
            enable_second_processor = 0;
        if (mode == 2) {
            UnitContext *direct_target = (UnitContext *)RetailCall_08099644(
                lookup_context, lookup_x_shift >> 24, lookup_y_shift >> 24);
            s32 fallback_index;
            if (direct_target &&
                (u8)RetailCall_080b4c90((u32)source->unit,
                                      (u32)direct_target->unit, 0, equipment)) {
                APPEND_ROW(record, direct_target);
                goto common_processors;
            }
            fallback_index = 0;
            if (fallback_index < query_count) {
                register u8 *fallback_count_address asm("r6") = &record->row_count;
                const CandidateCoordinate *fallback_cursor = coordinates;
                do {
                    UnitContext *fallback_target = (UnitContext *)RetailCall_08099644(
                        lookup_context, fallback_cursor->x, fallback_cursor->y);
                    UnitContext *first_row;
                    if (!fallback_target)
                        goto next_fallback;
                    if ((u8)RetailCall_080c8298((u32)fallback_target->unit))
                        goto next_fallback;
                    if (action == 0 && override_context != fallback_target &&
                        (u8)RetailCall_0812e470((u32)fallback_target->unit) == 0)
                        goto next_fallback;
                    {
                        register u32 row_offset asm("r1") = *fallback_count_address * 44;
                        register u8 *row_base asm("r0") = (u8 *)record + 32;
                        ((TargetRow *)(row_base + row_offset))->context = fallback_target;
                        *fallback_count_address = *fallback_count_address + 1;
                    }
                    first_row = RECORD_ROWS(record)[0].context;
                    record->x = first_row->unit->x;
                    record->y = first_row->unit->y;
                    goto common_processors;
next_fallback:
                    fallback_cursor++;
                    fallback_index++;
                } while (fallback_index < query_count);
            }
        } else if (query_count > 0) {
            register u8 *all_count_address asm("r6") = &record->row_count;
            const CandidateCoordinate *all_cursor = coordinates;
            s32 remaining = query_count;
            do {
                UnitContext *admitted_target = (UnitContext *)RetailCall_08099644(
                    lookup_context, all_cursor->x, all_cursor->y);
                if (!admitted_target)
                    goto next_coordinate;
                if ((u8)RetailCall_080c8298((u32)admitted_target->unit))
                    goto next_coordinate;
                if (action == 0 && override_context != admitted_target &&
                    (u8)RetailCall_0812e470((u32)admitted_target->unit) == 0)
                    goto next_coordinate;
                {
                    register u32 row_offset asm("r1") = *all_count_address * 44;
                    register u8 *row_base asm("r0") = (u8 *)record + 32;
                    ((TargetRow *)(row_base + row_offset))->context = admitted_target;
                    *all_count_address = *all_count_address + 1;
                }
next_coordinate:
                all_cursor++;
            } while (--remaining != 0);
        }
    }

common_processors:
    /* The same live action gate controls both processors. */
    if (record->action != 0 && record->action != 301) {
        RetailCall_080a3778((u32)record, lookup_context, flag);
        if (mode != 9 && enable_second_processor)
            RetailCall_080a3848((u32)record, lookup_context, flag);
    }
    if (required_context && (mode == 4 || mode == 6)) {
        register s32 membership_sample asm("r0");
        TargetRow *row;
        if (*(volatile u8 *)&record->row_count == 0)
            return 0; /* This original exit deliberately leaves action normalized. */
        index = 0;
        membership_sample = *(volatile u8 *)&record->row_count;
        if (index < membership_sample) {
            s32 membership_count = membership_sample;
            row = RECORD_ROWS(record);
            do {
                if (row->context == required_context) {
                    record->action = original_action;
                    return 1;
                }
                row++;
                index++;
            } while (index < membership_count);
        }
        record->action = original_action;
        return 0;
    }
    record->action = original_action;
    return 1;
}

#undef APPEND_ROW
#undef RECORD_ROWS
