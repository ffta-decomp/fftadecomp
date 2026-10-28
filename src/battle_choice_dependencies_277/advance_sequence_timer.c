typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SequenceEntry { u16 payload_index; u16 duration; };
struct BattleSequenceView {
    const u32 *relative_offsets;
    u8 unknown4[10];
    s16 next_entry;
    u16 remaining;
    u16 unknown18;
    const u8 *current;
    const u8 *sequence;
    u8 unknown28;
    u8 enabled;
};
typedef char current_offset_check[(u32)&((struct BattleSequenceView *)0)->current==20?1:-1];
typedef char enabled_offset_check[(u32)&((struct BattleSequenceView *)0)->enabled==29?1:-1];
/* Header uses byte reads; entry halfwords keep the original access widths. */
void StepBattleObjectSequence(struct BattleSequenceView *state)
{
    s32 remaining;
    u32 clear_value;
    const u8 *sequence;
    u32 low;
    u32 count;
    s32 index;
    const struct SequenceEntry *entry;
    const u32 *data;
    s32 entry_offset;
    u32 payload_index;
    remaining = state->remaining - 1;
    clear_value = 0;
    __asm__("" : "+r"(clear_value));
    state->remaining = remaining;
    if ((s16)remaining <= 0) {
        state->current = (const u8 *)clear_value;
        state->remaining = clear_value;
        sequence = state->sequence;
        low = sequence[0];
        count = sequence[1];
        count = (count << 8) | low;
        index = state->next_entry;
        if ((s32)count <= index) {
            state->enabled = 0;
        } else {
            entry_offset = 4 * index + 2;
            __asm__("" : "+r"(entry_offset));
            entry = (const struct SequenceEntry *)(sequence + entry_offset);
            payload_index = entry->payload_index;
            __asm__("" : "+r"(payload_index));
            data = state->relative_offsets;
            state->current = (const u8 *)data + data[payload_index];
            ++state->next_entry;
            state->remaining = entry->duration;
        }
    }
}
