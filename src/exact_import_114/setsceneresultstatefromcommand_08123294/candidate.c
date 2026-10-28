#include "contract.h"

/* Event0x11c transfers to the result-state consumer; the command does not
 * advance the VM program counter itself. Preserve the aliased byte-read order. */
u32 SetSceneResultStateFromCommand_08123294(SceneResultContext *context,
                                          const SceneResultCommand *command)
{
    context->result_state = 7;
    context->result_selector = command->selector;
    return 0x11c;
}

/* The original module owns two zero alignment bytes after the leaf.
 * This directive emits alignment only, never Thumb instructions. */
__asm__(".balign 4, 0");
