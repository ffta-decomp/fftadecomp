typedef unsigned char u8;
typedef unsigned int u32;
struct ProgressionSelectorRecord { u8 selector; u8 unknown01[11]; };
extern const struct ProgressionSelectorRecord ProgressionSelectorRecords[];
extern u32 GetSceneSelectorValueByIndex(u32 one_based_index);
asm(".global ProgressionSelectorRecords\n.set ProgressionSelectorRecords,0x08563a70\n.global GetSceneSelectorValueByIndex\n.thumb_set GetSceneSelectorValueByIndex,0x08036331");

u8 ReadProgressionSelectorOrdinal(u32 record_input)
{
    u8 record_index=record_input;
    /* Retail wraps selector value zero to ordinal255; no clamp is present. */
    return GetSceneSelectorValueByIndex(ProgressionSelectorRecords[record_index].selector)-1;
}
