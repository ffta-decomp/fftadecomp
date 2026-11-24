typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
extern u8 *gSceneContext;
extern int ResolveMenuSelection(void *,int);
void PublishMenuSelection(u32 slot,u32 selection)
{
 u8 **cell=&gSceneContext;
 u32 stride=204*slot;
 int resolved=ResolveMenuSelection((u8 *)(stride+(u32)*cell+0x9cc),(s8)selection);
 *(u8 *)((u32)*cell+stride+0x98a)=resolved;
}
asm(".global gSceneContext\n.set gSceneContext,0x03002810\n.global ResolveMenuSelection\n.thumb_set ResolveMenuSelection,0x08017b69");
