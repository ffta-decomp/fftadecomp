#include "interfaces.h"

void CoreDependency29_0000A040(const void *event_record_descriptor)
{
    const void *const descriptor_snapshot = event_record_descriptor;
    const u8 input_byte = gRamBase[0x1f69];
    const u8 predicate_result = (u8)EvaluateMissionEventByte(input_byte);

    ForwardMissionRecord(descriptor_snapshot, predicate_result);
}
