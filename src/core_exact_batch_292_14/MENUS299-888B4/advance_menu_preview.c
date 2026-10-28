typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct Context {u8 unknown0[8];void *resource_pool;u8 unknown12[0x434-12];u8 content,palette;s16 x,y;u8 draw_mode,unknown43b,selection,previous_selection;u8 unknown43e[2];void *sprite,*animation,*node;u8 unknown44c[0x1d09-0x44c];u8 marker_flags;};
extern struct Context *gContext;
extern u8 gPreviewContinuation;
extern void *CreateSprite(void *,u32,u32,u32,u32);
extern void FillPalette(const void *,void *,u32);
extern void *GetSpriteAnimation(void *);
extern void SetAnimationMode(void *,u32,u32);
extern void ReleaseAnimationNode(void *,void *);
extern void *StartAnimation(void *,u32,u32,u32,u32,u32,u32);
extern void TickSprite(void *);
extern void FreeSprite(void *);
extern void DrawPreview(void *,int,int,u32,u32,u32,u32,u32,u32,u32);
extern void DrawMarker(const void *,int,int,u32,u32,u32,u32,u32,u32,u32,u32);

void AdvanceMenuPreview(void *task,u8 *state)
{
 switch(*state) {
 case 0: {
  u16 palette_zero;
  gContext->sprite=CreateSprite(gContext->resource_pool,500,540,0,0);
  gContext->selection=0;
  gContext->previous_selection=0;
  palette_zero=0;
  FillPalette(&palette_zero,gContext->node,0x01000002);
  gContext->animation=GetSpriteAnimation(gContext->sprite);
  SetAnimationMode(gContext->animation,0,2);
  if(gContext->node)ReleaseAnimationNode(gContext->animation,gContext->node);
  gContext->node=StartAnimation(gContext->animation,0,0,20,gContext->content,gContext->selection,0);
  *state=252;
  break;
 }
 case 2:
  if(gContext->node)ReleaseAnimationNode(gContext->animation,gContext->node);
  gContext->node=StartAnimation(gContext->animation,0,0,20,gContext->content,gContext->selection,0);
  *state=3;
 case 4:
  {
   int y=gContext->y;
   int draw_y=y-8;
   int x;
   if((u32)(y+24)>192)return;
   x=gContext->x;
   if((u32)(x+16)>240)return;
   DrawPreview(gContext->animation,x+16,draw_y,0,0,0,0,0,gContext->palette,gContext->draw_mode);
   if(gContext->marker_flags&1) {
    if(gContext->marker_flags&4)DrawMarker((void *)0x08393eca,x,y-9,0,0,0,0,0,0,1,0);
    else if(gContext->marker_flags&24)DrawMarker((void *)0x08393ed2,x,y-9,0,0,0,0,0,0,1,0);
   }
  }
  break;
 case 3:
  if(gContext->previous_selection!=gContext->selection) {
   gContext->previous_selection=gContext->selection;
   if(gContext->node)ReleaseAnimationNode(gContext->animation,gContext->node);
   gContext->node=StartAnimation(gContext->animation,0,0,20,gContext->content,gContext->selection,0);
   SetAnimationMode(gContext->animation,0,2);
  }
  TickSprite(gContext->sprite);
  {
   int y=gContext->y;
   int draw_y=y-8;
   int x;
   if((u32)(y+24)>192)return;
   x=gContext->x;
   if((u32)(x+16)>240)return;
   DrawPreview(gContext->animation,x+16,draw_y,0,0,0,0,0,gContext->palette,gContext->draw_mode);
   if(gContext->marker_flags&1) {
    if(gContext->marker_flags&4)DrawMarker((void *)0x08393eca,x,y-9,0,0,0,0,0,0,1,0);
    else if(gContext->marker_flags&24)DrawMarker((void *)0x08393ed2,x,y-9,0,0,0,0,0,0,1,0);
   }
  }
  break;
 case 5:
  TickSprite(gContext->sprite);
  DrawPreview(gContext->animation,24,148,0,0,0,0,0,gContext->palette,2);
  break;
 case 6: {
  int y,x;
  TickSprite(gContext->sprite);
  y=gContext->y+60;
  if((u32)y>160)break;
  x=gContext->x;
  if((u32)x>240)break;
  DrawPreview(gContext->animation,x,y,0,0,0,0,0,gContext->palette,2);
  break;
 }
 case 252:case 255:break;
 case 253:*state=gPreviewContinuation;break;
 case 254:FreeSprite(gContext->sprite);
 case 1:*state=252;break;
 }
}

__asm__(".global CoreRegion_000888B4\n.thumb_set CoreRegion_000888B4, AdvanceMenuPreview\n.global CreateSprite\n.thumb_set CreateSprite,0x8021a3d\n.global FillPalette\n.thumb_set FillPalette,0x814186d\n.global GetSpriteAnimation\n.thumb_set GetSpriteAnimation,0x8021b1d\n.global SetAnimationMode\n.thumb_set SetAnimationMode,0x8021df9\n.global ReleaseAnimationNode\n.thumb_set ReleaseAnimationNode,0x8021bd5\n.global StartAnimation\n.thumb_set StartAnimation,0x8021619\n.global TickSprite\n.thumb_set TickSprite,0x8021e7d\n.global FreeSprite\n.thumb_set FreeSprite,0x8021ad1\n.global DrawPreview\n.thumb_set DrawPreview,0x8021f19\n.global DrawMarker\n.thumb_set DrawMarker,0x8001cf1\n.global gContext\n.set gContext,0x03002818\n.global gPreviewContinuation\n.set gPreviewContinuation,0x0200f292\n");
