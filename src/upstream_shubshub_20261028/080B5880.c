/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080B5880.c
 * Original SHA-256: 24b43a5bde381fbf2041911f825f695e7882d3abcb25b87eafd6ff019aefc1b1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080B5880..0x080B591E: 158 bytes, including the middle literal pool. */
typedef struct Unit Unit;

typedef struct {
    Unit *unit;
} UnitOwner;

typedef struct {
    UnitOwner *owner;
    void *handle;
    u8 x;
    u8 y;
} CursorState;

extern CursorState data_02010050;

UnitOwner *func_0809961C(void *context, s8 x, s8 y);
u8 func_080C8298(const Unit *unit);
void func_0802D704(void *handle);
void func_080A9528(void);
void func_080A9538(void);
u32 func_0809DE00(void);
void *func_0802B70C(Unit *unit, u32 flags);

void func_080B5880(void *context, u8 x, u8 y)
{
    UnitOwner *owner;
    u8 flags;

    if (data_02010050.x == x && data_02010050.y == y)
        return;

    data_02010050.x = x;
    data_02010050.y = y;
    owner = func_0809961C(context, (s8)x, (s8)y);
    if (owner != 0) {
        if (func_080C8298(owner->unit))
            owner = 0;
    }

    if (owner == 0) {
        if (data_02010050.owner != 0) {
            func_0802D704(data_02010050.handle);
            data_02010050.owner = 0;
            func_080A9528();
        }
    } else {
        if (data_02010050.owner != owner) {
            data_02010050.owner = owner;
            flags = func_0809DE00();
            data_02010050.handle =
                func_0802B70C(data_02010050.owner->unit, flags | 1);
            if ((flags & 0xC0) == 0x40)
                func_080A9538();
            else
                func_080A9528();
        }
    }
}
