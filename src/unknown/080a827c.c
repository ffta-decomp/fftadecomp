typedef unsigned char u8;
typedef unsigned int u32;
struct BattleDirectionParameter { u8 preceding[16]; u8 value; };
extern struct BattleDirectionParameter BattleDirectionParameter;
void StoreBattleDirectionParameter(u32 value)
{
    BattleDirectionParameter.value = value;
}
asm(".set BattleDirectionParameter,0x0200f8a8\n");
