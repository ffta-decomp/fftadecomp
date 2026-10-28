/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct UnitAbilityView { u8 unknown0[6]; u8 category6; u8 unknown7[57]; u8 progress64[0]; } UnitAbilityView;
typedef char progress_offset64[((u32)&(((UnitAbilityView *)0)->progress64)==64)?1:-1];
typedef struct AbilityRecord { u8 unknown0[4]; u16 ability; u8 unknown6; u8 threshold; } AbilityRecord;
extern u32 ReadAbilityProperty(u32,u32);
extern u32 FindUnitAbilityIndex(UnitAbilityView *, const AbilityRecord *);
extern const AbilityRecord *ReadAbilityListEntry(u32,u32);
__asm__(".global ReadAbilityProperty\n.thumb_set ReadAbilityProperty,0x080ccd51");
__asm__(".global FindUnitAbilityIndex\n.thumb_set FindUnitAbilityIndex,0x08132ddd");
__asm__(".global ReadAbilityListEntry\n.thumb_set ReadAbilityListEntry,0x080cd481");

u32 FindFirstIncompleteUnitAbility(UnitAbilityView *,const AbilityRecord **,s32,s32 *);
u32 FindFirstIncompleteUnitAbility(UnitAbilityView *unit,const AbilityRecord **records,s32 count,s32 *ordinal)
{
    s32 i;
    for(i=0;i<count;++i) {
        if(ReadAbilityProperty(records[i]->ability,25)) {
            u16 index=(u16)FindUnitAbilityIndex(unit,records[i]);
            if(index) {
                u32 progress=unit->progress64[index]&127;
                const AbilityRecord *entry=ReadAbilityListEntry(unit->category6,(u8)index);
                if(progress<entry->threshold) {
                    *ordinal=i;
                    return index;
                }
            }
        }
    }
    return 0;
}
