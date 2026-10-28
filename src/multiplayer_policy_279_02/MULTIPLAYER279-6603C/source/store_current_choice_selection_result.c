typedef unsigned int u32;
struct ChoiceSelectionOwner { u32 preceding[4]; u32 selection_result; };
extern struct ChoiceSelectionOwner *gChoiceSelectionOwner;
asm(".global gChoiceSelectionOwner\n.set gChoiceSelectionOwner,0x0200f454\n");
void StoreCurrentChoiceSelectionResult(u32 value) asm("RemainingCore48_0006603C");
/* Real62834 forwards full65060 result here: keep both tag bits/pointer bits. */
void StoreCurrentChoiceSelectionResult(u32 value)
{
    gChoiceSelectionOwner->selection_result = value;
}
