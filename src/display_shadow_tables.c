typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void RetailCopyBytes(void *destination, const void *source, u32 length);

#if defined(DISPLAY_TABLE_HIGH_BITS)
#define TABLE_GETTER_NAME GetDisplayShadowHighBitMask
#define TABLE_ADDRESS 0x08149550
#elif defined(DISPLAY_TABLE_LOW_BITS_A)
#define TABLE_GETTER_NAME GetDisplayShadowLowBitMaskA
#define TABLE_ADDRESS 0x08149558
#elif defined(DISPLAY_TABLE_LOW_BITS_B)
#define TABLE_GETTER_NAME GetDisplayShadowLowBitMaskB
#define TABLE_ADDRESS 0x08149558
#else
#error Select one display-shadow table getter
#endif

/* The retail getter copies four masks to the stack before indexing them. */
u16 TABLE_GETTER_NAME(u8 index)
{
    u16 masks[4];
    RetailCopyBytes(masks, (const void *)TABLE_ADDRESS, 8);
    return masks[index];
}
