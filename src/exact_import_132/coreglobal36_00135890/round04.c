#include "interfaces.h"
void UpdateContentEntryFlow(u8 slot,u8 *state) __asm__("CoreGlobal36_00135890");
void UpdateContentEntryFlow(u8 slot,u8 *state)
{
    switch (*state) {
    case 0:
        InitializeContentEntryArena();
        ConfigureContentEntryTasks(&gContentEntryTasks,gContentEntryCallbacks,
            gContentEntryChildStates,1);
        AttachContentEntryTask(&gContentEntryTasks,0,StepContentEntryChoice);
        gContentEntryContinuation = *state = 1;
        break;
    case 1:
        RunContentEntryTasks(&gContentEntryTasks,1);
        *state = gContentEntryContinuation;
        break;
    case 2:
        ResetContentEntryTasks(&gContentEntryTasks);
        DestroyContentEntryArena();
        InitializeContentEntryArena();
        {
            void **allocation = &gContentEntryAllocation;
            *allocation = AllocateContentEntryBytes(0x22e0);
        }
        BindContentEntryDisplay(gContentEntryAllocation,0);
        gContentEntryDisplayMode = 0;
        SetContentEntryMode(7);
        gContentEntryContinuation = *state = 3;
        break;
    case 3:
        RunContentEntryTasks(&gContentEntryTasks,1);
        *state = gContentEntryContinuation;
        break;
    case 4:
        ResetContentEntryDisplayControls();
        ActivateContentEntry(1);
        SetContentEntryMode(2);
        *state = 255;
        break;
    case 5:
        SetContentEntryMode(11);
        *state = 255;
        break;
    case 255:
        break;
    }
}
