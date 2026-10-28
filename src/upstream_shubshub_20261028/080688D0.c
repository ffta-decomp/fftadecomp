/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080688D0.c
 * Original SHA-256: e6ef6085714c2c81ded0240ff8f762550b8a0aa4d2aecbc8275305a44bf24f92
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080688D0..0x0806890C: 60 bytes. */
typedef struct {
    u8 unknown_00[0x0C];
    u8 first_control[0x10];
    u8 second_control[0x10];
    void *menu;
} MenuContext;

typedef struct {
    u8 unknown_00[0x10];
    u8 index;
} MenuRecord;

extern MenuRecord g_state_020020D0;
extern const u8 data_0851BA72[];
extern const u8 data_0851BA7A[];
extern void func_08061518(void *context, u8 index);
extern void func_08017FA8(void *control, const u8 *text, u32 x, u32 y);

void func_080688D0(MenuContext *context)
{
    func_08061518(context->menu, g_state_020020D0.index);
    func_08017FA8(context->first_control, data_0851BA72, 0xD8, 0x0E);
    func_08017FA8(context->second_control, data_0851BA7A, 0x18, 0x0E);
}
