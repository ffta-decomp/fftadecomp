typedef unsigned char u8;typedef unsigned int u32;
extern u32 RefreshAvailability(void*) asm("RetailCall_080504bc");
extern void DrawSelected(void*,u32) asm("RetailCall_080505bc");
void RefreshChangedSelection(u8 *menu) asm("CoreRegion_00050E54");
void RefreshChangedSelection(u8 *menu) {if((u8)RefreshAvailability(menu))DrawSelected(menu,menu[121]);}
asm(".global RetailCall_080504bc\n.thumb_set RetailCall_080504bc,0x080504bd\n.global RetailCall_080505bc\n.thumb_set RetailCall_080505bc,0x080505bd\n");
