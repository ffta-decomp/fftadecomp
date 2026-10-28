typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

struct CoordinateStep {
    u16 x, y, end_x, end_y, step_x, step_y, dx, dy;
    u16 accumulator, half_dy, remaining;
};

struct NativeMenuTransition {
    u8 unknown_00[13];
    u8 half_code;
    u8 unknown_14[54];
    struct CoordinateStep step;
    void *snapshot;
};

extern struct NativeMenuTransition gNativeMenuTransition;
extern u8 gNativePaletteShadow[];
extern void (*const gNativeClearBytes)(u8 *destination, s32 bytes);
extern void CaptureNativeMenuTransitionSnapshot(void);
/* The native caller supplies signed full-word values; the callee stores LOW16. */
extern void InitializeNativeTransitionStep(struct CoordinateStep *step,
                                            s32 x, s32 y,
                                            s32 end_x, s32 end_y);

void ConfigureNativeMenuTransition(u16 code, u8 mode)
{
    gNativeMenuTransition.half_code = code >> 1;
    switch (mode) {
    case 15:
        gNativeClearBytes(gNativePaletteShadow, 1024);
        InitializeNativeTransitionStep(&gNativeMenuTransition.step,
                                         (s16)code, 0, 0, (s16)code);
        break;
    case 16:
        if (gNativeMenuTransition.snapshot == 0) {
            CaptureNativeMenuTransitionSnapshot();
            InitializeNativeTransitionStep(&gNativeMenuTransition.step,
                                             0, 0, (s16)code, (s16)code);
        }
        break;
    }
}

asm(".set gNativeMenuTransition, 0x0200F390\n"
    ".set gNativePaletteShadow, 0x03003860\n"
    ".set gNativeClearBytes, 0x0836D4B8\n"
    ".thumb_set CaptureNativeMenuTransitionSnapshot, 0x08022E25\n"
    ".thumb_set InitializeNativeTransitionStep, 0x08007621\n"
    ".thumb_set _call_via_r2, 0x0814224D\n"
    ".thumb_set _call_via_r3, 0x08142251\n");
