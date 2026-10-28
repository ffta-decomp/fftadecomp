typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct RowIndicator {u16 x;u16 y;u8 *asset;};
extern u8 *PairContext;
extern u8 StyleEnabledAsset[];
extern u8 StyleDisabledAsset[];
__asm__(".global PairContext\n.set PairContext,0x0200F444\n.global StyleEnabledAsset\n.set StyleEnabledAsset,0x0839176A\n.global StyleDisabledAsset\n.set StyleDisabledAsset,0x08391772");
void CoreFrontier_0002E08C(u32 incoming_row,u32 input_style)
{
 register u32 row __asm__("r4")=incoming_row;
 register u32 predicate __asm__("r1")=input_style<<24;
 struct RowIndicator *indicator;
 u8 *context;
 __asm__("" : "+r"(row), "+r"(predicate));
 indicator=(struct RowIndicator *)(PairContext+1148+row*8);
 if(predicate) indicator->asset=StyleEnabledAsset;
 else indicator->asset=StyleDisabledAsset;
 context=PairContext;
 indicator->x=(*(u16 *)context-1)*8+2;
 indicator->y=((row+1)*2+*(u16 *)(context+2))*8;
 __asm__ __volatile__("" : : "r"(row));
}
