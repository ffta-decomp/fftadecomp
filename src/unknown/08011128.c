typedef unsigned char u8;
typedef unsigned int u32;
u32 ReadDefinitionFlag40(const u8*) __asm__("Source52_00011128");
u32 ReadDefinitionFlag40(const u8 *object)
{
    return object[40];
}
