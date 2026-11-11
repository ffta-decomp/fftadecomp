typedef unsigned char u8;
typedef unsigned int u32;
struct BattleRecordBufferView { u8 prefix[0x54ec]; void *buffer; };
typedef char BufferOffset[(u32)&((struct BattleRecordBufferView *)0)->buffer == 0x54ec ? 1 : -1];
extern struct BattleRecordBufferView gBattleRecordBufferView;
extern void ReleaseBattleRecordMemory(void *pointer);
__asm__(".global gBattleRecordBufferView\n.set gBattleRecordBufferView,0x020101f8\n.global ReleaseBattleRecordMemory\n.thumb_set ReleaseBattleRecordMemory,0x08022855");
void ReleaseBattleRecordBuffer(void)
{
    void *buffer = gBattleRecordBufferView.buffer;
    if (buffer != 0) {
        ReleaseBattleRecordMemory(buffer);
        gBattleRecordBufferView.buffer = 0;
    }
}
