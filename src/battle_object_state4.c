/* Observed ROM 0x00149368, Thumb 0x08149369, span 28 bytes. */
typedef unsigned char u8;

/* The high bit is excluded before testing the observed state value. */
u8 IsBattleObjectStateFour(u8 *object)
{
    if ((object[0x980] & 0x7f) == 4)
        return 1;
    return 0;
}
