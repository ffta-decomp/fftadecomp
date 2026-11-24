#include "abi/interfaces/0800a490_bindings.h"
extern void TestSceneSlotAndSkip(ScriptContext *,const SceneSkipCommand *);
/* Original nested opcode13 delegates the authored scene-slot condition and PC skip.
 * Existing helper policy and save selector are reused without reinterpretation. */
void OriginalOpcode309_0000A4EC(ScriptContext *context,const SceneSkipCommand *command)
{
 TestSceneSlotAndSkip(context,command);
}
asm(".global TestSceneSlotAndSkip\n.thumb_set TestSceneSlotAndSkip,0x0800A491");
