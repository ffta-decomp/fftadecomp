typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u8 unknown[246];u8 x,y;} Unit;
typedef struct {void *unknown;void *reference;} ReferenceNode;
typedef struct {void *actor;void *previous;Unit *affected;u8 unknown12[26];u16 flags;} EffectContext;
void *CurrentRuntime(void) __asm__("RetailCall_08096d7c");
ReferenceNode *FindNode(void*,void*) __asm__("RetailCall_08099560");
u32 ProducePoint(void*,void*,void*,void*,u8*,u8*) __asm__("EffectApplicationCall_08098E7C");
