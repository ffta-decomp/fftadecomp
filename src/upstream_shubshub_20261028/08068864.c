/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08068864.c
 * Original SHA-256: 04039a4957b4084888a9ff0f10ab1456b908303db7dbe5f1672d854951f417ea
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 frame;
    u8 unknown_0a[4];
    s16 ticks;
} Label08068864;

typedef struct {
    u8 unknown_00[0xd];
    u8 active;
    u8 unknown_0e[0x16];
    u8 renderer[0x2c];
    u8 unknown_50[0x6c];
    Label08068864 first_label;
    Label08068864 second_label;
} Object08068864;

extern void func_08016234(void *);
extern void func_08068548(Object08068864 *);
extern void func_08017FE8(Label08068864 *);

/* 0x08068864..0x080688D0: 108 bytes, 50 instructions. */
void func_08068864(Object08068864 *object)
{
    func_08016234(object->renderer);
    if (object->active) {
        func_08068548(object);
        if (++object->first_label.ticks > 5) {
            object->first_label.ticks = 0;
            if (++object->first_label.frame > 2)
                object->first_label.frame = 0;
            if (--object->second_label.frame <= -3)
                object->second_label.frame = 0;
        }
        func_08017FE8(&object->first_label);
        func_08017FE8(&object->second_label);
    }
}
