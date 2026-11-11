typedef unsigned char u8;
typedef unsigned long u32;
struct ChoiceTableView { u8 observed_prefix[0x1248]; void *entries[0]; };
extern u8 *gMenuSelectionContext;
__asm__(".global gMenuSelectionContext\n.set gMenuSelectionContext,0x0200f448");
extern void ResetPanel(unsigned,unsigned,unsigned,unsigned);
extern void SetupChoice(unsigned,unsigned);
extern void ShowChoice(unsigned);
extern void SetChoiceRows(void *,unsigned);
extern void StepChoice(unsigned,unsigned);
extern unsigned QueryChoice(unsigned);
extern void ApplyChoice(void *);
extern void FinishChoice(void);
__asm__(".global ResetPanel\n.thumb_set ResetPanel,0x0802a2c1\n.global SetupChoice\n.thumb_set SetupChoice,0x08060ded\n.global ShowChoice\n.thumb_set ShowChoice,0x0805f44d\n.global SetChoiceRows\n.thumb_set SetChoiceRows,0x0805f541\n.global StepChoice\n.thumb_set StepChoice,0x0805f4d9\n.global QueryChoice\n.thumb_set QueryChoice,0x08060e0d\n.global ApplyChoice\n.thumb_set ApplyChoice,0x080613d1\n.global FinishChoice\n.thumb_set FinishChoice,0x0805f4ad");
void StepMenuChoice(void) {
 if (gMenuSelectionContext[0x119c] == 0) {
  ResetPanel(0,0,30,10);
  SetupChoice(5,2);
  ShowChoice(5);
  SetChoiceRows(gMenuSelectionContext+0x1248,gMenuSelectionContext[0x11aa]+2);
  gMenuSelectionContext[0x119c]=1;
  gMenuSelectionContext[0x119a]=9;
  gMenuSelectionContext[0x1199]=1;
 } else {
  unsigned choice;
  StepChoice(5,0);
  choice=(u8)QueryChoice(5);
  if (choice != 2) {
   unsigned index=gMenuSelectionContext[0x11aa]+choice;
   void *value;
   __asm__("" : "+r"(index));
   value=((struct ChoiceTableView *)gMenuSelectionContext)->entries[index];
   if(value) ApplyChoice(value);
  }
  gMenuSelectionContext[0x119c]=0;
  gMenuSelectionContext[0x119a]=10;
  gMenuSelectionContext[0x1199]=1;
  FinishChoice();
 }
}
