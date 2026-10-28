#include "scene_vm_abi.h"
struct SystemStateByte { u8 prefix[12]; u8 scene_byte; };
void DestroySceneState_08121EF0(void)
{
    u8 *state;
    void *backing;
    SceneHelper_08005B18((void *)WORD(STATE_POINTER));
    SceneHelper_08005C34((void *)WORD(STATE_POINTER));
    backing=(void *)WORD(STATE_POINTER+4);
    Free_08007170(POOL_POINTER,backing);
    state=STATE_POINTER;
    WORD(state+4)=0;
    ((struct SystemStateByte *)0x0200f390)->scene_byte=(u8)WORD(state+16);
    Free_08007170(POOL_POINTER,state);
    STATE_POINTER=0;
}
