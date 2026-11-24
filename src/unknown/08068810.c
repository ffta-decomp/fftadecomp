/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08068810.c
 * Original SHA-256: fbc056e2bdb326bda4dd4a3f433586876276f4c660c22f7c17c883c4cedde438
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;

struct Context {
    u8 unknown_00[0x10];
    void *resources;
};

int func_08068810(struct Context *context)
{
    return context->resources != 0;
}
