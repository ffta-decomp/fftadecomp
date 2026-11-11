#include "ffta/unsigned_types.h"
typedef signed short s16;
typedef signed int s32;
typedef struct Axis { u16 value; u8 opaque02[10]; } Axis;
typedef struct SceneEvent {
    u16 state, opaque02;
    u8 *signal;
    s32 displacement;
    u8 opaque12[8];
    u16 mode, parameter, height, opaque26;
} SceneEvent;
typedef struct CurveStageWork {
    u16 flags, tick;
    u8 opaque04[4];
    u8 index, signal, restarted, opaque11;
    Axis x, y, blend_a, blend_b;
    void *child;
    u8 opaque64[4];
} CurveStageWork;
typedef struct Coordinate { s16 x, y; } Coordinate;
typedef struct StageDisplay {
    u16 flags;
    u8 opaque02[72];
    volatile u8 control74, control75, blend76, blend77;
} StageDisplay;
typedef s32 (*SceneCallback)(void *,SceneEvent *,void *);
extern StageDisplay CurveStageDisplay;
extern const Coordinate CurveStarts[], CurveEnds[];
extern const u8 StageLayerKinds[], StageChildParameters[], StageChildTimes[];
extern const s16 StageChildDisplacements[];
extern void InitAxis(Axis *,s32,s32,s32) asm("RetailCall_080e0608");
extern void AdvanceAxis(Axis *) asm("RetailCall_080e064c");
extern u32 IsAxisComplete(Axis *) asm("RetailCall_080e0690");
extern void SetupStageLayer(u32,u32,u32,s32,s32,void *,void *) asm("RetailCall_080d74e0");
extern u32 GetStageLayerMask(u32) asm("RetailCall_080035a8");
extern void SetStageScrollX(s32,u32) asm("RetailCall_08003508");
extern void SetStageScrollY(s32,u32) asm("RetailCall_08003558");
extern void *CreateSceneChild(SceneCallback,u32,const SceneEvent *,void *) asm("RetailCall_08005b6c");
extern void *PollSceneChild(void *) asm("RetailCall_080e051c");
extern s32 StageRasterChild(void *,SceneEvent *,void *) asm("StageRasterChild_0811FD75");
extern void ClearStageBackground(void) asm("RetailCall_080d4020");
#define READ_INDEX() (*(const volatile u8 *)&work->index)
#define READ_TICK() (*(const volatile u16 *)&work->tick)
#define UPDATE_SCROLL() \
    SetStageScrollX((s16)-work->x.value,0); \
    SetStageScrollY((s16)-work->y.value,0)
#define UPDATE_BLEND() \
    CurveStageDisplay.blend76 = work->blend_a.value; \
    CurveStageDisplay.blend77 = work->blend_b.value
s32 AdvanceIndexedCurveStage(void *,SceneEvent *,CurveStageWork *) asm("RemainingBand43_0011FFD8");
s32 AdvanceIndexedCurveStage(void *parent,SceneEvent *event_in,CurveStageWork *work_in)
{
    register SceneEvent *event asm("r9") = event_in;
    CurveStageWork *work;
    register u32 flags asm("r1");
    register u32 mask asm("r0");
    register u32 paused asm("r10");
    register SceneEvent *store_event __asm__("r3");
    register u32 store_value __asm__("r0");
    SceneEvent first_child_event;
    SceneEvent second_child_event;
    {
        register CurveStageWork *input_work asm("r2") = work_in;
        asm("" : "+r"(event), "+r"(input_work));
        work = input_work;
    }
    flags = work->flags;
    mask = 0x8000;
    asm("" : "+r"(flags), "+r"(mask));
    mask &= flags;
    mask = (u16)mask;
    paused = mask;
    asm("" : "+r"(paused));
    if (mask) return 0;
    switch (event->state) {
    case 0:
        {
            register SceneEvent *mode_event __asm__("r1") = event;
            __asm__("" : "+r"(mode_event));
            work->index = mode_event->mode;
        }
        break;
    case 1:
        break;
    case 256:
    {
        register const u8 *kind_base __asm__("r0") = StageLayerKinds;
        u32 index;
        register u32 kind __asm__("r1");
        register const Coordinate *starts __asm__("r5");
        register const Coordinate *initial_point __asm__("r2");
        register const Coordinate *ends __asm__("r6");
        s32 x, y;
        u32 layer_mask;
        register u32 display_flags __asm__("r1");
        register s32 from __asm__("r1");
        register s32 to __asm__("r2");
        register Axis *first_axis __asm__("r0");
        register Axis *second_axis __asm__("r0");
        __asm__("" : "+r"(kind_base));
        index = READ_INDEX();
        kind = *(const u8 *)(index + (u32)kind_base); __asm__("" : "+r"(kind));
        starts = CurveStarts; __asm__("" : "+r"(starts));
        initial_point = (const Coordinate *)((index << 2) + (u32)starts); __asm__("" : "+r"(initial_point));
        x = (s16)-(u16)initial_point->x;
        y = (s16)-(u16)initial_point->y;
        SetupStageLayer(0,kind,0,x,y,(void *)0x06000000,(void *)0x06006000);
        layer_mask = GetStageLayerMask(0);
        display_flags = CurveStageDisplay.flags; __asm__("" : "+r"(display_flags));
        display_flags |= layer_mask;
        CurveStageDisplay.flags = (u16)display_flags;
        first_axis = &work->x; __asm__("" : "+r"(first_axis));
        index = READ_INDEX();
        from = starts[index].x; __asm__("" : "+r"(from));
        ends = CurveEnds; __asm__("" : "+r"(ends));
        to = ends[index].x; __asm__("" : "+r"(to));
        InitAxis(first_axis,from,to,260);
        second_axis = &work->y; __asm__("" : "+r"(second_axis));
        index = READ_INDEX();
        from = starts[index].y;
        to = ends[index].y;
        InitAxis(second_axis,from,to,260);
        first_child_event.mode = paused;
        first_child_event.parameter = StageChildParameters[READ_INDEX()];
        first_child_event.height = 80;
        first_child_event.signal = &work->signal;
        first_child_event.displacement = StageChildDisplacements[READ_INDEX()];
        work->child = CreateSceneChild(StageRasterChild,360,&first_child_event,parent);
        CurveStageDisplay.control74 = 65;
        CurveStageDisplay.control75 = 62;
        InitAxis(&work->blend_a,0,0,60);
        InitAxis(&work->blend_b,16,6,60);
        goto shared_scene_increment;
    }
    case 257:
    {
        u32 next_tick;
        AdvanceAxis(&work->x);
        AdvanceAxis(&work->y);
        AdvanceAxis(&work->blend_a);
        AdvanceAxis(&work->blend_b);
        UPDATE_SCROLL();
        UPDATE_BLEND();
        next_tick = READ_TICK()+1;
        work->tick = (u16)next_tick;
        if ((u16)next_tick > 19) {
            store_event = event; __asm__("" : "+r"(store_event));
            store_value = (u32)store_event->state + 1;
            __asm__("" : "+r"(store_value));
            goto shared_state_store;
        }
        break;
    }
    case 258:
    {
        Axis *blend = &work->blend_a;
        register u32 comparison_tick __asm__("r2");
        if (!(u8)IsAxisComplete(blend)) {
            register Axis *other_blend __asm__("r5");
            AdvanceAxis(blend);
            other_blend = &work->blend_b; __asm__("" : "+r"(other_blend));
            AdvanceAxis(other_blend);
            UPDATE_BLEND();
            if ((u8)IsAxisComplete(blend) && !work->restarted) {
                InitAxis(blend,0,0,20);
                InitAxis(other_blend,6,12,20);
                work->restarted = 1;
            }
        }
        if (work->child) work->child = PollSceneChild(work->child);
        AdvanceAxis(&work->x);
        AdvanceAxis(&work->y);
        UPDATE_SCROLL();
        work->tick = READ_TICK()+1;
        comparison_tick = READ_TICK(); __asm__("" : "+r"(comparison_tick));
        if (comparison_tick == 260u-StageChildTimes[READ_INDEX()]) {
            second_child_event.mode = 1;
            second_child_event.parameter = StageChildParameters[READ_INDEX()];
            second_child_event.height = 80;
            second_child_event.signal = &work->signal;
            second_child_event.displacement = StageChildDisplacements[READ_INDEX()];
            work->child = CreateSceneChild(StageRasterChild,360,&second_child_event,parent);
        }
        if (READ_TICK() > 239) {
            InitAxis(blend,0,0,20);
            InitAxis(&work->blend_b,12,16,20);
            {
                store_event = event; __asm__("" : "+r"(store_event));
                store_value = (u32)store_event->state + 1;
                __asm__("" : "+r"(store_value));
                goto shared_state_store;
            }
        }
        break;
    }
    case 259:
    {
        Axis *x_axis = &work->x;
        AdvanceAxis(x_axis);
        AdvanceAxis(&work->y);
        AdvanceAxis(&work->blend_a);
        AdvanceAxis(&work->blend_b);
        UPDATE_SCROLL();
        UPDATE_BLEND();
        if ((u8)IsAxisComplete(x_axis)) {
            work->signal = 1;
            work->child = PollSceneChild(work->child);
            if (!work->child) {
shared_scene_increment:
                {
                    register SceneEvent *increment_event __asm__("r1") = event;
                    __asm__("" : "+r"(increment_event));
                    increment_event->state++;
                }
            }
        }
        break;
    }
    case 260:
    {
        u32 layer_mask = GetStageLayerMask(0);
        CurveStageDisplay.flags &= ~layer_mask;
        ClearStageBackground();
        store_value = 2;
        store_event = event;
shared_state_store:
        store_event->state = (u16)store_value;
        break;
    }
    }
    return 0;
}
typedef char WorkSize[(sizeof(CurveStageWork)==68)?1:-1];
typedef char EventSize[(sizeof(SceneEvent)==28)?1:-1];
typedef char CurveSize[(sizeof(Axis)==12)?1:-1];
typedef char CoordinateStride[(sizeof(Coordinate)==4)?1:-1];
__asm__(".global CurveStageDisplay\n.set CurveStageDisplay,0x03000940\n"
        ".global CurveStarts\n.set CurveStarts,0x083A7928\n"
        ".global CurveEnds\n.set CurveEnds,0x083A793C\n"
        ".global StageLayerKinds\n.set StageLayerKinds,0x083A7950\n"
        ".global StageChildParameters\n.set StageChildParameters,0x083A7955\n"
        ".global StageChildTimes\n.set StageChildTimes,0x083A795A\n"
        ".global StageChildDisplacements\n.set StageChildDisplacements,0x083A7960\n"
        ".global StageRasterChild_0811FD75\n.thumb_set StageRasterChild_0811FD75,0x0811FD75\n");

__asm__(".global RetailCall_08003508\n.thumb_set RetailCall_08003508, 0x08003509\n.global RetailCall_08003558\n.thumb_set RetailCall_08003558, 0x08003559\n.global RetailCall_080035a8\n.thumb_set RetailCall_080035a8, 0x080035a9\n.global RetailCall_08005b6c\n.thumb_set RetailCall_08005b6c, 0x08005b6d\n.global RetailCall_080d4020\n.thumb_set RetailCall_080d4020, 0x080d4021\n.global RetailCall_080d74e0\n.thumb_set RetailCall_080d74e0, 0x080d74e1\n.global RetailCall_080e051c\n.thumb_set RetailCall_080e051c, 0x080e051d\n.global RetailCall_080e0608\n.thumb_set RetailCall_080e0608, 0x080e0609\n.global RetailCall_080e064c\n.thumb_set RetailCall_080e064c, 0x080e064d\n.global RetailCall_080e0690\n.thumb_set RetailCall_080e0690, 0x080e0691\n");
