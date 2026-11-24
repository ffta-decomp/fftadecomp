typedef unsigned char u8;
typedef unsigned int u32;
extern u8 gSave[];
extern void *GetPanelBuffer(u32,u32,u32,u32);
extern void DrawPanelNumber(void *,u32,u32,u32);
extern void RefreshPanel(u32,u32);
void RefreshCurrencyPanel(void) {
 u8 *save=gSave;
 u32 currency;
 void *buffer;
 asm("" : "+r" (save));
 currency=*(u32 *)(save+0x1f64);
 buffer=GetPanelBuffer(2,1,1,1);
 DrawPanelNumber(buffer,8,currency,0xd000);
 RefreshPanel(2,2);
}
asm(".global gSave\n.set gSave,0x02000000\n.global GetPanelBuffer\n.thumb_set GetPanelBuffer,0x0808b8e5\n.global DrawPanelNumber\n.thumb_set DrawPanelNumber,0x08035bd5\n.global RefreshPanel\n.thumb_set RefreshPanel,0x0808a605");
