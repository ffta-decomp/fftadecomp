typedef unsigned char u8;typedef unsigned short u16;
struct State;struct Definition;
struct DefinitionEntry {struct Definition *definition;u16 slot,reserved;};
void ApplyDefinition(struct State *,struct Definition *) __asm__("RetailCall_081458ac");
void SceneTaskDependency_00141540(unsigned int index)
{
    u16 definition_index=index;
    if(*(u8 *)0x020084d8 & 2) {
        register struct State *state __asm__("r0")=(struct State *)0x0200f320;
        register struct DefinitionEntry *definitions __asm__("r2")=(struct DefinitionEntry *)0x0814bb48;
        /* Native materializes defined state r0 and table r2 before scaling
         * the captured low16 ordinal from r3 into argument r1. */
        asm("" : "+r" (state), "+r" (definitions));
        ApplyDefinition(state,definitions[definition_index].definition);
    }
}
asm(".global RetailCall_081458ac\n.thumb_set RetailCall_081458ac,0x081458ad\n");
