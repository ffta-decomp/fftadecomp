typedef unsigned char u8;
typedef unsigned int u32;
extern void SetupText(u32,u32,u32,void*,void*,int,u32,u32,u32,u32) asm("RetailCall_0801174c");
extern u32 GetText(u32) asm("RetailCall_080c83cc");
extern void SetText(u32,u32) asm("RetailCall_080132b8");
extern void SetWindow(u8,u8,u8,u8) asm("RetailCall_0802a2c0");
extern void SetMode(u32) asm("RetailCall_0801339c");
void InitializeKindHeader(u32 text,u8 kind) asm("CoreFrontier_00061028");
void InitializeKindHeader(u32 text,u8 kind) {
 SetupText(text,4,kind,(void*)0x030008b0,(void*)0x03000990,-1,0,22,6,256);
 SetText(GetText(53),1);SetWindow(0,0,30,10);
 switch(kind) {case 64:case 67:case 68:case 76:case 82:case 83:case 85:case 86:SetMode(2);break;}
}
asm(".global RetailCall_0801174c\n.thumb_set RetailCall_0801174c,0x0801174d\n");
asm(".global RetailCall_080c83cc\n.thumb_set RetailCall_080c83cc,0x080c83cd\n");
asm(".global RetailCall_080132b8\n.thumb_set RetailCall_080132b8,0x080132b9\n");
asm(".global RetailCall_0802a2c0\n.thumb_set RetailCall_0802a2c0,0x0802a2c1\n");
asm(".global RetailCall_0801339c\n.thumb_set RetailCall_0801339c,0x0801339d\n");
