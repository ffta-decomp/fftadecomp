typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct MissionPackedId { u16 mission_id:10; u16 other_bits:6; } __attribute__((packed));
typedef char MissionPackedIdSize[(sizeof(struct MissionPackedId)==2)?1:-1];

extern u16 WriteUnsignedNumberText(u8 *output, u32 value);
extern u32 GetMissionProperty(u16 mission_id, u8 selector);

typedef struct {
    const u8 *selected_record;
    u8 reserved_04[4];
    const u8 *secondary_text;
    u16 context_mission_id;
} TextMissionContext;

#define TEXT_MISSION_CONTEXT ((volatile TextMissionContext *)0x020020d0)

#if defined(CONTEXT_MISSION_NUMBER)
u32 WriteContextMissionIdAsNumber(u8 *output)
{
    WriteUnsignedNumberText(output, TEXT_MISSION_CONTEXT->context_mission_id);
    return 0;
}
#elif defined(SELECTED_MISSION_PROPERTY30)
u32 WriteSelectedMissionProperty30AsNumber(u8 *output)
{
    volatile TextMissionContext *context = TEXT_MISSION_CONTEXT;
    const u8 *selected_record = context->selected_record;
    /* Selected records carry a ten-bit mission ID in their first two bytes. */
    u16 mission_id = selected_record
        ? (u16)((const struct MissionPackedId *)selected_record)->mission_id
        : context->context_mission_id;

    WriteUnsignedNumberText(output, GetMissionProperty(mission_id, 30));
    return 0;
}
#else
#error Select one text mission-context callback
#endif
