typedef unsigned int u32;
const void **LookupOperationProgramTable(u32 bank, u32 selector) __asm__("Remaining38_00021004");
const void **LookupOperationProgramTable(u32 bank, u32 selector)
{
    register u32 encoded_selector __asm__("r2") = selector;
    register unsigned char **banks __asm__("r1") = (unsigned char **)0x08390e44U;
    unsigned char *base;
    u32 offset;
    /* Defined operands preserve the original table-address load before bank
       scaling, after retaining the full selector in R2. No memory effects. */
    __asm__("" : "+r"(encoded_selector), "+r"(banks));
    base = banks[bank];
    switch ((int)(encoded_selector & 3)) {
    case 1:
    case 2:
        offset = (encoded_selector & ~3U) * 6 + 12;
        break;
    default:
        offset = (encoded_selector & ~3U) * 6;
        break;
    }
    return (const void **)(base + offset);
}
