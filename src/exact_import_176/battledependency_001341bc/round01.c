typedef unsigned char u8;
typedef unsigned int u32;

struct UnitTargetCategories {
    u8 unknown_00[231];
    u8 category_candidates;
    u8 unknown_e8[28];
    u8 category;
};

u32 MatchesUnitTargetCategory(const struct UnitTargetCategories *actor,
                             const struct UnitTargetCategories *target)
    __asm__("BattleDependency_001341BC");
u32 MatchesUnitTargetCategory(const struct UnitTargetCategories *actor,
                             const struct UnitTargetCategories *target)
{
    u8 categories, first_category, second_category, target_category;
    if (actor == target)
        return 0;
    categories = actor->category_candidates;
    first_category = categories & 15;
    second_category = categories >> 4;
    target_category = target->category;
    if (first_category == target_category || second_category == target_category)
        return 1;
    return 0;
}
