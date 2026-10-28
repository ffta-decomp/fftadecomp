#include "../../../src/task_tree_core.h"
extern u32 (*SaveSectorAction)(u16 sector);
extern void WaitForVBlankEdges(u16 count);
/* Retry policy only: the selected Flash implementation remains the real target. */
void EraseAllSaveSectorsWithRetries(void)
{
    signed int index = 0;
    u32 (**action)(u16) = &SaveSectorAction;
    for (; index <= 15; ++index) {
        u16 sector = index;
        if ((u16)(*action)(sector) != 0) {
            WaitForVBlankEdges(10);
            if ((u16)(*action)(sector) != 0) {
                WaitForVBlankEdges(10);
                (*action)(sector);
            }
        }
    }
}
asm(".global SaveSectorAction\n.set SaveSectorAction,0x0200f37c\n"
    ".global WaitForVBlankEdges\n.thumb_set WaitForVBlankEdges,0x080033c9\n"
    ".global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n");
