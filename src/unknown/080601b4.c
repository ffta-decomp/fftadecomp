typedef unsigned char u8;
typedef unsigned int u32;
typedef struct MenuSelectionOrigin {
    u8 unknown[27];
    u8 row_origin;
} MenuSelectionOrigin;
extern MenuSelectionOrigin *MenuOrigin;
extern u32 ResolveMenuGlyph(u32 index, u8 origin);
u32 ResolveRelativeMenuGlyph(u32 unused, u32 index) __asm__("CoreRegion30_000601B4");
u32 ResolveRelativeMenuGlyph(u32 unused, u32 index)
{
    return ResolveMenuGlyph(index, (u8)(MenuOrigin->row_origin - 2));
}
__asm__(".global MenuOrigin\n.set MenuOrigin,0x0200F44C\n"
        ".global ResolveMenuGlyph\n.thumb_set ResolveMenuGlyph,0x08060155\n");
