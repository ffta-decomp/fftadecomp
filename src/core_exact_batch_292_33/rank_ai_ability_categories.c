typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef void (*ClearBytes)(void *, u32);
extern u32 AbilityProperty(u16 ability, u8 selector);
__asm__(".thumb_set AbilityProperty, 0x080ccd51");
struct EffectRow { u8 bytes[4]; };
typedef char EffectRowSize[(sizeof(struct EffectRow)==4)?1:-1];


/* Rank the original numeric effect categories; names are not inferred. */
u8 RankAiAbilityCategories(const u16 *abilities, u16 count, u8 *order)
    __asm__("CoreRegion30_000C1C38");

u8 RankAiAbilityCategories(const u16 *abilities, u16 count, u8 *order)
{
    u8 histogram[8];
    u16 index, other;
    u16 ability;
    const u8 *effects;
    s32 effect_index;
    s32 category;
    u8 temporary;

    (*(ClearBytes const *)0x0836d4b8)(histogram, 8);
    for (index = 0; index < count; index++) {
        ability = abilities[index];
        if (ability == 0)
            goto category_one;
        if (AbilityProperty(ability, 16) == 0)
            goto category_zero;
        effects = (const u8 *)AbilityProperty(ability, 9);
        for (effect_index = 0; effect_index <= 2; effect_index++) {
            switch (((const struct EffectRow *)0x08553e70)[effects[effect_index]].bytes[1]) {
            case 1:
                category = 6;
                goto category_ready;
            case 5:
                category = 4;
                goto category_ready;
            case 12:
            case 18:
            case 19:
            case 20:
            case 22:
            case 24:
            case 29:
            case 30:
            case 35:
            case 37:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 48:
            case 49:
            case 50:
            case 51:
            case 65:
            case 67:
            case 69:
            case 71:
            case 72:
            case 80:
                category = 7;
                goto category_ready;
            case 8:
            case 27:
            case 56:
            case 76:
            case 77:
                category = 3;
                goto category_ready;
            case 53:
            case 54:
                category = 5;
                goto category_ready;
            }
        }
        if (AbilityProperty(ability, 29) != 0) {
category_one:
            category = 1;
        } else {
            category = 2;
        }
        goto category_ready;
category_zero:
        category = 0;
category_ready:
        /* Preserve the initialized numeric result before the shared zero test. */
        asm("" : "+r"(category));
        if (category != 0)
            histogram[category]++;
    }
    for (index = 0; index <= 7; index++)
        order[index] = index;
    for (index = 0; index <= 6; index++) {
        for (other = index + 1; other <= 7; other++) {
            if (histogram[index] < histogram[other]) {
                temporary = histogram[index];
                histogram[index] = histogram[other];
                histogram[other] = temporary;
                temporary = order[other];
                order[other] = order[index];
                order[index] = temporary;
            }
        }
    }
    for (other = 0; other <= 7; other++)
        if (histogram[other] == 0)
            return (u8)other;
    return 8;
}
