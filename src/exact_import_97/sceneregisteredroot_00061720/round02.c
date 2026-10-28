#include "interfaces-final.h"
void InitializeItemModifierScene(void) __asm__("SceneRegisteredRoot_00061720");
void InitializeItemModifierScene(void)
{
    u8 *display_data;
    void **state_cell;
    u32 state_size;
    WriteSaveByte(13, 0);
    display_data = gModeSceneDisplayData;
    state_cell = &gModeSceneState;
    state_size = 0x45b4;
    *state_cell = AllocateModeSceneState(state_size);
    gModeSceneClearBytes(*state_cell, state_size);
    DecodeModeSceneData(display_data, gModeSceneCompressedData);
    BiosCpuSet(display_data + 0x300, (void *)0x06012700, 128);
}
