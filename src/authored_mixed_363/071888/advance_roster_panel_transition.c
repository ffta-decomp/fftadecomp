typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *SceneDisplayRoot;
extern u8 UnitPool[];
extern void *RosterSpriteBanks[];
extern u8 *RosterPanelTasks[];
extern const u8 RosterImageTable[];
extern const u8 RosterFrameTable[];
extern void DrawRosterRow(void *,u32,u32,u32,u32,u32,u32,const void *,const void *,u32,s32);
extern void HideRosterRow(void *,u32);
extern void UpdateRosterRowPosition(void *,u32,u32,u32);
extern void ReplaceRosterPropertyPanel(void *,u32,u32);
__asm__(".global SceneDisplayRoot\n.set SceneDisplayRoot,0x03002818\n"
        ".global UnitPool\n.set UnitPool,0x02000080\n"
        ".global RosterSpriteBanks\n.set RosterSpriteBanks,0x03000e30\n"
        ".global RosterPanelTasks\n.set RosterPanelTasks,0x03002730\n"
        ".global RosterImageTable\n.set RosterImageTable,0x0894eae0\n"
        ".global RosterFrameTable\n.set RosterFrameTable,0x0894eb6c\n"
        ".global DrawRosterRow\n.thumb_set DrawRosterRow,0x0804c525\n"
        ".global HideRosterRow\n.thumb_set HideRosterRow,0x0804c7a1\n"
        ".global UpdateRosterRowPosition\n.thumb_set UpdateRosterRowPosition,0x0804c789\n"
        ".global ReplaceRosterPropertyPanel\n.thumb_set ReplaceRosterPropertyPanel,0x080717cd");
#define BANK_AT(base,home) ({ register void **actual_bank __asm__(home) = (base); __asm__("" : "+r"(actual_bank)); actual_bank[1]; })
#define ROW_SLOT(value,home) ({ register s32 full_slot __asm__(home) = (value); register u32 projected_slot __asm__("r1"); __asm__("" : "+r"(full_slot)); projected_slot = (u16)full_slot; __asm__("" : "+r"(projected_slot)); projected_slot; })
#define ROW_TILE(value) ({ register u32 projected_tile __asm__("r2") = (u16)(value); __asm__("" : "+r"(projected_tile)); projected_tile; })
/* Four bounded mixed signed-halfword reads (16 emitted instruction bytes).
 * The original needs an explicit low zero-index scratch. Ordinary typed C
 * leaves this reload scratch to Thumb sign-extend lowering. Address and exact
 * halfword memory are inputs; the actual LDRSH defines the signed result and
 * MOV defines the early-clobber scratch. No hidden stores or hard R7. */
#define SIGNED_HALF_AT(address,result_home,scratch_home) ({ \
    register s32 signed_value __asm__(result_home); \
    register u32 zero_index __asm__(scratch_home); \
    __asm__("mov %1,#0\n\tldrsh %0,[%2,%1]" \
        : "=l"(signed_value), "=&l"(zero_index) \
        : "l"(address), "m"(*(s16 *)(address)) : "cc"); \
    signed_value; \
})
#define SIGNED_ROW_C(address) (*(address))
#define SIGNED_ROW_R2(address) SIGNED_HALF_AT(address,"r1","r2")
#define SIGNED_POSITION_R3(address) SIGNED_HALF_AT(address,"r0","r3")
#define SLIDING_ROW_X(row_base,root_base,operation,x_home,signed_read) ({ \
    register u32 x_offset __asm__(x_home) = 0x9f6; \
    register s16 *x_address __asm__("r0"); \
    register s32 row_x __asm__("r1"); \
    register u32 tick_offset __asm__("r5"); \
    register u16 *tick_address __asm__("r0"); \
    register u32 tick_step __asm__("r0"); \
    __asm__("" : "+r"(x_offset)); \
    x_address = (s16 *)((row_base) + x_offset); \
    __asm__("" : "+r"(x_address)); \
    row_x = signed_read(x_address); \
    __asm__("" : "+r"(row_x)); \
    tick_offset = 0xbe4; \
    __asm__("" : "+r"(tick_offset)); \
    tick_address = (u16 *)((root_base) + tick_offset); \
    __asm__("" : "+r"(tick_address)); \
    tick_step = *tick_address; \
    __asm__("" : "+r"(tick_step)); \
    tick_step <<= 3; \
    __asm__("" : "+r"(tick_step)); \
    row_x operation tick_step; \
})
/* The two arms deliberately have distinct lifetimes and initialization. */
u32 AdvanceRosterPanelTransition(u32 direction) __asm__("CoreGlobal36_00071888");
u32 AdvanceRosterPanelTransition(u32 direction)
{
    register u32 working_direction __asm__("r2") = direction;
    register u8 **opening_slot __asm__("r4");
    register u8 *opening_owner __asm__("r1");
    register u32 opening_tick_offset __asm__("r3");
    register u8 *opening_tick_address __asm__("r0");
    register u32 tick __asm__("r0");
    register u16 *final_tick __asm__("r1");
    u8 **root_slot;
    register u8 *owner __asm__("r3");
    s32 working_y;
    __asm__("" : "+r"(working_direction));
    opening_slot = &SceneDisplayRoot;
    __asm__("" : "+r"(opening_slot));
    root_slot = &SceneDisplayRoot;
    opening_owner = *opening_slot;
    __asm__("" : "+r"(opening_owner));
    opening_tick_offset = 0xbe4;
    __asm__("" : "+r"(opening_tick_offset));
    opening_tick_address = opening_owner + opening_tick_offset;
    __asm__("" : "+r"(opening_tick_address));
    tick = *(u16 *)opening_tick_address;
    __asm__("" : "+r"(tick));
    if (tick > 29)
        return 1;
    if (working_direction != 0) {
        register s32 initial_index __asm__("r5") = 0;
        register s32 index __asm__("r8");
        register u32 count_offset __asm__("r2");
        register u8 *count_address __asm__("r0");
        u32 row_offset;
        register u32 continuation_count __asm__("r0");
        __asm__("" : "+r"(initial_index));
        index = initial_index;
        __asm__("" : "+r"(index));
        count_offset = 0x95c;
        __asm__("" : "+r"(count_offset));
        count_address = opening_owner + count_offset;
        __asm__("" : "+r"(count_address));
        if (index < (s32)*count_address) {
            register void **initial_bank __asm__("r3") = RosterSpriteBanks;
            register void **banks __asm__("r10");
            register u32 initial_offset __asm__("r4");
            __asm__("" : "+r"(initial_bank));
            banks = initial_bank;
            __asm__("" : "+r"(banks));
            initial_offset = 0;
            __asm__("" : "+r"(initial_offset));
            row_offset = initial_offset;
            __asm__("" : "+m"(row_offset));
            do {
                register s32 unit_id __asm__("r4");
                register s32 screen_x __asm__("r5");
                register u32 tile_or_clip __asm__("r6");
                register u8 *row __asm__("r2");
                register u8 *iteration_root __asm__("r1");
                register u8 *fresh_root __asm__("r3");
                u32 style;
                {
                    register u8 **iteration_slot __asm__("r5") = &SceneDisplayRoot;
                    register u32 id_offset __asm__("r2");
                    register u8 *id_address __asm__("r0");
                    register u32 stored_row_offset __asm__("r3");
                    register u32 descriptor_offset __asm__("r5");
                    register u32 stored_index __asm__("r0");
                    register u8 **fresh_slot __asm__("r1");
                    register u32 fresh_row_offset __asm__("r5");
                    register u32 id_field_offset __asm__("r1");
                    register u16 *id_destination __asm__("r0");
                    __asm__("" : "+r"(iteration_slot));
                    iteration_root = *iteration_slot;
                    __asm__("" : "+r"(iteration_root));
                    id_offset = 0x9ba;
                    __asm__("" : "+r"(id_offset));
                    id_address = iteration_root + id_offset;
                    __asm__("" : "+r"(id_address));
                    id_address += index;
                    __asm__("" : "+r"(id_address));
                    unit_id = *id_address;
                    __asm__("" : "+r"(unit_id));
                    stored_row_offset = row_offset;
                    __asm__("" : "+r"(stored_row_offset));
                    iteration_root += stored_row_offset;
                    __asm__("" : "+r"(iteration_root));
                    descriptor_offset = 0x9ee;
                    __asm__("" : "+r"(descriptor_offset));
                    iteration_root += descriptor_offset;
                    __asm__("" : "+r"(iteration_root));
                    stored_index = index;
                    __asm__("" : "+r"(stored_index));
                    *iteration_root = (u8)stored_index;
                    fresh_slot = &SceneDisplayRoot;
                    __asm__("" : "+r"(fresh_slot));
                    fresh_root = *fresh_slot;
                    __asm__("" : "+r"(fresh_root));
                    fresh_row_offset = row_offset;
                    __asm__("" : "+r"(fresh_row_offset));
                    row = fresh_root + fresh_row_offset;
                    __asm__("" : "+r"(row));
                    id_field_offset = 0x9f0;
                    __asm__("" : "+r"(id_field_offset));
                    id_destination = (u16 *)(row + id_field_offset);
                    __asm__("" : "+r"(id_destination));
                    *id_destination = (u16)unit_id;
                }
                {
                    register u32 y_offset __asm__("r5") = 0x9f8;
                    register s16 *y_address __asm__("r0");
                    register s32 row_y __asm__("r1");
                    register u32 origin_offset __asm__("r5");
                    register s16 *origin_address __asm__("r0");
                    register s32 origin_y __asm__("r0");
                    __asm__("" : "+r"(y_offset));
                    y_address = (s16 *)(row + y_offset);
                    __asm__("" : "+r"(y_address));
                    row_y = *y_address;
                    __asm__("" : "+r"(row_y));
                    origin_offset = 0x994;
                    __asm__("" : "+r"(origin_offset));
                    origin_address = (s16 *)(fresh_root + origin_offset);
                    __asm__("" : "+r"(origin_address));
                    origin_y = *origin_address;
                    __asm__("" : "+r"(origin_y));
                    row_y -= origin_y;
                    __asm__("" : "+r"(row_y));
                    working_y = row_y + 44;
                }
                if (*(u16 *)(row + 0x9f4) & 1)
                    screen_x = SLIDING_ROW_X(row,fresh_root,-,"r5",SIGNED_ROW_C);
                else
                    screen_x = SLIDING_ROW_X(row,fresh_root,+,"r1",SIGNED_ROW_R2);
                __asm__("" : "+r"(screen_x));
                iteration_root = *root_slot;
                __asm__("" : "+r"(iteration_root));
                {
                    register u32 selection_offset __asm__("r2") = 0x986;
                    register u8 *selection_address __asm__("r0");
                    register u32 selection __asm__("r0");
                    __asm__("" : "+r"(selection_offset));
                    selection_address = iteration_root + selection_offset;
                    __asm__("" : "+r"(selection_address));
                    selection = *selection_address;
                    __asm__("" : "+r"(selection));
                    tile_or_clip = (u32)(working_y - 1);
                    __asm__("" : "+r"(tile_or_clip));
                    if ((s32)selection == index) {
                        register u32 selected_id_offset __asm__("r3") = 0x9ba;
                        register u8 *selected_id_address __asm__("r0");
                        register u32 selected_id __asm__("r1");
                        register u32 selected_product __asm__("r0");
                        register u8 *unit_base __asm__("r1");
                        register u8 *selected_pointer __asm__("r0");
                        register u8 *selected_unit __asm__("r9");
                        register u8 *selected_low __asm__("r3");
                        register u32 selected_flags __asm__("r1");
                        __asm__("" : "+r"(selected_id_offset));
                        selected_id_address = iteration_root + selected_id_offset;
                        __asm__("" : "+r"(selected_id_address));
                        selected_id_address += index;
                        __asm__("" : "+r"(selected_id_address));
                        selected_id = *selected_id_address;
                        __asm__("" : "+r"(selected_id));
                        selected_product = selected_id * 264;
                        __asm__("" : "+r"(selected_product));
                        unit_base = UnitPool;
                        __asm__("" : "+r"(unit_base));
                        selected_pointer = (u8 *)(selected_product + (u32)unit_base);
                        __asm__("" : "+r"(selected_pointer));
                        selected_unit = selected_pointer;
                        __asm__("" : "+r"(selected_unit));
                    if (tile_or_clip <= 190 && screen_x > 0 && screen_x <= 219)
                        UpdateRosterRowPosition(BANK_AT(banks,"r1"),25,(u8)screen_x,(u8)working_y);
                    else
                        HideRosterRow(BANK_AT(banks,"r2"),25);
                    selected_low = selected_unit;
                    __asm__("" : "+r"(selected_low));
                    selected_flags = *(u16 *)(selected_low + 40);
                    __asm__("" : "+r"(selected_flags));
                    if (selected_flags & 28) {
                        if (tile_or_clip <= 190 && screen_x > 0 && screen_x <= 219)
                            UpdateRosterRowPosition(BANK_AT(banks,"r1"),24,(u8)screen_x,(u8)working_y);
                        else
                            HideRosterRow(BANK_AT(banks,"r2"),24);
                    }
                }
                }
                if (tile_or_clip <= 190 && screen_x > -16 && screen_x <= 219) {
                    if (unit_id <= 7) {
                        register u32 product __asm__("r0") = 20 * (u32)unit_id;
                        __asm__("" : "+r"(product));
                        tile_or_clip = product;
                        __asm__("" : "+r"(tile_or_clip));
                        tile_or_clip += 128;
                    } else {
                        register s32 adjusted_id __asm__("r1") = unit_id - 8;
                        register u32 product __asm__("r0");
                        register u32 tile_bias __asm__("r3");
                        __asm__("" : "+r"(adjusted_id));
                        product = 20 * (u32)adjusted_id;
                        __asm__("" : "+r"(product));
                        tile_bias = 664;
                        __asm__("" : "+r"(tile_bias));
                        tile_or_clip = product + tile_bias;
                    }
                    __asm__("" : "+r"(tile_or_clip));
                    {
                        register u8 **style_slot __asm__("r4") = &SceneDisplayRoot;
                        register u8 *style_root __asm__("r0");
                        register u32 style_offset __asm__("r1");
                        __asm__("" : "+r"(style_slot));
                        style_root = *style_slot;
                        __asm__("" : "+r"(style_root));
                        style_offset = 0xbcc;
                        __asm__("" : "+r"(style_offset));
                        style_root += style_offset;
                        __asm__("" : "+r"(style_root));
                        style_root += index;
                        __asm__("" : "+r"(style_root));
                        style = *style_root + 3;
                    }
                    DrawRosterRow(BANK_AT(banks,"r2"),ROW_SLOT(index,"r3"),0,(u8)screen_x,(u8)working_y,0,1,
                        RosterImageTable,RosterFrameTable,ROW_TILE(tile_or_clip),(s8)style);
                } else {
                    HideRosterRow(BANK_AT(banks,"r4"),ROW_SLOT(index,"r5"));
                }
                row_offset += 20;
                __asm__("" : "+m"(row_offset));
                {
                    register s32 index_step __asm__("r1") = 1;
                    register u8 **continuation_slot __asm__("r2");
                    register u8 *continuation_address __asm__("r0");
                    register u32 continuation_offset __asm__("r3");
                    __asm__("" : "+r"(index_step));
                    index += index_step;
                    __asm__("" : "+r"(index));
                    continuation_slot = &SceneDisplayRoot;
                    __asm__("" : "+r"(continuation_slot));
                    continuation_address = *continuation_slot;
                    __asm__("" : "+r"(continuation_address));
                    continuation_offset = 0x95c;
                    __asm__("" : "+r"(continuation_offset));
                    continuation_address += continuation_offset;
                    __asm__("" : "+r"(continuation_address));
                    continuation_count = *continuation_address;
                    __asm__("" : "+r"(continuation_count));
                }
            } while (index < (s32)continuation_count);
        }
        {
            register u8 **tick_slot __asm__("r4") = &SceneDisplayRoot;
            register u8 *tick_root __asm__("r1");
            register u32 tick_offset __asm__("r5");
            __asm__("" : "+r"(tick_slot));
            tick_root = *tick_slot;
            __asm__("" : "+r"(tick_root));
            tick_offset = 0xbe4;
            __asm__("" : "+r"(tick_offset));
            final_tick = (u16 *)(tick_root + tick_offset);
            __asm__("" : "+r"(final_tick));
        }
    } else {
        register s32 index __asm__("r8");
        register s32 initial_row_zero __asm__("r5");
        register s32 panel_x __asm__("r5");
        register u16 *panel_destination __asm__("r1");
        register u32 panel_value __asm__("r0");
        register u32 panel_tick __asm__("r0");
        register u8 **position_slot __asm__("r4");
        if (tick == 0) {
            register u32 selected_offset __asm__("r2") = 0x987;
            register u8 *selected_address __asm__("r0");
            register u32 selected_id __asm__("r1");
            register u8 *selection_root __asm__("r1");
            register u32 selection_offset __asm__("r3");
            register u8 *selection_address __asm__("r1");
            __asm__("" : "+r"(selected_offset));
            selected_address = opening_owner + selected_offset;
            __asm__("" : "+r"(selected_address));
            selected_id = *selected_address;
            __asm__("" : "+r"(selected_id));
            ReplaceRosterPropertyPanel(UnitPool + 264 * selected_id,0,3);
            RosterPanelTasks[3][5] = 3;
            selection_root = *opening_slot;
            __asm__("" : "+r"(selection_root));
            selection_offset = 0x986;
            __asm__("" : "+r"(selection_offset));
            selection_address = selection_root + selection_offset;
            __asm__("" : "+r"(selection_address));
            HideRosterRow(RosterSpriteBanks[1],*selection_address);
        }
        {
            register u8 *control_root __asm__("r1") = *opening_slot;
            register u32 state_offset __asm__("r5");
            register u8 *state_address __asm__("r0");
            register u32 state __asm__("r0");
            __asm__("" : "+r"(control_root));
            state_offset = 0x450;
            __asm__("" : "+r"(state_offset));
            state_address = control_root + state_offset;
            __asm__("" : "+r"(state_address));
            state = *state_address;
            __asm__("" : "+r"(state));
            if (state == 8) {
                register u32 count_offset __asm__("r0") = 0x453;
                register u8 *count_address __asm__("r1");
                register u32 count __asm__("r0");
                __asm__("" : "+r"(count_offset));
                count_address = control_root + count_offset;
                __asm__("" : "+r"(count_address));
                count = *count_address;
                __asm__("" : "+r"(count));
                if (count != 0) {
                    register u8 *publication_address __asm__("r0");
                    register u32 publication_offset __asm__("r1");
                    register u32 published __asm__("r1");
                    register u8 *count_root __asm__("r2");
                    register u32 fresh_count_offset __asm__("r3");
                    register u8 *fresh_count_address __asm__("r0");
                    register u32 position_value __asm__("r0");
                    register u32 position_offset __asm__("r4");
                    register u16 *position_address __asm__("r1");
                    register u32 final_value __asm__("r0");
                    count -= 1;
                    *count_address = (u8)count;
                    publication_address = *opening_slot;
                    __asm__("" : "+r"(publication_address));
                    publication_offset = 0x452;
                    __asm__("" : "+r"(publication_offset));
                    publication_address += publication_offset;
                    __asm__("" : "+r"(publication_address));
                    published = 1;
                    __asm__("" : "+r"(published));
                    *publication_address = (u8)published;
                    count_root = *opening_slot;
                    __asm__("" : "+r"(count_root));
                    fresh_count_offset = 0x453;
                    __asm__("" : "+r"(fresh_count_offset));
                    fresh_count_address = count_root + fresh_count_offset;
                    __asm__("" : "+r"(fresh_count_address));
                    position_value = *fresh_count_address;
                    __asm__("" : "+r"(position_value));
                    position_value <<= 3;
                    __asm__("" : "+r"(position_value));
                    position_value = 0 - position_value;
                    __asm__("" : "+r"(position_value));
                    position_offset = 0x458;
                    __asm__("" : "+r"(position_offset));
                    position_address = (u16 *)(count_root + position_offset);
                    __asm__("" : "+r"(position_address));
                    *position_address = (u16)position_value;
                    state_offset += 10;
                    __asm__("" : "+r"(state_offset));
                    count_root += state_offset;
                    __asm__("" : "+r"(count_root));
                    final_value = 56;
                    __asm__("" : "+r"(final_value));
                    *(u16 *)count_root = (u16)final_value;
                }
            }
        }
        {
            register u8 **panel_slot __asm__("r0") = &SceneDisplayRoot;
            register u32 panel_tick_offset __asm__("r1");
            register u16 *panel_tick_address __asm__("r0");
            __asm__("" : "+r"(panel_slot));
            owner = *panel_slot;
            __asm__("" : "+r"(owner));
            panel_tick_offset = 0xbe4;
            __asm__("" : "+r"(panel_tick_offset));
            panel_tick_address = (u16 *)(owner + panel_tick_offset);
            __asm__("" : "+r"(panel_tick_address));
            panel_tick = *panel_tick_address;
            __asm__("" : "+r"(panel_tick));
        }
        if (panel_tick <= 28) {
            register u32 destination_offset __asm__("r2") = 0xbe8;
            register u16 *destination __asm__("r1");
            register u32 source_offset __asm__("r4");
            register u16 *source __asm__("r0");
            register u32 value __asm__("r0");
            register u32 previous __asm__("r5");
            register u32 final_destination_offset __asm__("r0");
            register u32 final_previous __asm__("r3");
            __asm__("" : "+r"(destination_offset));
            destination = (u16 *)(owner + destination_offset);
            __asm__("" : "+r"(destination));
            source_offset = 0xbec;
            __asm__("" : "+r"(source_offset));
            source = (u16 *)(owner + source_offset);
            __asm__("" : "+r"(source));
            value = *source;
            __asm__("" : "+r"(value));
            previous = *destination;
            __asm__("" : "+r"(previous));
            value += previous;
            __asm__("" : "+r"(value));
            *destination = (u16)value;
            final_destination_offset = 0xbea;
            __asm__("" : "+r"(final_destination_offset));
            panel_destination = (u16 *)(owner + final_destination_offset);
            __asm__("" : "+r"(panel_destination));
            destination_offset += 6;
            __asm__("" : "+r"(destination_offset));
            source = (u16 *)(owner + destination_offset);
            __asm__("" : "+r"(source));
            panel_value = *source;
            __asm__("" : "+r"(panel_value));
            final_previous = *panel_destination;
            __asm__("" : "+r"(final_previous));
            panel_value += final_previous;
            __asm__("" : "+r"(panel_value));
        } else {
            register u32 source_offset __asm__("r4") = 0xbf0;
            register u16 *source __asm__("r0");
            register u32 value __asm__("r1");
            register u32 destination_offset __asm__("r5");
            register u16 *destination __asm__("r0");
            register u32 cleared __asm__("r2");
            register u32 second_source_offset __asm__("r1");
            register u32 final_destination_offset __asm__("r0");
            __asm__("" : "+r"(source_offset));
            source = (u16 *)(owner + source_offset);
            __asm__("" : "+r"(source));
            value = *source;
            __asm__("" : "+r"(value));
            destination_offset = 0xbe8;
            __asm__("" : "+r"(destination_offset));
            destination = (u16 *)(owner + destination_offset);
            __asm__("" : "+r"(destination));
            cleared = 0;
            __asm__("" : "+r"(cleared));
            *destination = (u16)value;
            second_source_offset = 0xbf2;
            __asm__("" : "+r"(second_source_offset));
            source = (u16 *)(owner + second_source_offset);
            __asm__("" : "+r"(source));
            value = *source;
            __asm__("" : "+r"(value));
            source_offset -= 6;
            __asm__("" : "+r"(source_offset));
            destination = (u16 *)(owner + source_offset);
            __asm__("" : "+r"(destination));
            *destination = (u16)value;
            destination_offset = 0x458;
            __asm__("" : "+r"(destination_offset));
            destination = (u16 *)(owner + destination_offset);
            __asm__("" : "+r"(destination));
            *destination = (u16)cleared;
            final_destination_offset = 0x45a;
            __asm__("" : "+r"(final_destination_offset));
            panel_destination = (u16 *)(owner + final_destination_offset);
            __asm__("" : "+r"(panel_destination));
            panel_value = 56;
            __asm__("" : "+r"(panel_value));
        }
        *panel_destination = (u16)panel_value;
        position_slot = &SceneDisplayRoot;
        __asm__("" : "+r"(position_slot));
        {
            register u8 *position_owner __asm__("r1") = *position_slot;
            __asm__("" : "+r"(position_owner));
            {
                register u32 source_offset __asm__("r2") = 0xbe8;
                register s16 *source_address __asm__("r0");
                register s32 raw_position __asm__("r0");
                register u32 x_destination_offset __asm__("r2");
                register u32 y_destination_offset __asm__("r3");
                register u16 *destination __asm__("r0");
                __asm__("" : "+r"(source_offset));
                source_address = (s16 *)(position_owner + source_offset);
                __asm__("" : "+r"(source_address));
                raw_position = SIGNED_POSITION_R3(source_address);
                __asm__("" : "+r"(raw_position));
                panel_x = raw_position / 8;
                __asm__("" : "+r"(panel_x));
                source_offset = 0xbea;
                __asm__("" : "+r"(source_offset));
                source_address = (s16 *)(position_owner + source_offset);
                __asm__("" : "+r"(source_address));
                raw_position = SIGNED_POSITION_R3(source_address);
                __asm__("" : "+r"(raw_position));
                working_y = raw_position / 8;
                __asm__("" : "+r"(working_y));
                x_destination_offset = 0x436;
                __asm__("" : "+r"(x_destination_offset));
                destination = (u16 *)(position_owner + x_destination_offset);
                __asm__("" : "+r"(destination));
                *destination = (u16)panel_x;
                y_destination_offset = 0x438;
                __asm__("" : "+r"(y_destination_offset));
                destination = (u16 *)(position_owner + y_destination_offset);
                __asm__("" : "+r"(destination));
                *destination = (u16)working_y;
            }
            UpdateRosterRowPosition(RosterSpriteBanks[1],25,(u8)panel_x,(u8)working_y);
        }
        initial_row_zero = 0;
        __asm__("" : "+r"(initial_row_zero));
        index = initial_row_zero;
        __asm__("" : "+r"(index));
        if (index < (s32)(*position_slot)[0x95c]) {
            register u8 **row_root_slot __asm__("r9") = position_slot;
            register u32 row_offset __asm__("r10") = (u32)initial_row_zero;
            register u32 continuation_count __asm__("r0");
            __asm__("" : "+r"(row_root_slot), "+r"(row_offset));
            do {
                register s32 unit_id __asm__("r4");
                register s32 screen_x __asm__("r5");
                register u32 tile __asm__("r6");
                register u32 descriptor_offset __asm__("r5");
                register u8 *row __asm__("r2");
                register u8 *iteration_root __asm__("r1");
                register u8 *fresh_root __asm__("r3");
                u32 style;
                {
                    register u8 **iteration_slot __asm__("r2") = row_root_slot;
                    register u32 id_offset __asm__("r3");
                    register u8 *id_address __asm__("r0");
                    register u32 stored_index __asm__("r0");
                    register u32 fresh_row_offset __asm__("r1");
                    register u16 *id_destination __asm__("r0");
                    __asm__("" : "+r"(iteration_slot));
                    iteration_root = *iteration_slot;
                    __asm__("" : "+r"(iteration_root));
                    id_offset = 0x9ba;
                    __asm__("" : "+r"(id_offset));
                    id_address = iteration_root + id_offset;
                    __asm__("" : "+r"(id_address));
                    id_address += index;
                    __asm__("" : "+r"(id_address));
                    unit_id = *id_address;
                    __asm__("" : "+r"(unit_id));
                    iteration_root += row_offset;
                    __asm__("" : "+r"(iteration_root));
                    descriptor_offset = 0x9ee;
                    __asm__("" : "+r"(descriptor_offset));
                    iteration_root += descriptor_offset;
                    __asm__("" : "+r"(iteration_root));
                    stored_index = index;
                    __asm__("" : "+r"(stored_index));
                    *iteration_root = (u8)stored_index;
                    fresh_root = *iteration_slot;
                    __asm__("" : "+r"(fresh_root));
                    fresh_row_offset = row_offset;
                    __asm__("" : "+r"(fresh_row_offset));
                    row = fresh_root + fresh_row_offset;
                    __asm__("" : "+r"(row));
                    descriptor_offset += 2;
                    __asm__("" : "+r"(descriptor_offset));
                    id_destination = (u16 *)(row + descriptor_offset);
                    __asm__("" : "+r"(id_destination));
                    *id_destination = (u16)unit_id;
                }
                if ((s32)fresh_root[0x986] != index) {
                    descriptor_offset += 8;
                    __asm__("" : "+r"(descriptor_offset));
                    {
                        register s16 *y_address __asm__("r0") = (s16 *)(row + descriptor_offset);
                        register s32 row_y __asm__("r1");
                        register u32 origin_offset __asm__("r5");
                        register s16 *origin_address __asm__("r0");
                        register s32 origin_y __asm__("r0");
                        __asm__("" : "+r"(y_address));
                        row_y = *y_address;
                        __asm__("" : "+r"(row_y));
                        origin_offset = 0x994;
                        __asm__("" : "+r"(origin_offset));
                        origin_address = (s16 *)(fresh_root + origin_offset);
                        __asm__("" : "+r"(origin_address));
                        origin_y = *origin_address;
                        __asm__("" : "+r"(origin_y));
                        row_y -= origin_y;
                        __asm__("" : "+r"(row_y));
                        working_y = row_y + 44;
                    }
                    if (*(u16 *)(row + 0x9f4) & 1)
                        screen_x = SLIDING_ROW_X(row,fresh_root,-,"r5",SIGNED_ROW_C);
                    else
                        screen_x = SLIDING_ROW_X(row,fresh_root,+,"r1",SIGNED_ROW_R2);
                    __asm__("" : "+r"(screen_x));
                    if ((u32)(working_y - 1) <= 190 && screen_x > -16 && screen_x <= 219) {
                        if (unit_id <= 7) {
                            register u32 product __asm__("r0") = 20 * (u32)unit_id;
                            __asm__("" : "+r"(product));
                            tile = product;
                            __asm__("" : "+r"(tile));
                            tile += 128;
                        } else {
                            register s32 adjusted_id __asm__("r1") = unit_id - 8;
                            register u32 product __asm__("r0");
                            register u32 tile_bias __asm__("r1");
                            __asm__("" : "+r"(adjusted_id));
                            product = 20 * (u32)adjusted_id;
                            __asm__("" : "+r"(product));
                            tile_bias = 664;
                            __asm__("" : "+r"(tile_bias));
                            tile = product + tile_bias;
                        }
                        __asm__("" : "+r"(tile));
                        {
                            register u8 **style_slot __asm__("r2") = row_root_slot;
                            register u8 *style_root __asm__("r0");
                            register u32 style_offset __asm__("r3");
                            __asm__("" : "+r"(style_slot));
                            style_root = *style_slot;
                            __asm__("" : "+r"(style_root));
                            style_offset = 0xbcc;
                            __asm__("" : "+r"(style_offset));
                            style_root += style_offset;
                            __asm__("" : "+r"(style_root));
                            style_root += index;
                            __asm__("" : "+r"(style_root));
                            style = *style_root + 3;
                        }
                        DrawRosterRow(RosterSpriteBanks[1],ROW_SLOT(index,"r2"),0,(u8)screen_x,(u8)working_y,0,1,
                            RosterImageTable,RosterFrameTable,ROW_TILE(tile),(s8)style);
                    } else {
                        HideRosterRow(RosterSpriteBanks[1],ROW_SLOT(index,"r3"));
                    }
                }
                {
                    register u32 row_step __asm__("r4") = 20;
                    register s32 index_step __asm__("r5");
                    register u8 **continuation_slot __asm__("r1");
                    register u8 *continuation_address __asm__("r0");
                    register u32 continuation_offset __asm__("r2");
                    __asm__("" : "+r"(row_step));
                    row_offset += row_step;
                    __asm__("" : "+r"(row_offset));
                    index_step = 1;
                    __asm__("" : "+r"(index_step));
                    index += index_step;
                    __asm__("" : "+r"(index));
                    continuation_slot = row_root_slot;
                    __asm__("" : "+r"(continuation_slot));
                    continuation_address = *continuation_slot;
                    __asm__("" : "+r"(continuation_address));
                    continuation_offset = 0x95c;
                    __asm__("" : "+r"(continuation_offset));
                    continuation_address += continuation_offset;
                    __asm__("" : "+r"(continuation_address));
                    continuation_count = *continuation_address;
                    __asm__("" : "+r"(continuation_count));
                }
            } while (index < (s32)continuation_count);
        }
        {
            register u8 **tick_slot __asm__("r0") = &SceneDisplayRoot;
            register u8 *tick_root __asm__("r1");
            register u32 tick_offset __asm__("r3");
            __asm__("" : "+r"(tick_slot));
            tick_root = *tick_slot;
            __asm__("" : "+r"(tick_root));
            tick_offset = 0xbe4;
            __asm__("" : "+r"(tick_offset));
            final_tick = (u16 *)(tick_root + tick_offset);
            __asm__("" : "+r"(final_tick));
        }
    }
    *final_tick += 1;
    return 0;
}
