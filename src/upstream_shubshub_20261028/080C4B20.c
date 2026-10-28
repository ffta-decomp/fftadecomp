/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C4B20.c
 * Original SHA-256: 57082e23e7f94c7b9a0f911a30e05d6228ae83f04d3e676ba9b2a7e63af31d1e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

struct Unit {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
};

struct Actor {
    struct Unit *unit;
    u8 unknown_04[0x38];
    void *map;
};

struct Grid;
struct Entry;

struct Context {
    struct Actor *actor;
    struct Actor *target;
    u8 unknown_08[0xC];
    struct Grid *grid;
    u8 destination_x;
    u8 destination_y;
    u8 direction;
    u8 flags;
    u8 unknown_1C;
    u8 height_limit;
    u8 unknown_1E[2];
    u16 stage;
};

extern int abs(int value);
extern u16 func_08002804(void);
extern int func_08099FB0(struct Actor *actor, int x, int y);
extern struct Entry *func_080BDB2C(struct Grid *grid);
extern int func_080BDB6C(struct Entry *entry);
extern void func_080BDB74(struct Entry *entry, s16 value);
extern void func_080BDBAC(struct Grid *grid);
extern void func_080BDBC4(struct Grid *grid, struct Entry *entry, u8 x, u8 y);
extern struct Entry *func_080BDC20(struct Grid *grid, u8 x, u8 y);
extern void func_080BDC44(struct Grid *grid, u8 x, u8 y);
extern u8 func_080C4964(struct Context *context, u8 x, u8 y);
extern int func_080C4A40(struct Context *context, u8 x, u8 y);
extern int func_081493AC(void *map, u8 x, u8 y);

/* Target: 080C4B20..080C4E78, 856 bytes. */
int func_080C4B20(struct Context *context)
{
    switch (context->stage) {
    case 0: {
        s8 x, y;
        int found = 0;
        func_080BDBAC(context->grid);
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                if (func_08099FB0(context->actor, x, y)) {
                    s16 distance = abs(context->target->unit->x - x)
                                 + abs(context->target->unit->y - y);
                    struct Entry *entry = func_080BDB2C(context->grid);
                    func_080BDB74(entry, distance);
                    func_080BDBC4(context->grid, entry, x, y);
                    found = 1;
                }
            }
        }
        if (!found) {
            context->destination_x = context->actor->unit->x;
            context->destination_y = context->actor->unit->y;
            goto finish;
        }
        context->stage = 1;
        break;
    }
    case 1: {
        s8 x, y;
        s8 best_height = -1;
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                if (func_080BDC20(context->grid, x, y)) {
                    s8 height = func_081493AC(context->actor->map, x, y);
                    if (context->height_limit >= height && best_height < height)
                        best_height = height;
                }
            }
        }
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                if (func_080BDC20(context->grid, x, y)
                    && best_height != (s8)func_081493AC(context->actor->map, x, y))
                    func_080BDC44(context->grid, x, y);
            }
        }
        context->stage = 2;
        break;
    }
    case 2: {
        s8 x, y;
        s16 nearest = 0x100;
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                struct Entry *entry = func_080BDC20(context->grid, x, y);
                if (entry) {
                    s16 distance = func_080BDB6C(entry);
                    if (distance < nearest)
                        nearest = distance;
                }
            }
        }
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                struct Entry *entry = func_080BDC20(context->grid, x, y);
                if (entry && (s16)func_080BDB6C(entry) != nearest)
                    func_080BDC44(context->grid, x, y);
            }
        }
        context->stage = 3;
        break;
    }
    case 3: {
        s8 x, y;
        struct Entry *entry;
        s16 best_cost = 0x100;
        s8 chosen_x, chosen_y;
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                entry = func_080BDC20(context->grid, x, y);
                if (entry) {
                    s16 cost = func_080C4A40(context, x, y);
                    if (cost < best_cost)
                        best_cost = cost;
                    func_080BDB74(entry, cost);
                }
            }
        }
        chosen_x = -1;
        chosen_y = -1;
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                entry = func_080BDC20(context->grid, x, y);
                if (entry && (s16)func_080BDB6C(entry) == best_cost) {
                    if (chosen_x < 0 || (func_08002804() % 2)) {
                        chosen_x = x;
                        chosen_y = y;
                    }
                }
            }
        }
        context->destination_x = chosen_x;
        context->destination_y = chosen_y;
finish:
        context->direction = func_080C4964(context, context->destination_x,
                                          context->destination_y);
        context->flags |= 2;
        return 0;
    }
    }
    return 1;
}
