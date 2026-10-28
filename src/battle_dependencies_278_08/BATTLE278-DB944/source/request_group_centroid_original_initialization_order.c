typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct ScenePositionRecord { u8 prefix[8]; s16 x, height, y; };
extern void *AllocateCurrentGamePool(u32 bytes);
extern void FreeCurrentGamePool(void *allocation);
extern u32 CollectSceneGroupObjects(u8 selector, struct ScenePositionRecord **objects, void *context);
extern void ProjectBattlePoint(s16 x, s16 height, s16 y, u16 *, u16 *, u16 *);
extern s32 SignedDivide(s32 numerator, s32 denominator);
extern u32 RequestFixedPositionTransition(s32 x, s32 y);

static inline void AverageProjectedSceneGroup(u8 selector, void *context,
                                               s16 *average_x, s16 *average_y,
                                               s16 *average_depth)
{
    struct ScenePositionRecord **objects;
    struct ScenePositionRecord *object;
    s16 projected_x, projected_y, projected_depth;
    s32 sum_x, sum_y, sum_depth;
    u8 count, index;
    objects = AllocateCurrentGamePool(96);
    count = CollectSceneGroupObjects(selector, objects, context);
    sum_x = 0;
    sum_y = 0;
    sum_depth = 0;
    for (index = 0; index < count; index++) {
        s16 *x = &projected_x;
        s16 *y = &projected_y;
        s16 *depth = &projected_depth;
        object = objects[index];
        ProjectBattlePoint(object->x, object->height, object->y,
                           (u16 *)x, (u16 *)y, (u16 *)depth);
        sum_x += projected_x;
        sum_y += *y;
        sum_depth += *depth;
    }
    FreeCurrentGamePool(objects);
    sum_x = SignedDivide(sum_x, count);
    sum_y = SignedDivide(sum_y, count);
    sum_depth = SignedDivide(sum_depth, count);
    *average_x = sum_x;
    *average_y = sum_y;
    *average_depth = sum_depth;
}

u32 RemainingBand43_000DB944(u8 selector, void *context)
{
    s16 x, y, depth;
    AverageProjectedSceneGroup(selector, context, &x, &y, &depth);
    x = (u16)x - 120;
    y = (u16)y - 80;
    return (u8)RequestFixedPositionTransition(x, y);
}
asm(".global AllocateCurrentGamePool\n.thumb_set AllocateCurrentGamePool,0x0800a655\n"
    ".global FreeCurrentGamePool\n.thumb_set FreeCurrentGamePool,0x0800a669\n"
    ".global CollectSceneGroupObjects\n.thumb_set CollectSceneGroupObjects,0x080dcd09\n"
    ".global ProjectBattlePoint\n.thumb_set ProjectBattlePoint,0x0801c919\n"
    ".global SignedDivide\n.thumb_set SignedDivide,0x08141871\n"
    ".global RequestFixedPositionTransition\n.thumb_set RequestFixedPositionTransition,0x080d8b29");
