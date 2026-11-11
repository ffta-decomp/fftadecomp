typedef unsigned int u32;
extern void ConfigureWindow(u32,u32,u32,u32) asm("ConfigureWindow");
void CoreRegion30_00061188(void){ConfigureWindow(2,2,26,6);}
asm(".global ConfigureWindow\n.thumb_set ConfigureWindow,0x0802a2c1\n");
