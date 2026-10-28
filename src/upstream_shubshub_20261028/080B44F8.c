/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080B44F8.c
 * Original SHA-256: b633b0a7e43a4719898c23314519f8a642454799c6389d5f1606d5297ab8c1fc
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct Tile {
    u8 x;
    u8 y;
    u8 value;
    u8 unknown_03;
};

extern int func_080C92F0(void *owner, int option);
extern int func_080B7C94(u16 first, u16 second, int enabled);
extern u8 func_0801CC18(u8 x, u8 y);
extern int func_080A0254(void *owner, u8 start_x, u8 start_y,
    u8 x, u8 y, u16 first, u16 second, int flags);

int func_080B44F8(void *owner, int unused_first, int unused_second,
    s8 x, s8 y, u16 first, u16 second, struct Tile *tiles)
{
    int budget;
    int remaining;
    int step_x;
    int radius;
    int count;
    int distance;

    if (owner != 0 && (func_080C92F0(owner, 40) & 4))
        budget = 1;
    else
        budget = func_080B7C94(first, second, 1);
    remaining = (u8)budget;

    if (remaining == 1) {
        tiles->x = x;
        tiles->y = y;
        tiles->value = func_0801CC18(x, y);
        return 1;
    }

    radius = 0;
    switch (remaining) {
    case 4:
    case 5:
        radius = 1;
        break;
    case 12:
    case 13:
        radius = 2;
        break;
    }

    count = 0;
    for (distance = !(remaining & 1); distance <= radius; distance++) {
        int current_x = (s8)x - distance;
        int current_y = (s8)y;
        int step_y;

        step_x = 1;
        step_y = -1;

        while (remaining > 0) {
            if (func_080A0254(owner, x, y, current_x, current_y, first, second, 0)) {
                tiles->x = current_x;
                tiles->value = func_0801CC18(current_x, current_y);
                tiles->y = current_y;
                tiles++;
                count++;
            }

            remaining--;
            if ((s8)x == current_x && (s8)y == current_y)
                break;

            current_x += step_x;
            current_y += step_y;
            if (current_x == (s8)x) {
                step_y = -step_y;
                if (step_x == 1 && step_y == -1)
                    break;
            }
            if (current_y == (s8)y) {
                step_x = -step_x;
                if (step_x == 1 && step_y == -1)
                    break;
            }
        }
    }

    return count;
}
