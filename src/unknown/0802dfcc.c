typedef unsigned char u8;
typedef unsigned int u32;
struct PairRequestContext { u8 prefix[1124]; u8 selector; };
extern struct PairRequestContext *PairContext;
__asm__(".global PairContext\n.set PairContext,0x0200F444");
void *CoreFrontier_0002DFCC(void)
{
 u8 old=PairContext->selector++;
 u8 *slot=(u8 *)PairContext+676+old*28;
 PairContext->selector &= 15;
 return slot;
}
