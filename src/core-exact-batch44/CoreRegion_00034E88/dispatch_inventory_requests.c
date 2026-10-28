#include "interfaces.h"

void DispatchInventoryRequestControllers(void)
{
    UpdateInventoryRequestInput();
    switch (InventoryRequestRoot->primary) {
    case 1: RunRequest43468(0); break;
    case 3: RunInventorySelection(0); break;
    case 4: RunRequest3BAE8(0); break;
    case 5: RunRequest39424(0); break;
    case 6: RunRequest3A07C(0); break;
    case 7: RunRemovalStaging(0); break;
    case 8: RunInventoryProgression(0); break;
    case 9: RunRequest3D550(0); break;
    case 10: RunRequest3DC1C(0); break;
    case 11: RunRequest3DE40(0); break;
    }
    switch (InventoryRequestRoot->secondary) {
    case 2: RunRequest4393C(1); break;
    case 13: RunRequest3C21C(1); break;
    case 14: RunRequest3CA18(1); break;
    case 15: RunRequest3F6F8(1); break;
    case 16: RunRequest49FB4(1); break;
    case 17: RunRequest4AFE0(1); break;
    case 19: RunRequest3D820(1); break;
    }
    if (InventoryRequestRoot->tertiary == 20)
        RunRequest4B7E8(2);
}
