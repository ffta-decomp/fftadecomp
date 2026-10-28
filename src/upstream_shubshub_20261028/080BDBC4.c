/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BDBC4.c
 * Original SHA-256: af692e218bc1d1739b209f3893e7844a77d6f5c8095f53a456c57454f60502a5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080BDBC4..0x080BDC20: 92 bytes. */
typedef struct Node {
    u8 unknown_00;
    u8 type;
    u8 unknown_02[2];
    struct Node *next;
} Node;

typedef struct {
    Node *cells[16][16];
    u8 blocked[16][16];
} Grid;

void func_080BDBC4(Grid *grid, void *object, u8 x, u8 y)
{
    Node *node = object;
    Node *head;

    if (node->type <= 3) {
        if ((grid->blocked[y][x] >> node->type) & 1)
            return;
    }

    head = grid->cells[y][x];
    if (head == (Node *)-1)
        return;
    if (head == 0) {
        grid->cells[y][x] = node;
    } else {
        while (head->next != 0)
            head = head->next;
        head->next = node;
    }
}
