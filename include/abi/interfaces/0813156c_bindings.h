#include "ffta/unsigned_types.h"
struct EffectQuantityTarget { u8 unknown_00[214]; u16 quantity; };
struct EffectQuantityContext { void *actor; struct EffectQuantityTarget *target; };
