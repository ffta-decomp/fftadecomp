typedef unsigned char u8;
struct BattleContextPairView { u8 unknown00[24]; u8 field24, field25; };

/* Keep the second source read after the first OUT store, including aliases. */
void ReadBattleContextBytePair(const struct BattleContextPairView *context, u8 *first, u8 *second)
{
    *first = context->field24;
    *second = context->field25;
}
