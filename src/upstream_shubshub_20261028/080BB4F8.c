/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BB4F8.c
 * Original SHA-256: 603218658bf8804076b990be76ecadb92f8f4e19c1b4612725019dec10467bcd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} Position;

typedef struct {
    u8 unknown_00;
    s8 velocity;
    u8 unknown_02[6];
    u8 mode;
    u8 unknown_09[3];
    s32 end_x;
    s32 end_z;
    s32 start_x;
    s32 start_z;
    s32 scalar;
    s32 step;
    s32 scale;
    s32 end_axis;
    s32 end_height;
    s32 start_axis;
    s32 start_height;
    s32 inverse_scalar;
    s32 phase;
    s32 magnitude;
} Motion;

extern u32 func_08002804(void);
extern void func_080BB370(Motion *motion);

/* Target: 0x080BB4F8..0x080BB5C2 (202 bytes). */
u32 func_080BB4F8(Position *source, Position **destination, Motion *motion,
                  s32 scalar)
{
    s32 start_x, start_z, end_x, end_z;
    s32 distance_x, distance_z;

    func_08002804();
    motion->velocity = -((s16)func_08002804() % 6 + 5);
    motion->scale = 1024;
    motion->step = 1;
    start_x = source->x << 8;
    motion->start_x = start_x;
    start_z = source->z << 8;
    motion->start_z = start_z;
    end_x = (*destination)->x << 8;
    motion->end_x = end_x;
    end_z = (*destination)->z << 8;
    motion->end_z = end_z;
    motion->scalar = scalar;
    motion->inverse_scalar = 255 - scalar;
    motion->magnitude = 512;
    distance_x = end_x - start_x;
    if (distance_x < 0)
        distance_x = -distance_x;
    distance_z = end_z - start_z;
    if (distance_z < 0)
        distance_z = -distance_z;
    motion->start_height = (source->y + 48) << 8;
    if (distance_x >= distance_z) {
        motion->start_axis = start_x;
        motion->end_axis = end_x;
    } else {
        motion->start_axis = start_z;
        motion->end_axis = end_z;
    }
    motion->phase = 1;
    motion->end_height = ((*destination)->y + 24) << 8;
    motion->mode = 3;
    func_080BB370(motion);
    return 1;
}
