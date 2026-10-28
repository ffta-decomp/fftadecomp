#include "../../../src/task_tree_core.h"
/* This is a view of fields inside the actual 0x3CA8-byte decoded image. */
struct SaveSummaryView {
    u8 unknown0[47];
    u8 indexed_summary;
    u8 unknown48[0x3c28 - 48];
    u16 direct_summary;
    u8 summary_index;
};
struct PrimarySummaryRecord { u8 unknown0[6]; u8 secondary_index; u8 unknown7[5]; };
struct SecondarySummaryRecord { u8 value; u8 unknown1[26]; } __attribute__((packed));
typedef char PrimaryRecordSize[sizeof(struct PrimarySummaryRecord)==12?1:-1];
typedef char SecondaryRecordSize[sizeof(struct SecondarySummaryRecord)==27?1:-1];
extern const struct PrimarySummaryRecord PrimarySummaryRecords[];
extern const struct SecondarySummaryRecord SecondarySummaryRecords[];
u32 SelectSaveHeaderSummaryValue(u8 *image,u8 selector)
{
    struct SaveSummaryView *summary = (struct SaveSummaryView *)image;
    if (selector == 0) {
        if (summary->direct_summary != 0) {
            summary->indexed_summary = 0;
            return summary->direct_summary;
        } else {
            u8 index = summary->summary_index;
            u32 primary_offset = (u32)index * 12;
            u8 secondary_index = ((const struct PrimarySummaryRecord *)(primary_offset + (u32)PrimarySummaryRecords))->secondary_index;
            const struct SecondarySummaryRecord *record = &SecondarySummaryRecords[secondary_index];
            summary->indexed_summary = 1;
            return record->value;
        }
    } else if (selector == 1) {
        summary->indexed_summary = 0;
        return summary->direct_summary;
    } else {
        u8 index = summary->summary_index;
        u32 primary_offset = (u32)index * 12;
            u8 secondary_index = ((const struct PrimarySummaryRecord *)(primary_offset + (u32)PrimarySummaryRecords))->secondary_index;
        const struct SecondarySummaryRecord *record = &SecondarySummaryRecords[secondary_index];
        summary->indexed_summary = 1;
        return record->value;
    }
}
asm(".global PrimarySummaryRecords\n.set PrimarySummaryRecords,0x08563a70\n"
    ".global SecondarySummaryRecords\n.set SecondarySummaryRecords,0x08564670\n");
