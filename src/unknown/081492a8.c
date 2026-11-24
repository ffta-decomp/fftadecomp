/* Observed ROM 0x001492a8, Thumb 0x081492a9, span 40 bytes. */
typedef unsigned char u8;

/* Clears the observed low-seven-bit state and two transient object bytes. */
void ClearBattleObjectTransientState(u8 *object)
{
    u8 state = object[0x980];
    int high_bit_mask = -128;

    high_bit_mask &= state;
    object[0x980] = high_bit_mask;
    object[0x984] = 0;
    object[0x985] = 0;
}
