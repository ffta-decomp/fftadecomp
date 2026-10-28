typedef unsigned short u16;
typedef signed short s16;
extern int ReadRandomValue(void);
asm(".global ReadRandomValue\n.thumb_set ReadRandomValue,0x08002805\n.global __modsi3\n.thumb_set __modsi3,0x08142951");

/* Signed RNG remainders are preserved before each unsigned halfword wrap. */
unsigned RollBattleProbability(u16 probability)
{
    if (probability == 0)
        return 0;
    if (probability <= 99) {
        probability *= 100;
        probability += (s16)ReadRandomValue() % 100;
        if (probability < (u16)((s16)ReadRandomValue() % 10000 + 1))
            return 0;
    }
    return 1;
}
