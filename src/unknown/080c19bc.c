typedef unsigned char u8;
typedef unsigned int u32;
/* Actual low/high nibble ownership; this view does not allocate the object. */
union BattleProgressByte {
    u8 value;
    struct { u8 preserved : 4; u8 advance_count : 4; } __attribute__((packed)) fields;
} __attribute__((packed));
struct BattleActionProgressView { u8 prefix[0x54d4]; union BattleProgressByte progression; };
typedef char ProgressByteSize[sizeof(union BattleProgressByte) == 1 ? 1 : -1];
typedef char ProgressOffset[(u32)&((struct BattleActionProgressView *)0)->progression == 0x54d4 ? 1 : -1];
extern struct BattleActionProgressView gBattleActionProgressView;
__asm__(".global gBattleActionProgressView\n.set gBattleActionProgressView,0x020101f8");
void StoreBattleActionAdvanceCount(u8 count)
{
    gBattleActionProgressView.progression.fields.advance_count = count;
}
