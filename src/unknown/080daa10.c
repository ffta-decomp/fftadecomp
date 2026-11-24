/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DAA10.c
 * Original SHA-256: dfe590346e5e006196326c291a462a75626276ef38e6b16745f561baa6ae68dd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct {
    u8 unknown_0[4];
    void *object;
} DrawingState;

extern DrawingState *func_08005BFC(void *task);
extern void *func_0800C614(void *object);
extern void func_080DA3B8(s16 first_x, s16 first_y, s16 second_x,
                         s16 second_y, void *context);
extern void func_080DA598(s16 first_x, s16 first_y, s16 second_x,
                         s16 second_y, void *context);

/* 0x080DAA10: 178 bytes. Draw four sides around a center point. */
void func_080DAA10(void *task, u16 x, u16 y, u16 width, u16 height)
{
    DrawingState *state = func_08005BFC(task);
    void *context = func_0800C614(state->object);
    int center_x = (s16)x;
    int center_y = (s16)y;

    if (width && height) {
        u16 left = center_x - width;
        u16 right = center_x + width;
        u16 top = center_y - height;
        u16 bottom = center_y + height;

        func_080DA3B8(center_x, top, left, center_y, context);
        func_080DA598(center_x, top, right, center_y, context);
        func_080DA3B8(left, center_y, center_x, bottom, context);
        func_080DA598(right, center_y, center_x, bottom, context);
    }
}
