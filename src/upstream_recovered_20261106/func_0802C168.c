/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0802C168.c
 * Original SHA-256: 943ac223542470c709e438986b08c91fa9a309b811a147d9c7ef3abe245c2f84
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 first;
    u16 unknown_1A;
    u16 second;
    u8 unknown_1E[0xA];
    u16 flags;
} SourceObject;

typedef struct {
    u16 state;
    u16 unknown_02;
    s16 x, y;
    u32 unknown_08;
    SourceObject *object;
    u16 flags;
    u8 unknown_12[0x316];
    u8 first_digits[0x60];
    u8 second_digits[0x60];
} Owner;

typedef void (*BufferCopier)(void *, const void *, u32);
extern BufferCopier data_0836D4BC[];
extern u16 data_03003BC0[];
extern u16 data_03003BCC;
extern void func_0802C0E0(SourceObject *);
extern void func_0802C034(Owner *);
extern void func_0802BB70(void *, u16, u16);
extern u8 *func_080CBABC(u32);
extern u8 *func_080CBA84(u32);
extern u8 func_080C8240(void *);
extern u8 func_080C8260(const SourceObject *);

/* Complete target: 0802C168..0802C270, 264 bytes. */
void func_0802C168(Owner *owner)
{
    u16 color;
    if (owner->flags & 0x10) {
        func_0802C0E0(owner->object);
        data_0836D4BC[0](data_03003BC0, func_080CBABC(2), 32);
        data_0836D4BC[0](data_03003BC0 + 16, func_080CBABC(1), 32);
    } else {
        func_0802C034(owner);
        func_0802BB70(owner->first_digits, owner->object->first, 0x40);
        func_0802BB70(owner->second_digits, owner->object->second, 0x140);
        data_0836D4BC[0](data_03003BC0, func_080CBABC(2), 64);
        if (owner->flags & 2) {
            if (owner->flags & 4)
                data_0836D4BC[0](data_03003BC0 + 1, func_080CBABC(2) + 2, 6);
            else
                data_0836D4BC[0](data_03003BC0 + 1, func_080CBA84(12) + 8, 6);
        }
    }
    color = ((u16 *)func_080CBA84(12))[7];
    if (func_080C8240(owner->object))
        color = ((u16 *)func_080CBA84(11))[7];
    else if (func_080C8260(owner->object))
        color = ((u16 *)func_080CBA84(9))[7];
    data_03003BCC = color;
}
