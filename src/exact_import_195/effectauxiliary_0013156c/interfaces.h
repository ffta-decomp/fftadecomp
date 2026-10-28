typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EffectQuantityTarget { u8 unknown_00[214]; u16 quantity; };
struct EffectQuantityContext { void *actor; struct EffectQuantityTarget *target; };
