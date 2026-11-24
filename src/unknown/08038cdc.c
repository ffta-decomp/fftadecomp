typedef unsigned char u8;
typedef unsigned int u32;
extern const u8 SceneSelectorCategoryTable[];
u32 GetOriginalSceneSelectorCategory(u32 selector) asm("Remaining38_00038CDC");
u32 GetOriginalSceneSelectorCategory(u32 selector)
{
    register u32 shifted_selector asm("r0") = selector << 24;
    asm("" : "+r"(shifted_selector));
    return SceneSelectorCategoryTable[(shifted_selector >> 22) - 4];
}
asm(".set SceneSelectorCategoryTable,0x08391ca4\n");
