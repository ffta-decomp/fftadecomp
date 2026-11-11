typedef unsigned char u8;typedef unsigned int u32;
typedef struct { unsigned char visible:1;unsigned char other:7;u8 bytes[5];u8 style; } SceneChild;
extern void ConfigureSceneDisplay(void*,u32,u32,u32,u32,u32,u32,void*,void*,u32);
asm(".global ConfigureSceneDisplay\n.thumb_set ConfigureSceneDisplay,0x0804C599");
void CoreRegion_000358B0(u32 visible) { register u8 **root_cell asm("r3")=(u8**)0x03002810; register u32 zero asm("r2"); register u8 *panel_state asm("r0"); register u8 *display_base asm("r0"); SceneChild *child;
 /* Root-cell address stays in R3 only through its last pre-call reload. */
 asm("" : "+r"(root_cell)); child=*(SceneChild**)(*root_cell+4); child->visible=visible; panel_state=*root_cell+0xF3E; zero=0;
 /* Original R2 zero is shared by stack argument2 and register argument2. */
 asm("" : "+r"(zero), "+r"(panel_state)); *panel_state=6; display_base=(u8*)0x03000E30;
 /* The original loads word4 from the display-context base, not an absolute field address. */
 asm("" : "+r"(display_base)); ConfigureSceneDisplay(*(void**)(display_base+4),0,zero,(*(SceneChild**)(*root_cell+4))->style,240,1,zero,(void*)0x08950258,(void*)0x089511A4,0xFFA6); }
