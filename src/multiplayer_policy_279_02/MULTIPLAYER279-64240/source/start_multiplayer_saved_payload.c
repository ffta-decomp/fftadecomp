typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *gChoiceContext;
extern u8 gSavedExchangePayload[];
extern void RequestPolicyMode(u16);
extern void InitializePayloadPlan(void *,const void *,u16,u8);
__asm__(".global gChoiceContext\n.set gChoiceContext,0x0200f450\n.global gSavedExchangePayload\n.set gSavedExchangePayload,0x02003c34\n.global RequestPolicyMode\n.thumb_set RequestPolicyMode,0x080c71b5\n.global InitializePayloadPlan\n.thumb_set InitializePayloadPlan,0x080c73c5");
void StartMultiplayerSavedPayload(void)
{
    u8 *state;
    void *plan;
    u8 mode;
    register const void *payload __asm__("r1");
    RequestPolicyMode(1);
    state=gChoiceContext;
    plan=state+108;
    payload=gSavedExchangePayload;
    __asm__("" : "+r"(payload));
    mode=0;
    if (*(u32 *)(state+88)==0) mode=1;
    InitializePayloadPlan(plan,payload,8,mode);
    *(u16 *)gChoiceContext=45;
}
