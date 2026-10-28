typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Field roles are inferred from accesses; unknown bytes remain unnamed. */
typedef struct ScenePositionRecord {
    u8 flags;               /* +0: bit 0 allows display position updates */
    u8 unknown_1[2];
    u8 mode_flags;          /* +3: low bits select full-height behavior */
    u8 unknown_4[2];
    u16 source_y;           /* +6 */
    u16 bottom_y;           /* +8 */
    u8 previous_source_y;  /* +10 */
    u8 visible_height;     /* +11 */
    u16 top_y;              /* +12 */
    u8 unknown_14[4];
    u8 layout_mode;         /* +18: observed modes 0, 1, and 2 */
} ScenePositionRecord;

extern void SetDisplayRecordPosition(void *display, u16 slot, u8 y, u8 height);

/* The state pointer is reread at the observed boundaries. */
#define SCENE ((u8 *)*(volatile u32 *)0x03002810)
#define RECORD ((ScenePositionRecord *)*(u32 *)(SCENE + 4))

static __inline__ void *GetActiveDisplayRecords(void)
{
    register void **display_base __asm__("r0") = (void **)0x03000e30;
    /* Keep the base load followed by a +4 field load, as in retail. */
    __asm__ volatile("" : "+r" (display_base));
    return display_base[1];
}

#define DISPLAY GetActiveDisplayRecords()

/* Refresh the vertical display window and its one-byte transition timer. */
void UpdateScenePositionRecord(void)
{
    register u32 shift __asm__("r5");
    register u32 height __asm__("r4");
    u32 shift_gate;
    ScenePositionRecord *record;
    u8 *scene;

    record = RECORD;
    /* A nonzero low-seven-bit phase chooses an eight-pixel adjustment. */
    shift_gate = (((u8 *)record)[0x8c] - 1) & 0x7f;
    shift = 0;
    if (shift_gate != 0)
        shift -= 8;
    record->previous_source_y = (u8)record->source_y;

    record = RECORD;
    {
        register u32 bottom __asm__("r0") = record->bottom_y;
        register u32 top __asm__("r1") = record->top_y;
        /* Preserve the retail subtraction and 16-bit wrap before clamping. */
        __asm__ volatile("" : "+r" (bottom), "+r" (top));
        bottom -= top;
        __asm__ volatile("" : "+r" (bottom));
        height = (u16)bottom;
    }
    if (height > 239)
        height = 240;
    record->visible_height = (u8)height;

    scene = SCENE;
    if (*(u16 *)(scene + 0x9e) == 0) {
        record = *(ScenePositionRecord **)(scene + 4);
        if ((record->flags & 1) != 0 && scene[0xf3e] == 0) {
            switch (record->layout_mode) {
            case 0:
                SetDisplayRecordPosition(DISPLAY, 0, record->previous_source_y,
                                         (u8)height);
                break;
            case 1:
                if ((record->mode_flags & 15) > 2)
                    SetDisplayRecordPosition(DISPLAY, 0,
                                             (u8)(record->previous_source_y + shift),
                                             (u8)(height - shift));
                else
                    SetDisplayRecordPosition(DISPLAY, 0, record->previous_source_y, 240);
                break;
            case 2:
                if ((record->mode_flags & 7) > 1)
                    SetDisplayRecordPosition(DISPLAY, 0,
                                             (u8)(record->previous_source_y + shift),
                                             (u8)(height - shift));
                else
                    SetDisplayRecordPosition(DISPLAY, 0, record->previous_source_y, 240);
                break;
            }
            goto after_display;
        }
    }
    SetDisplayRecordPosition(DISPLAY, 0, RECORD->previous_source_y, 240);
after_display:
    {
        register u32 scene_address __asm__("r0") =
            *(volatile u32 *)0x03002810;
        u8 *counter;
        __asm__ volatile("" : "+r" (scene_address));
        counter = (u8 *)(scene_address + 0xf3e);
        if (*counter != 0)
            --*counter;
    }
}
