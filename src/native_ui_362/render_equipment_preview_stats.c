typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern const u16 gPreviewTemplate[];
extern u8 gTileRenderers[];
extern u8 *gPreviewContext;
extern void CopyPreviewTemplate(const u16 *, u16 *, u32, u32);
extern u16 *GetPreviewTilePosition(u32, u32, s32, s32);
/* The existing renderer consumes LOW16 of each of its six numeric inputs. */
extern void RenderPreviewNumber(u16 *, u32, u32, u32, u32, u32, u32);
extern u32 ReadUnitEquipmentValue16(const u8 *);
extern u32 RefreshAndReadUnitDerivedByte(u8 *);
extern u32 ReadUnitEquipmentValue15(const u8 *);
extern u32 GetUnitStat20Capped(const u8 *);
extern u32 GetUnitStat22Capped(const u8 *);
extern u32 GetUnitStat24Capped(const u8 *);
extern u32 GetUnitStat26Capped(const u8 *);
extern u32 ReadUnitEquipmentValue14(const u8 *);

__asm__(
    ".global gPreviewTemplate\n.set gPreviewTemplate,0x0894f7dc\n"
    ".global gTileRenderers\n.set gTileRenderers,0x030009e0\n"
    ".global gPreviewContext\n.set gPreviewContext,0x03002818\n"
    ".global CopyPreviewTemplate\n.thumb_set CopyPreviewTemplate,0x08035579\n"
    ".global GetPreviewTilePosition\n.thumb_set GetPreviewTilePosition,0x0808b8e5\n"
    ".global RenderPreviewNumber\n.thumb_set RenderPreviewNumber,0x080899ad\n"
    ".global ReadUnitEquipmentValue16\n.thumb_set ReadUnitEquipmentValue16,0x080ca395\n"
    ".global RefreshAndReadUnitDerivedByte\n.thumb_set RefreshAndReadUnitDerivedByte,0x080ca611\n"
    ".global ReadUnitEquipmentValue15\n.thumb_set ReadUnitEquipmentValue15,0x080ca5c5\n"
    ".global GetUnitStat20Capped\n.thumb_set GetUnitStat20Capped,0x080ca521\n"
    ".global GetUnitStat22Capped\n.thumb_set GetUnitStat22Capped,0x080ca551\n"
    ".global GetUnitStat24Capped\n.thumb_set GetUnitStat24Capped,0x080ca539\n"
    ".global GetUnitStat26Capped\n.thumb_set GetUnitStat26Capped,0x080ca569\n"
    ".global ReadUnitEquipmentValue14\n.thumb_set ReadUnitEquipmentValue14,0x080ca581\n"
);

/* Each row is a distinct original call sequence. Only the unsigned value is
 * printed; its signed LOW16 projection is used for the comparison attribute. */
#define ROW_VALUES \
    register u32 shifted __asm__("r0"); \
    s32 previous; \
    s32 comparison; \
    u32 value; \
    u32 attributes; \
    register u32 output_value __asm__("r3"); \
    u16 *destination

#define READ_ROW(GETTER, OFFSET) \
    shifted = (u32)GETTER(unit) << 16; \
    __asm__("" : "+r"(shifted)); \
    previous = *(s16 *)(gPreviewContext + (OFFSET)); \
    value = shifted >> 16; \
    comparison = (s32)shifted >> 16; \
    attributes = 0xa000; \
    if (previous <= comparison) { \
        attributes = 0xd000; \
        if (previous < comparison) \
            attributes = 0x8000; \
    }

#define GLOBAL_STRIDE_ROW(GETTER, OFFSET, X, Y, BASE, DIGITS) do { \
    ROW_VALUES; \
    register u8 *renderer __asm__("r1"); \
    register u32 output_stride __asm__("r1"); \
    READ_ROW(GETTER, OFFSET); \
    destination = GetPreviewTilePosition(3, 1, X, Y); \
    renderer = gTileRenderers; \
    __asm__("" : "+r"(renderer)); \
    output_stride = renderer[268]; \
    __asm__("" : "+r"(output_stride)); \
    output_value = value; \
    __asm__("" : "+r"(output_value)); \
    RenderPreviewNumber(destination, output_stride, BASE, output_value, \
                        DIGITS, 0, attributes); \
} while (0)

#define FIXED_STRIDE_ROW(GETTER, OFFSET, X, Y, BASE, DIGITS) do { \
    ROW_VALUES; \
    READ_ROW(GETTER, OFFSET); \
    destination = GetPreviewTilePosition(0, 1, X, Y); \
    output_value = value; \
    __asm__("" : "+r"(output_value)); \
    RenderPreviewNumber(destination, 32, BASE, output_value, DIGITS, 0, attributes); \
} while (0)

void RenderEquipmentPreviewStats(u8 *) __asm__("CoreScene34_0007614C");

void RenderEquipmentPreviewStats(u8 *unit)
{
    register const u16 *source __asm__("r0") = gPreviewTemplate;
    register u8 *renderer __asm__("r1");

    __asm__("" : "+r"(source));
    renderer = gTileRenderers;
    __asm__("" : "+r"(renderer));
    CopyPreviewTemplate(source, *(u16 **)(renderer + 256), 192, 254);

    GLOBAL_STRIDE_ROW(ReadUnitEquipmentValue16, 0x1cec, 6, 1, 100, 1);
    FIXED_STRIDE_ROW(RefreshAndReadUnitDerivedByte, 0x1cee, 6, 9, 120, 1);
    GLOBAL_STRIDE_ROW(ReadUnitEquipmentValue15, 0x1cf0, 12, 2, 120, 3);
    GLOBAL_STRIDE_ROW(GetUnitStat20Capped, 0x1cf8, 11, 4, 120, 3);
    GLOBAL_STRIDE_ROW(GetUnitStat22Capped, 0x1cfa, 11, 6, 100, 3);
    FIXED_STRIDE_ROW(GetUnitStat24Capped, 0x1cfc, 11, 14, 120, 3);
    GLOBAL_STRIDE_ROW(GetUnitStat26Capped, 0x1cfe, 11, 9, 100, 3);
    FIXED_STRIDE_ROW(ReadUnitEquipmentValue14, 0x1d00, 11, 17, 120, 3);
}
