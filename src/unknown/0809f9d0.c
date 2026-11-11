typedef unsigned char u8;
typedef unsigned int u32;
struct BattleRecordTarget {
    u8 prefix[40];
    u32 word_40;
};
struct BattleRecordLink { struct BattleRecordTarget *target; };
/* Completion clears this target word; its broader object meaning is unknown. */
u32 ClearBattleRecordTargetWord40(struct BattleRecordLink *record)
{
    record->target->word_40 = 0;
    return 0;
}
