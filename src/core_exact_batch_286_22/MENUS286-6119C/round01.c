typedef unsigned int u32;
extern void ConfigureWindow(u32,u32,u32,u32) asm("ConfigureWindow");
void CoreRegion30_0006119C(void){ConfigureWindow(0,0,0,0);}
asm(".global ConfigureWindow\n.thumb_set ConfigureWindow,0x0802a2c1\n");
