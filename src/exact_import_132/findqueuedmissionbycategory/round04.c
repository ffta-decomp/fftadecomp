#include "interfaces.h"

static inline int IsReservedMissionId(u16 mission_id)
{
    mission_id = (u16)(mission_id - 336);
    {
    int reserved = 0;
    if (mission_id <= 22)
        reserved = 1;
    return reserved;
    }
}

struct MissionNode *FindQueuedMissionByCategory(u8 mode, u16 category)
{
    struct MissionNode *head = gMissionQueueSave.queue;
    struct MissionNode *node;

    if (head != 0) {
        if (mode != 0) {
            node = head;
            while (node->next != 0)
                node = node->next;
            while (node->previous != 0) {
                if (node->descriptor->category == category) {
                    if (mode == 1 &&
                        IsMissionRequirementStateSatisfied(node->descriptor->mission_id) == 0) {
                        if (IsReservedMissionId(node->descriptor->mission_id) == 0)
                            return node;
                    } else if (mode == 2) {
                        if (IsReservedMissionId(node->descriptor->mission_id) == 0)
                            return node;
                    }
                }
                node = node->previous;
            }
        } else {
            node = head;
            while (node->next != 0) {
                if (node->descriptor->category == category &&
                    IsReservedMissionId(node->descriptor->mission_id) == 0)
                    return node;
                node = node->next;
            }
        }
    }
    return 0;
}
