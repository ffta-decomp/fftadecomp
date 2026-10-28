typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u16 pc; } ScriptContext;
typedef struct { u8 unknown[0x1f69]; u8 current_selector; } SaveSelectorView;
#define OFFSET(T,F) ((u32)&(((T*)0)->F))
typedef char SelectorOffset[(OFFSET(SaveSelectorView,current_selector)==0x1f69)?1:-1];
extern SaveSelectorView gSaveSelector;
extern u32 ResolveSceneSelector(u32 selector);
__asm__(".set gSaveSelector, 0x02000000");
__asm__(".thumb_set ResolveSceneSelector, 0x08036351");
