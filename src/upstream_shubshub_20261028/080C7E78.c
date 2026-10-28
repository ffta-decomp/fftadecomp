/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C7E78.c
 * Original SHA-256: 73ab3a8b8724db1bf1c19e30eeec8b32e1d5b926bc0b01da702d9e5fb246d448
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned int u32;

struct Object {
    u8 unknown_00[0x14];
    u32 flags;
};

/* Target: 080C7E78..080C7E94, 28 bytes. */
int func_080C7E78(struct Object *object, struct Object **result)
{
    if (object->flags & 1)
        return 1;
    *result = object;
    return 0;
}
