/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct Actor { void *unit; } Actor;
typedef struct InteractionRecord { u16 selector,item; u8 bytes4[6]; u16 valid; s16 delta; u8 bytes14[6]; } InteractionRecord;
typedef struct TargetGroup { Actor *actor; u8 records[800]; u16 count; u16 unknown806; } TargetGroup;
typedef struct TargetGroups { TargetGroup groups[13]; u16 count; } TargetGroups;
typedef struct Selection { Actor *actor; u16 values[41]; u16 current; } Selection;
typedef struct InventoryEntry { u16 item; u8 quantity,reserved; } InventoryEntry;
#define OFF(T,F) ((u32)&(((T*)0)->F))
typedef char record_size[sizeof(InteractionRecord)==20?1:-1];
typedef char group_size[sizeof(TargetGroup)==808?1:-1];
typedef char group_count[OFF(TargetGroup,count)==804?1:-1];
typedef char groups_count[OFF(TargetGroups,count)==0x2908?1:-1];
typedef char selection_index[OFF(Selection,current)==86?1:-1];
extern u32 ReadUnitField(const void *,u8);
extern u16 SelectBucketItem(u32);
extern u32 UnitField27HasBit15(const void *);
extern InventoryEntry *GetInventoryPartition(u16,s32 *);
extern void BuildInteraction(InteractionRecord *,Actor *,Actor *,u16,u16,u16);
__asm__(".global SelectBucketItem\n.thumb_set SelectBucketItem,0x080d2f79\n"
        ".global BuildInteraction\n.thumb_set BuildInteraction,0x080c2619\n");

/* Prepare one target group's record, filtering random items and signed result direction. */
u32 PrepareTargetGroupRecord(TargetGroups *targets, Selection *selection,
                         u16 supplied_item, u16 direction_filter, u16 mode, u8 index)
{
    u16 selected_index;
    u16 source_value;
    s32 processed;
    source_value=ReadUnitField(selection->actor->unit,6);
    selected_index=selection->current;
    processed=0;
    for (;;) {
        TargetGroup *write_group;
        Actor *source_actor;
        InteractionRecord *record;
        u16 item;
        if(index>=targets->count)
            return 255;
        item=supplied_item;
        {
            TargetGroup *scan_group=&targets->groups[index];
            record=(InteractionRecord *)(scan_group->records+20*scan_group->count);
        }
        if(selection->values[selected_index]==148 || selection->values[selected_index]==211) {
            item=SelectBucketItem((u8)source_value);
            if((u8)UnitField27HasBit15(selection->actor->unit)==0) {
                s32 count=0;
                InventoryEntry *entry=GetInventoryPartition(item,&count);
                s32 i;
                for(i=0;i<count;++i,++entry) {
                    if(entry->item==item) {
                        if((s32)entry->quantity-entry->reserved<=0)
                            item=0;
                        break;
                    }
                }
                if(item==0) goto next_group;
            }
        }
        source_actor=selection->actor;
        write_group=&targets->groups[index];
        BuildInteraction(record,source_actor,write_group->actor,
                         selection->values[selected_index],item,mode);
        if(record->valid==0) goto next_group;
        if((s16)direction_filter>0 && record->delta<0) goto next_group;
        if((s16)direction_filter<0 && record->delta>=0) goto next_group;
        ++write_group->count;
next_group:
        ++index;
        ++processed;
        if(processed>0) break;
    }
    return index;
}
