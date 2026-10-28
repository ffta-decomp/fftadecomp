typedef unsigned char u8;
typedef unsigned int u32;
struct BattleOutcomeContinuationFlags {
    u8 unknown_00[370];
    u8 flag370;
};
/* Selector24 writes this flag before pushing the selector33 continuation. */
u32 MarkBattleContinuationFlag370(struct BattleOutcomeContinuationFlags *record)
{
    record->flag370 = 1;
    return 1;
}
