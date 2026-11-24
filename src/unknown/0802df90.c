typedef unsigned char u8;
typedef unsigned int u32;
struct EffectCounterInput {
    u8 unknown_000[258];
    u8 weighted;
    u8 added;
};
u32 ClassifyEffectCounterTotal(const struct EffectCounterInput *input)
{
    register const u8 *added __asm__("r1") = &input->added;
    u8 total;
    __asm__("" : "+r"(added));
    total = input->weighted * 2 + *added;
    if (total <= 2)
        return 0;
    if (total <= 6)
        return 1;
    if (total <= 11)
        return 2;
    {
        register u32 tier __asm__("r0") = 3;
        __asm__("" : "+r"(tier));
        return tier;
    }
}
