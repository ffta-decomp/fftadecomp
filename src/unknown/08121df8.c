typedef unsigned char u8;
extern u8 *gSceneRoot;
/* Actual scene task context: caller initializes52B at this address. */
void *CoreRegion_00121DF8(void)
{
 return gSceneRoot+0x8A0;
}
asm(".global gSceneRoot\n.set gSceneRoot,0x020159CC");
