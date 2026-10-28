/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813B0D4.c
 * Original SHA-256: bc9a749ab5b759b30ead313e645ac8c666d523ca5fb501a39f8e15c6753bf802
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0813B0D4, 0x0813B2A8), 468 bytes. */
typedef struct {
    u32 reference;
    u8 active;
    u8 unknown_05[0x103];
} Record0813B0D4;

typedef struct {
    u32 reference;
    u8 unknown_04[12];
} __attribute__((packed)) CompactRecord0813B0D4;

typedef struct {
    u8 unknown_00[0x11];
    u8 flags;
    u8 unknown_12[0x6e];
    Record0813B0D4 records[24];
    u8 unknown_1940[0x1538];
    CompactRecord0813B0D4 compact_records[20];
    u8 unknown_2fb8[12];
    Record0813B0D4 extra_records[12];
} RecordSet0813B0D4;

typedef struct {
    u8 unknown_00[5];
    u8 enabled;
} State0813B0D4;

extern State0813B0D4 data_03000ED0;
extern void func_0813BC7C(u8);
extern void func_0813BB04(u8, void *);
extern u8 func_080C95D8(u32, void *);
extern u32 func_080CA0F8(Record0813B0D4 *);
extern u32 func_080CA150(CompactRecord0813B0D4 *);
extern u32 func_080CA1BC(Record0813B0D4 *);
extern u32 func_080CA1F0(CompactRecord0813B0D4 *);
extern void func_081452F4(void);
extern void func_08145798(void);
extern void func_080033C8(u32);
extern u32 func_0813B2A8(u8, void *);
extern void func_081457FC(void);

u32 func_0813B0D4(u8 mode, void *data)
{
    RecordSet0813B0D4 *set = data;
    u8 enabled = data_03000ED0.enabled;
    CompactRecord0813B0D4 *compact;
    u32 result;
    s32 i;

    data_03000ED0.enabled = 0;
    if (!set) {
        func_0813BC7C(mode);
        data_03000ED0.enabled = enabled;
        return 1;
    }

    func_0813BB04(mode, set);
    if (func_080C95D8(0x5ae, set))
        set->flags |= 2;

    for (i = 0; i < 24; i++) {
        if (set->records[i].active)
            set->records[i].reference = func_080CA0F8(&set->records[i]);
    }
    for (i = 0; i < 20; i++) {
        compact = &set->compact_records[i];
        if (compact->reference)
            compact->reference =
                func_080CA150(&set->compact_records[i]);
    }
    if (mode == 2) {
        for (i = 0; i < 12; i++) {
            if (set->extra_records[i].active)
                set->extra_records[i].reference =
                    func_080CA0F8(&set->extra_records[i]);
        }
    }

    func_081452F4();
    func_08145798();
    func_080033C8(2);
    result = func_0813B2A8(mode, data);
    func_081457FC();

    for (i = 0; i < 24; i++) {
        if (set->records[i].active)
            set->records[i].reference = func_080CA1BC(&set->records[i]);
    }
    for (i = 0; i < 20; i++) {
        compact = &set->compact_records[i];
        if (compact->reference)
            compact->reference =
                func_080CA1F0(&set->compact_records[i]);
    }
    if (mode == 2) {
        for (i = 0; i < 12; i++) {
            if (set->extra_records[i].active)
                set->extra_records[i].reference =
                    func_080CA1BC(&set->extra_records[i]);
        }
    }

    data_03000ED0.enabled = enabled;
    return result;
}
