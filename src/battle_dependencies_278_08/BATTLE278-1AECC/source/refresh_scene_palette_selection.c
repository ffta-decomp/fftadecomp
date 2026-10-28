typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern void ReadSceneSelectionPair(u8 *,u8 *);
extern void ApplyScenePaletteBank(s16,const u8 *);
extern u32 ReadSceneSelectionIndex(s16);
extern void ApplySceneSelectionIndex(u16);
extern u8 gScenePaletteBuffer[];
__asm__(".global ReadSceneSelectionPair\n.thumb_set ReadSceneSelectionPair,0x0801e6d5\n.global ApplyScenePaletteBank\n.thumb_set ApplyScenePaletteBank,0x0801a42d\n.global ReadSceneSelectionIndex\n.thumb_set ReadSceneSelectionIndex,0x0801db99\n.global ApplySceneSelectionIndex\n.thumb_set ApplySceneSelectionIndex,0x0801dc25\n.global gScenePaletteBuffer\n.set gScenePaletteBuffer,0x03003860");
void RefreshScenePaletteSelection(void)
{
    u8 selection[2];
    ReadSceneSelectionPair(&selection[0],&selection[1]);
    ApplyScenePaletteBank(-1,gScenePaletteBuffer+((u32)selection[0]<<5));
    ApplySceneSelectionIndex((u8)ReadSceneSelectionIndex(-1));
}
