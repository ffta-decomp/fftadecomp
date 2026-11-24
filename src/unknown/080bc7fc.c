struct UnitTransition;
unsigned int PollTransition(struct UnitTransition *) __asm__("RetailCall_080baee8");
unsigned char CoreFrontier_000BC7FC(void)
{
    return (unsigned char)PollTransition((struct UnitTransition *)0x020100c8);
}
asm(".global RetailCall_080baee8\n.thumb_set RetailCall_080baee8,0x080baee9\n");
