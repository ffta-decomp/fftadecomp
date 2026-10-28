typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct SaveStatePrefix { u8 padding[0x3c28]; u16 active_mission_id; };
struct EventState { u8 padding[4]; u32 selected_item_id; };
extern struct SaveStatePrefix gSaveData;
extern struct EventState gContentState;
extern u32 GetMissionProperty(u16 mission_id, u8 selector);
extern u8 HasInventoryItem(u16 item_id);
extern u8 ReadSaveByte(u16 index);
extern void WriteSaveByte(u16 index, u8 value);
extern int AddInventoryItem(u16 item_id, u8 quantity);

/* Choose an item from mission selector 18, record it in the event state,
 * then either advance the selector byte or add the item to inventory. */
u8 ProcessMissionItemGrant(void)
{
    u16 mission_id = gSaveData.active_mission_id;
    u32 item_selector;
    u16 item_id;
    u8 selector_index;

    item_selector = GetMissionProperty(mission_id, 18);
    if (item_selector == 1)
        goto selector_one;
    {
        u32 minimum_item_selector = 1;
        if (item_selector >= minimum_item_selector)
            goto selector_many;
    }
    item_id = 51;
    selector_index = 1;
    goto item_selected;

selector_one:
    item_id = 148;
    selector_index = 2;
    goto item_selected;

selector_many:
    item_id = 286;
    selector_index = 4;

item_selected:

    gContentState.selected_item_id = item_id;
    if (HasInventoryItem(item_id)) {
        u8 current_value = ReadSaveByte(selector_index);
        if (current_value <= 254)
            WriteSaveByte(selector_index, current_value + 1);
        return 14;
    }
    AddInventoryItem(item_id, 1);
    return 13;
}
