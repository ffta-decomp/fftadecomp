#include "interfaces.h"
/* Initialize mission operation candidates and their result/continuation states. */
void CoreFrontier_0005D23C(u16 incoming)
{
    int mode;
    u8 *root=gMissionContext;
    *(u32*)(root+0x1458)=0;
    *(void**)(root+0x1450)=0;
    *(u32*)(root+0x1454)=0;
    gClearRoutine(root+0x11ac,64);
    gClearRoutine(AT(0x11ec),92);
    gClearRoutine(AT(0x1248),264);
    gClearRoutine(AT(0x1350),256);
    NResetPair(3,0); NResetPair(2,0); NResetPair(7,0);
    mode=(s16)incoming;
    switch(mode) {
    case 0: {
        void *output=AT(0x1350);
        u8 selector=(u8)NResolveSelector(gMissionData[0x1f69]);
        u32 count=NCollectScene(output,64,selector);
        BYTE(0x11ab)=count;
        if (BYTE(0x11ab)) {
            BYTE(0x1198)=3; BYTE(0x119d)=64; BYTE(0x119a)=5; BYTE(0x1199)=2;
        } else {
            BYTE(0x1198)=mode; BYTE(0x119d)=65; BYTE(0x119a)=6; BYTE(0x1199)=2;
        }
        break;
    }
    case 1: {
        void *output;
        u8 selector;
        u32 count;
        NInitializePolicy(0);
        output=AT(0x11ac);
        selector=(u8)NResolveSelector(gMissionData[0x1f69]);
        count=NCollectPending(output,16,selector);
        BYTE(0x11a9)=count;
        if (BYTE(0x11a9)) {
            BYTE(0x1198)=4; BYTE(0x119d)=67; BYTE(0x119a)=5; BYTE(0x1199)=2;
        } else {
            BYTE(0x1198)=0; BYTE(0x119d)=66; BYTE(0x119a)=6; BYTE(0x1199)=2;
        }
        break;
    }
    case 2: {
        u32 count=NCollectAvailable(AT(0x11ac),16);
        BYTE(0x11a9)=count;
        if (NHasAvailable()) {
            BYTE(0x1198)=5; BYTE(0x119d)=68; BYTE(0x119a)=5; BYTE(0x1199)=mode;
        } else {
            BYTE(0x1198)=0; BYTE(0x119d)=69; BYTE(0x119a)=6; BYTE(0x1199)=mode;
        }
        break;
    }
    case 3: BYTE(0x119a)=10; BYTE(0x1199)=2; break;
    }
}
