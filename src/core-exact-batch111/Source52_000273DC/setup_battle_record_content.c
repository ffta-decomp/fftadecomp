typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*CopyBytes)(void *, const void *, u32);
struct RecordHeader { u8 kind, unused, length; };
struct RecordState { u8 before_header[128]; u8 kind, unused, length; u8 before_result[17]; u32 *resolved; u8 before_allocation[8]; u8 *allocation; };
struct RecordRoot { u8 before_code[12]; u16 code; };
extern struct RecordRoot *RecordRootCell;
extern CopyBytes RecordCopyCell;
extern u8 RecordPalette[];
extern const u8 PackedRecordBank[];
extern const u8 *const RecordTextWords[];
extern const u8 *RecordPaletteSource_080CBABC(u32);
extern u8 *AllocateRecordBuffer_08005B28(u32);
extern u32 DecodePackedRecord_08013E9C(u8 *, const u8 *, u8 *, u32, u8 *, u8 *);
extern u32 GetRecordProperty_080CCD50(u16, u8);
extern u16 CopyRecordText_08018C24(u8 *, const u8 *);
#define FIELD_OFFSET(T,M) ((u32)&(((T *)0)->M))
typedef char result_offset[(FIELD_OFFSET(struct RecordState,resolved)==148)?1:-1];
typedef char allocation_offset[(FIELD_OFFSET(struct RecordState,allocation)==160)?1:-1];
void Source52_000273DC(struct RecordState *state)
{
    register u32 header_offset asm("r0") = 128;
    register struct RecordHeader *header asm("r8");
    register struct RecordRoot **root_cell asm("r9");
    register struct RecordRoot **initial_cell asm("r1");
    u16 code;
    u16 first_category;
    asm("" : "+r" (header_offset));
    header = (struct RecordHeader *)(header_offset + (u32)state);
    asm("" : : "r" (header));
    initial_cell = &RecordRootCell;
    asm("" : "+r" (initial_cell));
    root_cell = initial_cell;
    asm("" : : "r" (root_cell));
    code = (*initial_cell)->code;
    first_category = code & 0x4000;
    if (first_category != 0) {
        CopyBytes *copy_cell = &RecordCopyCell;
        u8 *destination = RecordPalette;
        const u8 *source;
        u8 *allocation;
        asm("" : "+r" (copy_cell), "+r" (destination));
        source = RecordPaletteSource_080CBABC(0);
        (*copy_cell)(destination, source + 8, 6);
        destination += 18;
        source = RecordPaletteSource_080CBABC(0);
        (*copy_cell)(destination, source + 26, 6);
        allocation = AllocateRecordBuffer_08005B28(256);
        state->allocation = allocation;
        {
            register const u8 *bank asm("r1") = PackedRecordBank;
            register u8 *scratch asm("r2");
            register struct RecordRoot **decode_cell asm("r4");
            register struct RecordRoot *decode_root asm("r3");
            register u32 current_code asm("r4");
            register u32 category_mask asm("r5");
            register u32 index asm("r3");
            register u32 header_value asm("r0");
            register struct RecordHeader *header_target asm("r1");
            register u32 *output asm("r1");
            register struct RecordRoot **result_cell asm("r2");
            asm("" : "+r" (bank));
            scratch = allocation + 128;
            asm("" : "+r" (scratch));
            decode_cell = root_cell;
            asm("" : "+r" (decode_cell));
            decode_root = *decode_cell;
            asm("" : "+r" (decode_root));
            current_code = decode_root->code;
            asm("" : "+r" (current_code));
            category_mask = 0x3fff;
            asm("" : "+r" (category_mask));
            index = category_mask & current_code;
            asm("" : "+r" (index));
            DecodePackedRecord_08013E9C(allocation, bank, scratch, index, 0, 0);
            asm("" : "+r" (category_mask));
            header_value = 24;
            asm("" : "+r" (header_value));
            header_target = header;
            asm("" : "+r" (header_target));
            header_target->length = header_value;
            header_value = 2;
            asm("" : "+r" (header_value));
            header_target->kind = header_value;
            output = state->resolved;
            asm("" : "+r" (output));
            result_cell = root_cell;
            asm("" : "+r" (result_cell));
            category_mask &= (*result_cell)->code;
            asm("" : "+r" (category_mask));
            *output = category_mask;
        }
    } else {
        register u32 secondary_test asm("r0") = 0x8000;
        asm("" : "+r" (secondary_test));
        secondary_test &= code;
        asm("" : "+r" (secondary_test));
        if (secondary_test != 0) {
        u8 *allocation = AllocateRecordBuffer_08005B28(256);
        state->allocation = allocation;
        {
            register const u8 *bank asm("r1") = PackedRecordBank;
            register u8 *scratch asm("r2");
            register struct RecordRoot **decode_cell asm("r4");
            register struct RecordRoot *decode_root asm("r3");
            register u32 current_code asm("r5");
            register u32 category_mask asm("r4");
            register u32 index asm("r3");
            register u32 header_value asm("r0");
            register struct RecordHeader *header_target asm("r1");
            register u32 *output asm("r1");
            register struct RecordRoot **result_cell asm("r2");
            asm("" : "+r" (bank));
            scratch = allocation + 128;
            asm("" : "+r" (scratch));
            decode_cell = root_cell;
            asm("" : "+r" (decode_cell));
            decode_root = *decode_cell;
            asm("" : "+r" (decode_root));
            current_code = decode_root->code;
            asm("" : "+r" (current_code));
            category_mask = 0x7fff;
            asm("" : "+r" (category_mask));
            index = category_mask & current_code;
            asm("" : "+r" (index));
            DecodePackedRecord_08013E9C(allocation, bank, scratch, index, 0, 0);
            asm("" : "+r" (category_mask));
            header_value = 24;
            asm("" : "+r" (header_value));
            header_target = header;
            asm("" : "+r" (header_target));
            header_target->length = header_value;
            header_value = 2;
            asm("" : "+r" (header_value));
            header_target->kind = header_value;
            output = state->resolved;
            asm("" : "+r" (output));
            result_cell = root_cell;
            asm("" : "+r" (result_cell));
            category_mask &= (*result_cell)->code;
            asm("" : "+r" (category_mask));
            *output = category_mask;
        }
    } else {
        state->allocation = AllocateRecordBuffer_08005B28(64);
        {
            register struct RecordRoot **property_cell asm("r1") = root_cell;
            asm("" : "+r" (property_cell));
            *state->resolved = GetRecordProperty_080CCD50((*property_cell)->code, 0);
        }
        CopyRecordText_08018C24(state->allocation,
                              RecordTextWords[*state->resolved]);
    }
    }
}
asm(".set RecordRootCell,0x0200f438\n.set RecordCopyCell,0x0836d4bc\n.set RecordPalette,0x030039c8\n.set PackedRecordBank,0x08497418\n.set RecordTextWords,0x085567f0\n.thumb_set RecordPaletteSource_080CBABC,0x080cbabd\n.thumb_set AllocateRecordBuffer_08005B28,0x08005b29\n.thumb_set DecodePackedRecord_08013E9C,0x08013e9d\n.thumb_set GetRecordProperty_080CCD50,0x080ccd51\n.thumb_set CopyRecordText_08018C24,0x08018c25\n.thumb_set _call_via_r3,0x08142251\n");
