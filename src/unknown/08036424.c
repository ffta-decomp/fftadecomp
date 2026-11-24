typedef unsigned char u8;
typedef unsigned int u32;

extern u32 GetSceneSelectorValueByIndex(u32 one_based_index);
extern u32 TestSceneSelectorState(u32 selector_value, u32 selector_mode);

/* Resolve an indexed selector before testing it against the requested mode. */
u32 ResolveSceneSelectorState(u32 one_based_index, u32 selector_mode)
{
    /* Both call boundaries use one-byte selectors in the retail routine. */
    u32 selector_value = GetSceneSelectorValueByIndex((u8)one_based_index);

    return TestSceneSelectorState((u8)selector_value, selector_mode);
}
