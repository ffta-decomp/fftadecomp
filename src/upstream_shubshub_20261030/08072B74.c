/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08072B74.c
 * Original SHA-256: 6609071fae2af9cfd4c28d0fde21aa4cda06959308cbf4f78b5f8048c30e5a9c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 flags;
    u8 status;
    u16 item;
    u16 column;
    u16 row;
    u16 x;
    u16 y;
    u8 unknown_0c[8];
} GridSlot;

typedef struct __attribute__((packed, aligned(4))) {
    u8 unknown_000[0x9BA];
    u8 availability[24];
    u8 unknown_9d2[0x1C];
    GridSlot slots[24];
} GridState;

extern GridState *data_03002818;
extern u8 g_state_020020D0[];
extern void func_08072130(int selection, u8 *availability);
extern void func_08071378(void);
extern void func_080725B8(int selection);

/* 0x08072B74..0x08072C78: 260 bytes, 108 instructions. */
void func_08072B74(int preserve_selection)
{
    int i;

    for (i = 0; i < 24; i++) {
        data_03002818->slots[i].flags |= 0xFF;
        data_03002818->availability[i] |= 0xFF;
    }

    for (i = 0; i < 24; i++) {
        int row = i >> 2;
        data_03002818->slots[i].flags = 0xFF;
        data_03002818->slots[i].status = 0;
        data_03002818->slots[i].item = 0xFF;
        data_03002818->slots[i].column = i % 4;
        data_03002818->slots[i].row = row;
        data_03002818->slots[i].x = (i % 4) * 48 + ((row & 1) ? 24 : 48);
        data_03002818->slots[i].y = row * 40 + 8;
    }

    if (preserve_selection == 0) {
        func_08072130(g_state_020020D0[0x14], data_03002818->availability);
        func_08071378();
        func_080725B8(0);
    }
}
