typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct __attribute__((packed)) {
    u16 mission_id : 10;
    u16 unknown_id_bits : 6;
} PackedMissionRecord;
typedef char PackedMissionRecordSize[sizeof(PackedMissionRecord) == 2 ? 1 : -1];

/* The selected record pointer and fallback mission ID share one RAM block. */
typedef struct {
    const u8 *selected_record;
    u8 reserved_04[8];
    u16 context_mission_id;
} MissionContentContext;

typedef struct {
    u8 fields_00_68[69];
    u8 property60;
} __attribute__((packed)) MissionDefinitionBytes;
typedef char MissionDefinitionSize[sizeof(MissionDefinitionBytes) == 70 ? 1 : -1];
typedef char MissionPropertyOffset[(u32)&((MissionDefinitionBytes *)0)->property60 == 69 ? 1 : -1];

#define MISSION_CONTENT_CONTEXT ((volatile MissionContentContext *)0x020020d0)
#define MISSION_PROPERTY60_ROWS ((const u8 *)0x08563a70)

extern const MissionDefinitionBytes gMissionDefinitions[];
extern const u8 *const gJobContentPointers[];
extern u16 CopyEncodedTextToBuffer(u8 *output, const u8 *source);

u32 WriteMissionProperty60ContentName(u8 *output)
{
    volatile MissionContentContext *context = MISSION_CONTENT_CONTEXT;
    const u8 *selected_record = context->selected_record;
    const MissionDefinitionBytes *definition;
    u8 property60;
    const u8 *property_row;
    const u8 *name;
    if (selected_record != 0)
        definition = &gMissionDefinitions[
            ((const PackedMissionRecord *)selected_record)->mission_id];
    else
        definition = &gMissionDefinitions[context->context_mission_id];
    property60 = definition->property60;
    property_row = MISSION_PROPERTY60_ROWS + property60 * 12;
    name = gJobContentPointers[717 + *property_row];

    CopyEncodedTextToBuffer(output, name);
    return 0;
}
