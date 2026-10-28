typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneContinuationRecord {
    u8 table_selector;
    u8 continuation_code;
    u16 default_parameter;
    u16 override_parameter;
    u8 unknown_tail[6];
};
struct SceneContinuationRam {
    u8 unknown_prefix[0x2191];
    u8 scene_definition_byte;
    u8 unknown_2192[2];
    u16 queued_continuations[4];
    u8 queue_index;
};
typedef char SceneContinuationRecordSize[(sizeof(struct SceneContinuationRecord) == 12) ? 1 : -1];
typedef char SceneContinuationOverrideOffset[((u32)&((struct SceneContinuationRecord *)0)->override_parameter == 4) ? 1 : -1];
typedef char SceneContinuationQueueOffset[((u32)&((struct SceneContinuationRam *)0)->queued_continuations == 0x2194) ? 1 : -1];
typedef char SceneContinuationIndexOffset[((u32)&((struct SceneContinuationRam *)0)->queue_index == 0x219c) ? 1 : -1];
extern const struct SceneContinuationRecord gSceneContinuationRecords[];
extern struct SceneContinuationRam gSceneContinuationRam;
extern void WriteContinuationParameters(u16 first, u16 second);
extern const u8 *FindSceneDefinition(u16 continuation);
extern void ActivateSceneContinuation(u16 continuation);
__asm__(".global gSceneContinuationRecords\n.set gSceneContinuationRecords,0x085644fc\n.global gSceneContinuationRam\n.set gSceneContinuationRam,0x02000000");
__asm__(".global WriteContinuationParameters\n.thumb_set WriteContinuationParameters,0x08009c05\n.global FindSceneDefinition\n.thumb_set FindSceneDefinition,0x08009a15\n.global ActivateSceneContinuation\n.thumb_set ActivateSceneContinuation,0x08009afd");
