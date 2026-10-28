typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct SceneUnitRecord {
    u8 unknown0[40];
    u16 flags;
    u8 unknown42[222];
} SceneUnitRecord;
typedef struct ScenePosition {
    u8 unknown0[8];
    s16 x;
    u16 unknown10;
    s16 y;
} ScenePosition;
typedef char unit_stride_check[sizeof(SceneUnitRecord)==264 ? 1:-1];
extern SceneUnitRecord *ResolveSceneUnitIdentifier(u32);
extern SceneUnitRecord *FindUnitBySlot(u32);
extern void *GetSceneActionContextBase(void);
extern ScenePosition *FindSceneEntity(void *, SceneUnitRecord *);

static inline SceneUnitRecord *FindFlaggedSceneUnit(void)
{
    SceneUnitRecord *scan = (SceneUnitRecord *)0x02000080;
    s32 index;
    for (index = 0; index < 24; index++, scan++) {
        if (scan->flags & 0x400)
            return scan;
    }
    return 0;
}

/* LOW8 coordinates are interpreted signed for the sentinel and arithmetic.
   Early zero stores remain visible to every following opaque helper. */
void ComputeSceneEntityDeltas_08124E74(u8 selector, u8 target_x, u8 target_y,
                                      u16 *delta_x, u16 *delta_y)
{
    SceneUnitRecord *unit;
    ScenePosition *entity;
    if ((s8)target_x < 0)
        *delta_x = 0;
    if ((s8)target_y < 0)
        *delta_y = 0;
    if (selector == 255)
        unit = FindFlaggedSceneUnit();
    else if ((s8)selector < 0)
        unit = ResolveSceneUnitIdentifier(selector);
    else
        unit = FindUnitBySlot(selector);
    entity = FindSceneEntity(GetSceneActionContextBase(), unit);
    if ((s8)target_x >= 0) {
        s32 center_x = (s8)target_x * 32 + 16;
        s32 current_x = entity->x;
        *delta_x = center_x - current_x;
    }
    if ((s8)target_y >= 0) {
        s32 center_y = (s8)target_y * 32 + 16;
        s32 current_y = entity->y;
        *delta_y = center_y - current_y;
    }
}
asm(".global ResolveSceneUnitIdentifier\n.thumb_set ResolveSceneUnitIdentifier,0x08121cb5\n"
    ".global FindUnitBySlot\n.thumb_set FindUnitBySlot,0x080c83cd\n"
    ".global GetSceneActionContextBase\n.thumb_set GetSceneActionContextBase,0x08096d7d\n"
    ".global FindSceneEntity\n.thumb_set FindSceneEntity,0x08099561");
