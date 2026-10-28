typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct MissionPackedId { u16 mission_id:10; u16 other_bits:6; } __attribute__((packed));
typedef char MissionPackedIdSize[(sizeof(struct MissionPackedId)==2)?1:-1];

typedef struct {
    const u8 *selected_record;
    u8 reserved_04[8];
    u16 fallback_mission_id;
} MissionTextContext;

#define SELECTED_MISSION_ID(record) \
    ((u16)(((const struct MissionPackedId *)(record))->mission_id))

#define TEXT_CONTEXT ((volatile MissionTextContext *)0x020020d0)
#define JOB_CONTENT_POINTERS ((const u8 *const *)0x085567f0)
#define MISSION_CONTENT_POINTERS ((const u8 *const *)0x0855a64c)
#define CONTEXT_SELECTOR_VALUE (*(volatile const u8 *)0x02002182)
#define CONTEXT_SELECTOR_ENABLED (*(volatile const u8 *)0x02002184)
#define SCENE_SELECTOR_VALUE (*(volatile const u8 *)0x02001f69)

extern u32 GetMissionProperty(u16 mission_id, u8 selector);
extern u16 WriteUnsignedNumberText(u8 *output, u32 value);
extern u16 CopyEncodedTextToBuffer(u8 *output, const u8 *source);

#if defined(CALLBACK_G_190A8)
u32 WriteMissionProperty47OrDefaultText(u8 *output)
{
    register volatile MissionTextContext *context asm("r0");
    register const u8 *selected_record asm("r2");
    u16 mission_id;
    u32 property_46;

    context = TEXT_CONTEXT;
    asm("" : "+r"(context));
    selected_record = context->selected_record;
    asm("" : "+r"(selected_record));
    mission_id = selected_record
        ? SELECTED_MISSION_ID(selected_record)
        : context->fallback_mission_id;
    property_46 = GetMissionProperty(mission_id, 46);

    /* Only the selected path masks the ID; the fallback stays full u16. */
    if ((u16)property_46 != 0) {
        context = TEXT_CONTEXT;
        asm("" : "+r"(context));
        selected_record = context->selected_record;
        asm("" : "+r"(selected_record));
        mission_id = selected_record
            ? SELECTED_MISSION_ID(selected_record)
            : context->fallback_mission_id;
        WriteUnsignedNumberText(output, GetMissionProperty(mission_id, 47));
    } else {
        CopyEncodedTextToBuffer(output, JOB_CONTENT_POINTERS[0]);
    }
    return 0;
}
#elif defined(CALLBACK_G_19120)
/* The helper chain's semantic names remain provisional; preserve call widths. */
extern u32 ResolveCurrentSceneSelector(u32 selector);
extern u8 CountStatusRecordsWithBits0And1(u32 raw_selector_result);
extern u32 ResolveMissionTextValue(u16 mission_id, u8 selector_slot,
                                   u8 status_count);

u32 WriteMissionStatusSelectionText(u8 *output)
{
    const u8 *selected_record = TEXT_CONTEXT->selected_record;
    u8 record_flags = selected_record[2];
    u16 mission_id;
    u32 raw_selector_result;
    u8 selector_slot;
    u8 status_count;
    u16 text_value;
    u16 value_text_bytes;

    if ((record_flags & 0x1c) == 0) {
        CopyEncodedTextToBuffer(output, JOB_CONTENT_POINTERS[68]);
        return 0;
    }

    mission_id = SELECTED_MISSION_ID(selected_record);
    raw_selector_result = ResolveCurrentSceneSelector(SCENE_SELECTOR_VALUE);
    selector_slot = (u8)raw_selector_result;
    status_count = (u8)CountStatusRecordsWithBits0And1(raw_selector_result);
    text_value = (u16)ResolveMissionTextValue(
        mission_id, selector_slot, status_count);
    value_text_bytes = WriteUnsignedNumberText(output, text_value);

    /* The retail addition is 32-bit after narrowing the helper's length. */
    output = (u8 *)((u32)output + (u32)value_text_bytes);
    CopyEncodedTextToBuffer(output, JOB_CONTENT_POINTERS[732]);
    return 0;
}
#elif defined(CALLBACK_G_191B0)
extern u32 ResolveContextTextPointer(u8 selector_value);

u32 WriteMissionContextSelectedText(u8 *output)
{
    volatile u8 *context_bytes = (volatile u8 *)TEXT_CONTEXT;

    if (context_bytes[0xb4] != 0) {
        u32 source_address = ResolveContextTextPointer(
            context_bytes[0xb2]);
        CopyEncodedTextToBuffer(output, (const u8 *)source_address);
    } else {
        const u8 *selected_record = *(const u8 *volatile *)context_bytes;
        u32 mission_id = selected_record
            ? SELECTED_MISSION_ID(selected_record)
            : *(volatile u16 *)(context_bytes + 12);
        CopyEncodedTextToBuffer(output, MISSION_CONTENT_POINTERS[mission_id]);
    }
    return 0;
}
#else
#error Select one callback-cluster-G entry
#endif
