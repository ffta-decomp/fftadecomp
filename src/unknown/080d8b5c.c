/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D8B5C.c
 * Original SHA-256: 6928a0f303d51d4d3e85f62cc06147396a06959713cad7a1053f77d664b3f0e1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;

typedef struct {
    u8 unknown_0[0xA];
    s8 x;
    s8 y;
} Position;

extern Position *func_080A880C(void *object);

/* 0x080D8B5C: 30 bytes. Read the object's signed byte coordinates. */
void func_080D8B5C(void *object, s16 *x, s16 *y)
{
    Position *position = func_080A880C(object);

    *x = position->x;
    *y = position->y;
}
