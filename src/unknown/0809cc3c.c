/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809CC3C.c
 * Original SHA-256: b5278b929c5c1a8cbf003cac98b7fa00fdab1548f5691d7775bdc0bb4020e48e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct Unit {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
};

struct Owner {
    struct Unit *unit;
};

struct Context {
    struct Owner *owner;
    u16 x;
    u16 y;
    u8 unknown_08[2];
    s8 dx;
    s8 dy;
};

static inline void set_direction(s8 *dx, s8 *dy, s8 direction)
{
    switch (direction) {
    case 0:
        *dx = 0;
        *dy = 1;
        break;
    case 1:
        *dx = -1;
        *dy = 0;
        break;
    case 2:
        *dx = 0;
        *dy = -1;
        break;
    case 3:
        *dx = 1;
        *dy = 0;
        break;
    default:
        *dx = 0;
        *dy = 0;
        break;
    }
}

void func_0809CC3C(struct Context *context, struct Owner *owner, s8 direction)
{
    set_direction(&context->dx, &context->dy, direction);

    context->owner = owner;
    context->x = (context->dx + owner->unit->x) * 32 + 16;
    context->y = (context->dy + owner->unit->y) * 32 + 16;
    context->dx *= 4;
    context->dy *= 4;
}
