typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct BattleActionWorkFlags {
    u8 preceding_fields[38];
    u16 row_pass_mask;
} BattleActionWorkFlags;

typedef char RowPassMaskOffsetCheck[((u32)&((BattleActionWorkFlags *)0)->row_pass_mask == 38) ? 1 : -1];

/* The target resolver passes row-pass indices 0..2; retain its halfword RMW. */
void MarkBattleRowPass(u32 row_pass)
{
    BattleActionWorkFlags *work = (BattleActionWorkFlags *)0x0200f3f0;
    work->row_pass_mask |= 1u << row_pass;
}
