#ifndef FFTA_DISPLAY_H
#define FFTA_DISPLAY_H

typedef unsigned short u16;
struct InterruptState {
    u16 unknown[3];
    u16 enabled;
    u16 display_status;
};
extern volatile struct InterruptState gInterruptState;
extern volatile u16 gInterruptEnable;
extern volatile u16 gSavedDisplayControl;

#endif
