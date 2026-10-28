typedef unsigned char u8;
typedef unsigned int u32;
struct ChildFlags { u8 mode:1; u8 preserved:7; };
struct SceneContext { void *records; u8 *child; };
extern struct SceneContext *gSceneContext;
extern u32 gControlRoot[];
extern const u8 gPanelResourceA[],gPanelResourceB[];
extern void ConfigurePanel(u32,u32,u32,u32,u32,u32,u32,const void *,const void *,u32);
void ConfigureScenePanel(u32 mode) {
 u8 *child=gSceneContext->child;
 u32 zero;
 u8 *clear;
 ((struct ChildFlags *)child)->mode=mode;
 clear=(u8 *)gSceneContext+0xf3e;
 asm("" : "+r" (clear));
 zero=0;
 *clear=zero;
 ConfigurePanel(gControlRoot[1],0,zero,gSceneContext->child[6],240,zero,10,gPanelResourceA,gPanelResourceB,0xffa6);
}
asm(".global gSceneContext\n.set gSceneContext,0x03002810\n.global gControlRoot\n.set gControlRoot,0x03000e30\n.global gPanelResourceA\n.set gPanelResourceA,0x08950258\n.global gPanelResourceB\n.set gPanelResourceB,0x089511a4\n.global ConfigurePanel\n.thumb_set ConfigurePanel,0x0804c4d5");
