typedef unsigned char u8;
typedef signed short s16;
extern int ReadTargetDefense(void *target, int category);
extern int ReadRandomValue(void);
asm(".global ReadTargetDefense\n.thumb_set ReadTargetDefense,0x0812f705\n.global ReadRandomValue\n.thumb_set ReadRandomValue,0x08002805");
asm(".global __divsi3\n.thumb_set __divsi3,0x081426b9\n.global __modsi3\n.thumb_set __modsi3,0x08142951");
/* The helper return is signed; the original halves with an arithmetic shift. */
int CoreContinuation_0013010C(int baseAmount, void *target, u8 suppressVariation)
{
    int adjustedAmount = baseAmount - (ReadTargetDefense(target, 1) >> 1);
    if (suppressVariation == 0) {
        int spread = adjustedAmount / 10;
        if (spread < 0)
            spread = -spread;
        adjustedAmount += (s16)ReadRandomValue() % (spread * 2 + 1) - spread;
    }
    return adjustedAmount;
}
