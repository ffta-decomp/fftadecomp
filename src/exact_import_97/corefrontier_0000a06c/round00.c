#include "interfaces.h"

u32 ResolveNestedGroupPolicy(u32 group)
{
    u32 result;
    BeginNestedGroupPolicy();
    result = RunNestedGroup(group, group != 2);
    if (group - 5 <= 1 || group == 3) {
        result = (u8)ResolveGroupOutcome(result != 0);
        if (result == 2)
            return RunNestedGroup(7, 1);
    }
    return result;
}
