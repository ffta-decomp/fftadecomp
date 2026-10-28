/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Physical layouts only; wider mission/menu roles remain provisional. */
typedef struct {
    u16 mission_id:10;
    u16 flags:6;
    u16 unknown_02;
    u8 linked_record_a;
    u8 linked_record_b;
} __attribute__((packed)) SelectedMissionRecord;

typedef struct {
    u8 record_id;
    u8 flags;
    u16 mission_id;
} StatusRecord;

typedef struct {
    u8 before_state[0x119d];
    u8 next_state;
    u8 before_started[3];
    u8 started;
    u8 before_cost[2];
    u16 required_cost;
    u8 before_unit_count[2];
    u8 unit_count;
    u8 before_status_count;
    u8 status_count;
    u8 before_unit_storage[0x41];
    u8 unit_pointer_storage[0x5c];
    /* 520-byte physical storage extent; this is not a runtime count bound. */
    StatusRecord *status_pointer_storage[130];
    SelectedMissionRecord *selected_record;
    u32 pending;
    u8 before_indices[0x44];
    u8 unit_indices[1];
} MissionController;

typedef struct {
    u8 before_missing_item[12];
    u16 missing_item;
} MissionMessageContext;

#define FIELD_OFFSET(type, field) ((u32)&(((type *)0)->field))
typedef char SelectedMissionSize[(sizeof(SelectedMissionRecord) == 6) ? 1 : -1];
typedef char StateOffset[(FIELD_OFFSET(MissionController, next_state) == 0x119d) ? 1 : -1];
typedef char CostOffset[(FIELD_OFFSET(MissionController, required_cost) == 0x11a4) ? 1 : -1];
typedef char UnitCountOffset[(FIELD_OFFSET(MissionController, unit_count) == 0x11a8) ? 1 : -1];
typedef char StatusCountOffset[(FIELD_OFFSET(MissionController, status_count) == 0x11aa) ? 1 : -1];
typedef char UnitStorageOffset[(FIELD_OFFSET(MissionController, unit_pointer_storage) == 0x11ec) ? 1 : -1];
typedef char StatusStorageOffset[(FIELD_OFFSET(MissionController, status_pointer_storage) == 0x1248) ? 1 : -1];
typedef char SelectedOffset[(FIELD_OFFSET(MissionController, selected_record) == 0x1450) ? 1 : -1];
typedef char PendingOffset[(FIELD_OFFSET(MissionController, pending) == 0x1454) ? 1 : -1];
typedef char IndicesOffset[(FIELD_OFFSET(MissionController, unit_indices) == 0x149c) ? 1 : -1];

extern MissionController *gMissionController;
typedef struct {
    u8 available;
    u8 unknown_01;
} __attribute__((packed)) MissionCategoryRecord;

typedef struct {
    u8 before_amount[0x1f64];
    u32 available_amount;
    u8 unknown_1f68;
    u8 scene_selector;
    u8 before_categories[0x24a];
    /* The u8 selector gives this mechanical address domain, not a game count. */
    MissionCategoryRecord categories[256];
} MissionData;
typedef char AmountOffset[(FIELD_OFFSET(MissionData, available_amount) == 0x1f64) ? 1 : -1];
typedef char SelectorOffset[(FIELD_OFFSET(MissionData, scene_selector) == 0x1f69) ? 1 : -1];
typedef char CategoryOffset[(FIELD_OFFSET(MissionData, categories) == 0x21b4) ? 1 : -1];
typedef char CategoryStride[(sizeof(MissionCategoryRecord) == 2) ? 1 : -1];
extern MissionData gMissionDataBase;
extern MissionMessageContext gMissionMessage;
extern void (*gMissionClearEntry)(void *, u32);
/* Caller passes complete registers; the existing callee consumes low16/low8. */
extern u32 GetMissionProperty(u32 mission_id, u32 selector);
extern u8 CollectEligibleUnits(u32 mission_id, void **output, u8 *indices);
extern void ResetSelectionPair(u8 slot, u8 value);
extern u32 ResolveCurrentSceneSelector(u32 selector);
extern u8 CountStatusRecordsWithBits0And1(void);
extern u32 CalculateMissionCost(u32 mission_id, u32 selector, u32 count);

extern u8 CollectUnlinkedStatusRecords(StatusRecord **output);
extern StatusRecord *FindStatusRecordForItem(u16 item_id);
extern u32 QueryNextMissionState(u8 enabled);

asm(".global gMissionController\n.set gMissionController,0x0200f448\n"
    ".global gMissionDataBase\n.set gMissionDataBase,0x02000000\n"
    ".global gMissionMessage\n.set gMissionMessage,0x020020d0\n"
    ".global gMissionClearEntry\n.set gMissionClearEntry,0x0836d4b8\n"
    ".global GetMissionProperty\n.thumb_set GetMissionProperty,0x080ce4dd\n"
    ".global CollectEligibleUnits\n.thumb_set CollectEligibleUnits,0x080611f1\n"
    ".global ResetSelectionPair\n.thumb_set ResetSelectionPair,0x08060ded\n"
    ".global ResolveCurrentSceneSelector\n.thumb_set ResolveCurrentSceneSelector,0x08036351\n"
    ".global CountStatusRecordsWithBits0And1\n.thumb_set CountStatusRecordsWithBits0And1,0x080cecf5\n"
    ".global CalculateMissionCost\n.thumb_set CalculateMissionCost,0x080cec79\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n"
    ".global CollectUnlinkedStatusRecords\n.thumb_set CollectUnlinkedStatusRecords,0x080612c9\n"
    ".global FindStatusRecordForItem\n.thumb_set FindStatusRecordForItem,0x0805dd0d\n"
    ".global QueryNextMissionState\n.thumb_set QueryNextMissionState,0x0805d1c1\n");


/* Prepare the selected mission's eligible records and continuation state. */
u32 PrepareMissionEligibilityContinuation(void)
{
    u32 result = 0;
    u32 mission_id;
    u32 behavior;
    u32 current_mission_id;
    u32 raw_selector;
    u8 selector;
    u8 status_count;
    u32 cost;
    u16 first_item;
    u16 second_item;
    StatusRecord *first_record;
    StatusRecord *second_record;
    u32 category;
    u32 available;
    u32 helper_result;
    u32 continuation_state;

    mission_id = gMissionController->selected_record->mission_id;
    behavior = (u8)GetMissionProperty(mission_id, 1);
    if (gMissionController->started == 0) {
        gMissionController->pending = 0;
        helper_result = CollectEligibleUnits(
            0, (void **)gMissionController->unit_pointer_storage,
            gMissionController->unit_indices);
        gMissionController->unit_count = helper_result;
        ResetSelectionPair(4, 0);
        if (gMissionController->unit_count == 0 && behavior == 0) {
            gMissionController->next_state = 70;
            return 0;
        }

        current_mission_id = gMissionController->selected_record->mission_id;
        raw_selector = ResolveCurrentSceneSelector(gMissionDataBase.scene_selector);
        selector = (u8)raw_selector;
        status_count = CountStatusRecordsWithBits0And1();
        cost = CalculateMissionCost(current_mission_id, selector, status_count);
        gMissionController->required_cost = cost;
        if ((u16)cost != 0 &&
            gMissionDataBase.available_amount < gMissionController->required_cost) {
            gMissionController->next_state = 71;
            return result;
        }

        gMissionClearEntry(&gMissionController->selected_record->linked_record_a, 2);
        helper_result = CollectUnlinkedStatusRecords(
            gMissionController->status_pointer_storage);
        gMissionController->status_count = helper_result;
        second_record = 0;
        first_record = 0;
        first_item = GetMissionProperty(mission_id, 42);
        if (first_item != 0) {
            first_record = FindStatusRecordForItem(first_item);
            if (first_record != 0) {
                first_record->flags |= 1;
                first_record->mission_id = gMissionController->selected_record->mission_id;
                gMissionController->selected_record->linked_record_a = first_record->record_id;
                gMissionController->status_pointer_storage
                    [gMissionController->status_count] = first_record;
            }
        }

        second_item = GetMissionProperty(mission_id, 44);
        if (second_item != 0) {
            second_record = FindStatusRecordForItem(second_item);
            if (second_record != 0) {
                second_record->flags |= 1;
                second_record->mission_id = gMissionController->selected_record->mission_id;
                gMissionController->selected_record->linked_record_b = second_record->record_id;
                gMissionController->status_pointer_storage
                    [gMissionController->status_count + 1] = second_record;
            }
        }

        if (first_item != 0) {
            if (second_item != 0) {
                if (first_record == 0) {
                    if (second_record == 0) {
                        gMissionController->next_state = 87;
                        return result;
                    }
                    gMissionMessage.missing_item = first_item;
                    gMissionController->next_state = 73;
                    return result;
                }
                if (second_record == 0) {
                    gMissionMessage.missing_item = second_item;
                    gMissionController->next_state = 73;
                    return result;
                }
            } else if (first_record == 0) {
                gMissionMessage.missing_item = first_item;
                gMissionController->next_state = 72;
                return result;
            }
        } else if (second_item != 0 && second_record == 0) {
            gMissionMessage.missing_item = second_item;
            gMissionController->next_state = 72;
            return result;
        }

        category = (u8)GetMissionProperty(mission_id, 46);
        if (category != 0) {
            available = gMissionDataBase.categories[category].available;
            if (available < GetMissionProperty(mission_id, 47)) {
                gMissionController->next_state = 74;
                return result;
            }
        }

        if ((u8)GetMissionProperty(mission_id, 48) != 0) {
            helper_result = CollectEligibleUnits(
                mission_id, (void **)gMissionController->unit_pointer_storage,
                gMissionController->unit_indices);
            gMissionController->unit_count = helper_result;
            if (gMissionController->unit_count == 0) {
                gMissionController->next_state = 75;
                return result;
            }
        }
    }

    if (behavior == 0) {
        gMissionController->started = 1;
        gMissionController->next_state = 76;
        result = 7;
    } else {
        gMissionController->started = 1;
        continuation_state = QueryNextMissionState(1);
        gMissionController->next_state = continuation_state;
        result = 9;
    }
    return result;
}
