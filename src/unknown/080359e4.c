typedef unsigned char u8;
typedef unsigned int u32;
struct CodeView { u8 unknown[1208]; u8 codes[0]; };
struct ResetView { u8 unknown[1214]; u8 reset[0]; };
extern u8 *gPanelContext asm("PanelContext");
void ConfigurePanel(u32 index,u32 value) asm("CoreRegion_000359E4");
void ConfigurePanel(u32 index,u32 value) {
 register u8 *destination asm("r2")=gPanelContext;
 asm("" : "+r"(destination));
 destination+=204*index;
 destination+=2439;
 asm("" : "+r"(destination));
 {
 register u32 zero asm("r3")=0;
 asm("" : "+r"(zero));
 *destination=zero;
 ((struct CodeView *)gPanelContext)->codes[index]=value;
 ((struct ResetView *)gPanelContext)->reset[index]=zero;
 }

}
asm(".global PanelContext\n.set PanelContext,0x03002810\n");
