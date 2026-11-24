typedef unsigned char u8;
struct NativeShopIndicatorControl;
extern void SetNativeShopIndicatorTags(struct NativeShopIndicatorControl *,u8,u8);
extern void BindNativeShopIndicatorResource(struct NativeShopIndicatorControl *,u8 *,u8);
__asm__(".global SetNativeShopIndicatorTags\n.thumb_set SetNativeShopIndicatorTags,0x08016E1D\n"
        ".global BindNativeShopIndicatorResource\n.thumb_set BindNativeShopIndicatorResource,0x08016E4D\n");
void ConfigureNativeShopIndicators(struct NativeShopIndicatorControl *,u8 *,u8,u8)
    __asm__("SceneTaskDependency_0002B368");
void ConfigureNativeShopIndicators(struct NativeShopIndicatorControl *control,
                                   u8 *data,u8 first_tag,u8 second_tag)
{
    SetNativeShopIndicatorTags(control,first_tag,second_tag);
    if (first_tag != 0)
        BindNativeShopIndicatorResource(control,data,1);
    if (second_tag != 0)
        BindNativeShopIndicatorResource(control,data + 192,0);
}
