typedef unsigned short u16;
typedef struct {
    u16 displayControl;
    volatile u16 layer0;
    volatile u16 layer1;
    volatile u16 layer2;
    volatile u16 layer3;
} RosterDisplayShadow;

/* Fixed native background-layer preset used by the roster lifecycle.
 * Selective volatile fields preserve the original ordered halfword accesses. */
void CoreGlobal36_00089540(void)
{
    RosterDisplayShadow *shadow = (RosterDisplayShadow *)0x03000940;
    shadow->layer0 = 0xAE0B;
    shadow->layer1 = 0xAC0A;
    shadow->layer2 = 0x2B09;
    shadow->layer3 = 0x2A08;
}
