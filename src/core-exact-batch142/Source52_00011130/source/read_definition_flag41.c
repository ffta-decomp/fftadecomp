typedef unsigned char u8;
typedef unsigned int u32;
u32 ReadDefinitionFlag41(const u8*) __asm__("Source52_00011130");
u32 ReadDefinitionFlag41(const u8 *object)
{
    return object[41];
}
