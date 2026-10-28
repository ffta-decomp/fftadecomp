typedef unsigned char u8;
typedef unsigned int u32;
void SetNativeMenuControlParameter79C(u8 *,u32) __asm__("SceneTaskDependency_0002B590");
void SetNativeMenuControlParameter79C(u8 *control,u32 raw_value)
{
    control[0x79C] = raw_value;
}
