/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0804C97C.c
 * Original SHA-256: d2084ad2ca99cc1bcb60e4fa0224e3925e638e218b9d934dd79ad172f66a6e72
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

/* Complete 0x0804C97C..0x0804C9E2, 102 bytes, 37 instructions.
 * Target: 70b581b0114c206800f072f800252560684605800e4c0f4e211c321cf4f068ff684602300580802189006418211c321cf4f05eff00f048f8b6f7d2ff000600280ad00320b6f7b8ff09e0000040f5010260380003000100010120b6f777ff01b070bc01bc0047
 */
extern u32 data_0201F540;
extern u16 data_03003860[];
extern void func_0804CA6C(u32 bytes);
extern void func_0804CA44(void);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u8 func_0800395C(void);
extern void func_08003934(u8 value);
extern void func_080038C8(u16 value);

void func_0804C97C(void)
{
    u16 first;
    u16 second;

    func_0804CA6C(data_0201F540);
    data_0201F540 = 0;
    first = 0;
    func_0814186C(&first, data_03003860, 0x01000100);
    second = 0;
    func_0814186C(&second, data_03003860 + 0x100, 0x01000100);
    func_0804CA44();
    if (func_0800395C())
        func_08003934(3);
    else
        func_080038C8(1);
}
