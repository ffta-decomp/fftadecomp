typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *PairContext;
extern u32 TransferBankB[];
extern u8 MarkerData[];
extern void *Call_0802DFCC(void);
extern u32 Call_080161A0(u32,u32,u32);
extern void Call_08000BAC(void *,u32,u32,u16,u16,u16,u16);
__asm__(".global PairContext\n.set PairContext,0x0200F444\n.global TransferBankB\n.set TransferBankB,0x03000990\n.global MarkerData\n.set MarkerData,0x083C4AA8\n.global Call_0802DFCC\n.thumb_set Call_0802DFCC,0x0802DFCD\n.global Call_080161A0\n.thumb_set Call_080161A0,0x080161A1\n.global Call_08000BAC\n.thumb_set Call_08000BAC,0x08000BAD");
void CoreFrontier_0002E008(void)
{
 void *request;
 u8 *context;
 u32 offset;
 u32 target;
 {
  register u8 *state __asm__("r0")=PairContext;
  register u32 count __asm__("r1")=state[8];
  register u32 zero __asm__("r2");
  __asm__("" : "+r"(state), "+r"(count));
  state +=1125;
  __asm__("" : "+r"(state), "+r"(count));
  zero=0;
  __asm__("" : "+r"(zero), "+r"(state), "+r"(count));
  *state=count;
  state=PairContext+1126;
  *state=zero;
 }
 request=Call_0802DFCC();
 context=PairContext;
 offset=Call_080161A0(context[0],context[2],32);
 target=TransferBankB[5]+(u16)offset*2;
 Call_08000BAC(request,(u32)MarkerData,target,26,2,52,64);
}
