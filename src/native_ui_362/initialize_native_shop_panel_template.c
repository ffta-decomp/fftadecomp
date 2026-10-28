typedef unsigned short u16;
struct NativeShopPanelTemplate {
    u16 header[3];
    u16 tiles[80];
};
extern const u16 gNativeShopPanelTemplate[80];
__asm__(".global gNativeShopPanelTemplate\n.set gNativeShopPanelTemplate,0x083AF62C\n");
void InitializeNativeShopPanelTemplate(struct NativeShopPanelTemplate *panel)
    __asm__("SceneTaskDependency_0006F028");
void InitializeNativeShopPanelTemplate(struct NativeShopPanelTemplate *panel)
{
    const u16 *source = gNativeShopPanelTemplate;
    u16 index;
    for (index = 0; index < 80; ++index)
        panel->tiles[index] = source[index] + 192;
}
