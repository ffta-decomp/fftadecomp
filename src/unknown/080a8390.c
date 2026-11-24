typedef signed char s8;
void CompareDirectionPair(s8 first, s8 second, s8 *first_output, s8 *second_output) __asm__("RetailCall_080a1d84");
void BattleRuntimeDependency_000A8390(int first, int second, s8 *first_output, s8 *second_output)
{
    CompareDirectionPair((s8)first, (s8)second, first_output, second_output);
}
asm(".global RetailCall_080a1d84\n.thumb_set RetailCall_080a1d84,0x080a1d85\n");
