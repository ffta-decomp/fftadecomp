typedef unsigned short u16;
typedef unsigned int u32;
extern void RunTaskGroup(void *group, u32 count) __asm__("0x080069f4");

/* Advance this native menu group before observing its current state. */
u32 CoreRegion_0004C9E4(void)
{
    RunTaskGroup((void *)0x03002710, 5);
    return **(u16 **)0x0201F540;
}
