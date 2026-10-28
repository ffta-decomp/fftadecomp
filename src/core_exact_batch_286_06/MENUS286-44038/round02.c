typedef unsigned char u8;
struct Actor { u8 active:1; u8 reset:1; u8 unknown:6; u8 padding[48]; u8 low:4; u8 high:4; u8 tail[2]; };
struct Context {u8 unknown[1976];struct Actor actors[6];};
extern struct Context *gPanelContext asm("PanelContext");
void ResetActorControl(void) asm("CoreRegion_00044038");
void ResetActorControl(void) { int i; for(i=0;i<=5;i++) { if(gPanelContext->actors[i].active) { gPanelContext->actors[i].reset=0; gPanelContext->actors[i].low=0; gPanelContext->actors[i].high=1; } } }
asm(".global PanelContext\n.set PanelContext,0x03002810\n");
