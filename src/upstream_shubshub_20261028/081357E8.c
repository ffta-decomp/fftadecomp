/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081357E8.c
 * Original SHA-256: 183bb09f8b27da976436c9b93754fa2a393bdd45949c627d4d139be9be34984f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x081357E8, 0x08135890), 168 bytes, 74 instructions.
 * Local views retain only the field offsets observed in this function. */
typedef struct {
    u8 unknown_00;
    u8 kind;
} Entry081357E8;

typedef struct {
    void *context;
    void *object;
    u8 unknown_08[0x1e];
    u16 flags;
    u8 unknown_28[8];
    Entry081357E8 *entry;
} State081357E8;

typedef struct {
    u8 unknown_00[12];
    u8 mode;
} Descriptor081357E8;

extern State081357E8 data_0200F3F0;
extern void func_0812F2A4(u16, u16, u8);
extern void func_0812F328(u8);
extern u8 func_08130FBC(void);
extern u8 func_08131378(void);
extern void func_0812F34C(void *);
extern void func_0812F39C(s32);
extern u8 func_080C8280(const void *);

u32 func_081357E8(void *context, void *object, u16 event,
                  const u8 *attributes, const Descriptor081357E8 *descriptor)
{
    s32 index;

    switch (descriptor->mode) {
    case 2:
    case 3:
        if (object == 0 || event == 0)
            break;
        func_0812F2A4(event, 0, 0);
        data_0200F3F0.flags |= 0x10;
        data_0200F3F0.context = context;
        data_0200F3F0.object = object;
        for (index = 0; index < 3; index++) {
            func_0812F328((u8)index);
            if (func_08130FBC() && func_08131378()) {
                func_0812F34C(object);
                func_0812F39C(index);
                if (data_0200F3F0.entry->kind == 0x3b)
                    return 3;
            }
        }
        /* The remaining object checks also apply after the entry scan. */
    case 1:
        if (object != 0 && attributes != 0) {
            s32 flags = attributes[0];

            if (((flags >> 6) & 1) || func_080C8280(object))
                return 3;
        }
        break;
    }
    return 1;
}
