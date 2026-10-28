typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gSceneContext;
extern u8 gTextScratch[],gPopupResources[];
extern void *gDisplayControl[];
extern void ConfigurePopup(u32,u32,void *,void *,void *,void *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
extern void CopyTiles(const void *,void *,u32);
extern void DrawPopupResource(const void *,u32,u32,u32,u32,u32,u32);
extern void DrawPopupFrame(const void *,u32,u32,u32,u32,u32,u32);
extern void *GetPanelBuffer(u32,u32,u32,u32);
extern void FillPanelBuffer(u32,void *,u32,u32,u32);
extern void *ResolveTextBuffer(void *,u32,u32);
extern void SubmitPanelText(u32,void *,void *,u32);
void ConfigureTextPopup(u32 rows)
{
 register void *scratch asm("r9")=gTextScratch;
 u32 y;
 u32 child_kind;
 u8 height;
 u16 zero;
 u8 *root;
 void *panel;
 void *header;
 u8 *buffer;
 u8 *resources;
 void *grid;
 void *text;
 register u32 text_attribute asm("r5");
 asm("" : "+r" (scratch));
 child_kind=(*(u8 **)(gSceneContext+4))[11];
 y=1;
 if(child_kind<=80) {
  y=14;
  if(rows==2) y=13;
 }
 root=gSceneContext;
 panel=*(void **)(root+148);
 header=*(void **)(root+144);
 buffer=gDisplayControl[4];
 ConfigurePopup(4,12,panel,header,buffer,buffer+364,0,0,2,y,26,(u8)(2*rows+3),2,y,26,(u8)(2*rows+3),26,(u8)(2*rows+3));
 height=(u8)(2*rows+3);
 zero=0;
 CopyTiles(&zero,(void *)0x06009960,0x01000c00);
 resources=gPopupResources;
 DrawPopupResource(*(void **)(resources+332),resources[344],resources[345],192,resources[344],5,12);
 DrawPopupFrame(*(void **)(resources+328),26,height,192,26,1,12);
 FillPanelBuffer(4,GetPanelBuffer(4,1,1,2),203,24,0xc000);
 if(rows==2) {
  FillPanelBuffer(4,GetPanelBuffer(4,1,1,4),251,24,0xc000);
 }
 text_attribute=0xc03e;
 asm("" : "+r" (text_attribute));
 grid=GetPanelBuffer(4,1,1,1);
 text=ResolveTextBuffer(scratch,62,18);
 SubmitPanelText(text_attribute,grid,text,1);
}
asm(".global gSceneContext\n.set gSceneContext,0x03002810\n.global gTextScratch\n.set gTextScratch,0x02003cb0\n.global gPopupResources\n.set gPopupResources,0x030009e0\n.global gDisplayControl\n.set gDisplayControl,0x03002740\n.global ConfigurePopup\n.thumb_set ConfigurePopup,0x0808a269\n.global CopyTiles\n.thumb_set CopyTiles,0x0814186d\n.global DrawPopupResource\n.thumb_set DrawPopupResource,0x08016345\n.global DrawPopupFrame\n.thumb_set DrawPopupFrame,0x08016561\n.global GetPanelBuffer\n.thumb_set GetPanelBuffer,0x0808b8e5\n.global FillPanelBuffer\n.thumb_set FillPanelBuffer,0x0808b7c1\n.global ResolveTextBuffer\n.thumb_set ResolveTextBuffer,0x08018525\n.global SubmitPanelText\n.thumb_set SubmitPanelText,0x08035679");
