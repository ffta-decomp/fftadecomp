typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleHandleContext { u8 prefix[68]; const u16 *primary; };
extern u16 GetBattleTargetHandleLowWord(const u16 *);
u32 CoreConsumer_00099C9C(struct BattleHandleContext *context)
{
    u32 flags = GetBattleTargetHandleLowWord(context->primary) & 0x100;
    if (flags != 0)
        return 1;
    return 0;
}
asm(".global GetBattleTargetHandleLowWord\n.thumb_set GetBattleTargetHandleLowWord,0x08021DE1\n");
