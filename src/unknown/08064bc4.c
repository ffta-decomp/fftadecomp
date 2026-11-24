typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
struct SelectorStack {u16 selector,depth;u16 entries[0];};
extern u8 *gContext asm("ContextPtr");
extern u8 gDescriptor[] asm("MenuDescriptor");
extern void UpdateCurrencyPanel(void *,u32,void *,u32,u32,u32) asm("UpdateCurrencyPanel");
void RemainingCore48_00064BC4(void){
 struct SelectorStack *context;u32 depth;
 if (*(u32 *)(gContext+84)&1) UpdateCurrencyPanel(gDescriptor,0,0,20,16,1);
 else UpdateCurrencyPanel(gDescriptor,0,0,20,16,0);
 context=(struct SelectorStack *)gContext;
 depth=context->depth-1;
 context->depth=depth;
 context->selector=context->entries[(u16)depth];
}
asm(".global ContextPtr\n.set ContextPtr,0x0200f450\n.global MenuDescriptor\n.set MenuDescriptor,0x030008b0\n.global UpdateCurrencyPanel\n.thumb_set UpdateCurrencyPanel,0x08029e49\n");
