typedef unsigned char u8;
struct PairSelection { u8 prefix[1125]; u8 choice; u8 saved_choice; };
extern struct PairSelection *PairSelectionCell;
__asm__(".global PairSelectionCell\n.set PairSelectionCell,0x0200F444");
void CoreFrontier_0002E070(void)
{
 struct PairSelection *state=PairSelectionCell;
 state->saved_choice=state->choice;
}
