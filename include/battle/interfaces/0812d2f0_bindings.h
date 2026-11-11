typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef signed int s32;
struct UnitCoordinateView {
    u8 before_coordinates[246];
    s8 coordinates[3];
};
typedef char coordinate_offset[((u32)&(((struct UnitCoordinateView*)0)->coordinates)==246)?1:-1];
/* Caller passes signed fullword coordinates; callee retains their low bytes.
 * The selector remains full32 through both existing implementations. */
extern u32 QueryEffectFeasibility(const struct UnitCoordinateView *actor,
    const struct UnitCoordinateView *target, s32 actor_x, s32 actor_y,
    s32 target_x, s32 target_y, s32 target_direction, u32 selector);
extern u32 CheckEffectTargetState(const struct UnitCoordinateView *target, u32 selector);
__asm__(".thumb_set QueryEffectFeasibility, 0x0812D1DD\n.thumb_set CheckEffectTargetState, 0x08133A59");
