typedef unsigned char u8;
typedef unsigned int u32;
void SetNativeMenuControlParameter79A(u8 *,u32) __asm__("SceneTaskDependency_0002B554");
void SetNativeMenuControlParameter79A(u8 *control,u32 raw_value)
{
    control[0x79A] = raw_value;
}
