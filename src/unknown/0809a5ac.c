/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809A5AC.c
 * Original SHA-256: b280d0c17dfbef856fdf206b507f1fc2eb04350bff063ab8acd41c3f09ad01a7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct Context {
    u8 unknown_00[0x40];
    void *object;
};

extern void func_08021DF8(void *object, u16 first, u16 second);

void func_0809A5AC(struct Context *context, u16 first, u16 second)
{
    func_08021DF8(context->object, first, second);
}
