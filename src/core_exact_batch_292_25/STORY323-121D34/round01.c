typedef unsigned char u8;
typedef unsigned int u32;
struct SceneRoot { u8 unknown00[16]; u32 saved_runtime_control; };
extern struct SceneRoot *gSceneRoot;
/* The initializer snapshots a byte here, but this ABI returns the full word. */
u32 CoreRegion_00121D34(void)
{
 return gSceneRoot->saved_runtime_control;
}
asm(".global gSceneRoot\n.set gSceneRoot,0x020159CC");
