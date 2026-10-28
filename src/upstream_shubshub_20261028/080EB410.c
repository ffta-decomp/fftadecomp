/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080EB410.c
 * Original SHA-256: d2912d1f7400b6543570a98eb854cb1c910257368195d31cb1cb2509147069ba
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x080EB410 .. 0x080EB514, complete target bytes:
f0b557464e464546e0b4071c00208246814649468800391c44310d1828680028
3cd08c204c464443201c64303e1830229219904640461cf72bf9301c5c301cf7
27f9301d1cf724f92868391c943109190023c95e3a1cc03212190023d25e0023
25f7b0f93819031cec33ee30008819884018002618802868391c683109190024
0a5f1b88111c25f719ff40461cf7f0f9002803d0286825f7bfff2e6048460130
0004000c81460728b3d9386900281dd03c1c1434201c1cf7ebf880218900081c
7a888018788038691423fa5e7b88111c25f7f4fe201c1cf7cbf9002806d03869
25f79aff002038610124a246f868eaf719fef860504638bc9846a146aa46f0bc
02bc0847
*/
#include "ffta.h"

typedef struct MotionInterpolator {
    s32 value;
    s32 unknown_04[9];
    s32 remaining;
} MotionInterpolator;

typedef struct OrbitRecord {
    u32 unknown_00;
    MotionInterpolator scale;
    MotionInterpolator x;
    MotionInterpolator y;
    u16 angle;
    u16 angle_step;
} OrbitRecord;

typedef struct OrbitPayload {
    u16 unknown_00;
    u16 large_angle;
    u8 unknown_04[8];
    void *coordinate_task;
    Vec3 *large_object;
    MotionInterpolator large_scale;
    u32 unknown_40;
    Vec3 *objects[8];
    OrbitRecord records[8];
} OrbitPayload;

extern void func_080076A0(void *state);
extern u32 func_08007880(const void *state);
extern void func_080107D4(Vec3 *object, s16 x, s16 y, s16 z);
extern void func_080112CC(Vec3 *object, s16 x, s16 y, u16 angle);
extern void func_08011428(Vec3 *object);
extern void *func_080D6134(void *task);

u8 func_080EB410(OrbitPayload *payload)
{
    u8 completed = 0;
    u16 index;

    for (index = 0; index < 8; index++) {
        if (payload->objects[index] != 0) {
            func_080076A0(&payload->records[index].x);
            func_080076A0(&payload->records[index].y);
            func_080076A0(&payload->records[index].scale);
            func_080107D4(payload->objects[index], (s16)payload->records[index].x.value,
                         (s16)payload->records[index].y.value, 0);
            payload->records[index].angle += payload->records[index].angle_step;
            func_080112CC(payload->objects[index], (s16)payload->records[index].scale.value,
                         (s16)payload->records[index].scale.value, payload->records[index].angle);
            if (func_08007880(&payload->records[index].x)) {
                func_08011428(payload->objects[index]);
                payload->objects[index] = 0;
            }
        }
    }
    if (payload->large_object != 0) {
        func_080076A0(&payload->large_scale);
        payload->large_angle += 0x200;
        func_080112CC(payload->large_object, (s16)payload->large_scale.value,
                     (s16)payload->large_scale.value, payload->large_angle);
        if (func_08007880(&payload->large_scale)) {
            func_08011428(payload->large_object);
            payload->large_object = 0;
            completed = 1;
        }
    }
    payload->coordinate_task = func_080D6134(payload->coordinate_task);
    return completed;
}
