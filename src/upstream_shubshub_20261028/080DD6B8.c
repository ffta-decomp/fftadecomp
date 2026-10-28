/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DD6B8.c
 * Original SHA-256: 6fb063fd6e54550e231e8407f5c61eb70349d0544ca27808154cc3dc376e6364
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x080DD6B8, 0x080DD6E0), 40 bytes. */
typedef struct Unit Unit;

typedef struct {
    Unit *unit;
} UnitOwner;

extern void *func_08096D7C(void);
extern UnitOwner *func_0809961C(void *context, s8 x, s8 y);

UnitOwner *func_080DD6B8(u8 x, u8 y)
{
    return func_0809961C(func_08096D7C(), (s8)x, (s8)y);
}
