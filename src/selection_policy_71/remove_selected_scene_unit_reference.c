/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Unit {u8 gap[40];u16 flags;u8 tail[222];};
struct Reference {u32 unknown;struct Unit *unit;};
extern struct Unit gUnits[];
extern struct Unit gSecondary[];
extern void (*gClearRoutine)(void *,u32);
extern void *GetContentContext(void);
extern void *FindRecord(void *,void *);
extern void *RemoveRecord(void *);
extern struct Unit *FindUnitById(u32);
extern struct Unit *ResolveSceneUnit(u32);
extern struct Reference *GetSceneReference(u8);
extern void ClearTrampoline(void *,u32,void (*)(void *,u32));

asm(".global gUnits\n.set gUnits,0x02000080\n.global gSecondary\n.set gSecondary,0x02002fc4\n.global gClearRoutine\n.set gClearRoutine,0x0836d4b8\n.global GetContentContext\n.thumb_set GetContentContext,0x8096d7d\n.global FindRecord\n.thumb_set FindRecord,0x8099561\n.global RemoveRecord\n.thumb_set RemoveRecord,0x80995c1\n.global FindUnitById\n.thumb_set FindUnitById,0x80c83cd\n.global ResolveSceneUnit\n.thumb_set ResolveSceneUnit,0x8121cb5\n.global GetSceneReference\n.thumb_set GetSceneReference,0x8121c71\n.global ClearTrampoline\n.thumb_set ClearTrampoline,0x814224d\n");
static inline struct Unit *FindMarkedUnit(void)
{
    struct Unit *unit = gUnits;
    int index;
    for (index = 0; index <= 23; index++,unit++) {
        if (unit->flags & 0x400) return unit;
    }
    return 0;
}
asm(".global _call_via_r2\n.thumb_set _call_via_r2,0x814224d");
void RemoveSelectedSceneUnitReference(u8 selector)
{
    struct Unit *unit;
    struct Unit *scan;
    struct Reference *reference;
    int index;
    if (selector == 255) {
        unit = FindMarkedUnit();
    } else if ((s8)selector < 0) unit = ResolveSceneUnit(selector);
    else unit = FindUnitById(selector);
selected:
    RemoveRecord(FindRecord(GetContentContext(),unit));
    if ((s8)selector < 0) {
        reference = GetSceneReference(selector);
        if (reference->unit == unit) reference->unit = 0;
    }
    if ((u32)unit >= (u32)gSecondary) gClearRoutine(unit,264);
}
