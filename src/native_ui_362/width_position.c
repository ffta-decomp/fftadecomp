typedef unsigned short u16;
typedef unsigned int u32;
extern const unsigned char SceneSpriteTemplate[];
extern u32 MeasureSceneEncodedPairs(void *);
extern void AppendSprite(const void *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
void DrawSceneWidthPositionedSprite(void *context) asm("CoreRegion_0012B504");
void DrawSceneWidthPositionedSprite(void *context)
{
    u32 x = (u16)MeasureSceneEncodedPairs(context);
    AppendSprite(SceneSpriteTemplate,x+92,149,0,0,0,0,0,0,0,0);
}
asm(".set SceneSpriteTemplate,0x0851ba62\n.thumb_set MeasureSceneEncodedPairs,0x0812b185\n.thumb_set AppendSprite,0x08001cf1\n");
