/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08019D18.c
 * Original SHA-256: e7c6235b074de9983b4ceded619e88f406eb38c1b898a5d55a6363b1a9b68305
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct __attribute__((packed)) {
    u8 value;
    u8 unknown_01;
} Cell;

typedef struct {
    u32 unknown_00;
    Cell *cells;
    u8 width;
    u8 height;
    u8 min_column;
    u8 min_value;
    u8 min_row;
    u8 occupied_width;
    u8 max_value;
    u8 occupied_height;
} Grid;

typedef struct {
    u8 unknown_00[0xC];
    u16 offset_x;
    u16 offset_y;
    u8 unknown_10[0x10];
    u16 x;
    u16 y;
    u16 target_x;
    u16 target_y;
    u16 aligned_x;
    u16 aligned_y;
} MapState;

extern Grid data_02007F10;
extern Cell data_02007CB0[];
extern MapState g_state_02007F40;

void func_0801B6C8(void);
void func_08020484(void *source);
void func_08020478(void *source);
void func_0802046C(void *source);

/* Complete target: [0x08019D18, 0x08019E84), 364 bytes. */
void func_08019D18(void *first, void *second, void *third, u8 x, u8 y)
{
    u8 max_column = 0;
    u8 max_value = 0;
    u8 max_row = 0;
    u8 min_column = 32;
    u8 min_value = 32;
    u8 min_row = 32;
    s16 row;
    s16 column;
    u32 occupied;
    Cell *cell;
    MapState *state;

    func_0801B6C8();
    func_08020484(first);
    func_08020478(third);
    func_0802046C(second);
    data_02007F10.cells = data_02007CB0;
    data_02007F10.width = 16;
    data_02007F10.height = 16;

    for (row = 0; row < data_02007F10.height; row++) {
        occupied = 0;
        for (column = 0; column < data_02007F10.width; column++) {
            cell = data_02007F10.cells + data_02007F10.width * row + column;
            if (cell->value != 0) {
                occupied = 1;
                if (column > max_column) {
                    max_column = column;
                }
                if (column < min_column) {
                    min_column = column;
                }
                if (cell->value > max_value) {
                    max_value = cell->value;
                }
                if (cell->value < min_value) {
                    min_value = cell->value;
                }
            }
        }
        if (occupied) {
            if (row > max_row) {
                max_row = row;
            }
            if (row < min_row) {
                min_row = row;
            }
        }
    }

    data_02007F10.occupied_width = max_column - min_column + 1;
    data_02007F10.max_value = max_value;
    data_02007F10.occupied_height = max_row - min_row + 1;
    data_02007F10.min_column = min_column;
    data_02007F10.min_value = min_value;
    data_02007F10.min_row = min_row;
    state = &g_state_02007F40;
    state->x = x * 8;
    state->y = y * 8;
    state->aligned_x = (state->target_x - state->offset_x) & ~7;
    state->aligned_y = (state->target_y - state->offset_y) & ~7;
}
