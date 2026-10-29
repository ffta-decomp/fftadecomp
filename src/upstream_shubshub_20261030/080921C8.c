/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080921C8.c
 * Original SHA-256: dc127e72ec8c0d5c22b660a8a771c85d035977ce50270d1f175f6e3b5beb8861
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

typedef struct {
    u8 unknown_00[0x14];
    u32 destination;
} TransferState;

extern RequestNode data_0200F460[2];
extern u8 data_0600C800[];
extern TransferState data_030008B0;
extern void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count);
extern void func_08000B20(RequestNode *entry, u16 first, u32 second, u16 count);

/* 0x080921C8..0x08092210: 72 bytes, 26 instructions. */
void func_080921C8(u32 palette)
{
    func_08000B68(&data_0200F460[0], 0x77777777, (u32)data_0600C800, 8);
    func_08000B20(&data_0200F460[1], (palette << 12) | 0x640,
                  data_030008B0.destination, 0x400);
}
