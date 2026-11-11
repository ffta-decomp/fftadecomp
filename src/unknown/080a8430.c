typedef signed short s16; typedef unsigned short u16;
struct Triplet {s16 x,y,z;};
int PairAngle(s16,s16) __asm__("RetailCall_08141860");
int BattleStateDependency_000A8430(struct Triplet *first, struct Triplet *second)
{
    int dx = first->x - second->x;
    int dz;
    register int value __asm__("r1");
    register int angle __asm__("r1");
    int raw_angle;
    register int masked __asm__("r0");
    register int dividend __asm__("r0");
    if (dx < 0) dx = -dx;
    dz = first->z - second->z;
    if (dz < 0) dz = -dz;
    {
        int second_y = second->y;
        int first_y = first->y;
        /* Original snapshots separate signed Y operands before adding the
         * absolute horizontal deltas, then subtracts them for the call. */
        asm("" : "+r" (second_y), "+r" (first_y));
        raw_angle = (u16)PairAngle((s16)(dx+dz), (s16)(second_y-first_y));
    }
    angle = raw_angle >> 8;
    asm("" : "+r" (angle));
    angle -= 64;
    asm("" : "+r" (angle));
    masked = 255 & ~angle;
    asm("" : "+r" (masked));
    value = masked;
    value -= 15;
    if (value < 0) value=0;
    if (value >126) value=127;
    /* The original retains the fully defined clamped value in r1 until
     * the signed division moves it into return register r0. */
    asm("" : "+r" (value));
    dividend = value;
    asm("" : "+r" (dividend));
    return dividend/16;
}
asm(".global RetailCall_08141860\n.thumb_set RetailCall_08141860,0x08141861\n");
