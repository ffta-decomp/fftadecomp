typedef unsigned char u8;
typedef unsigned int u32;
struct BattleRegistryFlagsView { u8 unaccessed[36]; u32 flags; };
/* The flag meaning is not named beyond the observed battle transition. */
void SetBattleRegistryFlag8(struct BattleRegistryFlagsView *registry, u8 enabled)
{
    if (enabled != 0)
        registry->flags |= 8;
    else
        registry->flags &= ~8u;
}
