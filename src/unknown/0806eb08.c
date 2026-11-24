typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *gMenuContext asm("MenuContext");
extern const u8 gCueAsset[] asm("CueAsset");
extern void DrawActionPair(const u8 *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_08001f34");
void DrawOptionalMenuCue(void) asm("SceneTaskDependency_0006EB08");
void DrawOptionalMenuCue(void) {
 if(gMenuContext[0x4bf9])DrawActionPair(gCueAsset,216,0,0,0,0,0,0,0,0,0);
}
asm(".global MenuContext\n.set MenuContext,0x0200f428\n.global CueAsset\n.set CueAsset,0x08393b00\n.global RetailCall_08001f34\n.thumb_set RetailCall_08001f34,0x08001f35\n");
