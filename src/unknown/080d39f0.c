/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D39F0.c
 * Original SHA-256: 6b54ce4ebf9c3d7c8dcf8ff473d730e9b9efd8349cdd8dca35cd254d9530d25e
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

/* 0x080D39F0..0x080D3A12: 34 bytes. */
u8 func_080D39F0(void)
{
    State *state = func_08005BFC(data_020159C0);

    if (state->flags & 0x20)
        return 1;
    return 0;
}
