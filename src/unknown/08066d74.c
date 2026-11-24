/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08066D74.c
 * Original SHA-256: 44689d15ddffffa81c400dac73a0182e874d94427a60ea093f56f0cf09b45da8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;

struct Context {
    u8 unknown_00[9];
    u8 flags;
    u8 unknown_0A[0xB2];
    void *child;
};

extern void func_08005B40(void *child);

void func_08066D74(struct Context *context)
{
    if (context->child) {
        func_08005B40(context->child);
        context->child = 0;
    }
    context->flags |= 2;
}
