/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080A9940.c
 * Original SHA-256: d65d447c908d578667e42fd210a7bd6251c21b7dfc443a99795bb8e0afde9913
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[0xF6];
    u8 x, z;
    s8 direction;
} Unit;

typedef struct {
    Unit *unit;
    u32 unknown_04;
    s16 x, y, z;
} Object;

typedef struct {
    Object *object;
    u8 unknown_04[0x3C];
    u8 flags;
    u8 unknown_41[0x14B];
} UpdateEntry;

typedef u32 (*EntryCallback)(UpdateEntry *, u32, u32, u32);

typedef struct {
    UpdateEntry entries[13];
    u32 unknown_141C;
    u32 context;
    u8 unknown_1424[0x68];
    EntryCallback callbacks[13];
    s16 delays[16];
    u32 first;
    u32 second;
    u8 unknown_14E8[0x50];
    u8 count;
} Owner;

extern s32 func_08099C1C(void *, s8, s8);
extern void func_0809836C(Object *, u32, s8, u32);

/* Complete target: 080A9940..080A9A48, 264 bytes. */
u32 func_080A9940(Owner *owner)
{
    s32 i;
    u32 active = 0;

    for (i = 0; i < owner->count; i++) {
        EntryCallback callback = owner->callbacks[i];
        if (callback && (owner->entries[i].flags & 1)) {
            if (owner->delays[i] > 1) {
                owner->delays[i]--;
            } else {
                active = 1;
                if (!callback(&owner->entries[i], owner->context,
                              owner->first, owner->second)) {
                    owner->callbacks[i] = 0;
                    owner->entries[i].object->x = owner->entries[i].object->unit->x * 32 + 16;
                    owner->entries[i].object->z = owner->entries[i].object->unit->z * 32 + 16;
                    owner->entries[i].object->y = func_08099C1C(owner->entries[i].object,
                        (s8)owner->entries[i].object->unit->x,
                        (s8)owner->entries[i].object->unit->z) * 16;
                    func_0809836C(owner->entries[i].object, 0,
                                 owner->entries[i].object->unit->direction, 0);
                }
            }
        }
    }
    return active;
}
