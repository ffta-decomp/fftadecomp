typedef unsigned char u8;
typedef unsigned int u32;
struct BattleRegistryFlagsView { u8 unaccessed_prefix[36]; u32 flags; };
/* The full-word zero test controls bit0; its game meaning is not established. */
void SetBattleRegistryFlag1FromZeroTest(struct BattleRegistryFlagsView *registry, u32 value)
{
    u32 cleared_flags = registry->flags & ~1u;
    registry->flags = cleared_flags;
    if (value == 0)
        registry->flags = cleared_flags | 1u;
}
