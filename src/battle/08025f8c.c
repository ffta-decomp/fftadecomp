typedef unsigned char u8;
typedef unsigned int u32;
struct BattleChoiceContext { u8 bytes00[24]; void *unit; };
extern struct BattleChoiceContext *BattleChoice;
extern u32 UnitStateECBit0(void *unit);
extern u32 UnitStateE9HasBit0(void *unit);
extern u32 IsAbilityAvailable(void *unit,u32 ability);
__asm__(".global BattleChoice\n.set BattleChoice,0x0200f438\n.global UnitStateECBit0\n.thumb_set UnitStateECBit0,0x080cdbb5\n.global UnitStateE9HasBit0\n.thumb_set UnitStateE9HasBit0,0x080cd95d\n.global IsAbilityAvailable\n.thumb_set IsAbilityAvailable,0x080cd561");
u32 CanUseBattleChoice(u32 incoming)
{
 register u32 choice __asm__("r5")=(u8)incoming;
 register u32 later_choice __asm__("r6")=choice;
 __asm__("" : "+r"(choice), "+r"(later_choice));
 if ((u8)UnitStateECBit0(BattleChoice->unit)) {
reject:
  return 0;
 }
 if (!(u8)UnitStateE9HasBit0(BattleChoice->unit)) goto accept;
 if (choice==1) goto accept;
 if (later_choice!=21) goto reject;
 return (u8)IsAbilityAvailable(BattleChoice->unit,26);
accept:
 return 1;
}
