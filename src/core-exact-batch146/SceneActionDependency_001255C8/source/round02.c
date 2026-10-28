typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct UnitRecordView { u8 prefix[40]; u16 flags; u8 remaining[222]; };
typedef char UnitStride[sizeof(struct UnitRecordView)==264?1:-1];
typedef char FlagsOffset[(u32)&(((struct UnitRecordView *)0)->flags)==40?1:-1];
struct SceneActor;
extern struct UnitRecordView gUnitRecords[];
extern u8 *FindUnitPoolRecordById(u32);
extern u32 ResolveSceneUnitByEncodedId(u32);
extern void *GetBattleActionRegistry(void);
extern struct SceneActor *FindPrimaryActor(void *,const void *);
struct SceneActor *ResolveSceneCommandPrimaryActor(u32 selector_argument)
{
    u32 selector=(u8)selector_argument;
    u32 result;
    register u32 selected_mask __asm__("r4");
    register struct UnitRecordView *record __asm__("r2");
    register s32 ordinal __asm__("r3");
    register u32 record_flags __asm__("r1");
    register u32 tested_mask __asm__("r0");
    if(selector!=255)goto explicit_selector;
    record=gUnitRecords;
    ordinal=0;
    selected_mask=0x400;
    /* Native keeps the initialized selection mask across the whole scan. */
    asm("" : "+r"(record), "+r"(ordinal), "+r"(selected_mask));
scan_record:
    record_flags=record->flags;
    asm("" : : "r"(record_flags));
    tested_mask=selected_mask;
    asm("" : "+r"(tested_mask));
    tested_mask &= record_flags;
    asm("" : : "r"(tested_mask));
    if(tested_mask!=0)goto found_record;
    ordinal++;
    record++;
    if(ordinal<=23)goto scan_record;
    result=0;
    goto selected_unit;
explicit_selector:
    if((s32)(selector<<24)>=0)goto positive_selector;
    result=ResolveSceneUnitByEncodedId(selector);
    goto selected_unit;
found_record:
    result=(u32)record;
    goto selected_unit;
positive_selector:
    result=(u32)FindUnitPoolRecordById(selector);
selected_unit:
    return FindPrimaryActor(GetBattleActionRegistry(),(const void *)result);
}
asm(".global gUnitRecords\n.set gUnitRecords,0x02000080\n"
    ".global FindUnitPoolRecordById\n.thumb_set FindUnitPoolRecordById,0x080c83cd\n"
    ".global ResolveSceneUnitByEncodedId\n.thumb_set ResolveSceneUnitByEncodedId,0x08121cb5\n"
    ".global GetBattleActionRegistry\n.thumb_set GetBattleActionRegistry,0x08096d7d\n"
    ".global FindPrimaryActor\n.thumb_set FindPrimaryActor,0x08099561\n");
