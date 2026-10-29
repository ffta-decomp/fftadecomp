typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *SceneDisplayRoot;
extern u8 UnitPool[];
extern void *RosterSpriteBanks[];
extern const u8 RosterImageTable[];
extern const u8 RosterFrameTable[];
extern const u8 FirstRosterIndicator[];
extern const u8 SecondRosterIndicator[];
extern void DrawRosterRow(void *,u32,u32,u32,u32,u32,u32,const void *,const void *,u32,s32);
extern void HideRosterRow(void *,u32);
extern void UpdateRosterRowPosition(void *,u32,u32,u32);
extern void AppendRosterIndicator(const u8 *,s32,s32,u32,u32,u32,u32,u32,u32,u32,u32);
__asm__(".global SceneDisplayRoot\n.set SceneDisplayRoot,0x03002818\n"
        ".global UnitPool\n.set UnitPool,0x02000080\n"
        ".global RosterSpriteBanks\n.set RosterSpriteBanks,0x03000e30\n"
        ".global RosterImageTable\n.set RosterImageTable,0x0894eae0\n"
        ".global RosterFrameTable\n.set RosterFrameTable,0x0894eb6c\n"
        ".global FirstRosterIndicator\n.set FirstRosterIndicator,0x08393eca\n"
        ".global SecondRosterIndicator\n.set SecondRosterIndicator,0x08393ed2\n"
        ".global DrawRosterRow\n.thumb_set DrawRosterRow,0x0804c525\n"
        ".global HideRosterRow\n.thumb_set HideRosterRow,0x0804c7a1\n"
        ".global UpdateRosterRowPosition\n.thumb_set UpdateRosterRowPosition,0x0804c789\n"
        ".global AppendRosterIndicator\n.thumb_set AppendRosterIndicator,0x08001cf1");
#define ROSTER_TILE_R2(raw) ({ register u32 projected __asm__("r2") = (u16)(raw); __asm__("" : "+r"(projected)); projected; })
#define ROSTER_TILE_R1(raw) ({ register u32 projected __asm__("r1"); __asm__("lsl %0,%1,#16\n\tlsr %0,%0,#16" : "=l"(projected) : "l"(raw) : "cc"); projected; })
#define ROSTER_DRAW_SLOT(word) ({ register u32 slot_word __asm__("r3") = (word); __asm__("" : "+r"(slot_word)); slot_word>>16; })
#define ROSTER_ROW_X(root,offset) ({ register u8 *row_address __asm__("r2") = (root); register u32 row_offset __asm__("r3") = (offset); register u32 field_offset __asm__("r3"); __asm__("" : "+r"(row_offset)); row_address += row_offset; __asm__("" : "+r"(row_address)); field_offset = 0x9F6; __asm__("" : "+r"(field_offset)); row_address += field_offset; __asm__("" : "+r"(row_address)); *row_address; })
#define ROSTER_BANK(reg) ({ register void **bank_slots __asm__(reg) = RosterSpriteBanks; __asm__("" : "+r"(bank_slots)); bank_slots[1]; })
#define ROSTER_HIDE_SLOT(word) ({ register u32 slot_word __asm__("r2") = (word); __asm__("" : "+r"(slot_word)); slot_word>>16; })
struct RosterIteration { s32 index;u32 byte_offset;u32 slot_fixed; };
typedef char RosterIterationSize[(sizeof(struct RosterIteration)==12)?1:-1];
void RefreshUnitRosterRowDescriptors(void) __asm__("CoreGlobal36_00071378");
void RefreshUnitRosterRowDescriptors(void)
{
    struct RosterIteration iteration;
    u8 *owner;
    s32 screen_y;
    s32 next_index;
    u32 next_count;
    {
        register u32 initial_zero __asm__("r0") = 0;
        register u8 **count_root __asm__("r1");
        register u8 *count_address __asm__("r0");
        register u32 count_offset __asm__("r2");
        register s32 initial_index __asm__("r3");
        __asm__("" : "+r"(initial_zero));
        iteration.index = initial_zero;
        __asm__("" : "+m"(iteration.index));
        count_root = &SceneDisplayRoot;
        __asm__("" : "+r"(count_root));
        count_address = *count_root;
        __asm__("" : "+r"(count_address));
        count_offset = 0x95C;
        __asm__("" : "+r"(count_offset));
        count_address += count_offset;
        __asm__("" : "+r"(count_address));
        initial_index = iteration.index;
        __asm__("" : "+r"(initial_index));
        count_address = (u8 *)(u32)*count_address;
        __asm__("" : "+r"(count_address));
        if (initial_index >= (s32)count_address)
            goto final_marker;
    }
    {
        register u32 offset_zero __asm__("r4") = 0;
        register u32 slot_zero __asm__("r0");
        __asm__("" : "+r"(offset_zero));
        iteration.byte_offset = offset_zero;
        __asm__("" : "+m"(iteration.byte_offset));
        slot_zero = 0;
        __asm__("" : "+r"(slot_zero));
        iteration.slot_fixed = slot_zero;
        __asm__("" : "+m"(iteration.slot_fixed));
        do {
            register s32 unit_id __asm__("r5");
            register u8 *unit __asm__("r8");
            register u32 base_style __asm__("r10");
            register u32 tile_code __asm__("r6");
            u32 flags;
            u32 first_mask;
            register u32 first_flags __asm__("r3");
            s32 delta;
            u32 row_style;
            u32 masked;
            {
                register u8 **root_slot __asm__("r2") = &SceneDisplayRoot;
                register u8 *first_root __asm__("r1");
                register u32 field_offset __asm__("r3");
                register u8 *first_address __asm__("r0");
                register s32 row_index __asm__("r4");
                register u32 row_offset __asm__("r0");
                register u32 row_field __asm__("r2");
                register u8 **fresh_slot __asm__("r4");
                register u8 *fresh_root __asm__("r3");
                register u8 *row_base __asm__("r2");
                register u32 half_offset __asm__("r1");
                register u8 *half_address __asm__("r0");
                register u32 unit_address __asm__("r0");
                register u32 unit_base __asm__("r1");
                register u32 style_offset __asm__("r4");
                register u8 *style_address __asm__("r0");
                register u32 y_offset __asm__("r0");
                register s32 row_y __asm__("r1");
                register s32 scroll_y __asm__("r0");
                __asm__("" : "+r"(root_slot));
                first_root = *root_slot;
                __asm__("" : "+r"(first_root));
                field_offset = 0x9BA;
                __asm__("" : "+r"(field_offset));
                first_address = first_root+field_offset;
                __asm__("" : "+r"(first_address));
                row_index = iteration.index;
                __asm__("" : "+r"(row_index));
                first_address += row_index;
                __asm__("" : "+r"(first_address));
                unit_id = *first_address;
                __asm__("" : "+r"(unit_id));
                row_offset = iteration.byte_offset;
                __asm__("" : "+r"(row_offset));
                first_root += row_offset;
                __asm__("" : "+r"(first_root));
                row_field = 0x9EE;
                __asm__("" : "+r"(row_field));
                first_root += row_field;
                __asm__("" : "+r"(first_root));
                *first_root = (u8)row_index;
                fresh_slot = &SceneDisplayRoot;
                __asm__("" : "+r"(fresh_slot));
                fresh_root = *fresh_slot;
                __asm__("" : "+r"(fresh_root));
                row_base = fresh_root+row_offset;
                __asm__("" : "+r"(row_base));
                half_offset = 0x9F0;
                __asm__("" : "+r"(half_offset));
                half_address = row_base+half_offset;
                __asm__("" : "+r"(half_address));
                *(u16 *)half_address = (u16)unit_id;
                unit_address = 264*unit_id;
                __asm__("" : "+r"(unit_address));
                unit_base = (u32)UnitPool;
                __asm__("" : "+r"(unit_base));
                unit_address += unit_base;
                __asm__("" : "+r"(unit_address));
                unit = (u8 *)unit_address;
                __asm__("" : "+r"(unit));
                style_offset = 0xBCC;
                __asm__("" : "+r"(style_offset));
                style_address = fresh_root+style_offset;
                __asm__("" : "+r"(style_address));
                style_address += unit_id;
                __asm__("" : "+r"(style_address));
                base_style = *style_address;
                __asm__("" : "+r"(base_style));
                y_offset = 0x9F8;
                __asm__("" : "+r"(y_offset));
                row_base += y_offset;
                __asm__("" : "+r"(row_base));
                row_y = *(s16 *)row_base;
                __asm__("" : "+r"(row_y));
                y_offset -= 100;
                __asm__("" : "+r"(y_offset));
                fresh_root += y_offset;
                __asm__("" : "+r"(fresh_root));
                scroll_y = *(s16 *)fresh_root;
                __asm__("" : "+r"(scroll_y));
                row_y -= scroll_y;
                __asm__("" : "+r"(row_y));
                delta = row_y;
            }
            screen_y = delta+44;
            if ((u32)(delta+43)>190)
                goto hide_current;
            {
                register u8 *flags_unit __asm__("r3") = unit;
                register u32 loaded_flags __asm__("r1");
                __asm__("" : "+r"(flags_unit));
                loaded_flags = *(u16 *)(flags_unit+40);
                __asm__("" : "+r"(loaded_flags));
                first_mask = loaded_flags&4;
                __asm__("" : "+r"(first_mask));
                first_flags = loaded_flags;
                __asm__("" : "+r"(first_flags));
            }
            if (first_mask)
                tile_code = 984;
            else if (first_flags&24)
                tile_code = 1004;
            else if (unit_id<=7) {
                register u32 product __asm__("r0") = 20*unit_id;
                __asm__("" : "+r"(product));
                tile_code = product+128;
            } else {
                register s32 adjusted_id __asm__("r1") = unit_id;
                register u32 product __asm__("r0");
                register u32 art_base __asm__("r4");
                __asm__("" : "+r"(adjusted_id));
                adjusted_id -= 8;
                __asm__("" : "+r"(adjusted_id));
                product = 20*adjusted_id;
                __asm__("" : "+r"(product));
                art_base = 664;
                __asm__("" : "+r"(art_base));
                tile_code = product+art_base;
            }
            __asm__("" : "+r"(tile_code));
            {
                register u8 **selection_slot __asm__("r0") = &SceneDisplayRoot;
                register u8 *selection_owner __asm__("r2");
                register u32 selection_offset __asm__("r1");
                register u8 *selection_address __asm__("r0");
                register u32 selection_value __asm__("r0");
                register s32 selection_index __asm__("r4");
                __asm__("" : "+r"(selection_slot));
                selection_owner = *selection_slot;
                __asm__("" : "+r"(selection_owner));
                selection_offset = 0x986;
                __asm__("" : "+r"(selection_offset));
                selection_address = selection_owner+selection_offset;
                __asm__("" : "+r"(selection_address));
                selection_value = *selection_address;
                __asm__("" : "+r"(selection_value));
                selection_index = iteration.index;
                __asm__("" : "+r"(selection_index));
            if ((s32)selection_value != selection_index) {
                u32 style_mask = first_flags&28;
                __asm__("" : "+r"(style_mask));
                row_style = base_style+3;
                if (style_mask)
                    row_style = 0;
                DrawRosterRow(ROSTER_BANK("r1"),ROSTER_DRAW_SLOT(iteration.slot_fixed),0,
                    ROSTER_ROW_X(selection_owner,iteration.byte_offset),(u8)screen_y,0,2,
                    RosterImageTable,RosterFrameTable,ROSTER_TILE_R2(tile_code),(s8)row_style);
            } else {
                masked = first_flags&28;
                if (masked != 0)
                    HideRosterRow(ROSTER_BANK("r4"),ROSTER_HIDE_SLOT(iteration.slot_fixed));
                else
                    DrawRosterRow(ROSTER_BANK("r3"),ROSTER_DRAW_SLOT(iteration.slot_fixed),0,
                        ROSTER_ROW_X(selection_owner,iteration.byte_offset),(u8)screen_y,masked,2,
                        RosterImageTable,RosterFrameTable,ROSTER_TILE_R2(tile_code),(s8)base_style);
            }
            }
            owner = SceneDisplayRoot;
            if (owner[0x970]&2) {
                {
                    register u8 *flags_unit __asm__("r2") = unit;
                    __asm__("" : "+r"(flags_unit));
                    if (!(*(u16 *)(flags_unit+40)&28))
                        goto next_row;
                }
                goto hide_overlay;
            }
            {
                register u32 selection_field __asm__("r4") = 0x986;
                register u8 *selection_address __asm__("r0");
                register u32 selected_row __asm__("r0");
                register s32 current_row __asm__("r1");
                __asm__("" : "+r"(selection_field));
                selection_address = owner+selection_field;
                __asm__("" : "+r"(selection_address));
                selected_row = *selection_address;
                __asm__("" : "+r"(selected_row));
                current_row = iteration.index;
                __asm__("" : "+r"(current_row));
                if ((s32)selected_row != current_row)
                    goto next_row;
            }
            {
                register u8 *flags_unit __asm__("r2") = unit;
                __asm__("" : "+r"(flags_unit));
                if (!(*(u16 *)(flags_unit+40)&28))
                    goto hide_overlay;
            }
            if (unit_id<=7) {
                register u32 product __asm__("r0") = 20*unit_id;
                
                tile_code = product+128;
            } else {
                register s32 adjusted_id __asm__("r1") = unit_id;
                register u32 product __asm__("r0");
                register u32 art_base __asm__("r3");
                
                adjusted_id -= 8;
                
                product = 20*adjusted_id;
                
                /* Actual 664 constant formation, 4 emitted bytes. */
                __asm__("mov %0,#166\n\tlsl %0,%0,#2" : "=l"(art_base) : : "cc");
                tile_code = product+art_base;
            }
            __asm__("" : "+r"(tile_code));
            {
                register u32 cleared __asm__("r4");
                register u8 **selected_root __asm__("r5");
                register u32 row_x_offset __asm__("r9");
                DrawRosterRow(
                    ({ register void **bank_slots __asm__("r4") = RosterSpriteBanks;
                       register void *bank __asm__("r0");
                       __asm__("" : "+r"(bank_slots));
                       bank = bank_slots[1];
                        bank; }),24,0,
                    ({ register u8 *row_address __asm__("r1");
                       register u32 row_offset __asm__("r2");
                       register u32 field_offset __asm__("r3");
                       selected_root = &SceneDisplayRoot;
                       __asm__("" : "+r"(selected_root));
                       row_address = *selected_root;
                       
                       row_offset = iteration.byte_offset;
                       
                       row_address += row_offset;
                       
                       field_offset = 0x9F6;
                       
                       /* Original fullword offset transfer, 2 emitted bytes. */
                       __asm__("mov %0,%1" : "=h"(row_x_offset) : "l"(field_offset));
                       row_address += row_x_offset;
                        *row_address; }),
                    (u8)screen_y,
                    ({ cleared = 0;  cleared; }),2,
                    RosterImageTable,RosterFrameTable,ROSTER_TILE_R1(tile_code),(s8)base_style);
                {
                    register u8 *flags_unit __asm__("r3") = unit;
                    register u32 indicator_flags __asm__("r1");
                    register u32 indicator_mask __asm__("r0");
                    register u32 normalized_mask __asm__("r3");
                    
                    indicator_flags = *(u16 *)(flags_unit+40);
                    
                    /* Original mask and normalization phases, 8 emitted bytes. */
                    __asm__("mov %0,#4\n\tand %0,%0,%1"
                        : "=&l"(indicator_mask) : "l"(indicator_flags) : "cc");
                    __asm__("lsl %0,%0,#16\n\tlsr %1,%0,#16"
                        : "+l"(indicator_mask), "=l"(normalized_mask) : : "cc");
                if (normalized_mask != 0) {
                    register u8 *x_address __asm__("r0") = *selected_root;
                    register u32 row_offset __asm__("r1");
                    register u32 x_field __asm__("r2");
                    register s32 x __asm__("r1");
                    
                    row_offset = iteration.byte_offset;
                    
                    x_address += row_offset;
                    
                    x_field = 0x9F6;
                    __asm__("" : "+r"(x_field));
                    x_address += x_field;
                    
                    x = *(s16 *)x_address;
                    
                    AppendRosterIndicator(FirstRosterIndicator,x,screen_y-12,0,
                        cleared,cleared,cleared,cleared,cleared,10,cleared);
                } else if (indicator_flags&24) {
                    register u8 *x_address __asm__("r0") = *selected_root;
                    register u32 row_offset __asm__("r4");
                    register s32 x __asm__("r1");
                    u32 zero_mask = normalized_mask;
                    register u32 signed_index __asm__("r2");
                    
                    row_offset = iteration.byte_offset;
                    
                    x_address += row_offset;
                    
                    x_address += row_x_offset;
                    /* Actual zero-index signed read, 4 emitted bytes. */
                    __asm__("mov %1,#0\n\tldrsh %0,[%2,%1]"
                        : "=l"(x), "=&l"(signed_index)
                        : "l"(x_address), "m"(*(s16 *)x_address) : "cc");
                    
                    AppendRosterIndicator(SecondRosterIndicator,x,screen_y-12,0,
                        zero_mask,zero_mask,zero_mask,zero_mask,zero_mask,10,zero_mask);
                }
                }
            }
            goto next_row;
        hide_overlay:
            HideRosterRow(ROSTER_BANK("r3"),24);
            goto next_row;
        hide_current:
            HideRosterRow(ROSTER_BANK("r4"),ROSTER_HIDE_SLOT(iteration.slot_fixed));
        next_row:
            {
                register u32 next_offset __asm__("r3") = iteration.byte_offset;
                register u32 next_slot __asm__("r4");
                register u32 slot_step __asm__("r0");
                register u8 **count_slot __asm__("r2");
                register u8 *count_address __asm__("r0");
                register u32 count_field __asm__("r3");
                __asm__("" : "+r"(next_offset));
                next_offset += 20;
                __asm__("" : "+r"(next_offset));
                iteration.byte_offset = next_offset;
                __asm__("" : "+m"(iteration.byte_offset));
                next_slot = iteration.slot_fixed;
                __asm__("" : "+r"(next_slot));
                slot_step = 0x10000;
                __asm__("" : "+r"(slot_step));
                next_slot += slot_step;
                __asm__("" : "+r"(next_slot));
                iteration.slot_fixed = next_slot;
                __asm__("" : "+m"(iteration.slot_fixed));
                next_index = iteration.index+1;
                iteration.index = next_index;
                __asm__("" : "+m"(iteration.index));
                count_slot = &SceneDisplayRoot;
                __asm__("" : "+r"(count_slot));
                count_address = *count_slot;
                __asm__("" : "+r"(count_address));
                count_field = 0x95C;
                __asm__("" : "+r"(count_field));
                count_address += count_field;
                __asm__("" : "+r"(count_address));
                next_count = *count_address;
                __asm__("" : "+r"(next_count));
            }
        } while (next_index < (s32)next_count);
    }
final_marker:
    {
        register u8 **final_slot __asm__("r4") = &SceneDisplayRoot;
        register u8 *final_owner __asm__("r2");
        register u32 row_y_field __asm__("r1");
        register u8 *row_y_address __asm__("r0");
        register s32 row_y __asm__("r0");
        register u32 signed_index __asm__("r3");
        register u32 scroll_field __asm__("r4");
        register u8 *scroll_address __asm__("r1");
        register s32 scroll_y __asm__("r1");
        register u8 *marker_address __asm__("r0");
        __asm__("" : "+r"(final_slot));
        final_owner = *final_slot;
        __asm__("" : "+r"(final_owner));
        row_y_field = 0x97A;
        __asm__("" : "+r"(row_y_field));
        row_y_address = final_owner+row_y_field;
        __asm__("" : "+r"(row_y_address));
        /* Actual zero-index signed read, 4 emitted bytes. */
        __asm__("mov %1,#0\n\tldrsh %0,[%2,%1]"
            : "=l"(row_y), "=&l"(signed_index)
            : "l"(row_y_address), "m"(*(s16 *)row_y_address) : "cc");
        __asm__("" : "+r"(row_y));
        scroll_field = 0x994;
        __asm__("" : "+r"(scroll_field));
        scroll_address = final_owner+scroll_field;
        __asm__("" : "+r"(scroll_address));
        scroll_y = *(s16 *)scroll_address;
        __asm__("" : "+r"(scroll_y));
        row_y -= scroll_y;
        __asm__("" : "+r"(row_y));
        screen_y = row_y+44;
        __asm__("" : "+r"(screen_y));
        scroll_field -= 30;
        __asm__("" : "+r"(scroll_field));
        marker_address = final_owner+scroll_field;
        __asm__("" : "+r"(marker_address));
        *(u16 *)marker_address = (u16)screen_y;
        UpdateRosterRowPosition(RosterSpriteBanks[1],25,
            ({ register u32 marker_x_field __asm__("r1") = 0x978;
               __asm__("" : "+r"(marker_x_field));
               final_owner += marker_x_field;
               __asm__("" : "+r"(final_owner)); *final_owner; }), (u8)screen_y);
    }
}
