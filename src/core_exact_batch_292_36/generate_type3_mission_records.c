typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

/* Physical mission definitions have a 70-byte stride. */
struct MissionDefinition {
    u8 prefix00[14];
    u32 unknown14 : 3;
    u32 encoded_value14 : 8;
    u32 unknown15 : 11;
    u32 encoded_value16 : 8;
    u32 unknown17 : 2;
    u8 unknown18[52];
} __attribute__((packed));

/* These fields cross byte boundaries in the original 16-byte record. */
struct MissionRecord {
    u32 mission_id : 10;
    u32 definition_value16 : 8;
    u32 record_type : 3;
    u32 unknown02 : 3;
    u8 definition_value14;
    u8 unknown04[2];
    u16 random_value;
    u8 unknown08[8];
} __attribute__((packed));

typedef char DefinitionStride[(sizeof(struct MissionDefinition) == 70) ? 1 : -1];
typedef char RecordStride[(sizeof(struct MissionRecord) == 16) ? 1 : -1];
typedef char RandomValueOffset[((u32)&((struct MissionRecord *)0)->random_value == 6) ? 1 : -1];

typedef void (*ClearRecordBytes)(void *, u32);
extern const struct MissionDefinition MissionDefinitions[];
extern ClearRecordBytes ClearMissionRecord;
extern u8 ReadMissionProgressFlag(u16 flag);
extern u32 NextRandom15(void);
extern s32 SignedModulo(s32 value, s32 divisor);

/* Existing implementations only: no helper bodies or emitted inline instructions. */
__asm__(".global MissionDefinitions\n.set MissionDefinitions,0x0855ae4c\n"
        ".global ClearMissionRecord\n.set ClearMissionRecord,0x0836d4b8\n"
        ".global ReadMissionProgressFlag\n.thumb_set ReadMissionProgressFlag,0x080c9541\n"
        ".global NextRandom15\n.thumb_set NextRandom15,0x08002805\n"
        ".global SignedModulo\n.thumb_set SignedModulo,0x08142951\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
        ".global _call_via_r3\n.thumb_set _call_via_r3,0x08142251\n");


u32 GenerateType3MissionRecords(struct MissionRecord *output)
    __asm__("OriginalGameplayDependency_000D29D4");

u32 GenerateType3MissionRecords(struct MissionRecord *output)
{
    const struct MissionDefinition *definition = MissionDefinitions + 1;
    u32 count = 0;
    s32 mission_id;

    for (mission_id = 1; mission_id <= 511; ++mission_id, ++definition) {
        struct MissionRecord *record;
        u32 value14;
        u16 random_value;

        if ((definition->prefix00[2] & 0x38) != 0x18)
            continue;
        if (!ReadMissionProgressFlag(54) && (u32)(mission_id - 371) <= 2)
            continue;

        ++count;
        record = output++;
        ClearMissionRecord(record, 16);
        record->mission_id = (u16)mission_id;
        record->definition_value16 = definition->encoded_value16;
        record->record_type = 2;

        value14 = definition->encoded_value14;
        record->definition_value14 = value14 ? value14 : 255;
        random_value = SignedModulo((s16)NextRandom15(), 310);
        record->random_value = random_value;
    }
    return count;
}
