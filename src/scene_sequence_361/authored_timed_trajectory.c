typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct SceneEvent {
    u16 state;
    u8 opaque02[18];
    u16 x, y, ordinal;
} SceneEvent;
typedef struct AxisInterpolation { s16 value; u8 opaque02[10]; } AxisInterpolation;
typedef struct TrajectoryWork {
    u16 flags;
    u8 opaque02[6];
    void *object;
    u8 ordinal, trajectory;
    u8 opaque14[2];
    AxisInterpolation x, y;
} TrajectoryWork;
typedef struct AuthoredTrajectory {
    u8 duration, opaque01;
    u16 x_delta, y_delta;
    u16 opaque06;
} AuthoredTrajectory;
extern const u8 SceneTrajectoryMap[];
extern const u8 SceneObjectModes[];
extern const u8 SceneTrajectoryOffsetX[];
extern const u8 SceneTrajectoryOffsetY[];
extern const AuthoredTrajectory SceneTrajectories[];
extern void *CreateSceneObject(const void *,u32,s32,s32,u32,u32,u32,u32) asm("RetailCall_080D5CC0");
extern void InitSceneAxis(AxisInterpolation *,s32,s32,u32) asm("RetailCall_080E0608");
extern void AdvanceSceneAxis(AxisInterpolation *) asm("RetailCall_080E064C");
extern void PositionSceneObject(void *,s32,s32,u32) asm("RetailCall_080107D4");
extern void *PollSceneObject(void *) asm("RetailCall_08011484");
s32 UpdateAuthoredTimedTrajectory(void *,SceneEvent *,TrajectoryWork *) asm("RemainingBand43_0011ED40");
s32 UpdateAuthoredTimedTrajectory(void *parent,SceneEvent *event,TrajectoryWork *work)
{
    register s32 x asm("r4");
    register s32 y asm("r5");
    u32 offset;
    u32 mode;
    register const AuthoredTrajectory *trajectory asm("r1");
    register const void *asset asm("r0");
    const AuthoredTrajectory *trajectories;
    register AxisInterpolation *axis asm("r0");
    if (work->flags & 0x8000) return 0;
    switch (event->state) {
    case 0:
        work->ordinal = event->ordinal;
        work->trajectory = SceneTrajectoryMap[work->ordinal];
        offset = SceneTrajectoryOffsetX[work->ordinal];
        x = event->x;
        x += offset;
        offset = SceneTrajectoryOffsetY[work->ordinal];
        y = event->y;
        y += offset;
        asset = (const void *)0x085087D8;
        asm("" : "+r"(asset), "+r"(x), "+r"(y));
        mode = SceneObjectModes[work->ordinal];
        x = (s16)x;
        y = (s16)y;
        work->object = CreateSceneObject(asset,mode,x,y,972,6,0,0);
        axis = &work->x;
        asm("" : "+r"(axis));
        trajectories = SceneTrajectories;
        asm("" : "+r"(trajectories));
        trajectory = (const AuthoredTrajectory *)((u32)work->trajectory * 8 + (u32)trajectories);
        asm("" : "+r"(trajectory));
        InitSceneAxis(axis,x,(s16)(x+trajectory->x_delta),trajectory->duration);
        axis = &work->y;
        asm("" : "+r"(axis));
        trajectory = (const AuthoredTrajectory *)((u32)work->trajectory * 8 + (u32)trajectories);
        asm("" : "+r"(trajectory));
        InitSceneAxis(axis,y,(s16)(y+trajectory->y_delta),trajectory->duration);
        break;
    case 256:
        AdvanceSceneAxis(&work->x);
        AdvanceSceneAxis(&work->y);
        PositionSceneObject(work->object,work->x.value,work->y.value,0);
        work->object = PollSceneObject(work->object);
        if (!work->object) event->state = 2;
        break;
    case 1:
        break;
    }
    return 0;
}
__asm__(".global RetailCall_080D5CC0\n.thumb_set RetailCall_080D5CC0,0x080D5CC1\n"
        ".global RetailCall_080E0608\n.thumb_set RetailCall_080E0608,0x080E0609\n"
        ".global RetailCall_080E064C\n.thumb_set RetailCall_080E064C,0x080E064D\n"
        ".global RetailCall_080107D4\n.thumb_set RetailCall_080107D4,0x080107D5\n"
        ".global RetailCall_08011484\n.thumb_set RetailCall_08011484,0x08011485");

__asm__(".global SceneTrajectoryMap\n.set SceneTrajectoryMap,0x083A7546\n"
        ".global SceneTrajectoryOffsetX\n.set SceneTrajectoryOffsetX,0x083A755C\n"
        ".global SceneTrajectoryOffsetY\n.set SceneTrajectoryOffsetY,0x083A7572\n"
        ".global SceneTrajectories\n.set SceneTrajectories,0x083A7588");

__asm__(".global SceneObjectModes\n.set SceneObjectModes,0x083A7530");
