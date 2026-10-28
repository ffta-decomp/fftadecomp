typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattleMarkerNode {
    void *object; u8 active, x, y, scaled_value; struct BattleMarkerNode *next;
};
struct BattleMarkerState { struct BattleMarkerNode *head; u8 unknown_04[156]; u8 counter; };
extern u16 BattleMarkerPalette[];
extern void (*const CopyMarkerPaletteCell)(void *, const void *, u32);
extern void UpdateMarkerObject_0808EFCC(void *, u32, u32, u32);
void UpdateBattleFrameMarkerNodes(struct BattleMarkerState *state)
{
    u8 *counter = &state->counter;
    u32 next_counter = *counter + 1;
    struct BattleMarkerNode *node;
    *counter = next_counter;
    if ((s8)next_counter > 5) {
        u16 first = BattleMarkerPalette[0];
        CopyMarkerPaletteCell(BattleMarkerPalette, BattleMarkerPalette + 1, 12);
        {
            register u32 zero asm("r0");
            /* Lock the observed store/zero order; the output is defined here. */
            asm("strh %2, [%3, #12]\n\tmov %0, #0"
                : "=r"(zero), "=m"(BattleMarkerPalette[6])
                : "r"(first), "r"(BattleMarkerPalette)
                : "cc");
            *counter = zero;
        }
    }
    node = state->head;
    while (node != 0) {
        if (node->active != 0)
            UpdateMarkerObject_0808EFCC(node->object, (u32)node->x * 32 + 16,
                (u32)node->scaled_value * 16, (u32)node->y * 32 + 16);
        node = node->next;
    }
}
asm(".set BattleMarkerPalette, 0x03003ba4\n");
asm(".set CopyMarkerPaletteCell, 0x0836d4bc\n");
asm(".thumb_set UpdateMarkerObject_0808EFCC, 0x0808efcd\n");
asm(".thumb_set _call_via_r3, 0x08142251\n");
