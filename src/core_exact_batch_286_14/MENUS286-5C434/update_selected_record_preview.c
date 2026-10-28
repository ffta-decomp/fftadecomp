typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u8 *gMenuContext;
extern u8 gRecordData[];
extern void UpdateRecordCard(void *);
extern unsigned ReadRecordCardStatus(void *);
extern void *AdvancePreviewAnimation(void *);
extern void SubmitPreview(const void *,u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
void UpdateSelectedRecordPreview(u32 x,u32 y)
{
 u16 horizontal=x;
 u16 vertical=y;
 UpdateRecordCard(gMenuContext+0x1bc0);
 if((u8)ReadRecordCardStatus(gMenuContext+0x1bc0)==1) {
  register u8 *records asm("r1")=gRecordData;
  u8 *root;
  asm("" : "+r" (records));
  root=gMenuContext;
  if(*(u32 *)(16*(u32)root[0x1bb6]+(u32)records+0x2e78)!=0) {
   void *frame=AdvancePreviewAnimation(root+0x33e8);
   SubmitPreview(frame,(s16)horizontal,(s16)vertical,0,0,0,0,0,800,0,0);
  }
 }
}
asm(".global gMenuContext\n.set gMenuContext,0x0200f428\n.global gRecordData\n.set gRecordData,0x02000000\n.global UpdateRecordCard\n.thumb_set UpdateRecordCard,0x0802995d\n.global ReadRecordCardStatus\n.thumb_set ReadRecordCardStatus,0x08029d2d\n.global AdvancePreviewAnimation\n.thumb_set AdvancePreviewAnimation,0x0802b3d5\n.global SubmitPreview\n.thumb_set SubmitPreview,0x08001cf1");
