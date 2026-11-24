typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
extern const u8 SceneBackground[];
extern const u8 SceneMarker[];
extern const u8 SceneMarkerPositions[];
extern void SpriteActive(const void *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void SpriteBank(const void *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void RenderEncodedSprites(u8 *,u32,u32);
void RenderSceneTextAndMarker(u8 *context) asm("CoreRegion_0012A52C");
void RenderSceneTextAndMarker(u8 *context)
{
    SpriteActive(SceneBackground,80,128,0,0,0,0,0,0,0,0);
    RenderEncodedSprites(context,92,136);
    SpriteBank(*(void **)(context+664),240,154,0,0,1,0,0,576,0,0);
    SpriteActive(SceneMarker,SceneMarkerPositions[*(s8 *)(context+758)],8,0,0,0,0,0,0,0,0);
}
asm(".set SceneBackground,0x083a8298\n.set SceneMarker,0x083a82ec\n.set SceneMarkerPositions,0x083a8295\n.thumb_set SpriteActive,0x08001f35\n.thumb_set SpriteBank,0x08001cf1\n.thumb_set RenderEncodedSprites,0x0812addd\n");
