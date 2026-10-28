typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*CopyBytes)(void *, const void *, u32);
struct ActionPositions { u16 x, y, x_copy, y_copy, x_other, y_other, x_next, y_next; };
struct WidgetPosition { u8 before_xy[8]; u16 x, y; };
struct ActionWork { u8 text[44]; u8 *widget; u32 vram; };
extern u8 *ActionRootCell;
extern u8 ActionScratch[], ActionSecondConverted[], ActionPalette[];
extern u8 ActionWordBank[], ActionCoordinateBank[];
extern CopyBytes ActionCopyCell;
extern void (*ActionClearCell)(void *, u32);
extern const u8 *GetActionPalette_080CBABC(u32);
extern void QueueActionDma_08000ADC(void *, u32, u32, u16);
extern u16 WriteActionPrefix_08018CB8(u8 *, s8);
extern u16 CopyActionText_08018C24(u8 *, const u8 *);
extern u32 RenderActionText_08015110(void *, u32, const u8 *, u32, u32);
extern void ReorderActionText_0802807C(u8 *, const u8 *);
extern u32 GetActionSelection_08027D10(void);
extern void DrawActionWidget_08017E80(void *);
extern void InitializeActionWidget_08017C28(void *, void *, void (*)(void *), u32);
void TaskConstructor45_000280F4(u8 *object_argument)
{
    struct ActionWork work;
    register u8 *object asm("r9") = object_argument;
    register u8 *root asm("sl");
    register u8 *word_bank asm("r8");
    register u8 *scratch asm("r4");
    register u8 *append asm("r6");
    void *request;
    u8 *converted;
    const u8 *palette;
    u32 selection;
    u8 *coordinates;
    asm("" : : "r" (object));
    work.widget = object_argument + 88;
    asm("" : "+m" (work.widget));
    {
        register u8 **initial_cell asm("r1") = &ActionRootCell;
        register u8 *initial_root asm("r1");
        asm("" : "+r" (initial_cell));
        initial_root = *initial_cell;
        asm("" : "+r" (initial_root));
        root = initial_root;
        asm("" : : "r" (root));
    }
    request = root + 708;
    asm("" : "+r" (request));
    {
        register u32 initial_vram asm("r2") = 0x06015800;
        asm("" : "+r" (initial_vram));
        work.vram = initial_vram;
    }
    asm("" : "+m" (work.vram));
    scratch = ActionScratch;
    asm("" : "+r" (scratch));
    {
        register CopyBytes *copy_cell asm("r5") = &ActionCopyCell;
        register const u8 *palette_argument asm("r1");
        register CopyBytes copy asm("r3");
        asm("" : "+r" (copy_cell));
        palette_argument = GetActionPalette_080CBABC(0);
        asm("" : "+r" (palette_argument));
        copy = *copy_cell;
        asm("" : "+r" (copy));
        copy(ActionPalette, palette_argument, 32);
    }
    {
        register void *submitted asm("r0") = request;
        register u32 source_argument asm("r1");
        register u32 destination_argument asm("r2");
        asm("" : "+r" (submitted));
        request = root + 736;
        asm("" : "+r" (request));
        source_argument = (u32)scratch;
        asm("" : "+r" (source_argument));
        destination_argument = work.vram;
        asm("" : "+r" (destination_argument));
        QueueActionDma_08000ADC(submitted, source_argument, destination_argument, 160);
    }
    {
        register u32 increment asm("r0") = 640;
        register u32 next_vram asm("r1");
        asm("" : "+r" (increment));
        next_vram = work.vram + increment;
        asm("" : "+r" (next_vram));
        work.vram = next_vram;
        asm("" : "+m" (work.vram));
        scratch += increment;
    }
    ActionClearCell(scratch, 512);
    work.text[0] = 140;
    work.text[1] = 101;
    WriteActionPrefix_08018CB8(work.text + 2, -2);
    append = work.text + 5;
    asm("" : "+r" (append));
    {
        register u8 *bank_start asm("r1") = ActionWordBank;
        asm("" : "+r" (bank_start));
        word_bank = bank_start;
        asm("" : : "r" (word_bank));
    }
    CopyActionText_08018C24(append, *(const u8 **)(word_bank + 220));
    {
        register u8 **text_cell asm("r2") = &ActionRootCell;
        asm("" : "+r" (text_cell));
        RenderActionText_08015110(*text_cell + 52, (u32)scratch, work.text, 5, 1);
    }
    {
        register u32 converted_offset asm("r2") = 512;
        asm("" : "+r" (converted_offset));
        converted = scratch + converted_offset;
        asm("" : "+r" (converted));
    }
    ReorderActionText_0802807C(converted, scratch);
    {
        register void *submitted asm("r0") = request;
        register u32 source_argument asm("r1");
        register u32 destination_argument asm("r2");
        asm("" : "+r" (submitted));
        request = root + 764;
        asm("" : "+r" (request));
        source_argument = (u32)converted;
        asm("" : "+r" (source_argument));
        destination_argument = work.vram;
        asm("" : "+r" (destination_argument));
        QueueActionDma_08000ADC(submitted, source_argument, destination_argument, 128);
    }
    {
        register u32 next_vram asm("r0") = work.vram;
        register u32 increment asm("r1");
        asm("" : "+r" (next_vram));
        increment = 512;
        asm("" : "+r" (increment));
        next_vram += increment;
        work.vram = next_vram;
        asm("" : "+m" (work.vram));
        {
            register u32 scratch_step asm("r2") = 1024;
            asm("" : "+r" (scratch_step));
            scratch += scratch_step;
        }
        ActionClearCell(scratch, increment);
    }
    {
        register u32 increment asm("r1") = 224;
        register u8 *word_cell asm("r2");
        asm("" : "+r" (increment));
        word_bank += increment;
        asm("" : "+r" (word_bank));
        word_cell = word_bank;
        asm("" : "+r" (word_cell));
        {
            register const u8 *source_text asm("r1") = *(const u8 **)word_cell;
            asm("" : "+r" (source_text));
            CopyActionText_08018C24(append, source_text);
        }
    }
    {
        register u8 **text_cell asm("r1") = &ActionRootCell;
        register void *text_context asm("r0");
        register u32 initialization_flags asm("r2");
        asm("" : "+r" (text_cell));
        text_context = *text_cell + 52;
        asm("" : "+r" (text_context));
        initialization_flags = 1;
        asm("" : "+r" (initialization_flags));
        RenderActionText_08015110(text_context, (u32)scratch, work.text, 5,
                                 initialization_flags);
    }
    {
        register u8 *converted_argument asm("r0") = ActionSecondConverted;
        asm("" : "+r" (converted_argument));
        ReorderActionText_0802807C(converted_argument, scratch);
    }
    {
        register void *submitted asm("r0") = request;
        register u32 source_argument asm("r1");
        register u32 destination_argument asm("r2");
        asm("" : "+r" (submitted));
        source_argument = (u32)ActionSecondConverted;
        asm("" : "+r" (source_argument));
        destination_argument = work.vram;
        asm("" : "+r" (destination_argument));
        QueueActionDma_08000ADC(submitted, source_argument, destination_argument, 128);
    }
    selection = GetActionSelection_08027D10();
    coordinates = ActionCoordinateBank + selection * 20;
    object += 128;
    asm("" : "+r" (object));
    {
        register u32 first_coordinate asm("r0") = coordinates[0] * 8;
        register struct ActionPositions *positions asm("r2");
        asm("" : "+r" (first_coordinate));
        positions = (struct ActionPositions *)object;
        asm("" : "+r" (positions));
        positions->x_copy = first_coordinate;
        positions->y_copy = coordinates[1] * 8;
        positions->x = coordinates[0] * 8;
        positions->y = coordinates[1] * 8;
        positions->x_next = (coordinates[0] + 1) * 8;
        positions->y_next = (coordinates[1] + 2) * 8;
        positions->x_other = coordinates[0] * 8;
        positions->y_other = coordinates[1] * 8;
    }
    {
        register void (*callback)(void *) asm("r2") = DrawActionWidget_08017E80;
        asm("" : "+r" (callback));
        InitializeActionWidget_08017C28(work.widget, 0, callback, 7);
    }
    {
        register struct ActionPositions *positions asm("r1") = (struct ActionPositions *)object;
        register struct WidgetPosition *widget asm("r2");
        register u32 adjusted asm("r0");
        asm("" : "+r" (positions));
        adjusted = positions->x_copy - 6;
        asm("" : "+r" (adjusted));
        widget = (struct WidgetPosition *)work.widget;
        asm("" : "+r" (widget));
        widget->x = adjusted;
        adjusted = positions->y_copy + 3;
        asm("" : "+r" (adjusted));
        widget->y = adjusted;
    }
}
asm(".set ActionRootCell,0x0200f438\n.set ActionScratch,0x02003cb0\n.set ActionSecondConverted,0x02004530\n.set ActionPalette,0x03003bc0\n.set ActionWordBank,0x085567f0\n.set ActionCoordinateBank,0x08391454\n.set ActionCopyCell,0x0836d4bc\n.set ActionClearCell,0x0836d4b8\n.thumb_set GetActionPalette_080CBABC,0x080cbabd\n.thumb_set QueueActionDma_08000ADC,0x08000add\n.thumb_set WriteActionPrefix_08018CB8,0x08018cb9\n.thumb_set CopyActionText_08018C24,0x08018c25\n.thumb_set RenderActionText_08015110,0x08015111\n.thumb_set ReorderActionText_0802807C,0x0802807d\n.thumb_set GetActionSelection_08027D10,0x08027d11\n.thumb_set InitializeActionWidget_08017C28,0x08017c29\n.thumb_set DrawActionWidget_08017E80,0x08017e81\n.thumb_set _call_via_r2,0x0814224d\n.thumb_set _call_via_r3,0x08142251\n");
