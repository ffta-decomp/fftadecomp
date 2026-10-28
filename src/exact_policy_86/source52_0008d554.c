/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct InventoryContext {
    u8 unknown00[0xc1d]; u8 category;
    u8 unknownc1e[0x3e]; u16 category_counts[6];
};
typedef char CategoryOffset[(u32)&((struct InventoryContext*)0)->category==0xc1d?1:-1];
typedef char CountOffset[(u32)&((struct InventoryContext*)0)->category_counts==0xc5c?1:-1];
extern struct InventoryContext *gInventoryContext;
/* The existing ASM sound helper consumes low16 of the caller's full register. */
extern void PlayInventoryNavigationSound(u32);
__asm__(".global gInventoryContext\n.set gInventoryContext,0x03002818");
__asm__(".global PlayInventoryNavigationSound\n.thumb_set PlayInventoryNavigationSound,0x08141541");

u32 SelectNextAvailableInventoryCategory(void);
u32 SelectNextAvailableInventoryCategory(void)
{
    u8 previous_category = gInventoryContext->category;
    do {
        if (gInventoryContext->category <= 4)
            gInventoryContext->category++;
        else
            gInventoryContext->category = 0;
    } while (!gInventoryContext->category_counts[gInventoryContext->category]);
    if (previous_category != gInventoryContext->category)
        PlayInventoryNavigationSound(101);
    return gInventoryContext->category;
}
