typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct {u8 prefix[17];s8 index;} IndexView;
extern u16 gInput[] asm("Input");
extern u8 *gOwner asm("Owner");
extern void AcknowledgeInput(void *) asm("RetailCall_080023d0");
extern u32 GetSelection(void *,int) asm("RetailCall_08017b68");
extern u32 GetEnd(void *) asm("RetailCall_08017be8");
extern u32 GetCount(void *) asm("RetailCall_08017b50");
extern void SetRowStyle(void *,int,u32) asm("RetailCall_08017af4");
extern u32 CanWrap(void *,u32) asm("RetailCall_08017a90");
extern void FastStep(void *,u32) asm("RetailCall_0805f774");
extern void Step(void *,u32,int,u32) asm("RetailCall_0805f708");
extern void Sound(u32) asm("RetailCall_08141540");
u32 UpdateRepeatSelection(u8 *object) asm("CoreRegion30_0005FA4C");
u32 UpdateRepeatSelection(u8 *object) {
 void *data=object+60;
 IndexView *view=(IndexView *)(object+92);
 u16 repeat=gInput[2];
 u16 held=gInput[0];
 if(repeat&128) {
  int index;
  int next;
  u16 current;
  AcknowledgeInput(gInput);
  if(held&512) {FastStep(object,128);return 1;}
  index=view->index;
  current=GetSelection(data,index);
  if(current<(s16)GetEnd(data))SetRowStyle(data,index,255);
  next=(s8)(index+1);
  if(next<(u16)GetCount(data)) {
   if((s8)object[1]>1)Sound(109);
   Step(object,128,next,0);
   return 1;
  }
  if((u8)CanWrap(data,128)) {
   Sound(109);Step(object,128,next,1);gOwner[22]=5;return 2;
  }
 } else if(repeat&64) {
  int index;
  int next;
  AcknowledgeInput(gInput);
  if(held&512) {FastStep(object,64);return 1;}
  index=view->index;
  if((u16)GetSelection(data,index))SetRowStyle(data,index,255);
  next=(s8)(index-1);
  if(next>=0) {
   if((s8)object[1]>1)Sound(109);
   Step(object,64,next,0);
   return 1;
  }
  if((u8)CanWrap(data,64)) {
   Sound(109);Step(object,64,next,1);gOwner[22]=5;return 2;
  }
 }
 return 0;
}
asm(".global Input\n.set Input,0x03000000\n.global Owner\n.set Owner,0x0200f44c\n.global RetailCall_080023d0\n.thumb_set RetailCall_080023d0,0x80023d1\n.global RetailCall_08017b68\n.thumb_set RetailCall_08017b68,0x8017b69\n.global RetailCall_08017be8\n.thumb_set RetailCall_08017be8,0x8017be9\n.global RetailCall_08017b50\n.thumb_set RetailCall_08017b50,0x8017b51\n.global RetailCall_08017af4\n.thumb_set RetailCall_08017af4,0x8017af5\n.global RetailCall_08017a90\n.thumb_set RetailCall_08017a90,0x8017a91\n.global RetailCall_0805f774\n.thumb_set RetailCall_0805f774,0x805f775\n.global RetailCall_0805f708\n.thumb_set RetailCall_0805f708,0x805f709\n.global RetailCall_08141540\n.thumb_set RetailCall_08141540,0x8141541\n");
