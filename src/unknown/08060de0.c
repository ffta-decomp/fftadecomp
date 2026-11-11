typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *gMenuInteractionContext;
asm(".global gMenuInteractionContext\n.set gMenuInteractionContext,0x0200f44c\n");

u32 ReadMenuInteractionSelector(void) __asm__("CoreFrontier_00060DE0");
u32 ReadMenuInteractionSelector(void)
{
    return gMenuInteractionContext[23];
}
