typedef unsigned char u8;
typedef unsigned int u32;
struct BattleFlagContext { u8 prefix[36]; u32 flags; };
/* These callers bracket their action/continuation work with bit 0x20. */
void SetBattleContextFlag20(struct BattleFlagContext *context, u32 enabled)
{
    if ((u8)enabled != 0)
        context->flags |= 0x20u;
    else
        context->flags &= ~0x20u;
}
