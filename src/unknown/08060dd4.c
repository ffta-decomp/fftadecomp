typedef unsigned char u8;
extern u8 *gMenuOutcomeContext;
__asm__(".global gMenuOutcomeContext\n.set gMenuOutcomeContext,0x0200f44c");
unsigned QueryMenuOutcome(void)
{
    return gMenuOutcomeContext[22];
}
