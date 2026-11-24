typedef unsigned char u8;
typedef unsigned int u32;
struct GridRecord { u32 payload; struct GridRecord *volatile next; };
/* Caller passes a non-NULL record. A head match clears the entire slot. */
void RemoveBattleGridRecord(void *grid, struct GridRecord *record, u32 x, u32 y)
{
    u32 shifted_x = x << 24;
    u32 shifted_y = y << 24;
    u32 column_bytes = shifted_x >> 22;
    u32 row_bytes = shifted_y >> 18;
    struct GridRecord **slot = (struct GridRecord **)((u8 *)grid + (column_bytes + row_bytes));
    struct GridRecord *previous = *slot;
    struct GridRecord *tested_next;
    if (previous == (struct GridRecord *)~0u || previous == 0) return;
    if (previous == record) {
        *slot = 0;
    } else {
        goto test_next;
advance:
        previous = previous->next;
test_next:
        tested_next = previous->next;
        if (tested_next && tested_next != record) goto advance;
        if (previous->next == record) previous->next = record->next;
    }
}
