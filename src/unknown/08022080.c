typedef unsigned int u32;
/* Keep the two observed scaled contributions; their object split is unproved. */
u32 ComputeBattleRecordPoolBytes(u32 entry_count)
{
    u32 primary_bytes = entry_count * 72;
    u32 auxiliary_bytes = entry_count * 32;
    return auxiliary_bytes + primary_bytes + 1000;
}
