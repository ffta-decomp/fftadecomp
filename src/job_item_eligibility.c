typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

enum {
    SPECIAL_JOB_GROUP = 4,
    GROUP_ONLY_ITEM_CATEGORY = 22,
    RESTRICTED_ITEM_CATEGORY_A = 23,
    RESTRICTED_ITEM_CATEGORY_B = 25,
    RESTRICTED_ITEM_A = 287,
    RESTRICTED_ITEM_B = 311,
    RESTRICTED_ITEM_C = 316
};

extern u32 GetJobProperty(u8 job_id, u8 fallback_job, u8 property);
extern u32 GetItemProperty(u16 item_id, u8 property);
extern const u32 gEquipmentClassMasks[];

/* Combine the job's equipment-class mask with the item category. The three
 * observed item IDs in categories 23/25 require job group 4 as well.
 */
u8 JobAllowsItem(u8 job_id, u16 item_id)
{
    u8 group = GetJobProperty(job_id, job_id, 1);
    u32 category_mask = gEquipmentClassMasks[GetJobProperty(job_id, job_id, 36)];
    u8 category = GetItemProperty(item_id, 3);

    if (category == GROUP_ONLY_ITEM_CATEGORY)
        return group == SPECIAL_JOB_GROUP;
    if (!(category_mask & (1U << (category - 1))))
        return 0;
    if (category == RESTRICTED_ITEM_CATEGORY_B ||
        category == RESTRICTED_ITEM_CATEGORY_A) {
        if (item_id == RESTRICTED_ITEM_B ||
            item_id == RESTRICTED_ITEM_C ||
            item_id == RESTRICTED_ITEM_A) {
            if (group != SPECIAL_JOB_GROUP)
                return 0;
        }
    }
    return 1;
}
