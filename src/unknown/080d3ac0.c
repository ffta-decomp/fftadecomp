/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D3AC0.c
 * Original SHA-256: 568b34101429cd1f95b44d207fc6e645f22abecafb66ce58c473feecf5129a83
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[2];
    u16 flags;
} State;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* 0x080D3AC0..0x080D3AF6: 54 bytes. */
void func_080D3AC0(u8 enabled)
{
    State *state = func_08005BFC(data_020159C0);

    if (enabled)
        state->flags &= 0xFFEF;
    else
        state->flags |= 0x10;
}
