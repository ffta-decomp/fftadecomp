typedef unsigned char u8;

typedef struct NativeShopGlyphDescriptor {
    u8 selected;
    u8 glyphs[6];
    u8 count;
    u8 width;
    u8 height;
    u8 unknown_10[2];
    void *buffer;
    u8 unknown_16[104];
    u8 x;
    u8 y;
} NativeShopGlyphDescriptor;

void SceneTaskDependency_0006EC20(NativeShopGlyphDescriptor *descriptor,
    void *buffer, u8 x, u8 y, u8 width, u8 height)
{
    u8 index;
    descriptor->selected = 0;
    descriptor->buffer = buffer;
    descriptor->x = x;
    descriptor->y = y;
    descriptor->width = width;
    descriptor->height = height;
    descriptor->count = 6;
    for (index = 0; index < 6; index++)
        descriptor->glyphs[index] = ((const u8 *)0x08393B40)[index];
}
