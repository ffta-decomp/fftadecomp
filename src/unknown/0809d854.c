typedef unsigned char u8;
typedef unsigned int u32;
extern void ChooseLateralStep(u8 direction, void *node, u32 magnitude)
    __asm__("RetailCall_0809c6b8");

void CoreFrontier_0009D854(u8 *node, u32 direction, u32 magnitude)
{
    node[28] = 0;
    ChooseLateralStep((u8)direction, node, magnitude);
}
