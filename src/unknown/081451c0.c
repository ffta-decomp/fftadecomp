typedef unsigned short u16;
typedef unsigned int u32;
struct IndexedDefinition {
    const void *data;
    u16 slot_index;
    u16 unknown_at_06;
};
struct DefinitionDispatchSlot {
    void *state;
    u32 unknown_after_00[2];
};
extern const struct DefinitionDispatchSlot gDefinitionDispatchSlots[];
extern const struct IndexedDefinition gIndexedDefinitions[];
__asm__(".global gDefinitionDispatchSlots\n.set gDefinitionDispatchSlots, 0x0814bb24\n"
        ".global gIndexedDefinitions\n.set gIndexedDefinitions, 0x0814bb48");
extern void DispatchDefinition(void *state, const void *definition);
__asm__(".global DispatchDefinition\n.thumb_set DispatchDefinition, 0x081458ad");

/* Retain the real service and its state effects; no inferred table bounds. */
void DispatchIndexedDefinition(u16 index) __asm__("CoreLibrary42_001451C0");
void DispatchIndexedDefinition(u16 index)
{
    register const struct DefinitionDispatchSlot *slots __asm__("r2") =
        gDefinitionDispatchSlots;
    const struct IndexedDefinition *definitions;
    const struct IndexedDefinition *definition;
    void *state;
    const void *data;
    /* Original LDR keeps the slot base in r2 while the ordinal uses r3.
     * The initialized identity operand fixes that allocation without instructions. */
    __asm__("" : "+r" (slots));
    definitions = gIndexedDefinitions;
    definition = definitions + index;
    state = slots[definition->slot_index].state;
    data = definition->data;
    DispatchDefinition(state, data);
}
