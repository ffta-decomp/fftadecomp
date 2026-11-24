typedef unsigned char u8;

/* Clear the observed high state bit at object offset 0x980. */
void ClearBattleObjectStateFlag(u8 *object)
{
    object[0x980] &= 0x7f;
}
