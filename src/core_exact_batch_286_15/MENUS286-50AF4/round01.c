typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u32 GetLastRow(void*) asm("RetailCall_08017be8");
extern void PlayMenuSound(u32) asm("RetailCall_08141540");
extern void RefreshPage(void*) asm("RetailCall_0804f948");
void MoveMenuPage(u8 *context,u8 direction) asm("CoreRegion_00050AF4");
void MoveMenuPage(u8 *context,u8 direction) {
 u8 *request=context+72;
 u8 *view=context+104;
 u16 *destination=(u16 *)(*(u8 **)context+0x53c+4*context[8]);
 int oldtop=*(s16 *)(request+26);
 int top=oldtop;
 int end=(s16)GetLastRow(request)+1;
 int selection=view[17];
 int remaining=context[10];
 while(remaining) {
  remaining--;
  if(direction==128) {
   int page=context[10];
   if(top+page<end)top++;
   else {remaining=0;if(oldtop==end-page)selection=page-1;}
  } else {
   if(top>0)top--;
   else {remaining=0;if(oldtop==0)selection=0;}
  }
 }
 if(oldtop!=top || view[17]!=selection) {
  destination[0]=top;destination[1]=selection;
  PlayMenuSound(109);RefreshPage(context);
 }
}
asm(".global RetailCall_08017be8\n.thumb_set RetailCall_08017be8,0x08017be9\n.global RetailCall_08141540\n.thumb_set RetailCall_08141540,0x08141541\n.global RetailCall_0804f948\n.thumb_set RetailCall_0804f948,0x0804f949\n");
