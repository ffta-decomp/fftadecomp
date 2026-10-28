/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DE188.c
 * Original SHA-256: 717c0c2099ba2ae07d7e21a201e43d265a02b6ca1639a5697aff9755a5cc02d2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 unknown_0[0x1F];
    s8 value;
    u8 unknown_20[0x10];
    u32 flags;
} Object;

extern Object *func_080DD350(Object *object);
extern void func_0809836C(Object *object, u16 command, int value, u16 duration);
extern void func_080DE12C(Object *object, u16 command, int value);

/* 0x080DE188: 104 bytes. Dispatch an object update using command control bits. */
void func_080DE188(Object *object, u16 command, u16 duration, u8 value)
{
    if (!(command & 0x4000))
        object->flags |= 2;
    else
        command &= 0xBFFF;

    if (command & 0x8000) {
        command &= 0x7FFF;
        func_0809836C(object, command, (s8)value, duration);
    } else {
        Object *state = func_080DD350(object);

        func_080DE12C(object, command, state->value);
    }
}
