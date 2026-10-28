/* Original-only fixed-O2 reconstruction. Bounded MIXED address/width primitives
 * replace phantom-length observations; all phase CFG, calls and rules remain C.
 * Each .Lw6_85aa8_m148_* label marks a straight-line native primitive, never a
 * control-flow or literal-pool island. See the same-ID owned source-cause map. */
#include "interfaces.h"
extern u16 NativeInputWords_03000000[] asm("0x03000000");
extern u32 NativeMenuResourceRoot_03000E30[] asm("0x03000e30");
#define CTX (*(u8 **)0x03002818)
#define B(p,o) (*(u8 *)((u8 *)(p) + (o)))
#define H(p,o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p,o) (*(u32 *)((u8 *)(p) + (o)))

void CoreRegistration33_00085AA8(u32 unused, u8 *state_input)
{
    register u8 *state_byte asm("r8") = state_input;
    register s32 state asm("r6") = *state_byte;
    u8 *context;
    register u32 next_state asm("r0");
    register s32 scaled_halfword_value asm("r0");
    register u16 *scaled_halfword_target asm("r1");
    asm("" : "+r"(state_byte), "+r"(state));
    /* Terminal 255 is actually written by phase254 and is a no-op on reentry. */
    switch (state) {
    case 0: goto phase_0;
    case 2: return;
    case 3: goto phase_3;
    case 4: goto phase_4;
    case 5: goto phase_5;
    case 6: goto phase_6;
    case 7: goto phase_7;
    case 8: goto phase_8;
    case 9: goto phase_9;
    case 10: goto phase_10;
    case 11: goto phase_11;
    case 12: goto phase_12;
    case 13: goto phase_13;
    case 14: goto phase_14;
    case 15: goto phase_15;
    case 16: goto phase_16;
    case 17: goto phase_17;
    case 18: goto phase_18;
    case 19: goto phase_19;
    case 254: goto phase_254;
    case 255: return;
    default: return;
    }

phase_0: {
        register u8 **context_cell asm("r4");
        register u8 *initial_context asm("r0");
        register u32 initial_offset asm("r1");
        register u32 control_offset asm("r2");
        register u32 pair_offset asm("r3");
        register u32 second_pair_offset asm("r7");
        register u32 half_offset asm("r2");
        register u16 *half_address asm("r1");
        register u32 zero asm("r2");
        register u32 later_offset asm("r6");
        SceneTaskDependency_00141540(101);
        context_cell = (u8 **)0x03002818;
        asm("" : "+r"(context_cell));
        initial_context = (*context_cell);
        initial_offset = 0xbf5;
        asm("" : "+r"(initial_context), "+r"(initial_offset));
        B(initial_context, initial_offset) = 4;
        initial_context = (*context_cell);
        control_offset = 0x1d04;
        asm("" : "+r"(initial_context), "+r"(control_offset));
        B(initial_context, control_offset) = 6;
        initial_context = (*context_cell);
        pair_offset = 0x1258;
        asm("" : "+r"(initial_context), "+r"(pair_offset));
        B(initial_context, pair_offset) = state;
        initial_context = (*context_cell);
        second_pair_offset = 0x1259;
        asm("" : "+r"(initial_context), "+r"(second_pair_offset));
        B(initial_context, second_pair_offset) = state;
        initial_context = (*context_cell);
        half_offset = 0x126c;
        asm("" : "+r"(initial_context), "+r"(half_offset));
        half_address = (u16 *)(initial_context + half_offset);
        zero = 0;
        asm("" : "+r"(half_address), "+r"(zero));
        *half_address = state;
        pair_offset += 29;
        B(initial_context, pair_offset) = zero;
        CoreScene34_00080E00();
        CoreScene34_00085678(30);
        initial_context = *context_cell;
        later_offset = 0xbf5;
        asm("" : "+r"(initial_context), "+r"(later_offset));
        B(initial_context, later_offset) = 4;
        CoreRegion_00035578(0x0894ff54,
            ({ register u8 *resource_base asm("r1") = (u8 *)0x030009e0;
               second_pair_offset = 328;
               asm("" : "+r"(resource_base), "+r"(second_pair_offset));
               *(u32 *)(resource_base + second_pair_offset); }), 26, 50);
        {
            register u8 *copy_context asm("r1") = *context_cell;
            asm("" : "+r"(copy_context));
            CoreFrontier_001443FC(copy_context + 0x1be4,
                                 *(u8 **)(copy_context + 0x1d0c), 264);
        }
        {
            register u8 *job_context asm("r0") = *context_cell;
            register u8 selected_job asm("r1");
            asm("" : "+r"(job_context));
            selected_job = B(job_context, 0x1beb);
            asm("" : "+r"(job_context) : "r"(selected_job));
            ApplyUnitJobWithFlag(job_context + 0x1be4, selected_job);
        }
        CoreScene34_00080DB4((*context_cell) + 0x1be4);
        *(u8 *)0x0200f28c = 3;
        next_state = 7;
        goto state_tail_r4;
    }
{
    register s32 selected_index asm("r4");
    register u8 **selection_cell asm("r2");
    register u8 *selected_scan asm("r1");
    register u32 available_count asm("r3");
    register u8 **preserved_cell asm("r10");
    register u8 *selection_context asm("r2");
    register u32 original_job asm("r6");
    register s32 selected_offset asm("r5");
    register u32 scan_offset asm("r7");
selection_found: {
    register u32 flag_offset asm("r3") = 0x1284;
    register u8 *flag_source asm("r0");
    register u32 found_flag asm("r1");
    register u32 destination_offset asm("r6");
    register u8 *flag_destination asm("r0");
    register u32 zero asm("r2");
    register u8 **low_cell asm("r7");
    flag_source = selected_scan + flag_offset;
    asm("" : "+r"(flag_source) : "r"(flag_offset));
    found_flag = *flag_source;
    destination_offset = 0x1277;
    flag_destination = selection_context + destination_offset;
    zero = 0;
    asm("" : "+r"(flag_destination), "+r"(zero)
             : "r"(found_flag), "r"(flag_offset));
    *flag_destination = found_flag;
    low_cell = preserved_cell;
    asm("" : "+r"(low_cell));
    B(*low_cell + selected_offset, flag_offset) = zero;
    B(*low_cell, 0x1275) = selected_index;
    goto selection_done;
}
phase_3: {
        s32 index;
        s32 row_offset;
        u8 *unit;
        u8 current_job;
        u8 *rows;
        u8 *listed;
        u32 count;
        u8 derived[12];
        {
            register u8 **cell asm("r6") = (u8 **)0x03002818;
            register u8 *first_context asm("r1");
            register u32 unit_offset asm("r2");
            register u32 initial_job asm("r0");
            register u32 list_offset asm("r4");
            register u32 count_offset asm("r5");
            register u32 produced_count asm("r2");
            register u8 *count_context asm("r0");
            register u32 *count_destination asm("r1");
            asm("" : : "r"(cell));
            first_context = *cell;
            unit_offset = 0x1d0c;
            asm("" : "+r"(first_context), "+r"(unit_offset));
            initial_job = B(*(u8 **)(first_context + unit_offset), 7);
            asm("" : "+r"(first_context) : "r"(initial_job));
            B(first_context, 0x1274) = initial_job;
            first_context = *cell;
            asm("" : "+r"(first_context));
            produced_count = CoreGlobal36_000C8A24(
                *(u8 **)(first_context + unit_offset),
                ({ list_offset = 0x1278;
                   asm("" : : "r"(list_offset));
                   first_context + list_offset; }));
            count_context = *cell;
            count_offset = 0x1270;
            count_destination = (u32 *)(count_context + count_offset);
            asm("" : "+r"(produced_count), "+r"(count_context),
                     "+r"(count_destination) : "r"(count_offset));
            count = (u8)produced_count;
            *count_destination = count;
            CoreRecursive37_00089BA4(count_context + list_offset, 0, count - 1);
        }
        {
            register s32 first_index asm("r4") = 0;
            register u8 **initial_cell asm("r6") = (u8 **)0x03002818;
            register u8 **loop_cell asm("r3");
            register u32 flag_offset asm("r6");
            register u32 job_offset asm("r5");
            register s32 first_row_offset asm("r2");
            asm("" : "+r"(first_index) : "r"(initial_cell));
            if (first_index < (s32)W(*initial_cell, 0x1270)) {
                loop_cell = initial_cell;
                asm("" : "+r"(loop_cell));
                flag_offset = 0x1284;
                job_offset = 0x1287;
                first_row_offset = 0;
                asm("" : "+r"(flag_offset), "+r"(job_offset),
                         "+r"(first_row_offset));
                do {
                    register u8 *row_context asm("r1") = *loop_cell;
                    register u8 *row_base asm("r1");
                    register u32 row_job asm("r0");
                    register u8 *fresh_context asm("r0");
                    register u8 *list_base asm("r0");
                    list_base = row_context + 0x1278;
                    asm("" : "+r"(list_base));
                    if ((s8)list_base[first_index] >= 0) {
                        register u8 *flag_target asm("r0") =
                            row_context + first_row_offset + flag_offset;
                        register u32 flag_value asm("r1") = 0;
                        asm("" : "+r"(flag_target) : "r"(flag_value));
                        *flag_target = flag_value;
                        fresh_context = *loop_cell;
                        row_base = fresh_context + first_row_offset;
                        asm("" : "+r"(row_base) : "r"(fresh_context));
                        list_base = fresh_context + 0x1278;
                        asm("" : "+r"(list_base));
                        row_job = list_base[first_index];
                    } else {
                        register u8 *flag_target asm("r0") =
                            row_context + first_row_offset + flag_offset;
                        register u32 flag_value asm("r1") = 1;
                        asm("" : "+r"(flag_target) : "r"(flag_value));
                        *flag_target = flag_value;
                        fresh_context = *loop_cell;
                        row_base = fresh_context + first_row_offset;
                        asm("" : "+r"(row_base) : "r"(fresh_context));
                        list_base = fresh_context + 0x1278;
                        asm("" : "+r"(list_base));
                        row_job = list_base[first_index] + 128;
                    }
                    B(row_base, job_offset) = row_job;
                    B(*loop_cell + first_row_offset, 0x1285) = first_index;
                    first_row_offset += 28;
                    asm("" : "+r"(first_row_offset));
                    ++first_index;
                } while (first_index < (s32)W(*loop_cell, 0x1270));
            }
        }
        B(CTX, 0x1275) = 0;
        selected_index = 0;
        selection_cell = (u8 **)0x03002818;
        asm("" : "+r"(selected_index) : "r"(selection_cell));
        selected_scan = *selection_cell;
        available_count = W(selected_scan, 0x1270);
        preserved_cell = selection_cell;
        asm("" : "+r"(selected_scan), "+r"(available_count),
                 "+r"(preserved_cell));
        if (selected_index < (s32)available_count) {
            selection_context = selected_scan;
            asm("" : "+r"(selection_context));
            original_job = B(selection_context, 0x1274);
            selected_offset = 0;
            asm("" : "+r"(selected_offset) : "r"(original_job));
            scan_offset = 0x1287;
            asm("" : "+r"(scan_offset));
selection_scan:
            if (B(selected_scan, scan_offset) == original_job)
                goto selection_found;
            selected_scan += 28;
            selected_offset += 28;
            ++selected_index;
            if (selected_index < (s32)available_count)
                goto selection_scan;
        }
selection_done:
        {
            register u8 **row_cell asm("r6") = (u8 **)0x03002818;
            register u8 *row_context asm("r1");
            register u32 selected_byte_offset asm("r7");
            register u32 row_ordinal asm("r2");
            register u8 *output_context asm("r2");
            register u32 output_count_offset asm("r5");
            register s32 derived_index asm("r4");
            register u8 **output_cell asm("r2");
            register u32 derived_field_offset asm("r6");
            register s32 derived_stride asm("r3");
            asm("" : : "r"(row_cell));
            row_context = *row_cell;
            selected_byte_offset = 0x1275;
            asm("" : "+r"(row_context), "+r"(selected_byte_offset));
            row_ordinal = B(row_context, selected_byte_offset);
            asm("" : "+r"(row_ordinal), "+r"(row_context));
            row_context += 28 * row_ordinal;
            CoreScene34_00085770(B(row_context, 0x1287), B(row_context, 0x1284));
            output_context = *row_cell;
            asm("" : "+r"(output_context));
            CoreScene34_00087C5C(
                ({ register u32 argument_offset asm("r4") = 0x987;
                   register u8 *argument_address asm("r0") = output_context + argument_offset;
                   asm("" : "+r"(argument_address) : "r"(argument_offset));
                   *argument_address; }),
                ({ output_count_offset = 0x1270;
                   asm("" : : "r"(output_count_offset));
                   W(output_context, output_count_offset); }),
                ({ selected_byte_offset += 3;
                   asm("" : "+r"(selected_byte_offset));
                   output_context + selected_byte_offset; }), derived);
            derived_index = 0;
            asm("" : "+r"(derived_index) : "r"(row_cell));
            if (derived_index < (s32)W(*row_cell, output_count_offset)) {
                output_cell = row_cell;
                derived_field_offset = 0x1289;
                derived_stride = 0;
                asm("" : "+r"(output_cell), "+r"(derived_field_offset),
                         "+r"(derived_stride));
                do {
                    register u8 *destination_base asm("r1") =
                        *output_cell + derived_stride;
                    register u32 derived_value asm("r0") = derived[derived_index];
                    asm("" : "+r"(destination_base) : "r"(derived_value));
                    B(destination_base, derived_field_offset) = derived_value;
                    derived_stride += 28;
                    asm("" : "+r"(derived_stride));
                    ++derived_index;
                } while (derived_index < (s32)W(*output_cell, output_count_offset));
            }
        }
        {
            register u8 **setup_cell asm("r5") = (u8 **)0x03002818;
            register u8 *setup_context asm("r3");
            register u32 clear_offset asm("r1");
            register u16 *clear_target asm("r0");
            register u32 setup_zero asm("r6");
            register u32 dimensions_offset asm("r4");
            register u8 *dimensions asm("r2");
            register u32 height_offset asm("r7");
            register u32 count_argument asm("r0");
            register u32 width_argument asm("r1");
            register u32 height_argument asm("r2");
            register u8 *output_argument asm("r3");
            register u32 stack_cost asm("r4");
            register u8 *result_context asm("r1");
            register u8 *resource_root asm("r4");
            register u8 *window_field_base asm("r0");
            register u32 window_offset asm("r1");
            register u8 *job_context asm("r0");
            register u32 selected_field_offset asm("r2");
            register u32 job_ordinal asm("r2");
            register u32 job_field_offset asm("r3");
            register u8 *job_row asm("r1");
            register u8 job_value asm("r1");
            register u32 unit_copy_offset asm("r4");
            register u8 *mode_context asm("r5");
            register u32 mode_offset asm("r6");
            register u32 unit_source_offset asm("r7");
            register u8 *mode_source asm("r0");
            register u8 *mode_unit asm("r1");
            asm("" : : "r"(setup_cell));
            setup_context = *setup_cell;
            clear_offset = 0x126c;
            asm("" : "+r"(setup_context), "+r"(clear_offset));
            clear_target = (u16 *)(setup_context + clear_offset);
            setup_zero = 0;
            asm("" : "+r"(clear_target) : "r"(setup_zero));
            *clear_target = setup_zero;
            dimensions_offset = 0x13dc;
            asm("" : "+r"(dimensions_offset));
            dimensions = setup_context + dimensions_offset;
            *(u32 *)dimensions = 160;
            height_offset = 159u << 5;
            asm("" : "+r"(height_offset));
            W(setup_context, height_offset) = 120;
            count_argument = W(setup_context, 0x1270);
            width_argument = *(u32 *)dimensions;
            height_argument = *(u32 *)(dimensions + 4);
            asm("" : "+r"(count_argument), "+r"(width_argument),
                     "+r"(height_argument));
            dimensions_offset += 8;
            output_argument = setup_context + dimensions_offset;
            stack_cost = 58;
            asm("" : "+r"(output_argument) : "r"(stack_cost));
            count = CoreGlobal36_00088CDC(count_argument, width_argument,
                                         height_argument, output_argument, stack_cost);
            result_context = *setup_cell;
            height_offset -= 12;
            asm("" : "+r"(result_context), "+r"(height_offset));
            H(result_context, height_offset) = count;
            resource_root = (u8 *)0x03000e30;
            asm("" : "+r"(setup_zero), "+r"(resource_root));
            CoreRegion_0004C4D4(W(resource_root, 4), 26, 0, 160, 148,
                                setup_zero, 3,
                                ({ register u32 first_resource asm("r1") = 0x0894eaf4;
                                   asm("" : "+r"(first_resource));
                                   first_resource; }), 0x0894eb80, 432);
            window_field_base = *(u8 **)(resource_root + 4);
            window_offset = 182u << 2;
            asm("" : "+r"(window_field_base), "+r"(window_offset));
            window_field_base += window_offset;
            asm("" : "+r"(window_field_base));
            H(window_field_base, 20) = 1;
            job_context = *setup_cell;
            selected_field_offset = 0x1275;
            asm("" : "+r"(job_context), "+r"(selected_field_offset));
            job_row = job_context + selected_field_offset;
            asm("" : "+r"(job_row));
            job_ordinal = *job_row;
            asm("" : "+r"(job_ordinal), "+r"(job_context));
            job_row = job_context + 28 * job_ordinal;
            job_field_offset = 0x1287;
            asm("" : "+r"(job_field_offset) : "r"(job_row));
            job_value = B(job_row, job_field_offset);
            unit_copy_offset = 0x1be4;
            asm("" : "+r"(job_context), "+r"(unit_copy_offset) : "r"(job_value));
            ApplyUnitJobWithFlag(job_context + unit_copy_offset, job_value);
            mode_context = *setup_cell;
            mode_offset = 0x44c;
            asm("" : "+r"(mode_context), "+r"(mode_offset));
            mode_source = mode_context + mode_offset;
            asm("" : "+r"(mode_source));
            if (*mode_source == 1) {
                unit_source_offset = 0x1d0c;
                asm("" : "+r"(unit_source_offset));
                mode_source = mode_context + unit_source_offset;
                asm("" : "+r"(mode_source));
                mode_unit = *(u8 **)mode_source;
                asm("" : "+r"(mode_unit));
                CoreScene34_00075620(1, mode_unit, 1, 0);
            } else {
                register u32 fallback_offset asm("r1") = 0x1be4;
                register u8 *fallback_destination asm("r0");
                asm("" : "+r"(fallback_offset));
                fallback_destination = mode_context + fallback_offset;
                asm("" : "+r"(fallback_destination) : "r"(fallback_offset));
                CoreScene34_00075FA8(fallback_destination, 0);
            }
        }
        CoreRegion_0008A604(4, 2);
        CoreRegion_0008A604(3, 2);
        B(CTX, 37) = 15;
        next_state = 4;
        goto state_tail_r2;
    }
}
phase_5: {
        register u8 **job_cell asm("r4") = (u8 **)0x03002818;
        register u8 *initial_context asm("r2");
        register u32 clear_offset asm("r3");
        register u16 *counter_address asm("r1");
        register u32 counter_zero asm("r0");
        register u32 unit_offset asm("r5");
        register u8 *unit_pointer asm("r0");
        register u32 selected_offset asm("r6");
        register u8 *selected_address asm("r1");
        register u32 ordinal asm("r3");
        register u32 row_scale asm("r1");
        register u8 *row_address asm("r2");
        register u32 job_offset asm("r7");
        register u8 selected_job asm("r1");
        register u8 *mode_context asm("r4");
        register u32 mode_offset asm("r1");
        register u8 *mode_address asm("r0");
        register u8 *mode_unit asm("r1");
        asm("" : : "r"(job_cell));
        initial_context = *job_cell;
        clear_offset = 0x126c;
        asm("" : "+r"(initial_context), "+r"(clear_offset));
        counter_address = (u16 *)(initial_context + clear_offset);
        counter_zero = 0;
        asm("" : "+r"(counter_address) : "r"(counter_zero));
        *counter_address = counter_zero;
        unit_offset = 0x1d0c;
        asm("" : "+r"(unit_offset));
        unit_pointer = *(u8 **)(initial_context + unit_offset);
        asm("" : "+r"(unit_pointer));
        selected_offset = 0x1275;
        asm("" : "+r"(selected_offset));
        selected_address = initial_context + selected_offset;
        ordinal = *selected_address;
        asm("" : "+r"(ordinal));
        row_scale = 28 * ordinal;
        row_address = initial_context + row_scale;
        job_offset = 0x1287;
        asm("" : "+r"(job_offset) : "r"(row_address));
        row_address += job_offset;
        asm("" : "+r"(row_address));
        selected_job = *row_address;
        asm("" : : "r"(selected_job));
        ApplyUnitJob(unit_pointer, selected_job);
        mode_context = *job_cell;
        mode_offset = 0x44c;
        asm("" : "+r"(mode_context), "+r"(mode_offset));
        mode_address = mode_context + mode_offset;
        asm("" : "+r"(mode_address));
        if (*mode_address == 1) {
            mode_address = mode_context + unit_offset;
            asm("" : "+r"(mode_address));
            mode_unit = *(u8 **)mode_address;
            asm("" : "+r"(mode_unit));
            CoreScene34_00075620(1, mode_unit, 1, 0);
        } else {
            register u32 fallback_unit_offset asm("r2") = 0x1d0c;
            asm("" : "+r"(fallback_unit_offset));
            mode_address = mode_context + fallback_unit_offset;
            asm("" : "+r"(mode_address));
            mode_unit = *(u8 **)mode_address;
            asm("" : "+r"(mode_unit));
            CoreScene34_00075620(0, mode_unit, 1, 1);
        }
        {
            register u8 **refresh_cell asm("r4") = (u8 **)0x03002818;
            register u8 *refresh_context asm("r0");
            register u32 job_field_offset asm("r3");
            register u8 *job_address asm("r1");
            register u8 job_value asm("r1");
            register u32 unit_copy_offset asm("r5");
            register u32 timer_offset asm("r4");
            asm("" : : "r"(refresh_cell));
            refresh_context = *refresh_cell;
            job_field_offset = 0x1beb;
            asm("" : "+r"(refresh_context), "+r"(job_field_offset));
            job_address = refresh_context + job_field_offset;
            asm("" : "+r"(job_address));
            job_value = *job_address;
            unit_copy_offset = 0x1be4;
            asm("" : "+r"(refresh_context), "+r"(unit_copy_offset)
                     : "r"(job_value));
            ApplyUnitJobWithFlag(refresh_context + unit_copy_offset, job_value);
            CoreScene34_00080DB4(*refresh_cell + unit_copy_offset);
            CoreRegion_0008A604(3, 2);
            refresh_context = *refresh_cell;
            timer_offset = 0x43c;
            asm("" : "+r"(refresh_context), "+r"(timer_offset));
            B(refresh_context, timer_offset) = 24;
        }
        next_state = 6;
        goto state_tail_r5;
    }
phase_12: {
        register void *dialog_root asm("r0") = (void *)0x02003cb0;
        register u8 **dialog_cell asm("r4") = (u8 **)0x03002818;
        register u8 *dialog_context asm("r1");
        register u32 source_offset asm("r3");
        register u8 *source_address asm("r2");
        register u8 source_value asm("r2");
        register u32 destination_offset asm("r6");
        asm("" : : "r"(dialog_root), "r"(dialog_cell));
        dialog_context = *dialog_cell;
        source_offset = 0x43a;
        asm("" : "+r"(dialog_context), "+r"(source_offset));
        source_address = dialog_context + source_offset;
        asm("" : "+r"(source_address));
        source_value = *source_address;
        destination_offset = 0x43b;
        asm("" : "+r"(dialog_context), "+r"(destination_offset)
                 : "r"(source_value));
        B(dialog_context, destination_offset) = source_value;
        dialog_context = *dialog_cell;
        asm("" : "+r"(dialog_context) : "r"(source_offset));
        B(dialog_context, source_offset) = 3;
        SceneTaskDependency_0001174C(dialog_root, 1, 10, (void *)0x03000990,
                                    (void *)0x03000e80, 2, 2, 24, 4, 928);
        next_state = 13;
        goto state_tail_input;
    }
phase_13: {
        if ((u16)CoreMutationDependency_00011860() == 0)
            return;
        if ((u8)SceneTaskDependency_00013380() == 0) {
            sub_08013364();
            {
                register u8 *restore_context asm("r0") = CTX;
                register u32 saved_offset asm("r2") = 0x43b;
                register u8 *saved_address asm("r1");
                register u8 saved_value asm("r1");
                register u32 restore_offset asm("r3");
                asm("" : "+r"(restore_context), "+r"(saved_offset));
                saved_address = restore_context + saved_offset;
                asm("" : "+r"(saved_address));
                saved_value = *saved_address;
                restore_offset = 0x43a;
                asm("" : "+r"(restore_context), "+r"(restore_offset)
                         : "r"(saved_value));
                B(restore_context, restore_offset) = saved_value;
            }
            *(u8 *)0x0200f28c = 14;
            next_state = 16;
            goto state_tail_r4;
        } else {
            sub_08013364();
            {
                register u8 **restore_cell asm("r2") = (u8 **)0x03002818;
                register u8 *restore_context asm("r0");
                register u32 saved_offset asm("r5");
                register u8 *saved_address asm("r1");
                register u8 saved_value asm("r1");
                register u32 restore_offset asm("r6");
                asm("" : : "r"(restore_cell));
                restore_context = *restore_cell;
                saved_offset = 0x43b;
                asm("" : "+r"(restore_context), "+r"(saved_offset));
                saved_address = restore_context + saved_offset;
                asm("" : "+r"(saved_address));
                saved_value = *saved_address;
                restore_offset = 0x43a;
                asm("" : "+r"(restore_context), "+r"(restore_offset)
                         : "r"(saved_value));
                B(restore_context, restore_offset) = saved_value;
                B(*restore_cell, 37) = 15;
            }
            *(u8 *)0x0200f28c = 4;
            next_state = 16;
            goto state_tail_input;
        }
    }
phase_14: {
        register void *dialog_root asm("r4") = (void *)0x02003cb0;
        register u32 total asm("r3");
        register u8 **initial_cell asm("r0");
        register u8 **preserved_cell asm("r10");
        register u8 *unit asm("r0");
        register u32 unit_offset asm("r1");
        register u16 *stat_cursor asm("r1");
        register s32 remaining asm("r2");
        register u8 **read_cell asm("r2");
        register u8 *field_context asm("r1");
        register u32 active_offset asm("r2");
        register u8 *active_source asm("r0");
        register u8 active_value asm("r0");
        register u32 saved_offset asm("r3");
        register u8 *saved_target asm("r1");
        register u32 phase_zero asm("r3");
        register u8 **write_cell asm("r5");
        register u8 *active_target asm("r0");
        register u8 *phase_state asm("r6");
        asm("" : : "r"(dialog_root));
        total = 0;
        asm("" : "+r"(total));
        initial_cell = (u8 **)0x03002818;
        preserved_cell = initial_cell;
        asm("" : "+r"(preserved_cell) : "r"(initial_cell));
        unit = *initial_cell;
        unit_offset = 0x1d0c;
        asm("" : "+r"(unit), "+r"(unit_offset));
        unit = *(u8 **)(unit + unit_offset);
        stat_cursor = (u16 *)(unit + 42);
        asm("" : "+r"(stat_cursor));
        remaining = 4;
        asm("" : "+r"(remaining));
        do {
            total += *stat_cursor;
            ++stat_cursor;
            --remaining;
        } while (remaining >= 0);
        if (total == 0)
            goto phase14_zero;
        read_cell = preserved_cell;
        asm("" : "+r"(read_cell));
        field_context = *read_cell;
        active_offset = 0x43a;
        asm("" : "+r"(field_context), "+r"(active_offset));
        active_source = field_context + active_offset;
        asm("" : "+r"(active_source));
        active_value = *active_source;
        saved_offset = 0x43b;
        saved_target = field_context + saved_offset;
        phase_zero = 0;
        asm("" : "+r"(saved_target), "+r"(phase_zero)
                 : "r"(active_value));
        *saved_target = active_value;
        write_cell = preserved_cell;
        asm("" : "+r"(write_cell));
        active_target = *write_cell + active_offset;
        asm("" : "+r"(active_target));
        *active_target = 3;
        B(*write_cell, 37) = phase_zero;
        SceneTaskDependency_0001174C(dialog_root, 1, 18, (void *)0x03000990,
                                    (void *)0x03000e80, 2, 2, 24, 4, 928);
        next_state = 15;
        asm("" : "+r"(next_state));
        phase_state = state_byte;
        asm("" : "+r"(phase_state));
        *phase_state = next_state;
        return;
phase14_zero:
        next_state = 5;
        goto state_tail_input;
    }
phase_15: {
        register u8 **counter_cell asm("r4") = (u8 **)0x03002818;
        register u8 *counter_address asm("r0") = *counter_cell + 37;
        register u32 old_value asm("r1") = *counter_address;
        register u32 new_value asm("r2") = old_value + 1;
        
        *counter_address = new_value;
        asm(".Lw6_85aa8_m148_phase15_old_byte_high: lsl %0, %0, #24" : "+r"(old_value) : );
        old_value >>= 24;
        if (old_value > 70) {
            sub_08013364();
            {
                register u8 *restore_context asm("r0") = *counter_cell;
                register u32 saved_offset asm("r2") = 0x43b;
                register u8 *saved_source asm("r1");
                register u32 saved_value asm("r1");
                register u32 active_offset asm("r3");
                
                asm(".Lw6_85aa8_m149_phase15_saved_address: add %0, %1, %2"
                    : "=r"(saved_source) : "r"(restore_context), "r"(saved_offset));
                saved_value = *saved_source;
                active_offset = 0x43a;
                
                asm(".Lw6_85aa8_m149_phase15_active_address: add %0, %0, %1"
                    : "+r"(restore_context) : "r"(active_offset));
                *restore_context = saved_value;
            }
            *(u8 *)0x0200f28c = 5;
            {
                register u32 final_state asm("r0") = 16;
                register u8 *final_pointer asm("r4");
                
                final_pointer = state_byte;
                
                *final_pointer = final_state;
            }
        }
        CoreMutationDependency_00011860();
        return;
    }
phase_4: {
        register u8 **phase_cell asm("r0") = (u8 **)0x03002818;
        register u8 *initial_context asm("r2") = *phase_cell;
        register u8 *delay_address asm("r4") = initial_context + 37;
        register u32 delay asm("r3") = *delay_address;
        register u8 **preserved_cell asm("r10") = phase_cell;
        register u32 decremented asm("r0");
        register u16 *input_words asm("r1");
        u16 pressed;
        
        if (delay != 0) {
            decremented = delay - 1;
            
            *delay_address = decremented;
phase4_advance:
            CoreScene34_00085820();
            return;
        }
        input_words = NativeInputWords_03000000;
        
        pressed = input_words[1];
        if (pressed & 1) {
            register u32 flags_offset asm("r5") = 0x1d09;
            register u8 *flags_address asm("r0");
            asm(".Lw6_85aa8_m148_phase4_flag_address: add %0, %2, %1" : "=r"(flags_address), "+r"(flags_offset) : "r"(initial_context));
            if ((*flags_address & 28) != 0)
                goto phase4_reject;
            {
                register u32 selected_offset asm("r6") = 0x1275;
                register u32 selected_index asm("r1");
                register u32 row_offset asm("r7");
                register u8 *selected_row asm("r0");
                selected_row = initial_context + selected_offset;

                selected_index = *selected_row;
                selected_row = initial_context + 28 * selected_index;
                row_offset = 0x1284;
                asm(".Lw6_85aa8_m148_phase4_presence_address: add %0, %0, %1" : "+r"(selected_row) : "r"(row_offset), "r"(selected_offset));
                if (*selected_row == 0)
                    goto phase4_reject;
            }
            {
                register u32 unit_offset asm("r1") = 0x1d0c;
                register u8 *job_unit asm("r0");
                register u32 job asm("r4");
                register s32 index asm("r1");
                register u32 count_offset asm("r3");
                register s32 count asm("r0");
                register s32 *count_address asm("r0");
                asm(".Lw6_85aa8_m148_phase4_job_pointer_address: add %0, %2, %1" : "=r"(job_unit), "+r"(unit_offset) : "r"(initial_context));
                job_unit = *(u8 **)job_unit;
                job = B(job_unit, 7);
                
                index = 0;
                count_offset = 0x1270;

                asm(".Lw6_85aa8_m148_phase4_count_address: add %0, %2, %3" : "=r"(count_address), "+r"(index) : "r"(initial_context), "r"(count_offset));
                count = *count_address;
                if (index < count) {
                    register s32 scan_bound asm("r3") = count;
                    register u32 cursor_offset asm("r5") = 0x1287;
                    register u8 *job_cursor asm("r2");
                    asm(".Lw6_85aa8_m148_phase4_scan_address: add %0, %2, %3" : "=r"(job_cursor), "+r"(scan_bound) : "r"(initial_context), "r"(cursor_offset));
                    
                    do {
                        if (*job_cursor == job)
                            goto phase4_job_found;
                        job_cursor += 28;
                        ++index;
                    } while (index < scan_bound);
                }
                index = -1;
phase4_job_found:
                if (index != -1) {
                    register u8 **found_cell asm("r6") = preserved_cell;
                    register u8 *found_context asm("r0");
                    register u32 found_offset asm("r7");
                    
                    found_context = *found_cell;
                    found_offset = 0x1277;
                    
                    if (B(found_context, found_offset) != 0) {
                        register u32 found_state asm("r0") = 14;
                        register u8 *found_pointer asm("r1");
                        
                        found_pointer = state_byte;
                        
                        *found_pointer = found_state;
                        goto phase4_advance;
                    }
                }
                {
                    register u32 missing_state asm("r0") = 12;
                    register u8 *missing_pointer asm("r2");
                    
                    missing_pointer = state_byte;
                    
                    *missing_pointer = missing_state;
                }
            }
            goto phase4_advance;
phase4_reject:
            SceneTaskDependency_00141540(106);
            goto phase4_advance;
        }
        if (pressed & 2) {
            s32 index;
            {
                register u32 unit_offset asm("r3") = 0x1d0c;
                register u8 *cancel_unit asm("r0");
                asm(".Lw6_85aa8_m148_phase4_cancel_unit_address: add %0, %2, %1" : "=r"(cancel_unit), "+r"(unit_offset) : "r"(initial_context));
                cancel_unit = *(u8 **)cancel_unit;
                CoreScene34_00075E24(cancel_unit);
            }
            CoreRegion_0008A604(3, 2);
            {
                register u8 **cancel_cell asm("r4") = preserved_cell;
                register u8 *flags_address asm("r1");
                register u32 flags_offset asm("r5");
                register u32 old_flags asm("r2");
                register u32 clear_mask asm("r0");
                
                flags_address = *cancel_cell;
                flags_offset = 0x95e;
                flags_address += flags_offset;
                old_flags = *flags_address;
                clear_mask = (u32)-3;
                asm(".Lw6_85aa8_m148_phase4_cancel_clear_flag: and %0, %1" : "+r"(clear_mask), "+r"(old_flags), "+r"(flags_address) : "r"(flags_offset));
                
                *flags_address = clear_mask;
            }
            SceneTaskDependency_00141540(104);
            index = 0;
            {
                register s32 *count_address asm("r0");
                {
                    register u8 **count_cell asm("r6") = preserved_cell;
                    register u8 *count_context asm("r0");
                    register u32 count_offset asm("r7");
                    
                    count_context = *count_cell;
                    count_offset = 0x1270;
                    
                    count_address = (s32 *)(count_context + count_offset);
                }
                goto phase4_cancel_count_test;
                do {
                    CoreRegion_0004C7A0(NativeMenuResourceRoot_03000E30[1], (u16)index);
                    ++index;
                    {
                        register u8 *reloaded_context asm("r0") = CTX;
                        register u32 reloaded_offset asm("r1") = 0x1270;
                        
                        asm(".Lw6_85aa8_m153_phase4_reloaded_count_address: add %0, %0, %1" : "+r"(reloaded_context), "+r"(reloaded_offset) : );
                        count_address = (s32 *)reloaded_context;
                    }
phase4_cancel_count_test:
                    ;
                } while (index < *count_address);
            }
            CoreRegion_0004C7A0(NativeMenuResourceRoot_03000E30[1], 26);
            *(u8 *)0x0200f28c = 254;
            next_state = 8;
            goto state_tail_r2;
        }
        if (pressed & 16) {
            {
                register u32 flags_offset asm("r3") = 0x95e;
                register u8 *flags_address asm("r2");
                register u32 old_flags asm("r1");
                register u32 clear_mask asm("r0");
                flags_address = initial_context + flags_offset;
                old_flags = *flags_address;
                clear_mask = (u32)-3;
                asm(".Lw6_85aa8_m148_phase4_forward_clear_flag: and %0, %1" : "+r"(clear_mask), "+r"(old_flags), "+r"(flags_address) : "r"(flags_offset));
                
                *flags_address = clear_mask;
            }
            SceneTaskDependency_00141540(116);
            {
                register u8 **direction_cell asm("r4") = preserved_cell;
                register u8 *direction_address asm("r0");
                register u32 direction_offset asm("r5");
                register u32 direction_value asm("r1");
                
                direction_address = *direction_cell;
                direction_offset = 0x1276;
                asm(".Lw6_85aa8_m148_phase4_forward_direction_address: add %0, %0, %1" : "+r"(direction_address) : "r"(direction_offset));
                
                direction_value = 1;
                
                *direction_address = direction_value;
            }
            {
                register u32 direction_state asm("r0") = 10;
                register u8 *direction_pointer asm("r6");
                
                direction_pointer = state_byte;
                
                *direction_pointer = direction_state;
            }
            goto phase4_advance;
        }
        if (pressed & 32)
            goto phase4_left_direction;
        if ((*input_words & 256) != 0)
            goto phase4_advance;
        state &= pressed;
        
        if (state == 0)
            goto phase4_advance;
        next_state = 17;
state_tail_input:
        {
            register u32 state_store_address asm("r7");
            asm volatile(".Lw6_85aa8_m153_shared_input_state_store: mov %0, %1\n\tstrb %2, [%0]" : "=&r"(state_store_address) : "r"(state_byte), "r"(next_state) : "memory");
        }
        return;
phase4_left_direction:
        SceneTaskDependency_00141540(116);
        {
            register u8 **flags_cell asm("r0") = preserved_cell;
            register u8 *flags_address asm("r1");
            register u32 flags_offset asm("r2");
            register u32 old_flags asm("r2");
            register u32 clear_mask asm("r0");
            
            flags_address = *flags_cell;
            flags_offset = 0x95e;
            asm(".Lw6_85aa8_m148_phase4_reverse_flag_address: add %0, %0, %1" : "+r"(flags_address), "+r"(flags_offset) : );
            old_flags = *flags_address;
            clear_mask = (u32)-3;
            asm(".Lw6_85aa8_m148_phase4_reverse_clear_flag: and %0, %1" : "+r"(clear_mask), "+r"(old_flags) : );
            
            *flags_address = clear_mask;
        }
        {
            register u8 **direction_cell asm("r3") = preserved_cell;
            register u8 *direction_address asm("r0");
            register u32 direction_offset asm("r4");
            register u32 direction_value asm("r1");
            
            direction_address = *direction_cell;
            direction_offset = 0x1276;
            asm(".Lw6_85aa8_m148_phase4_reverse_direction_address: add %0, %0, %1" : "+r"(direction_address) : "r"(direction_offset));
            
            direction_value = 255;
            
            *direction_address = direction_value;
        }
        {
            register u32 direction_state asm("r0") = 9;
            register u8 *direction_pointer asm("r5");
            
            direction_pointer = state_byte;
            
            *direction_pointer = direction_state;
        }
        goto phase4_advance;
    }
phase_17: {
        register u8 **phase_cell asm("r4") = (u8 **)0x03002818;
        register u8 *row_context asm("r1") = *phase_cell;
        register u32 selected_offset asm("r6") = 0x1275;
        register u8 *selected_address asm("r0");
        register u32 selected_index asm("r2");
        register u32 job_offset asm("r7");
        register u32 text_value asm("r1");
        register u32 text_bias asm("r0");
        register u8 *copy_context asm("r2");
        register u32 mode_offset asm("r3");
        register u32 source_byte asm("r0");
        register u32 saved_mode_offset asm("r5");
        register u32 zero asm("r5");
        register u8 *fresh_context asm("r0");
        register u32 active_offset asm("r3");
        register u8 *active_address asm("r2");
        register u32 active_byte asm("r2");
        register u32 saved_offset asm("r6");
        register u32 timer_offset asm("r7");
        register u16 *timer_address asm("r2");
        register u32 active_value asm("r2");
        u8 job;
        
        selected_address = row_context + selected_offset;

        selected_index = *selected_address;
        
        row_context += 28 * selected_index;
        job_offset = 0x1287;
        asm(".Lw6_85aa8_m148_phase17_job_row_address: add %0, %0, %1" : "+r"(row_context) : "r"(job_offset), "r"(selected_offset), "r"(phase_cell));
        job = *row_context;
        text_value = GetJobProperty(job, job, 0);
        
        text_bias = 0x247;
        asm(".Lw6_85aa8_m148_phase17_text_bias_add: add %0, %0, %1" : "+r"(text_value), "+r"(text_bias) : );
        text_value = (u16)text_value;
        asm("" : : "r"(text_value));
        copy_context = *phase_cell;
        mode_offset = 0x1d04;
        
        source_byte = B(copy_context, mode_offset);
        saved_mode_offset = 0x42a;
        
        asm(".Lw6_85aa8_m150_phase17_saved_mode_address: add %0, %0, %1"
            : "+r"(copy_context), "+r"(saved_mode_offset));
        zero = 0;
        
        *copy_context = source_byte;
        fresh_context = *phase_cell;
        B(fresh_context, mode_offset) = zero;
        fresh_context = *phase_cell;
        active_offset = 0x43a;
        
        active_address = fresh_context + active_offset;
        
        active_byte = *active_address;
        saved_offset = 0x43b;
        
        asm(".Lw6_85aa8_m150_phase17_saved_active_address: add %0, %0, %1"
            : "+r"(fresh_context), "+r"(saved_offset));
        *fresh_context = active_byte;
        fresh_context = *phase_cell;
        timer_offset = 0xc0c;
        
        timer_address = (u16 *)(fresh_context + timer_offset);
        
        *timer_address = zero;
        fresh_context += active_offset;
        active_value = 3;
        
        *fresh_context = active_value;
        SceneTaskDependency_00019A8C((void *)0x02003cb0, (u16)text_value, (void *)0x03000990, (void *)0x03000e80);
        next_state = 18;
        goto state_tail_r1;
    }
phase_18: {
        if ((u16)CoreMutationDependency_00011860() != 0) {
            register u8 **phase_cell asm("r2") = (u8 **)0x03002818;
            register u8 *fresh_context asm("r0");
            register u32 setup_offset asm("r3");
            register u32 ten asm("r3");
            register u32 saved_offset asm("r4");
            register u32 active_offset asm("r5");
            register u32 saved_mode_offset asm("r6");
            register u32 mode_offset asm("r7");
            register u8 *source_address asm("r1");
            register u32 source_byte asm("r1");
            
            fresh_context = *phase_cell;
            setup_offset = 0x42b;
            asm(".Lw6_85aa8_m148_phase18_setup_address: add %0, %0, %1" : "+r"(fresh_context), "+r"(setup_offset) : );
            ten = 10;
            
            *fresh_context = ten;
            fresh_context = *phase_cell;
            saved_offset = 0x43b;
            asm(".Lw6_85aa8_m153_phase18_saved_active_address: add %0, %2, %1" : "=r"(source_address), "+r"(saved_offset) : "r"(fresh_context));
            
            source_byte = *source_address;
            active_offset = 0x43a;
            
            asm(".Lw6_85aa8_m153_phase18_active_address: add %0, %0, %1" : "+r"(fresh_context), "+r"(active_offset) : );
            *fresh_context = source_byte;
            fresh_context = *phase_cell;
            saved_mode_offset = 0x42a;
            asm(".Lw6_85aa8_m153_phase18_saved_mode_address: add %0, %2, %1" : "=r"(source_address), "+r"(saved_mode_offset) : "r"(fresh_context));
            
            source_byte = *source_address;
            mode_offset = 0x1d04;
            
            fresh_context += mode_offset;
            *fresh_context = source_byte;
            fresh_context = *phase_cell;
            B(fresh_context, 37) = ten;
            {
                register u32 final_state asm("r0") = 19;
                register u8 *final_pointer asm("r1");
                
                final_pointer = state_byte;
                
                *final_pointer = final_state;
            }
        }
        {
            register u16 *input_words asm("r1") = NativeInputWords_03000000;
            register u32 zero asm("r0");
            
            zero = 0;
            
            input_words[0] = zero;
            input_words[1] = zero;
        }
        return;
    }
phase_19: {
        register u8 *counter_context asm("r0") = CTX;
        register u8 *counter_address asm("r2") = counter_context + 37;
        register u32 old asm("r0");
        
        old = *counter_address;
        
        if (old != 0) {
            register u32 zero asm("r1");
            register u16 *input_words asm("r0");
            old -= 1;
            zero = 0;
            
            *counter_address = old;
            input_words = NativeInputWords_03000000;
            
            input_words[0] = zero;
            input_words[1] = zero;
            return;
        }
        old = 10;
        
        *counter_address = old;
        next_state = 4;
        goto state_tail_r2;
    }
phase_9: {
        u32 selected;
        u8 *row;
        register u8 **phase_cell asm("r0");
        register u8 *initial_context asm("r2");
        register u32 direction_offset asm("r3");
        register u8 *direction_address asm("r0");
        register s32 direction_value asm("r0");
        register u32 selected_offset asm("r4");
        register u8 *selected_address asm("r1");
        CoreScene34_00085820();
        phase_cell = (u8 **)0x03002818;
        
        initial_context = *phase_cell;
        direction_offset = 0x1276;
        direction_address = initial_context + direction_offset;

        direction_value = *(u8 *)direction_address;
        asm(".Lw6_85aa8_m148_phase9_direction_sign_high: lsl %0, %0, #24" : "+r"(direction_value) : "r"(initial_context), "r"(direction_offset));
        direction_value >>= 24;
        if (direction_value != 0)
            return;
        selected_offset = 0x1275;
        asm(".Lw6_85aa8_m148_phase9_selected_address: add %0, %2, %1" : "=r"(selected_address), "+r"(selected_offset) : "r"(initial_context));
        selected = *selected_address;
        if (selected == 0) {
            register u32 count_offset asm("r5") = 0x1270;
            register u32 *count_address asm("r0");
            asm(".Lw6_85aa8_m148_phase9_count_address: add %0, %2, %1" : "=r"(count_address), "+r"(count_offset) : "r"(initial_context));
            selected = *count_address;
        }
        *selected_address = selected - 1;
        {
            register u8 **row_cell asm("r5") = (u8 **)0x03002818;
            register u8 *row_context asm("r1");
            register u32 row_selected_offset asm("r4");
            register u8 *row_selected_address asm("r0");
            register u32 row_index asm("r2");
            register u32 job_offset asm("r6");
            register u8 *job_address asm("r0");
            register u32 job_value asm("r0");
            register u32 quality_offset asm("r7");
            register u32 quality_value asm("r1");
            register u8 *copy_context asm("r0");
            register u8 *copy_selected_address asm("r4");
            register u8 *copy_job_row asm("r1");
            register u32 copy_job asm("r1");
            register u32 copy_offset asm("r4");
            
            row_context = *row_cell;
            row_selected_offset = 0x1275;
            row_selected_address = row_context + row_selected_offset;
            
            row_index = *row_selected_address;
            
            row_context += 28 * row_index;
            job_offset = 0x1287;
            asm(".Lw6_85aa8_m153_phase9_job_address: add %0, %1, %2" : "=r"(job_address), "+r"(row_context), "+r"(job_offset) : );
            
            job_value = *job_address;
            
            quality_offset = 0x1284;
            asm(".Lw6_85aa8_m153_phase9_quality_address: add %0, %0, %1" : "+r"(row_context), "+r"(quality_offset) : "r"(job_value));
            
            quality_value = *row_context;
            CoreScene34_00085770(job_value, quality_value);
            copy_context = *row_cell;
            copy_selected_address = copy_context + row_selected_offset;
            
            row_index = *copy_selected_address;
            
            copy_job_row = copy_context + 28 * row_index;
            copy_job_row += job_offset;
            
            copy_job = *copy_job_row;
            copy_offset = 0x1be4;
            asm(".Lw6_85aa8_m148_phase9_unit_destination: add %0, %0, %1" : "+r"(copy_context) : "r"(copy_offset), "r"(copy_job));
            
            ApplyUnitJobWithFlag(copy_context, copy_job);
            CoreScene34_00075FA8(*row_cell + copy_offset, 0);
            CoreRegion_0008A604(3, 2);
            B(*row_cell, 37) = 0;
        }
        next_state = 4;
state_tail_r1:
        
        {
            register u8 *writeback asm("r1") = state_byte;
            asm volatile(".Lw6_85aa8_m148_phase9_state: strb %1, [%0]" :  : "r"(writeback), "r"(next_state) : "memory");
        }
        return;
    }
phase_10: {
        u8 **row_cell;
        register u8 *row_context asm("r1");
        register u32 direction_offset asm("r2");
        register u8 *direction_address asm("r0");
        register s32 direction_zero asm("r5");
        register u32 selected_offset asm("r6");
        register u8 *selected_address asm("r1");
        register u32 selected_value asm("r0");
        register u8 *count_context asm("r2");
        register u32 count_offset asm("r3");
        register s32 *count_address asm("r1");
        register s32 count asm("r1");
        register u8 *wrap_address asm("r0");
        register u8 *row_selected_address asm("r0");
        register u32 row_index asm("r2");
        register u32 job_offset asm("r4");
        register u8 *job_address asm("r0");
        register u32 job_value asm("r0");
        register u32 quality_offset asm("r2");
        register u32 quality_value asm("r1");
        register u8 *copy_context asm("r0");
        register u8 *copy_selected_address asm("r1");
        register u8 *copy_job_row asm("r1");
        register u32 copy_job asm("r1");
        register u32 copy_offset asm("r4");
        CoreScene34_00085820();
        row_cell = (u8 **)0x03002818;
        row_context = *row_cell;
        direction_offset = 0x1276;
        asm(".Lw6_85aa8_m153_phase10_direction_address: add %0, %1, %2" : "=r"(direction_address), "+r"(row_context), "+r"(direction_offset) : );
        
        direction_zero = 0;
        asm(".Lw6_85aa8_m148_phase10_direction_signed_byte: ldrsb %0, [%1, %0]" : "+r"(direction_zero) : "r"(direction_address), "m"(*(s8 *)direction_address));
        if (direction_zero != 0)
            return;
        
        selected_offset = 0x1275;
        selected_address = row_context + selected_offset;
        
        selected_value = *selected_address;
        selected_value += 1;

        *selected_address = selected_value;
        asm(".Lw6_85aa8_m152_phase10_selector_high: lsl %0, %0, #24"
            : "+r"(selected_value));
        selected_value >>= 24;
        count_context = *row_cell;
        count_offset = 0x1270;
        count_address = (s32 *)(count_context + count_offset);
        
        count = *count_address;
        if ((s32)selected_value >= count) {
            wrap_address = count_context + selected_offset;
            
            *wrap_address = direction_zero;
        }
        row_context = *row_cell;
        row_selected_address = row_context + selected_offset;
        
        row_index = *row_selected_address;
        
        row_context += 28 * row_index;
        job_offset = 0x1287;
        asm(".Lw6_85aa8_m153_phase10_job_address: add %0, %1, %2" : "=r"(job_address), "+r"(row_context), "+r"(job_offset) : );
        
        job_value = *job_address;
        
        quality_offset = 0x1284;
        asm(".Lw6_85aa8_m153_phase10_quality_address: add %0, %0, %1" : "+r"(row_context), "+r"(quality_offset) : "r"(job_value));
        
        quality_value = *row_context;
        CoreScene34_00085770(job_value, quality_value);
        copy_context = *row_cell;
        copy_selected_address = copy_context + selected_offset;
        
        row_index = *copy_selected_address;
        
        copy_job_row = copy_context + 28 * row_index;
        copy_job_row += job_offset;
        
        copy_job = *copy_job_row;
        copy_offset = 0x1be4;
        asm(".Lw6_85aa8_m148_phase10_unit_destination: add %0, %0, %1" : "+r"(copy_context) : "r"(copy_offset), "r"(copy_job));
        
        ApplyUnitJobWithFlag(copy_context, copy_job);
        CoreScene34_00075FA8(*row_cell + copy_offset, 0);
        CoreRegion_0008A604(3, 2);
        B(*row_cell, 37) = direction_zero;
        {
            register u32 final_state asm("r0") = 4;
            register u8 *final_pointer asm("r3");
            
            final_pointer = state_byte;
            
            *final_pointer = final_state;
        }
        return;
    }
phase_7: {
        register u8 *resource_base asm("r0") = (u8 *)0x030009e0;
        register u32 control_offset asm("r4") = 356;
        register u8 *control_address asm("r2");
        register u32 unsigned_snapshot asm("r3");
        register s32 signed_snapshot asm("r1");
        register u8 *saved_base asm("r4");
        register u32 updated_byte asm("r0");
        register u8 **scale_cell asm("r0");
        register u32 read_offset asm("r6");
        register u8 *read_address asm("r0");
        register u32 fresh_byte asm("r0");
        register s32 signed_byte asm("r0");
        register u32 target_offset asm("r7");
        
        asm(".Lw6_85aa8_m153_phase7_control_address: add %0, %2, %1" : "=r"(control_address), "+r"(control_offset) : "r"(resource_base));
        /* Keep the original independent unsigned and signed reads. */
        unsigned_snapshot = *(volatile u8 *)control_address;
        asm(".Lw6_85aa8_m151_phase7_signed_snapshot: mov %0, #0\n\tldrsb %0, [%1, %0]"
            : "=&r"(signed_snapshot) : "r"(control_address), "m"(*(s8 *)control_address));
        
        saved_base = resource_base;
        
        if (signed_snapshot == 16) {
            register u32 saved_state asm("r0") = *(u8 *)0x0200f28c;
            register u8 *restore_pointer asm("r5");
            
            restore_pointer = state_byte;
            
            *restore_pointer = saved_state;
            goto phase7_prepare_scale;
        }
        if (signed_snapshot > 16) {
            updated_byte = unsigned_snapshot - 1;
            goto phase7_store_byte;
        }
        if (signed_snapshot < 16) {
            updated_byte = unsigned_snapshot + 1;
phase7_store_byte:
            
            *control_address = updated_byte;
        }
phase7_prepare_scale:
        scale_cell = (u8 **)0x03002818;
        
        scaled_halfword_target = (u16 *)*scale_cell;
        read_offset = 356;
        asm(".Lw6_85aa8_m153_phase7_fresh_byte_address: add %0, %1, %2" : "=r"(read_address), "+r"(saved_base), "+r"(read_offset) : );
        
        asm(".Lw6_85aa8_m148_phase7_signed_scale_input: ldrb %0, [%1]\n\tlsl %0, %0, #24\n\tasr %0, %0, #24" : "=r"(signed_byte) : "r"(read_address), "m"(*read_address));
        scaled_halfword_value = signed_byte * 8;
        target_offset = 0x564;
        
        scaled_halfword_target = (u16 *)((u8 *)scaled_halfword_target + target_offset);
        goto shared_scaled_halfword_store;
    }
phase_6: {
        u16 old_counter;
        register u8 **initial_cell asm("r1") = (u8 **)0x03002818;
        register u8 *initial_context asm("r3") = *initial_cell;
        register u32 initial_counter_offset asm("r4") = 0x126c;
        register u16 *initial_counter_address asm("r0") = (u16 *)(initial_context + initial_counter_offset);
        register u32 initial_count asm("r0");
        register u8 **preserved_cell asm("r10");
        register u32 counter_offset asm("r9");
        u8 **event_cell;
        register u8 *event_context asm("r0");
        register u32 counter_seed asm("r3");
        register u16 *event_counter asm("r0");
        
        initial_count = *initial_counter_address;
        preserved_cell = initial_cell;
        
        if (initial_count > 38)
            goto phase6_late_motion;
        if (initial_count == 10)
            SceneTaskDependency_00141540(134);
        {
            register u8 **read_cell asm("r0") = preserved_cell;
            register u8 *read_context asm("r1");
            register u16 *count_address asm("r0");
            
            read_context = *read_cell;
            count_address = (u16 *)(read_context + initial_counter_offset);
            
            if (*count_address > 10) {
                register u32 motion_offset asm("r2") = 0x438;
                register u32 value asm("r0");
                asm(".Lw6_85aa8_m153_phase6_early_motion_address: add %0, %0, %1" : "+r"(read_context), "+r"(motion_offset) : );
                
                value = *(u16 *)read_context;
                value -= 2;
                
                *(u16 *)read_context = value;
            }
        }
        {
            register u8 **read_cell asm("r3") = preserved_cell;
            register u8 *read_context asm("r0");
            register u32 height_offset asm("r4");
            register u16 *height_address asm("r2");
            register u32 unsigned_snapshot asm("r3");
            register s32 signed_snapshot asm("r1");
            register u32 signed_read_zero asm("r5");
            register s32 lower_limit asm("r0");
            register u32 value asm("r0");
            
            read_context = *read_cell;
            height_offset = 0x458;
            asm(".Lw6_85aa8_m153_phase6_early_height_address: add %0, %2, %1" : "=r"(height_address), "+r"(height_offset) : "r"(read_context));
            
            /* Keep the original independent unsigned and signed reads. */
        unsigned_snapshot = *(volatile u16 *)height_address;
        asm(".Lw6_85aa8_m153_phase6_early_signed_halfword: mov %1, #0\n\tldrsh %0, [%2, %1]" : "=r"(signed_snapshot), "=&r"(signed_read_zero) : "r"(height_address), "m"(*(s16 *)height_address));
            
            lower_limit = -64;
            
            if (signed_snapshot > lower_limit) {
                value = unsigned_snapshot - 4;
                
                *height_address = value;
            }
        }
        goto phase6_after_motion;
phase6_late_motion:
        {
            register u32 motion_offset asm("r6") = 0x438;
            register u16 *motion_address asm("r0");
            register u32 motion_value asm("r1");
            register u32 height_offset asm("r7");
            register u16 *height_address asm("r1");
            register s32 value asm("r0");
            register u32 signed_read_zero asm("r2");
            asm(".Lw6_85aa8_m153_phase6_late_motion_address: add %0, %1, %2" : "=r"(motion_address), "+r"(initial_context), "+r"(motion_offset) : );
            
            motion_value = *motion_address;
            motion_value += 1;
            
            *motion_address = motion_value;
            height_offset = 0x458;
            height_address = (u16 *)(initial_context + height_offset);
            
            asm(".Lw6_85aa8_m153_phase6_late_signed_halfword: mov %1, #0\n\tldrsh %0, [%2, %1]" : "=r"(value), "=&r"(signed_read_zero) : "r"(height_address), "m"(*(s16 *)height_address));
            value += 4;
            if (value < 0) {
                
                value = *height_address + 4;
            } else {
                value = 0;
            }
            
            *height_address = value;
        }
phase6_after_motion:
        event_cell = preserved_cell;
        event_context = *event_cell;
        counter_seed = 0x126c;
        
        asm(".Lw6_85aa8_m148_phase6_counter_offset_home: mov %0, %1" : "=r"(counter_offset) : "r"(counter_seed));
        event_counter = (u16 *)(event_context + counter_offset);
        
        if (*event_counter == 39) {
            register void *scratch asm("r6") = (void *)0x02003cb0;
            register u32 setup_offset asm("r4");
            register u8 *call_address asm("r0");
            register u32 setup_value asm("r1");
            register u32 unit_offset asm("r5");
            register u8 *unit_input asm("r0");
            register u8 *unit_argument asm("r1");
            register u32 extent asm("r4");
            register u32 work_offset asm("r6");
            register u8 *work_target asm("r4");
            register u32 property_value asm("r0");
            register u32 callback_result asm("r0");
            register u8 *result_context asm("r1");
            register u32 result_offset asm("r3");
            register u32 *result_target asm("r2");
            register u32 state_offset asm("r4");
            register u32 state_value asm("r0");
            register u8 *copy_bank asm("r4");
            register u32 copy_control asm("r5");
            register u32 bank_step asm("r7");
            u8 *unit;
            asm("" : "+r"(scratch));
            BattleRuntimeDependency_00141520(113);
            call_address = *event_cell;
            setup_offset = 0x43c;
            asm(".Lw6_85aa8_m153_phase6_event_setup_address: add %0, %0, %1" : "+r"(call_address), "+r"(setup_offset) : );
            
            setup_value = 44;
            
            *call_address = setup_value;
            call_address = *event_cell;
            unit_offset = 0x1d0c;
            call_address += unit_offset;
            
            unit_input = *(u8 **)call_address;
            CoreRegion_000717CC(unit_input, 0, 3);
            call_address = *event_cell + unit_offset;
            asm(".Lw6_85aa8_m148_phase6_scene_unit: ldr %0, [%1]" : "=r"(unit_argument) : "r"(call_address), "m"(*(u8 **)call_address));
            CoreScene34_00075620(0, unit_argument, 2, 0);
            call_address = *event_cell + unit_offset;
            unit_input = *(u8 **)call_address;
            extent = CoreDependency29_000CB808(unit_input);
            
            call_address = *event_cell + unit_offset;
            asm(".Lw6_85aa8_m148_phase6_effect_unit: ldr %0, [%1]" : "=r"(unit_argument) : "r"(call_address), "m"(*(u8 **)call_address));
            CoreDependency29_000CB868(scratch, unit_argument);
            BiosCpuSet(scratch, (void *)0x06014300,
                ({ asm(".Lw6_85aa8_m148_phase6_half_extent: lsl %0, %0, #10\n\tlsr %0, %0, #11" : "+r"(extent) : ); extent; }));
            call_address = *event_cell;
            work_offset = 0x2e8;
            asm(".Lw6_85aa8_m148_phase6_work_record_address: add %0, %1, %2" : "=r"(work_target), "+r"(call_address), "+r"(work_offset) : );
            unit_input = *(u8 **)(call_address + unit_offset);
            property_value = ReadUnitRecordProperty10Or11(unit_input, 1);
            CoreDependency29_000CB8D4(work_target, (u8)property_value);
            unit_input = *(u8 **)(*event_cell + unit_offset);
            callback_result = CoreFrontier_000CB928(unit_input);
            result_context = *event_cell;
            result_offset = 0x454;
            asm(".Lw6_85aa8_m153_phase6_result_word_address: add %0, %2, %1" : "=r"(result_target), "+r"(result_offset) : "r"(result_context));
            
            *result_target = callback_result;
            state_offset = 0x452;
            asm(".Lw6_85aa8_m153_phase6_result_state_address: add %0, %0, %1" : "+r"(result_context), "+r"(state_offset) : );
            
            state_value = 3;
            
            *result_context = state_value;
            call_address = *event_cell + 0x28;
            
            copy_bank = (u8 *)0x03003860;
            copy_control = 0x04000080;
            asm("" : "+r"(copy_bank), "+r"(copy_control));
            BiosCpuSet(call_address, copy_bank, copy_control);
            call_address = *event_cell;
            asm(".Lw6_85aa8_m148_phase6_second_copy_addresses: sub %1, #192\n\tadd %0, %0, %1\n\tmov %3, #128\n\tlsl %3, %3, #2\n\tadd %2, %3" : "+r"(call_address), "+r"(work_offset), "+r"(copy_bank), "=&r"(bank_step) : );
            BiosCpuSet(call_address, copy_bank, copy_control);
        }
        {
            register u8 **read_cell asm("r0") = preserved_cell;
            register u8 *last_context asm("r3");
            register u32 low_offset asm("r1");
            register u16 *last_counter asm("r0");
            register u32 old_value asm("r1");
            register u32 incremented asm("r2");
            register u32 setup_offset asm("r2");
            register u8 *setup_address asm("r1");
            register u32 zero asm("r0");
            
            last_context = *read_cell;
            asm(".Lw6_85aa8_m153_phase6_retained_counter_address: mov %1, %3\n\tadd %0, %2, %1" : "=r"(last_counter), "=&r"(low_offset) : "r"(last_context), "r"(counter_offset));
            
            old_value = *last_counter;
            incremented = old_value + 1;
            
            *last_counter = incremented;
            asm(".Lw6_85aa8_m148_phase6_old_counter_high: lsl %0, %0, #16" : "+r"(old_value) : );
            old_value >>= 16;
            if (old_value <= 99)
                return;
            setup_offset = 0x43c;
            asm(".Lw6_85aa8_m153_phase6_final_setup_address: add %0, %2, %1" : "=r"(setup_address), "+r"(setup_offset) : "r"(last_context));
            
            zero = 0;
            
            *setup_address = zero;
        }
        {
            register u8 **read_cell asm("r3") = preserved_cell;
            register u8 *motion_context asm("r0");
            register u32 motion_offset asm("r4");
            register u16 *motion_address asm("r0");
            register u32 motion_value asm("r1");
            
            motion_context = *read_cell;
            motion_offset = 0x438;
            asm(".Lw6_85aa8_m153_phase6_final_motion_address: add %0, %1, %2" : "=r"(motion_address), "+r"(motion_context), "+r"(motion_offset) : );
            
            motion_value = 56;
            
            *motion_address = motion_value;
        }
        next_state = 3;
        goto state_tail_r5;
    }
phase_8: {
        register u8 *resource_base asm("r0") = (u8 *)0x030009e0;
        register u32 control_offset asm("r6") = 356;
        register u8 *control_address asm("r2");
        register u32 unsigned_snapshot asm("r1");
        register s32 signed_snapshot asm("r0");
        register u32 updated_byte asm("r0");
        register u8 **scale_cell asm("r0");
        register u32 target_offset asm("r3");
        register s32 scale_snapshot asm("r0");
        
        asm(".Lw6_85aa8_m152_phase8_control_address: add %0, %2, %1"
            : "=r"(control_address), "+r"(control_offset) : "r"(resource_base));
        /* Keep the original independent unsigned and signed reads. */
        unsigned_snapshot = *(volatile u8 *)control_address;
        asm(".Lw6_85aa8_m151_phase8_signed_snapshot: mov %0, #0\n\tldrsb %0, [%1, %0]"
            : "=&r"(signed_snapshot) : "r"(control_address), "m"(*(s8 *)control_address));
        
        if (signed_snapshot > 30) {
            register u8 **unit_cell asm("r4") = (u8 **)0x03002818;
            register u32 unit_offset asm("r7");
            register u8 *unit_address asm("r0");
            register u8 *unit_input asm("r0");
            
            unit_address = *unit_cell;
            unit_offset = 0x1d0c;
            unit_address += unit_offset;
            
            unit_input = *(u8 **)unit_address;
            if ((u8)BattleDependency_00133BC4(unit_input) == 1) {
                register u8 *value_address asm("r0") = *unit_cell;
                register u32 value_offset asm("r1") = 0x986;
                asm(".Lw6_85aa8_m153_phase8_value_byte_address: add %0, %0, %1" : "+r"(value_address), "+r"(value_offset) : );
                
                CoreScene34_00076420(*value_address);
            }
            next_state = *(u8 *)0x0200f28c;
            goto state_tail_r2;
        }
        updated_byte = unsigned_snapshot + 2;
        
        *control_address = updated_byte;
        scale_cell = (u8 **)0x03002818;
        
        scaled_halfword_target = (u16 *)*scale_cell;
        
        asm(".Lw6_85aa8_m151_phase8_scale_snapshot: mov %0, #0\n\tldrsb %0, [%1, %0]"
            : "=&r"(scale_snapshot) : "r"(control_address), "m"(*(s8 *)control_address));
        scaled_halfword_value = scale_snapshot * 8;
        target_offset = 0x564;
        
        asm(".Lw6_85aa8_m154_phase8_scale_target: add %0, %0, %1"
            : "+r"(scaled_halfword_target), "+r"(target_offset));
shared_scaled_halfword_store:
        *scaled_halfword_target = scaled_halfword_value;
        CoreRegion_0008A604(4, 3);
        return;
    }
phase_16: {
        if ((u16)CoreMutationDependency_00011860() == 0)
            return;
        next_state = *(u8 *)0x0200f28c;
state_tail_r4:
        {
            register u8 *writeback asm("r4");
            
            writeback = state_byte;
            asm volatile(".Lw6_85aa8_m148_phase16_state: strb %1, [%0]" :  : "r"(writeback), "r"(next_state) : "memory");
        }
        return;
    }
phase_11: {
        register u8 *resource_base asm("r2") = (u8 *)0x030009e0;
        u8 slot;
        asm("" : "+r"(resource_base));
        slot = *(u8 *)0x0200f28d;
        if (*(resource_base + 76 * slot) != 0)
            return;
        next_state = *(u8 *)0x0200f28c;
state_tail_r5:
        {
            register u8 *writeback asm("r5");
            
            writeback = state_byte;
            asm volatile(".Lw6_85aa8_m148_phase11_state: strb %1, [%0]" :  : "r"(writeback), "r"(next_state) : "memory");
        }
        return;
    }
phase_254: {
        register u8 **mode_cell asm("r2");
        register u8 *mode_address asm("r0");
        register u32 mode_offset asm("r6");
        register u32 zero asm("r1");
        register u32 mode asm("r3");
        register u8 *mode_context asm("r2");
        register u32 selector_offset asm("r7");
        register u32 unit_offset asm("r1");
        register u8 *unit_address asm("r0");
        register u8 *unit_argument asm("r1");
        CoreScene34_00087B30(255);
        mode_cell = (u8 **)0x03002818;
        
        mode_address = *mode_cell;
        mode_offset = 0x1d04;
        asm(".Lw6_85aa8_m153_phase254_mode_address: add %0, %0, %1" : "+r"(mode_address), "+r"(mode_offset) : );
        
        zero = 0;
        
        *mode_address = zero;
        mode = 0;
        
        mode_context = *mode_cell;
        selector_offset = 0x44c;
        mode_address = mode_context + selector_offset;
        
        if (*mode_address == 1)
            mode = 1;
        unit_offset = 0x1d0c;
        asm(".Lw6_85aa8_m153_phase254_unit_address: add %0, %2, %1" : "=r"(unit_address), "+r"(unit_offset) : "r"(mode_context));
        
        asm(".Lw6_85aa8_m148_phase254_scene_unit: ldr %0, [%1]" : "=r"(unit_argument) : "r"(unit_address), "m"(*(u8 **)unit_address));
        CoreScene34_00075620(mode, unit_argument, 1, 1);
        next_state = 255;
state_tail_r2:
        {
            register u8 *writeback asm("r2");
            
            writeback = state_byte;
            asm volatile(".Lw6_85aa8_m148_phase254_state: strb %1, [%0]" :  : "r"(writeback), "r"(next_state) : "memory");
        }
        return;
    }
}
