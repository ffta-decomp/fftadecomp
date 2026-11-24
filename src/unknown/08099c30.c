typedef unsigned char u8;
struct BattleRegistryContextView {
    u8 unaccessed_prefix[8];
    void *context_at8;
};
/* The ownership chain is known; the field role remains intentionally neutral. */
void *GetBattleRegistryContextAt8(struct BattleRegistryContextView *registry)
{
    return registry->context_at8;
}
