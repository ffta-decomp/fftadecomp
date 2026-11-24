typedef unsigned char u8;
void ClearBattleTreeVisitFlag(void)
{
    register u8 *state_base __asm__("r0") = (u8 *)0x0200f9e8;
    /* Original loads the base and offset separately; retain this defined address role. */
    __asm__("" : "+r" (state_base));
    state_base += 0x5dc;
    *state_base = 0;
}
