/* Contributed by gg; original source and attribution follow. */
/* Embedded42_00A398A8
   entry 0x08A398A8, 6 bytes, restored from the US retail ROM (AFXE).
   Self-contained: headers inlined. Address-named targets (f_XXXXXXXX)
   are bound by symbols/aliases.s. */
typedef unsigned char u8;
typedef unsigned int u32;
struct BattleContextControlView { u8 unknown00[20]; u8 control28, control29; };

/* The two control-byte meanings remain tentative; preserve write order. */
void SetBattleContextControlBytes(struct BattleContextControlView *context, u32 first, u32 second)
{
    context->control28 = first;
    context->control29 = second;
}
