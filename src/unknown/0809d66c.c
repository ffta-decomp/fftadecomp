typedef signed char s8;
void WriteBattleDirectionStep(s8 direction, s8 *x, s8 *y)
    asm("CoreContinuation_0009D66C");
/* The two outputs may alias: preserve X then Y stores. */
void WriteBattleDirectionStep(s8 direction, s8 *x, s8 *y)
{
    switch (direction) {
    case 0: *x = 0; *y = 1; break;
    case 1: *x = -1; *y = 0; break;
    case 2: *x = 0; *y = -1; break;
    case 3: *x = 1; *y = 0; break;
    default: *x = 0; *y = 0; break;
    }
}
