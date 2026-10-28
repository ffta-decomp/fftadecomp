/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0805FEA8.c
 * Original SHA-256: d9244ec7617263a4863723ecc213bd1952dfeaf503eedab3a467702882a937cf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0A : 6;
} Resource0805FEA8;

typedef union {
    Resource0805FEA8 *resource;
    u8 *item;
} Entry0805FEA8;

typedef struct {
    u8 unknown_00[0x1B];
    u8 count;
    u8 unknown_1C[4];
    Entry0805FEA8 entries[1];
} List0805FEA8;

typedef struct {
    u8 kind;
} Menu0805FEA8;

typedef struct {
    u8 unknown_00[2];
    u8 category;
    u8 unknown_03[13];
} Category0805FEA8;

extern List0805FEA8 *data_0200F44C;
extern const Category0805FEA8 g_table_08521214[];
extern void *func_08005B28(u32 size);
extern void func_08005B40(void *buffer);
extern u32 func_080CE4DC(u16 id, u32 field);
extern void func_080CB9B0(void *buffer, u32 category);
extern void func_080CB980(void *buffer, u32 id);
extern void func_0814186C(const void *source, void *destination, u32 size);

/* 0x0805FEA8..0x0805FFEE: 326 bytes, including literal pools. */
u8 *func_0805FEA8(Menu0805FEA8 *menu, void *output, u16 index)
{
    u8 *destination = output;
    void *buffer;

    switch (menu->kind) {
    case 3:
    case 7:
        {
            Resource0805FEA8 *resource;
            u8 category;

            buffer = func_08005B28(0x80);
            resource = data_0200F44C->entries[index].resource;
            category = func_080CE4DC(resource->id, 2);
            category += 15;
            if (func_080CE4DC(resource->id, 1) == 1)
                category = 6;
            func_080CB9B0(buffer, category);
            func_0814186C(buffer, destination, 0x40);
            func_08005B40(buffer);
            destination += 0x80;
        }
        break;
    case 5:
        if (index < 2) {
            u32 item_index = index - 2;
            u8 *item = data_0200F44C->entries[item_index + data_0200F44C->count].item;

            if (item != 0 && item[0] != 0) {
                u16 id;
                u32 offset;
                const Category0805FEA8 *entry;

                buffer = func_08005B28(0x80);
                offset = item[0] * sizeof(Category0805FEA8);
                entry = (const Category0805FEA8 *)((const u8 *)g_table_08521214 + offset);
                id = entry->category ? 0x18A + entry->category : 0;
                func_080CB980(buffer, id);
                func_0814186C(buffer, destination, 0x40);
                func_08005B40(buffer);
            }
        }
        destination += 0x80;
        break;
    case 6:
        {
            u16 id;
            u32 offset;
            const Category0805FEA8 *entry;

            buffer = func_08005B28(0x80);
            offset = data_0200F44C->entries[index].item[0] * sizeof(Category0805FEA8);
            entry = (const Category0805FEA8 *)((const u8 *)g_table_08521214 + offset);
            id = entry->category ? 0x18A + entry->category : 0;
            func_080CB980(buffer, id);
            func_0814186C(buffer, destination, 0x40);
            func_08005B40(buffer);
            destination += 0x80;
        }
        break;
    }
    return destination;
}
