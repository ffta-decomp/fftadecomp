typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

void *FindBattleActionTargetRow(const u8 *action_record, s32 target_index)
    __asm__("sub_080A8810");

/* Retail accepts equality and uses a signed comparison against the byte count. */
void *FindBattleActionTargetRow(const u8 *action_record, s32 target_index)
{
    u32 row_offset;
    if ((s32)action_record[704] < target_index)
        return 0;
    row_offset = (u32)target_index * 44u;
    row_offset += 32u;
    return (void *)((u32)action_record + row_offset);
}
