#include "interfaces.h"

u32 AdvanceMissionMenuOperation(void)
{
    u32 ready;
    int choice;
    switch (gMissionMenu->state) {
    case 0:
        ResetMissionMenuInput();
        ConfigureMissionMenuRuntime(gMissionRuntime, 0, 0, 20, 17, 1);
        InitializeMissionMenu(gMissionMenu, gMissionMenu->message);
        gMissionMenu->continuation = 3;
        gMissionMenu->state = 1;
        break;
    case 1:
        ready = WaitMissionMenuPanel();
        goto wait_result;
    case 2:
        ready = PollMissionMenuOperation();
    wait_result:
        if ((u16)ready != 0)
            gMissionMenu->state = gMissionMenu->continuation;
        break;
    case 3:
        OpenMissionMenu(1);
        gMissionMenu->continuation = 4;
        gMissionMenu->state = 2;
        break;
    case 4:
        choice = (u8)ReadMissionSelectionStatus();
        switch (choice) {
        case 1:
        case 2:
            BeginMissionOperation(0, 1);
            InitializeMissionOperation(3);
            break;
        case 3:
        case 4:
            BeginMissionOperation(0, 1);
            InitializeMissionOperation((s16)ReadMissionSelectedIndex());
            break;
        }
        break;
    case 5:
        CloseMissionMenu();
        SetMissionMenuMessage(gMissionMenu->message);
        gMissionMenu->continuation = 8;
        gMissionMenu->state = 1;
        break;
    case 6:
        CloseMissionMenu();
        SetMissionMenuMessage(gMissionMenu->message);
        gMissionMenu->continuation = 7;
        gMissionMenu->state = 1;
        break;
    case 7:
        if (gMissionKeys.pressed & 1) {
            CloseMissionMenu();
            SetMissionMenuMessage(63);
            gMissionMenu->continuation = 3;
            gMissionMenu->state = 1;
        }
        break;
    case 8:
        gMissionMenu->continuation = 9;
        gMissionMenu->state = 1;
        break;
    case 9:
        gMissionMenu->state = 0;
        return gMissionMenu->parent_mode;
    case 10:
        gMissionMenu->state = 0;
        return 6;
    case 11:
        InitializeMissionOperation(1);
        break;
    case 12:
        InitializeMissionOperation(2);
        break;
    }
    return 2;
}
