/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08073380.c
 * Original SHA-256: 6665ff59ed85cda328fc08403e683ccddcd4bbc1c381a78a99c9f3caa587648d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_000[0x970];
    u8 unknown_flag_0 : 1;
    u8 moving : 1;
    u8 unknown_flags_2 : 6;
    u8 unknown_971[3];
    u16 unknown_974;
    u16 unknown_976;
    u16 position_x;
    u16 position_y;
    u16 step_x;
    u16 step_y;
    u16 target_x;
    u16 target_y;
    u8 ticks_x;
    u8 ticks_y;
    u8 unknown_986;
    u8 unknown_987;
    u8 unknown_988[12];
    u16 position_z;
    u16 unknown_996;
    u16 render_z;
    u16 unknown_99a;
    u16 unknown_99c;
} MotionState;

typedef struct {
    u32 unknown_00;
    Entry *entries;
} SceneEntries;

typedef struct {
    u8 unknown_00[0x14];
    u16 enabled;
    u8 unknown_16[6];
} EntryFlags;

extern MotionState *data_03002818;
extern SceneEntries data_03000E30;
extern u8 data_0894EAF4[];
extern u8 data_0894EB80[];
extern void func_0804C524(Entry *, u16, u32, u8, u8, u32, u8, u32,
                         u8 *, u16, u8);
extern void func_08072C78(u16, u32);

/* Target: 0x08073380..0x080734CC, 332 bytes including literal pools. */
void func_08073380(u32 value)
{
    data_03002818->unknown_flag_0 = 0;
    data_03002818->moving = 0;
    data_03002818->unknown_974 = 0;
    data_03002818->unknown_976 = 48;
    data_03002818->position_x = 72;
    data_03002818->position_y = 8;
    data_03002818->step_x = 0;
    data_03002818->step_y = 0;
    data_03002818->target_x = 72;
    data_03002818->target_y = 8;
    data_03002818->ticks_x = 0;
    data_03002818->ticks_y = 0;
    data_03002818->unknown_986 = 0;
    data_03002818->unknown_987 = 0;
    data_03002818->position_z = 0;
    data_03002818->unknown_996 = 0;
    data_03002818->render_z = 0;
    data_03002818->unknown_99a = 0;
    data_03002818->unknown_99c = 0;

    func_0804C524(data_03000E30.entries, 25, 0, 0, 0, 0, 3,
                  (u32)data_0894EAF4, data_0894EB80, 0x1b0, 0);
    ((EntryFlags *)data_03000E30.entries)[25].enabled = 1;
    func_08072C78(0xffff, value);
    data_03002818->position_x = data_03002818->target_x;
    data_03002818->position_y = data_03002818->target_y;
    func_08072C78(0xffff, value);
}
