typedef unsigned char u8;
typedef unsigned int u32;
struct BattleContextByte26View { u8 unknown00[26]; u8 field26; };
u32 ReadBattleContextByte26(const struct BattleContextByte26View *context)
{
    return context->field26;
}
