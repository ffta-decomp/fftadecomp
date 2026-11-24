extern void DestroyNativeMenuPanelTask(void *) asm("destroy");
void ReleaseNativeMenuPanel(unsigned char *) asm("CoreRegion30_0005FD04");
void ReleaseNativeMenuPanel(unsigned char *panel)
{
    register unsigned char *root asm("r2");
    register unsigned char *entries asm("r1");
    unsigned char *flags;
    unsigned offset;
    register unsigned final_index asm("r4");
    DestroyNativeMenuPanelTask(*(void **)(panel + 148));
    root = *(unsigned char **)0x0200F44C;
    asm("" : "+r"(root));
    offset = 4 * panel[6];
    entries = root + 8;
    asm("" : "+r"(entries) : "r"(offset));
    *(unsigned *)(entries + offset) = 0;
    flags = root + 16;
    asm("" : "+r"(flags));
    /* Native rereads the index after the possibly aliasing registry store. */
    final_index = panel[6];
    asm("" : "+r"(final_index));
    flags[final_index] = 1;
}
__asm__(".thumb_set destroy,0x08005b41");
