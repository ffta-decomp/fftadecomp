typedef unsigned char u8; typedef signed char s8;
typedef unsigned short u16; typedef signed short s16;
struct Actor {u8 unknown0[8];u16 x;u16 unknown10;u16 z;};
struct Motion {struct Actor *actor;u8 unknown4[302];s8 dx; s8 dz;u8 unknown308[2];u16 target_x;u16 target_z;};
int BattleRuntimeDependency_000A9E6C(struct Motion *motion, int step)
{
    int result = 1;
    if (motion->dx) {
        motion->actor->x += motion->dx * step;
        if (motion->dx < 0) {
            if ((s16)motion->target_x > (s16)motion->actor->x) {
                motion->actor->x = motion->target_x;
                result = 0;
            }
        } else {
            if ((s16)motion->target_x < (s16)motion->actor->x) {
                motion->actor->x = motion->target_x;
                result = 0;
            }
        }
    }
    if (motion->dz) {
        motion->actor->z += motion->dz * step;
        if (motion->dz < 0) {
            if ((s16)motion->target_z > (s16)motion->actor->z) {
                motion->actor->z = motion->target_z;
                result = 0;
            }
        } else {
            if ((s16)motion->target_z < (s16)motion->actor->z) {
                motion->actor->z = motion->target_z;
                result = 0;
            }
        }
    }
    return result;
}
