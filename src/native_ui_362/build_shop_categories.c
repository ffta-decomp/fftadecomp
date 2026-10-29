typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

struct CategoryChoices {
    u8 selected;
    u8 entries[6];
    u8 count;
};

struct ItemDefinition {
    u8 unknown00[12];
    u8 availability;
    u8 unknown0d[19];
};

extern u8 ClassifyValueByTens(u16 value);
extern u8 GetInventoryItemClass(u16 item);
/* The caller reloads the already narrowed selector as a full SP word.
 * The existing callee consumes its LOW8; do not narrow this value again. */
extern u16 ReadItemAdjustmentEntry(u32 selector, u32 index);
extern u8 CountStatusRecordsWithBits0And1(void);
extern const u8 gSaveRam[];
extern const struct ItemDefinition gItemDefinitions[];

__asm__(
    ".global ClassifyValueByTens\n"
    ".thumb_set ClassifyValueByTens,0x080cc8b5\n"
    ".global GetInventoryItemClass\n"
    ".thumb_set GetInventoryItemClass,0x080cbd35\n"
    ".global ReadItemAdjustmentEntry\n"
    ".thumb_set ReadItemAdjustmentEntry,0x080cc9f1\n"
    ".global CountStatusRecordsWithBits0And1\n"
    ".thumb_set CountStatusRecordsWithBits0And1,0x080cecf5\n"
    ".global gSaveRam\n.set gSaveRam,0x02000000\n"
    ".global gItemDefinitions\n.set gItemDefinitions,0x0851d180\n"
);

void BuildShopCategoryChoices(struct CategoryChoices *, u8)
    __asm__("SceneTaskDependency_0006ED30");

/* Retail appends a class once and reloads helper-visible counts at each test.
 * Keep the unchecked class-index stores and the separate second class call. */
void BuildShopCategoryChoices(struct CategoryChoices *choices, u8 selector)
{
    u8 present[6];
    u32 saved_selector;
    register u32 availability_mask __asm__("r8");
    register u32 adjusted_class_five __asm__("r10");
    u16 index;
    u16 item;
    u8 value_class;
    register s32 end_bias __asm__("r9");
    s32 item_limit_base;
    register const u8 *ram_base __asm__("r0");
    /* This actual incoming word is saved before calls and used by the later
     * adjustment scan. Its initialized memory operand emits no instruction. */
    saved_selector = selector;
    __asm__("" : "+m"(saved_selector));
    /* Keep the observed object base before forming its large field offset. */
    ram_base = gSaveRam;
    __asm__("" : "+r"(ram_base));
    value_class = ClassifyValueByTens(*(const u16 *)(ram_base + 0x1f6c));
    availability_mask = 16;
    if (value_class == 1)
        availability_mask = 32;
    else if (value_class > 1)
        availability_mask = 64;
    __asm__("" : "+r"(availability_mask));

    choices->count = 0;
    adjusted_class_five = 0;
    __asm__("" : "+r"(adjusted_class_five));
    index = 0;
    do {
        present[index] = 0;
        ++index;
    } while (index <= 5);

    /* The original retains the initialized one separately from its 361 base
     * bound throughout this call-containing scan. No instruction is emitted. */
    end_bias = 1;
    __asm__("" : "+r"(end_bias));
    item_limit_base = 361;
    index = 1;
    do {
        if (gItemDefinitions[index].availability & availability_mask)
            present[GetInventoryItemClass(index)] = 1;
        ++index;
    } while ((int)index < item_limit_base + end_bias);

    index = 0;
    while (index <= CountStatusRecordsWithBits0And1()) {
        register u32 adjustment_index __asm__("r1");
        /* R1 is narrowed before the later fullword SP8 load into R0. */
        adjustment_index = (u8)index;
        __asm__("" : "+r"(adjustment_index));
        item = ReadItemAdjustmentEntry(saved_selector, adjustment_index);
        if (item != 0) {
            if (GetInventoryItemClass(item) == 5) {
                adjusted_class_five = 1;
                __asm__("" : "+r"(adjusted_class_five));
            }
            present[GetInventoryItemClass(item)] = 1;
        }
        ++index;
    }

    index = 0;
    do {
        if (present[index] == 1) {
            choices->entries[choices->count] =
                ((const u8 *)0x08393b40)[index];
            ++choices->count;
        }
        ++index;
    } while (index <= 5);

    if (adjusted_class_five == 0) {
        register const struct ItemDefinition *fallback_definitions __asm__("r2");
        register s32 fallback_limit __asm__("r1");
        /* The same halfword iterator starts the final scan. Its initialized
         * base precedes the separate fullword bound derived from that start. */
        index = 362;
        fallback_definitions = gItemDefinitions;
        __asm__("" : "+r"(fallback_definitions));
        fallback_limit = index;
        __asm__("" : "+r"(fallback_limit));
        fallback_limit += 14;
        do {
            if (fallback_definitions[index].availability & availability_mask) {
                choices->entries[choices->count] = 5;
                ++choices->count;
                return;
            }
            ++index;
        } while ((int)index < fallback_limit);
    }
}
