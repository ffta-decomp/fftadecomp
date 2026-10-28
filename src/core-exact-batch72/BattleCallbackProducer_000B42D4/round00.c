typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
/* The consumer uses the low halfword; the original leaf sign-extends it. */
s32 ReadBattleRecordFallbackSignedValue(const void *record)
{
    return *(const s16 *)((const u8 *)record + 0x153e);
}
