typedef unsigned char u8;
struct BattleMarkerNode { void *object; u8 active, x, y, scaled_value; struct BattleMarkerNode *next; };
struct BattleMarkerState { struct BattleMarkerNode *head; struct BattleMarkerNode nodes[13]; u8 counter; };
extern void ReleaseMarkerWorkObject_0808F7CC(void *);
extern void ReleaseMarkerState_08022854(void *);
void DestroyBattleFrameMarkerState(struct BattleMarkerState *state)
{
    struct BattleMarkerNode *node = state->nodes;
    int remaining = 12;
    do {
        ReleaseMarkerWorkObject_0808F7CC(node->object);
        ++node;
    } while (--remaining >= 0);
    ReleaseMarkerState_08022854(state);
}
asm(".thumb_set ReleaseMarkerWorkObject_0808F7CC,0x0808f7cd\n");
asm(".thumb_set ReleaseMarkerState_08022854,0x08022855\n");
