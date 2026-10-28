typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gSceneContext;
extern u8 gTextScratch[];
extern void LoadMenuIconKind0(void *,u32);
extern void LoadMenuIconKind1(void *,u32);
extern void CopyTiles(const void *,void *,u32);
extern void DrawText(void *,void *,const void *,u32,u32);
void BindMenuRowContent(u32 identifier,u32 row,void *buffer,u8 *definition,void *unused_target,u32 kind,u32 enabled)
{
 u16 content_id=identifier;
 u16 row_index=row;
 u8 content_kind=kind;
 void *scratch=gTextScratch;
 register void *caption asm("r4");
 if(content_kind==0) LoadMenuIconKind0(scratch,content_id);
 else if(content_kind==1) LoadMenuIconKind1(scratch,(u8)content_id);
 CopyTiles(scratch,buffer,64);
 caption=*(void **)(*(u8 **)(definition+24)+20*row_index+8);
 asm("" : "+r" (caption));
 if(enabled!=0)
  DrawText(gSceneContext+0xc4c,(u8 *)buffer+128,caption,0,1);
 else
  DrawText(gSceneContext+0xc4c,(u8 *)buffer+128,caption,1,1);
}
asm(".global gSceneContext\n.set gSceneContext,0x03002810\n.global gTextScratch\n.set gTextScratch,0x02003cb0\n.global LoadMenuIconKind0\n.thumb_set LoadMenuIconKind0,0x080cb981\n.global LoadMenuIconKind1\n.thumb_set LoadMenuIconKind1,0x080cb9b1\n.global CopyTiles\n.thumb_set CopyTiles,0x0814186d\n.global DrawText\n.thumb_set DrawText,0x08015111");
