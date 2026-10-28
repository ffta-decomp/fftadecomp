typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

__asm__(".global SceneActionDependency_00005BFC\n.thumb_set SceneActionDependency_00005BFC, 0x08005bfd");
extern u8 *SceneActionDependency_00005BFC(u8 *object);
void RemainingBand43_000DF964(u8 *object, u32 value) __asm__("RemainingBand43_000DF964");

void RemainingBand43_000DF964(u8 *object, u32 value)
{
    u16 narrowed = (u16)value;
    u8 *payload = SceneActionDependency_00005BFC(object);
    *(u16 *)(payload + 20) = narrowed;
}
