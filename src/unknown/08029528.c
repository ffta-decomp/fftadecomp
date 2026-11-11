typedef unsigned short u16;
typedef unsigned int u32;
extern void BeginBattleRequest(u32,u32,void *);
__asm__(".global BeginBattleRequest\n.thumb_set BeginBattleRequest,0x08025689");
void RequestFlaggedBattleAction(u16 code) __asm__("CoreGlobal36_00029528");
void RequestFlaggedBattleAction(u16 code)
{
    BeginBattleRequest((u32)code | 0x4000, 0, 0);
}
