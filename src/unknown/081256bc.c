typedef unsigned int u32;
extern void UpdateSceneEntityActions(u32 selector);
void UpdateAllSceneEntityActions(void) __asm__("CoreRegion_001256BC");
void UpdateAllSceneEntityActions(void)
{
 UpdateSceneEntityActions(255);
}
asm(".global UpdateSceneEntityActions\n.thumb_set UpdateSceneEntityActions,0x081247B5");
