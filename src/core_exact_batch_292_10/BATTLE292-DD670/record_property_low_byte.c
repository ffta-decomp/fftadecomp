typedef unsigned char u8;typedef unsigned int u32;
extern u32 property(void*,u8);
u32 RemainingBand43_000DD670(void *record,u8 selector)
{
 return (u8)property(record,selector);
}
__asm__(".global property\n.thumb_set property,0x080a883d");
