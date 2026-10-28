typedef unsigned char u8;
typedef unsigned int u32;

extern volatile u8 gSaveData[];
extern void UpdateSceneSelectorRecordFields(u32 selector_value);

/* Refresh a record, then store the current selector after the five records. */
void UpdateCurrentSceneSelectorValue(u32 selector_value)
{
    register u32 selector __asm__("r4") = selector_value;
    register volatile u8 *current __asm__("r1");
    register u32 offset __asm__("r0");
    register u32 previous __asm__("r2");
    register u32 mask __asm__("r0");

    /* Keep the original byte truncation after copying the argument to r4. */
    __asm__ volatile ("" : "+r" (selector));
    selector = (u8)selector;
    UpdateSceneSelectorRecordFields(selector);

    current = gSaveData;
    __asm__ volatile ("" : "+r" (current));
    offset = 0x2e54;
    __asm__ volatile ("" : "+r" (offset));
    current += offset;

    selector &= 0x1f;
    previous = *current;
    mask = 32;
    __asm__ volatile ("" : "+r" (mask));
    mask = (u32)-mask;
    __asm__ volatile ("" : "+r" (mask));
    mask &= previous;
    mask |= selector;
    *current = (u8)mask;
}
