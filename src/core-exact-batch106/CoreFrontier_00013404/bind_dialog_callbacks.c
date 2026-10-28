typedef unsigned int u32;
typedef unsigned char u8;
extern u8 *DialogCell;
__asm__(".global DialogCell\n.set DialogCell,0x0200918C");
void CoreFrontier_00013404(u32 first,u32 second)
{
 u8 *context=DialogCell;
 *(u32 *)(context+1868)=first;
 *(u32 *)(context+1872)=second;
}
