typedef unsigned char u8;typedef unsigned int u32;
extern u32 AdvancePanel(void*) asm("AdvancePanel");
u8 CoreRegion30_000603F4(u8 *context){return (u8)AdvancePanel(context+16);}
asm(".global AdvancePanel\n.thumb_set AdvancePanel,0x08017181\n");
