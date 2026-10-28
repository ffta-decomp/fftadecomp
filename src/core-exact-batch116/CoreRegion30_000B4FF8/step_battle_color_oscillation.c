typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct BattleColorOscillation {
    u8 unknown_00[71];
    u8 channel_directions[14];
};
extern u16 BattleColorShadow[];

void StepBattleColorOscillation(struct BattleColorOscillation *state, u32 bank)
{
    u16 *color = BattleColorShadow + bank * 16;
    int entry = 2;
    register u32 red_direction_mask asm("r8") = 1;
    u8 *direction;

    /* Native R8 holds the initialized red-direction bit across the loop. */
    asm("" : "+r" (red_direction_mask));
    direction = state->channel_directions;

    /* Native counter2..15 updates fourteen colors starting at bank offset0. */
    do {
        u16 red = *color & 31;
        u16 green = (*color & 992) >> 5;
        u16 blue = (*color & 31744) >> 10;
        /* Keep the initialized forward counter visible to loop optimization. */
        asm("" : "+r" (entry));

        if ((*direction & 1) != 0) {
            red++;
            if (red > 31) {
                red = 30;
                *direction &= 254;
            }
        } else if (red <= 15) {
            red++;
            *direction |= red_direction_mask;
        } else {
            red--;
        }
        if ((*direction & 2) != 0) {
            green++;
            if (green > 31) {
                green = 30;
                *direction &= 253;
            }
        } else if (green <= 15) {
            green++;
            *direction |= 2;
        } else {
            green--;
        }
        if ((*direction & 4) != 0) {
            blue++;
            if (blue > 31) {
                blue = 30;
                *direction &= 251;
            }
        } else if (blue <= 15) {
            blue++;
            *direction |= 4;
        } else {
            blue--;
        }
        *color = red | (green << 5) | (blue << 10);
        direction++;
        entry++;
        color++;
    } while (entry <= 15);
}

asm(".global BattleColorShadow\n.set BattleColorShadow, 0x03003a64\n");
