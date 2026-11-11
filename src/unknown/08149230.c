typedef unsigned char u8;

/* Store the five observed auxiliary bytes in the active battle object.
 * The field roles are still unknown; their offsets and byte widths are exact.
 */
void SetBattleObjectAuxiliaryBytes(u8 *object, u8 value81, u8 value82,
                                   u8 value83, u8 value86, u8 value87)
{
    object[0x981] = value81;
    object[0x982] = value82;
    object[0x983] = value83;
    object[0x986] = value86;
    object[0x987] = value87;
}
