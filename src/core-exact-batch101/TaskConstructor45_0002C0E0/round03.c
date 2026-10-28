typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleUnit { u8 unaccessed_prefix[40]; u16 flags; };
struct RecordGroup;
struct Record;
struct RecordState {
    void *backing;
    void *pool;
    void *owner;
    struct Record *entry;
    struct RecordGroup *group;
    u8 palette_selector;
    u8 unaccessed21;
    u16 property;
};
struct UnitTaskContext {
    u8 unaccessed_prefix[916];
    struct RecordState records;
    u16 palette[16];
};
typedef void (*MemoryCopy)(void *, const void *, u32);
extern struct UnitTaskContext *gUnitTaskContext;
extern MemoryCopy gMemoryCopy;
extern u8 gUnitTaskPalettes[][32];
extern u16 ReadUnitRecordPropertyAndSlot(const struct BattleUnit *, u8 *);
extern const u16 *GetUnitPalette(u8);
extern void TransformPalette(const u16 *, u16 *, u16, u16);
extern struct Record *CreateOrRefreshRecord(struct RecordGroup *, struct Record *, u32, u32, u32, u32, u32);
extern void SetRecordGroupCoordinates(struct RecordGroup *, u16, u16);
typedef char RecordStateSize[sizeof(struct RecordState) == 24 ? 1 : -1];
typedef char PaletteOffset[(u32)&((struct UnitTaskContext *)0)->palette == 940 ? 1 : -1];
/* Preserve the root snapshot, then reload all record fields after palette helpers. */
void RefreshUnitTaskRecord(struct BattleUnit *unit)
{
    struct UnitTaskContext *root = gUnitTaskContext;
    struct RecordState *state = &root->records;
    u16 *palette;
    register u32 palette_index asm("r1");
    register MemoryCopy *copy_slot asm("r2");
    register u8 *destination asm("r0");
    state->property = ReadUnitRecordPropertyAndSlot(unit, &state->palette_selector);
    if (unit->flags & 1) {
        const u16 *source = GetUnitPalette(state->palette_selector);
        palette = root->palette;
        TransformPalette(source, palette, 16, 153);
        /* Retail keeps the initialized palette ordinal in R1 through its byte store. */
        palette_index = 9;
        asm("" : "+r" (palette_index));
        state->palette_selector = palette_index;
        /* The observed callback-cell address precedes the independent offset shift. */
        copy_slot = &gMemoryCopy;
        asm("" : "+r" (copy_slot));
        /* The same R1 then holds the byte offset before the destination base load. */
        palette_index <<= 5;
        asm("" : "+r" (palette_index));
        destination = (u8 *)gUnitTaskPalettes;
        asm("" : "+r" (destination));
        destination += palette_index;
        asm("" : "+r" (destination));
        (*copy_slot)(destination, palette, 32);
    }
    state->entry = CreateOrRefreshRecord(state->group, state->entry, 0, 20, state->property, 0, 0);
    SetRecordGroupCoordinates(state->group, 0, 2);
}
asm(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200F440\n"
    ".global gMemoryCopy\n.set gMemoryCopy,0x0836D4BC\n"
    ".global gUnitTaskPalettes\n.set gUnitTaskPalettes,0x03003A60\n"
    ".global ReadUnitRecordPropertyAndSlot\n.thumb_set ReadUnitRecordPropertyAndSlot,0x08022239\n"
    ".global GetUnitPalette\n.thumb_set GetUnitPalette,0x080CBA3D\n"
    ".global TransformPalette\n.thumb_set TransformPalette,0x08148105\n"
    ".global CreateOrRefreshRecord\n.thumb_set CreateOrRefreshRecord,0x08021619\n"
    ".global SetRecordGroupCoordinates\n.thumb_set SetRecordGroupCoordinates,0x08021DF9\n"
    ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n");
