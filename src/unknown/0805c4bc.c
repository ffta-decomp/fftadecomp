typedef unsigned char u8;
typedef unsigned int u32;
extern u8 *gMenuContext asm("MenuContext");
extern const u8 gFirstA[] asm("FirstA");
extern const u8 gFirstB[] asm("FirstB");
extern const u8 gSecondA[] asm("SecondA");
extern const u8 gSecondB[] asm("SecondB");
extern void ConfigureResourcePair(void *,const void *,const void *,u32,u32) asm("RetailCall_0802b3a8");
void ConfigureSelectorResources(u8 selector,u8 mode) asm("SceneTaskDependency_0005C4BC");
void ConfigureSelectorResources(u8 selector,u8 mode) {
 if(selector<=78)ConfigureResourcePair(gMenuContext+0x33e8,gFirstA,gFirstB,0,mode);
 else ConfigureResourcePair(gMenuContext+0x33e8,gSecondA,gSecondB,0,mode);
}
asm(".global MenuContext\n.set MenuContext,0x0200f428\n.global FirstA\n.set FirstA,0x084229b8\n.global FirstB\n.set FirstB,0x0841ce9c\n.global SecondA\n.set SecondA,0x08422894\n.global SecondB\n.set SecondB,0x0841ce4c\n.global RetailCall_0802b3a8\n.thumb_set RetailCall_0802b3a8,0x0802b3a9\n");
