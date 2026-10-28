/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DBD70.c
 * Original SHA-256: 3ddf9e07240bf2aefc9977df80daf55cbadafeda04ad11c55f94edc2aced3f48
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_0[8];
    u16 first;
    u16 second;
    u16 third;
} ObjectValues;

/* 0x080DBD70: 8 bytes. Set three adjacent halfword fields. */
void func_080DBD70(ObjectValues *object, u16 first, u16 second, u16 third)
{
    object->first = first;
    object->second = second;
    object->third = third;
}
