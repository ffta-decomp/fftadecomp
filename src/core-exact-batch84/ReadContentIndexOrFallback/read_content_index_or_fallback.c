typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ContentIndexView {
    u8 unknown_00[160];
    u16 fallback_index;
    u16 preferred_index;
};
extern struct ContentIndexView gContentIndices;
asm(".global gContentIndices\n.set gContentIndices,0x020020d0");

u32 ReadContentIndexOrFallback(void)
{
    u32 index = gContentIndices.preferred_index;
    if (index == 0)
        index = gContentIndices.fallback_index;
    return index;
}
