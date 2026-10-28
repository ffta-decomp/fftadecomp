typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SceneResources { u8 before20[20]; void *resource20; void *resource24; };
struct RenderBuffers { u8 before8[8]; u16 *buffer8; };
struct AuthoredChannels { u8 before180[180]; u16 *buffer180; u8 before204[20]; u8 mode204; u8 row205; };
extern struct SceneResources *gSceneResources;
extern struct RenderBuffers gRenderBuffers;
extern struct AuthoredChannels gAuthoredChannels;
extern const u16 gAuthoredTiles[];
extern void ConfigureAuthoredChannel(u32,u8,void *,void *,u16 *,u16 *,void *,void *,u8,u8,u8,u8,u8,u8,u8,u8,u8,u8);
extern void CopyAuthoredTileContent(const u16 *,u16 *,u32,u16);
extern u16 *GetAuthoredTilePointer(u32,u32,u32,u32);
extern void FillAuthoredTileRegion(u16 *,u16,u16,u16,u16,u16,u32);
__asm__(".global gSceneResources\n.set gSceneResources,0x03002818\n.global gRenderBuffers\n.set gRenderBuffers,0x03002740\n.global gAuthoredChannels\n.set gAuthoredChannels,0x030009E0\n.global gAuthoredTiles\n.set gAuthoredTiles,0x0894F95C");
__asm__(".global ConfigureAuthoredChannel\n.thumb_set ConfigureAuthoredChannel,0x0808A269\n.global CopyAuthoredTileContent\n.thumb_set CopyAuthoredTileContent,0x08035579\n.global GetAuthoredTilePointer\n.thumb_set GetAuthoredTilePointer,0x0808B8E5\n.global FillAuthoredTileRegion\n.thumb_set FillAuthoredTileRegion,0x08089F99");
void InitializeAuthoredSceneChannelTwo(void) __asm__("CoreRegion_0008BA08");

/* Authored channel-two layout; keep the existing entry and helper interfaces. */
void InitializeAuthoredSceneChannelTwo(void)
{
    void *resource24 = gSceneResources->resource24;
    void *resource20 = gSceneResources->resource20;
    u16 *buffer = gRenderBuffers.buffer8;
    ConfigureAuthoredChannel(2,12,resource24,resource20,buffer,buffer+224,0,0,
                             1,11,28,8,1,11,28,8,28,8);
    gAuthoredChannels.mode204 = 1;
    gAuthoredChannels.row205 = 11;
    CopyAuthoredTileContent(gAuthoredTiles,gAuthoredChannels.buffer180,224,254);
    FillAuthoredTileRegion(GetAuthoredTilePointer(2,0,0,0),1,28,14,8,0xc000,0);
    FillAuthoredTileRegion(GetAuthoredTilePointer(2,0,14,0),1,28,14,3,0xb000,0);
}
