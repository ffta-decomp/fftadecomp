typedef unsigned char u8;
typedef unsigned short u16;
struct ServiceState;
struct Definition;
struct DefinitionEntry { struct Definition *definition; u16 slot; u16 reserved; };
void ApplyDefinition(struct ServiceState *, struct Definition *) __asm__("RetailCall_081458ac");
void BattleRuntimeDependency_00141570(int selector, int index)
{
    u16 definition_index = index;
    struct ServiceState *state = 0;
    if (*(u8 *)0x020084d8 & 2) {
        register struct DefinitionEntry *definitions __asm__("r1");
        switch (selector) {
        case 1: state = (struct ServiceState *)0x0200f2e0; break;
        case 2: state = (struct ServiceState *)0x0200f320; break;
        }
        definitions = (struct DefinitionEntry *)0x0814bb48;
        /* Original materializes the defined table base in r1 at the selector
         * join, before testing the selected state pointer. No instructions. */
        asm("" : "+r" (definitions));
        if (state)
            ApplyDefinition(state, definitions[definition_index].definition);
    }
}
asm(".global RetailCall_081458ac\n.thumb_set RetailCall_081458ac,0x081458ad\n");
