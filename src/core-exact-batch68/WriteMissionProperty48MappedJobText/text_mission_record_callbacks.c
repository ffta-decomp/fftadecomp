typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct __attribute__((packed)) {
    u16 mission_id : 10;
    u16 unknown_id_bits : 6;
} PackedMissionRecord;
typedef char MissionRecordSize[sizeof(PackedMissionRecord) == 2 ? 1 : -1];

typedef struct {
    const u8 *selected_record;
    u8 reserved_04[4];
    const u8 *secondary_text;
    u16 context_mission_id;
} TextMissionRecordContext;

#define TEXT_CONTEXT ((volatile TextMissionRecordContext *)0x020020d0)
#define JOB_CONTENT_POINTERS ((const u8 *const *)0x085567f0)
#define CONTENT_POINTERS ((const u8 *const *)0x08526680)
#define DEFAULT_MISSION_TEXT (*(const u8 * volatile *)0x02006680)

extern const u8 *const gJobContentPointers[];
extern u32 GetMissionProperty(u16 mission_id, u8 selector);
/* Selectors 46 and 48 are packed in four and six bits respectively. */
extern u8 GetMissionPropertyByte(u16 mission_id, u8 selector);
extern const u8 *GetContentPointer123(u16 index);
/* This caller supplies only a proven six-bit mission field to the byte lookup. */
extern u8 FindJobMappingKey(u8 value);
extern u32 GetJobProperty(u8 job_id, u8 fallback_job_id, u8 selector);
extern u16 CopyEncodedTextToBuffer(u8 *output, const u8 *source);
extern u16 WriteTextControlMarker(u8 *output, u8 value);

#if defined(MISSION_REQUIREMENT_ITEM_TEXT)
u32 WriteMissionRequirementItemText(u8 *output, u8 callback_index)
{
    const u8 *selected_record = TEXT_CONTEXT->selected_record;
    u16 mission_id = selected_record
        ? (u16)(selected_record[0] | ((selected_record[1] & 3) << 8))
        : TEXT_CONTEXT->context_mission_id;
    u8 item_selector = (callback_index == 23 || callback_index == 37) ? 44 : 42;
    u16 item_content_index = (u16)GetMissionProperty(mission_id, item_selector);
    u8 paired_selector = callback_index == 36 ? 42 :
                         callback_index == 37 ? 44 : 0;
    u16 marker_value = 0;

    if (!item_content_index) {
        CopyEncodedTextToBuffer(output, DEFAULT_MISSION_TEXT);
        return 0;
    }

    if (paired_selector)
        marker_value = (u16)GetMissionProperty(mission_id, paired_selector);
    if (marker_value)
        output += WriteTextControlMarker(output, 3);

    output += CopyEncodedTextToBuffer(
        output, GetContentPointer123(item_content_index));
    if (paired_selector && GetMissionProperty(
            mission_id, (u8)(paired_selector + 1)))
        output += CopyEncodedTextToBuffer(output, JOB_CONTENT_POINTERS[66]);
    if (marker_value)
        WriteTextControlMarker(output, 0);
    return 0;
}
#elif defined(MISSION_PROPERTY46_TEXT)
u32 WriteMissionProperty46Text(u8 *output)
{
    const u8 *selected_record = TEXT_CONTEXT->selected_record;
    u16 mission_id = selected_record
        ? (u16)(selected_record[0] | ((selected_record[1] & 3) << 8))
        : TEXT_CONTEXT->context_mission_id;
    u8 property_value = GetMissionPropertyByte(mission_id, 46);
    u16 content_index = property_value
        ? (u16)(property_value + 97)
        : 0;

    CopyEncodedTextToBuffer(output, JOB_CONTENT_POINTERS[content_index]);
    return property_value ? 0 : 13;
}
#elif defined(MISSION_PROPERTY48_MAPPED_JOB_TEXT)
u32 WriteMissionProperty48MappedJobText(u8 *output)
{
    const u8 *selected_record = TEXT_CONTEXT->selected_record;
    u16 mission_id = selected_record
        ? ((const PackedMissionRecord *)selected_record)->mission_id
        : TEXT_CONTEXT->context_mission_id;
    u32 property_value = GetMissionProperty(mission_id, 48);
    u32 mapped_job_id = FindJobMappingKey(property_value);
    u16 content_index = (u16)GetJobProperty(
        mapped_job_id, mapped_job_id, 0);
    const u8 *const *content_table = gJobContentPointers;

    CopyEncodedTextToBuffer(output, content_table[content_index]);
    return 0;
}
#else
#error Select one mission-record text callback
#endif
