typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
extern u8 *SceneDisplayRoot;
extern u8 PanelBufferState[];
extern u8 PanelLayouts[];
extern u8 ResourceScratch[];
extern const u8 UnitMenuLabels[];
extern u8 LabelTileBuffer[];
extern void *ConfigureUnitPanel(u32,u32,void *,void *,void *,void *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void NativeCpuSet(const void *,void *,u32);
extern u16 *GetWindowCell(u32,u32,u32,u32);
extern void DrawWindowTileRun(u32,u16 *,u32,u32,u32);
extern void DrawUnitMenuLabel(u8 *,u8 *,const u8 *,u32,u32);
extern void RenderUnitPanelFrame(u16 *,u32,u32,u32,u32,u32,u32);
extern void FillUnitPanelRows(u16 *,u32,u32,u32,u32,u32,u32);
extern u32 LoadUnitPanelResource(void *,u32,u32);
extern void WriteUnitPanelTiles(u32,u16 *,u32,u32);
__asm__(".global SceneDisplayRoot\n.set SceneDisplayRoot,0x03002818\n"
        ".global PanelBufferState\n.set PanelBufferState,0x03002740\n"
        ".global PanelLayouts\n.set PanelLayouts,0x030009e0\n"
        ".global ResourceScratch\n.set ResourceScratch,0x02003cb0\n"
        ".global UnitMenuLabels\n.set UnitMenuLabels,0x085668b0\n"
        ".global LabelTileBuffer\n.set LabelTileBuffer,0x0600b4e0\n"
        ".global ConfigureUnitPanel\n.thumb_set ConfigureUnitPanel,0x0808a269\n"
        ".global NativeCpuSet\n.thumb_set NativeCpuSet,0x0814186d\n"
        ".global GetWindowCell\n.thumb_set GetWindowCell,0x0808b8e5\n"
        ".global DrawWindowTileRun\n.thumb_set DrawWindowTileRun,0x0808b7c1\n"
        ".global DrawUnitMenuLabel\n.thumb_set DrawUnitMenuLabel,0x08015111\n"
        ".global RenderUnitPanelFrame\n.thumb_set RenderUnitPanelFrame,0x08016345\n"
        ".global FillUnitPanelRows\n.thumb_set FillUnitPanelRows,0x08016561\n"
        ".global LoadUnitPanelResource\n.thumb_set LoadUnitPanelResource,0x08018525\n"
        ".global WriteUnitPanelTiles\n.thumb_set WriteUnitPanelTiles,0x08035679");
u32 InitializeUnitThreeRowPanel(u8 *incoming) __asm__("CoreScene34_000751AC");
u32 InitializeUnitThreeRowPanel(u8 *incoming)
{
    register u8 *unit __asm__("r8") = incoming;
    u32 available = 0;
    register u8 *scratch_load __asm__("r0");
    register u8 *scratch __asm__("r9");
    register u8 **root_cell __asm__("r1");
    register u8 *flag_address __asm__("r0");
    register u32 flag_offset __asm__("r2");
    register u32 one __asm__("r6");
    u8 *owner;
    register void *context24 __asm__("r2");
    register void *context20 __asm__("r3");
    register u8 *buffer_state __asm__("r0");
    u8 *buffer;
    register u8 *layout_init __asm__("r2");
    register u8 *layout_final __asm__("r5");
    u16 zero;
    register s32 index __asm__("r5");
    register u32 disabled_offset __asm__("r6");
    register u32 columns __asm__("r1");
    register u32 rows __asm__("r2");
    register u32 final_one __asm__("r6");
    register u32 tile_flags __asm__("r5");
    u16 *tail_cell;
    u32 resource;
    __asm__("" : "+r"(unit));
    __asm__("" : "+r"(available));
    scratch_load = ResourceScratch;
    __asm__("" : "+r"(scratch_load));
    scratch = scratch_load;
    __asm__("" : "+r"(scratch));
    root_cell = &SceneDisplayRoot;
    __asm__("" : "+r"(root_cell));
    flag_address = *root_cell;
    __asm__("" : "+r"(flag_address));
    flag_offset = 0xBF5;
    __asm__("" : "+r"(flag_offset));
    flag_address += flag_offset;
    __asm__("" : "+r"(flag_address));
    one = 1;
    __asm__("" : "+r"(one));
    *flag_address = one;
    owner = *root_cell;
    context24 = *(void **)(owner+24);
    context20 = *(void **)(owner+20);
    __asm__("" : "+r"(context24), "+r"(context20));
    buffer_state = PanelBufferState;
    __asm__("" : "+r"(buffer_state));
    buffer = *(u8 **)(buffer_state+16);
    ConfigureUnitPanel(4,12,context24,context20,buffer,buffer+264,available,available,
        17,8,12,9,17,8,12,9,12,9);
    layout_init = PanelLayouts;
    __asm__("" : "+r"(layout_init));
    {
        register u32 offset3 __asm__("r3") = 356;
        register u32 offset1 __asm__("r1");
        register u32 offset0 __asm__("r0");
        register u8 *address0 __asm__("r0");
        register u8 *address1 __asm__("r1");
        register u16 *half_address __asm__("r3");
        register u32 cleared __asm__("r1");
        register u32 continued_offset __asm__("r3");
        __asm__("" : "+r"(offset3));
        address0 = layout_init + offset3;
        __asm__("" : "+r"(address0));
        *address0 = 17;
        offset1 = 357;
        __asm__("" : "+r"(offset1));
        address0 = layout_init + offset1;
        __asm__("" : "+r"(address0));
        *address0 = 8;
        offset0 = 318;
        __asm__("" : "+r"(offset0));
        half_address = (u16 *)(layout_init + offset0);
        __asm__("" : "+r"(half_address));
        cleared = 0;
        __asm__("" : "+r"(cleared));
        offset0 += 105;
        __asm__("" : "+r"(offset0));
        *half_address = (u16)offset0;
        continued_offset = 305;
        __asm__("" : "+r"(continued_offset));
        address0 = layout_init + continued_offset;
        __asm__("" : "+r"(address0));
        *address0 = cleared;
        offset1 = 376;
        __asm__("" : "+r"(offset1));
        address0 = layout_init + offset1;
        __asm__("" : "+r"(address0));
        *address0 = one;
        continued_offset += 72;
        __asm__("" : "+r"(continued_offset));
        address0 = layout_init + continued_offset;
        __asm__("" : "+r"(address0));
        *address0 = one;
        offset0 = 378;
        __asm__("" : "+r"(offset0));
        address1 = layout_init + offset0;
        __asm__("" : "+r"(address1));
        *address1 = 11;
        continued_offset += 2;
        __asm__("" : "+r"(continued_offset));
        address1 = layout_init + continued_offset;
        __asm__("" : "+r"(address1));
        *address1 = 6;
    }
    zero = (u16)available;
    NativeCpuSet(&zero,LabelTileBuffer,0x01000580);
    index = 0;
    disabled_offset = 1408;
    __asm__("" : "+r"(index), "+r"(disabled_offset));
    do {
        register s32 next __asm__("r4") = index+2;
        register u16 *row __asm__("r1");
        register u32 tile_id __asm__("r2");
        register u16 *cell __asm__("r0");
        register u32 tile_word __asm__("r2");
        register u32 stored_tile __asm__("r1");
        register const u8 *label_base __asm__("r1");
        register u32 label_index __asm__("r0");
        register const u8 *label __asm__("r3");
        __asm__("" : "+r"(next));
        row = GetWindowCell(4,1,1,next);
        __asm__("" : "+r"(row));
        tile_id = (u16)(11*index+423);
        __asm__("" : "+r"(tile_id));
        DrawWindowTileRun(4,row,tile_id,11,0xC000);
        cell = GetWindowCell(4,1,0,index+3);
        tile_word = 0xD00C;
        __asm__("" : "+r"(tile_word));
        stored_tile = tile_word;
        __asm__("" : "+r"(stored_tile));
        *cell = (u16)stored_tile;
        label_base = UnitMenuLabels;
        __asm__("" : "+r"(label_base));
        label_index = (index>>1)+49;
        label = *(const u8 **)(label_base+4*label_index);
        __asm__("" : "+r"(label));
        if (index == 4) {
            register const u8 *query_unit __asm__("r1");
            available = 0;
            query_unit = unit;
            __asm__("" : "+r"(query_unit));
            if (query_unit[6] <= 5)
                available = 1;
            if (available == 0)
                goto disabled;
        }
        {
            register u8 *font __asm__("r0") = SceneDisplayRoot;
            register u32 offset __asm__("r2");
            register u8 *destination __asm__("r1");
            register u32 row_byte_offset __asm__("r1");
            register u8 *tile_base __asm__("r2");
            __asm__("" : "+r"(font));
            offset = 0x68C;
            __asm__("" : "+r"(offset));
            font += offset;
            __asm__("" : "+r"(font));
            row_byte_offset = 352*index;
            __asm__("" : "+r"(row_byte_offset));
            tile_base = LabelTileBuffer;
            __asm__("" : "+r"(tile_base));
            row_byte_offset += (u32)tile_base;
            __asm__("" : "+r"(row_byte_offset));
            destination = (u8 *)row_byte_offset;
            __asm__("" : "+r"(destination));
            DrawUnitMenuLabel(font,destination,label,0,1);
        }
        goto next_row;
    disabled:
        {
            register u8 *font __asm__("r0") = SceneDisplayRoot;
            register u32 offset __asm__("r1");
            __asm__("" : "+r"(font));
            offset = 0x68C;
            __asm__("" : "+r"(offset));
            font += offset;
            __asm__("" : "+r"(font));
            DrawUnitMenuLabel(font,(u8 *)(0x0600B4E0u+disabled_offset),label,1,1);
        }
    next_row:
        index = next;
    } while (index <= 5);
    layout_final = PanelLayouts;
    __asm__("" : "+r"(layout_final));
    {
        register u32 frame_offset __asm__("r3") = 332;
        register u16 *frame __asm__("r0");
        register u32 column_offset __asm__("r2");
        register u8 *column_address __asm__("r1");
        register u8 *row_address __asm__("r2");
        __asm__("" : "+r"(frame_offset));
        frame = *(u16 **)(layout_final+frame_offset);
        __asm__("" : "+r"(frame));
        column_offset = 344;
        __asm__("" : "+r"(column_offset));
        column_address = layout_final+column_offset;
        __asm__("" : "+r"(column_address));
        columns = *column_address;
        __asm__("" : "+r"(columns));
        frame_offset += 13;
        __asm__("" : "+r"(frame_offset));
        row_address = layout_final+frame_offset;
        __asm__("" : "+r"(row_address));
        rows = *row_address;
        __asm__("" : "+r"(rows));
        RenderUnitPanelFrame(frame,columns,rows,192,columns,5,12);
    }
    {
        register u32 fill_offset __asm__("r1") = 328;
        register u16 *fill_surface __asm__("r0");
        register u8 *fill_address __asm__("r0");
        __asm__("" : "+r"(fill_offset));
        fill_address = layout_final+fill_offset;
        __asm__("" : "+r"(fill_address));
        fill_surface = *(u16 **)fill_address;
        __asm__("" : "+r"(fill_surface));
        FillUnitPanelRows(fill_surface,12,9,192,12,(final_one = 1),12);
        __asm__("" : "+r"(final_one));
    }
    tile_flags = 0xC03E;
    __asm__("" : "+r"(tile_flags));
    tail_cell = GetWindowCell(4,1,1,1);
    resource = LoadUnitPanelResource(scratch,62,3);
    WriteUnitPanelTiles(tile_flags,tail_cell,resource,1);
    flag_address = SceneDisplayRoot;
    __asm__("" : "+r"(flag_address));
    flag_offset = 0xBF5;
    __asm__("" : "+r"(flag_offset));
    flag_address += flag_offset;
    *flag_address = final_one;
    return available;
}
