/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08009414.c
 * Original SHA-256: 11916c712cad4e9f82465d0e52a9452dbeec8784f04897705aea8496b5a9ccf8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0x10];
    u8 *buffer;
} Display08009414;

typedef struct {
    u16 unknown_00;
    u16 row;
    u8 unknown_04[0x14];
    Display08009414 *display;
    u8 unknown_1C[8];
    u8 renderer[0x33C];
    u8 descriptor[0x80];
    u8 scratch[0x2E8];
    u8 work[0xB00];
} State08009414;

extern State08009414 *data_02009188;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern const u8 g_table_084E8FD4[];

extern u16 func_08013E9C(u8 *destination, const u8 *table, u8 *workspace,
                       u16 index, u8 *status, u8 *mode);
extern void func_080154D8(void *renderer, void *destination,
                         const u8 *descriptor, u8 width,
                         u8 first, u8 second, u32 style,
                         const void *source, u16 flags);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete [0x08009414, 0x080094BC): 168 bytes, 73 instructions. */
void func_08009414(u8 index)
{
    State08009414 **current = &data_02009188;
    u8 *destination = (*current)->display->buffer + (*current)->row * 32 + 0x2680;
    u8 *descriptor;
    u8 *scratch;

    g_callbacks_0836D4B8[0]((*current)->work, 0xB00);
    descriptor = (*current)->descriptor;
    scratch = (*current)->scratch;
    func_08013E9C(descriptor, g_table_084E8FD4, scratch, index, 0, 0);
    func_080154D8((*current)->renderer, (*current)->work, descriptor, 22,
                   0, 0, 0, 0, 0);
    func_0814186C((*current)->work, destination, 0x580);
}
