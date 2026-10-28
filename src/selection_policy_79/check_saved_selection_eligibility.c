typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct {u8 unknown0[0x2190];u8 flow;u8 unknown2191[0x2fc1-0x2191];unsigned char unused0:2;unsigned char choice:3;unsigned char unused5:3;u8 unknown2fc2[0x3c2a-0x2fc2];u8 region;} SelectionState;
typedef struct {s16 result;u8 done;u8 unknown3[0x480-3];u8 choices[6];} SelectionMenu;
typedef struct {u16 state;} Task;
typedef struct {u8 unknown0[7];u8 restrict_selection;u8 unknown8[4];} RegionRule;
extern SelectionState GameState __asm__("0x02000000");
extern SelectionMenu *SelectionRuntime __asm__("0x0200f438");
extern RegionRule RegionRules[] __asm__("0x08563a70");
u32 TestGameFlag(u32) __asm__("RetailCall_080c9540");
u32 ReadGameFlag(u32) __asm__("RetailCall_080c95a8");
u32 SelectionRestricted(void) __asm__("RetailCall_08027ae8");
void PrepareBattleContext(void) __asm__("RetailCall_08096d7c");
void *CurrentBattleActor(void) __asm__("RetailCall_08099544");
void PlaySelectionSound(u32,u32) __asm__("RetailCall_08141570");
/* Selection eligibility combines saved choice, game flags, region policy and
 * current battle availability. The exact six option labels remain tentative. */
u32 CheckSavedSelectionEligibility(void *unused,Task *task)
{
 RegionRule *rule;
 u32 rejected;
 switch(task->state) {
 case 0:
  SelectionRuntime->choices[0]=1;
  SelectionRuntime->choices[1]=2;
  SelectionRuntime->choices[2]=3;
  SelectionRuntime->choices[3]=4;
  SelectionRuntime->choices[4]=5;
  SelectionRuntime->choices[5]=6;
  break;
 case 1:
  break;
 case 256:
  SelectionRuntime->result=GameState.choice+1;
  switch(GameState.choice) {
  case 0: case 3:
   break;
  case 2:
   if((u8)TestGameFlag(2)) goto reject;
   if((u8)SelectionRestricted()) goto check;
   goto reject;
  case 4:
   rule=&RegionRules[GameState.region];
   if((u8)TestGameFlag(2)) goto reject;
   PrepareBattleContext();
   if(!CurrentBattleActor()) goto reject;
   if(GameState.flow==2) goto reject;
   rejected=rule->restrict_selection;
   goto final_gate;
  case 5:
   if((u8)ReadGameFlag(13)==1) goto reject;
  case 1:
   /* The shared predicate tests zero; keep only the helper low byte. */
   rejected=TestGameFlag(2)<<24;
  final_gate:
   if(rejected) goto reject;
   break;
  }
  goto check;
 reject:
  SelectionRuntime->result=-1;
 check:
  if(SelectionRuntime->result==-1) PlaySelectionSound(1,107);
  task->state=260;
  break;
 case 260:
  SelectionRuntime->done=1;
  task->state=3;
 }
 return 0;
}
/* Exact existing helper linkage only; these directives emit no instructions. */
asm(".global RetailCall_080c9540\n.thumb_set RetailCall_080c9540,0x080c9541\n.global RetailCall_080c95a8\n.thumb_set RetailCall_080c95a8,0x080c95a9\n.global RetailCall_08027ae8\n.thumb_set RetailCall_08027ae8,0x08027ae9\n.global RetailCall_08141570\n.thumb_set RetailCall_08141570,0x08141571");
typedef char VerifyChoiceOffset[((u32)&((SelectionMenu *)0)->choices==0x480)?1:-1];
typedef char VerifyRegionStride[(sizeof(RegionRule)==12)?1:-1];
typedef char VerifyFlowOffset[((u32)&((SelectionState *)0)->flow==0x2190)?1:-1];
