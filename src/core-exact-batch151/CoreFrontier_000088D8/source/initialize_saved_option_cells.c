typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SavedOptionCell { u8 value, choice_count, column, enabled; };
struct SavedOptionDefinition { u16 choice_count, column, text_ids[8]; };
extern u8 *gSavedOptionsContext;
extern const struct SavedOptionDefinition gSavedOptionDefinitions[];
extern u32 QueryOrUpdateSavedOption(u8, u8);
__asm__(".global gSavedOptionsContext\n.set gSavedOptionsContext,0x02009188");
__asm__(".global gSavedOptionDefinitions\n.set gSavedOptionDefinitions,0x0836d4d4");
__asm__(".global QueryOrUpdateSavedOption\n.thumb_set QueryOrUpdateSavedOption,0x080094bd");

/* Capture the ten display cells before querying the settings working copy. */
void InitializeSavedOptionCells(void)
{
    struct SavedOptionCell *cell = (struct SavedOptionCell *)(gSavedOptionsContext + 824);
    int option = 0;
    u32 cleared_value = 0;
    const struct SavedOptionDefinition *definition = gSavedOptionDefinitions;
    for (; option <= 9; ++definition, ++option, ++cell) {
        cell->choice_count = definition->choice_count;
        cell->column = definition->column;
        if (option == 9) {
            u32 result;
            u32 enabled;
            cell->value = cleared_value;
            result = QueryOrUpdateSavedOption(9, 1);
            enabled = 0;
            if ((u8)result == 0)
                enabled = 1;
            cell->enabled = enabled;
        } else {
            cell->value = QueryOrUpdateSavedOption(option, 1);
            cell->enabled = 1;
        }
    }
}
