typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
extern u8 *gContext asm("Context");
extern void SetRequestFlag(void *,u32) asm("RetailCall_08017fbc");
extern u32 GetSelection(void *,int) asm("RetailCall_08017b68");
extern void SetRowStyle(void *,int,u32) asm("RetailCall_08017af4");
extern void SetRowPosition(void *,u32) asm("RetailCall_08017fb0");
extern void RefreshRow(u32,int) asm("RetailCall_08037df0");
extern void RefreshRowMode(u32,int,void *) asm("RetailCall_08040b70");
extern void SetRequestMode(void *,u32,u32) asm("RetailCall_08017884");
void UpdateMenuRowMode(u32 slot,u8 flags,u8 rowArgument,u8 mode) asm("CoreRegion_000406D4");
void UpdateMenuRowMode(u32 slot,u8 flags,u8 rowArgument,u8 mode) {
 int row;
 u32 shifted;
 register u32 working asm("r4");
 register void *request asm("r0");
 SetRequestFlag(gContext+0x954+204*slot+172,flags);
 request=gContext+0x954+204*slot+120;
 asm("" : "+r"(request) : "r"(rowArgument));
 working=(u32)rowArgument<<24;
 asm("" : "+r"(working));
 shifted=working;
 row=(int)working>>24;
 GetSelection(request,row);
 if(!mode) {
  SetRowStyle(gContext+0x954+204*slot+120,row,11);
  SetRowPosition(gContext+0x954+204*slot+152,shifted>>24);
  RefreshRow(slot,row);
 } else {
  u8 *root;
  RefreshRowMode(slot,row,gContext+0x954+204*slot+120);
  RefreshRow(slot,row);
  SetRequestMode(gContext+0x954+204*slot+120,flags,1);
  root=gContext;
  SetRowStyle(root+0x954+204*slot+120,(s8)root[204*slot+0x9fd],11);
 }
}
asm(".global Context\n.set Context,0x03002810\n.global RetailCall_08017fbc\n.thumb_set RetailCall_08017fbc,0x8017fbd\n.global RetailCall_08017b68\n.thumb_set RetailCall_08017b68,0x8017b69\n.global RetailCall_08017af4\n.thumb_set RetailCall_08017af4,0x8017af5\n.global RetailCall_08017fb0\n.thumb_set RetailCall_08017fb0,0x8017fb1\n.global RetailCall_08037df0\n.thumb_set RetailCall_08037df0,0x8037df1\n.global RetailCall_08040b70\n.thumb_set RetailCall_08040b70,0x8040b71\n.global RetailCall_08017884\n.thumb_set RetailCall_08017884,0x8017885\n");
