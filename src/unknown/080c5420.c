typedef unsigned char u8;
typedef unsigned int u32;
struct BattleContextControlView { u8 unknown00[28]; u8 control28, control29; };

/* The two control-byte meanings remain tentative; preserve write order. */
void SetBattleContextControlBytes(struct BattleContextControlView *context, u32 first, u32 second)
{
    context->control28 = first;
    context->control29 = second;
}
