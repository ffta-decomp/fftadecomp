#include "interfaces.h"
void ApplySceneContinuationRecord(const struct SceneContinuationRecord *record,
    u8 table_selector) __asm__("SceneRegisteredRoot_00009C18");
void ApplySceneContinuationRecord(const struct SceneContinuationRecord *record,
    u8 table_selector)
{
    u16 continuation;
    u16 first_parameter;
    u16 second_parameter;
    if (record->override_parameter) {
        u32 row_byte_offset = table_selector * sizeof(struct SceneContinuationRecord);
        const struct SceneContinuationRecord *selected_record =
            (const struct SceneContinuationRecord *)(row_byte_offset + (u32)gSceneContinuationRecords);
        first_parameter = selected_record->default_parameter;
        second_parameter = record->override_parameter;
    } else {
        first_parameter = record->default_parameter;
        second_parameter = 0;
    }
    WriteContinuationParameters(first_parameter, second_parameter);
    if (record->continuation_code == 74)
        continuation = gSceneContinuationRam.queued_continuations[gSceneContinuationRam.queue_index];
    else
        continuation = record->continuation_code;
    if (continuation)
        gSceneContinuationRam.scene_definition_byte = FindSceneDefinition(continuation)[0];
    ActivateSceneContinuation(continuation);
}
