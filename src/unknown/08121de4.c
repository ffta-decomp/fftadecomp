typedef unsigned char u8;
typedef unsigned int u32;
struct SceneRoot { u8 unknown000[0x89C]; u32 field_89c; };
extern struct SceneRoot *gSceneRoot;
/* Full scene-root field forwarded by the opcode5A controller; identity unknown. */
u32 CoreRegion_00121DE4(void)
{
 return gSceneRoot->field_89c;
}
asm(".global gSceneRoot\n.set gSceneRoot,0x020159CC");
