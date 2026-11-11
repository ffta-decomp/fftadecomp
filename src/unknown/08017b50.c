#include "ffta/unsigned_types.h"
typedef signed short s16;
u32 sub_08017B50(u8 *object)
{ int count=*(s16 *)(object+24); int visible=object[22]; if(visible>count) visible=count; return (u16)visible; }
